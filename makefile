CC = gcc
CFLAGS = -Wall -g

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

LIBRARY_DEPENDENCIES = -lc -lglad -lglfw -lcglm
ifeq ($(uname), darwin)
	LIBRARY_DEPENDENCIES += -lopenal.1
	LIBRARY_LIST += 
else
	LIBRARY_DEPENDENCIES += -lopenal
	LIBRARY_LIST += ldd out/libfirefly.so
endif

# external lib details (in addition to the default search paths)
LIBRARY_PATHS = -L/opt/homebrew/lib/ \
				#-Llibs/glad-rf/out/ \
				-Llibs/glfw/out/ \
				-Llibs/cglm/out/ \
				-Llibs/openal/out/ \
				-Lexample_resources/

INCLUDE_DIRS := -I/include/ \
			    -I/opt/homebrew/include/ \
				-I/libs/glad/include/ \
				-I/libs/stb/include/ \
				-I/libs/cglm/include/ \
				-I/libs/openal/include/

# INCLUDE DIRECTORIES FOR THIS FireflyLib
LOCAL_CORE_INCLUDE = include/Core
LOCAL_IO_INCLUDE = include/IO
LOCAL_RESOURCE_INCLUDE = include/Resource
LOCAL_RENDERING_INCLUDE = include/Rendering

# FILE GLOBS FOR THIS FireflyLib
SOURCES = $(wildcard src/*.c)
H_CORE = $(LOCAL_CORE_INCLUDE)/*.h
H_IO = $(LOCAL_IO_INCLUDE)/*.h
H_RESOURCE = $(LOCAL_RESOURCE_INCLUDE)/*.h
H_RENDERING = $(LOCAL_RENDERING_INCLUDE)/*.h
HEADERS = $(H_CORE) $(H_IO) $(H_RESOURCE) $(H_RENDERING)

OBJECTS := $(patsubst src/%.c, obj/%.o, $(SOURCES))

# LIBRARY DIRECTORIES AND FILES FOR THIS FireflyLib
GLFW_LIB_BUILD = libs/glfw/out/libglfw3.a
GLFW_LIB_DIR = libs/glfw/out/
GLFW_LIB = glfw3

GLAD_LIB_BUILD = libs/glad-rf/out/libglad.a
GLAD_LIB_DIR = libs/glad-rf/out/
GLAD_LIB = glad

CGLM_LIB_BUILD = libs/cglm/out/libcglm.dylib
CGLM_LIB_DIR = libs/cglm/out/
CGLM_LIB = cglm

OPENAL_LIB_BUILD = libs/openal/out/libopenal.a
OPENAL_LIB_INSTALL = /usr/local/lib/libopenal.a
OPENAL_LIB_DIR = libs/openal/out/
OPENAL_LIB = openal

DYLIB_CMD = -Wl,-rpath,$(shell pwd)/libs/openal/out/
RESOURCES = $(wildcard example_resources/out/*.o)

.PHONY: build_static
build_static: prepare out/libfirefly.a

.PHONY: build_shared
build_shared: prepare out/libfirefly.so

prepare: build_libs build_resources
	sudo -k
	rm -rf out obj
	mkdir out obj

.PHONY: build_resources
build_resources:
	$(info =========================================================)
	$(info Building the resource files \(text files, images, etc.\))
	$(info =========================================================)
	$(info )
	make -C example_resources clean-build prepare
	make -C example_resources cam.fragment.o cam.vertex.o
	#make -C example_resources texture.fragment.o texture.vertex.o
	make -C example_resources clean-working-dir

# already a static library
build_libs: $(GLFW_LIB_BUILD) $(GLAD_LIB_BUILD) $(CGLM_LIB_BUILD) $(OPENAL_LIB_BUILD)
	$(shell sudo -k)

$(GLFW_LIB_BUILD):
	$(info =========================================================)
	$(info Building and installing glfw)
	$(info =========================================================)
	$(info )
	cmake -S libs/glfw/ -B libs/glfw/cmakeout/ && cd libs/glfw/cmakeout && make && sudo make install
	-mkdir libs/glfw/out/ && cp libs/glfw/cmakeout/src/libglfw3.a libs/glfw/out/

# already a static library
$(GLAD_LIB_BUILD):
	$(info =========================================================)
	$(info Building and installing glad)
	$(info =========================================================)
	$(info )
	cmake -S libs/glad-rf/ -B libs/glad-rf/cmakeout/ && cd libs/glad-rf/cmakeout && make && sudo make install
	-mkdir libs/glad-rf/out/ && cp libs/glad-rf/cmakeout/libglad.a libs/glad-rf/out/

# build options
#  Shared Lib => -DCGLM_SHARED=ON  -DCGLM_STATIC=OFF
#  Static Lib => -DCGLM_SHARED=OFF -DCGLM_STATUC=ON
$(CGLM_LIB_BUILD):
	$(info =========================================================)
	$(info Building and installing cglm)
	$(info =========================================================)
	$(info )
	cmake -DCGLM_SHARED=OFF -DCGLM_STATIC=ON -S libs/cglm/ -B libs/cglm/cmakeout/ && cd libs/cglm/cmakeout && make && sudo make install
	-mkdir libs/cglm/out/ && cp libs/cglm/cmakeout/libcglm.a libs/cglm/out/libcglm.a

# build options
#  Shared Lib => -DLIBTYPE=SHARED (default)
#  Static Lib => -DLIBTYPE=STATIC
$(OPENAL_LIB_BUILD):
	$(info =========================================================)
	$(info Building and installing openal)
	$(info =========================================================)
	$(info )
	cmake -DLIBTYPE=STATIC -S libs/openal/ -B libs/openal/cmakeout/ && cd libs/openal/cmakeout && make && sudo make install
	-mkdir libs/openal/out/ && cp libs/openal/cmakeout/libopenal.a libs/openal/out/libopenal.a

out/libfirefly.so: $(SOURCES)
	$(info =========================================================)
	$(info Building libfirefly.so to out/)
	$(info =========================================================)
	$(info )
	sudo -k
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(INCLUDE_DIRS) $(LIBRARY_PATHS) $(LIBRARY_DEPENDENCIES) $(RESOURCES) $(DYLIB_CMD)

out/libfirefly.a: $(OBJECTS)
	$(info =========================================================)
	$(info Building static lib 'libfirefly.a')
	$(info =========================================================)
	$(info _)
	sudo -k
	ar x /usr/local/lib/libglfw3.a
	ar x /usr/local/lib/libcglm.a
	ar x /usr/local/lib/libopenal.a
	ar x /usr/local/lib/libglad.a
	echo $(wildcard ./*.o)
	ar rcs out/libfirefly.a $(wildcard ./*.o) $(wildcard obj/*.o)
	rm -rf *.o
	
obj/%.o: src/%.c
	$(CC) -c $< -o $@

libinfo:
	objdump -t out/libfirefly.a >> libinfo.txt
	echo "wrote info to 'libinfo.txt'"

linked_libraries:
	otool -L out/libfirefly.a

install:
	$(info =========================================================)
	$(info Installing libfirefly.so to $(DESTDIR)$(PREFIX)/lib/ and its headers to $(DESTDIR)$(PREFIX)/include/firefly/)
	$(info =========================================================)
	$(info )
	sudo install -d $(DESTDIR)$(PREFIX)/lib/
	-sudo install -m 644 out/libfirefly.so $(DESTDIR)$(PREFIX)/lib/
	-sudo install -m 644 out/libfirefly.a $(DESTDIR)$(PREFIX)/lib

	# Create directories
	sudo install -d $(DESTDIR)$(PREFIX)/include/firefly
	sudo install -d $(DESTDIR)$(PREFIX)/include/firefly/Core
	sudo install -d $(DESTDIR)$(PREFIX)/include/firefly/IO
	sudo install -d $(DESTDIR)$(PREFIX)/include/firefly/Resource
	sudo install -d $(DESTDIR)$(PREFIX)/include/firefly/Rendering

	# Copy headers to the header search paths
	sudo install -m 664 $(H_CORE) $(DESTDIR)$(PREFIX)/include/firefly/Core/
	sudo install -m 664 $(H_IO) $(DESTDIR)$(PREFIX)/include/firefly/IO/
	sudo install -m 664 $(H_RESOURCE) $(DESTDIR)$(PREFIX)/include/firefly/Resource/
	sudo install -m 664 $(H_RENDERING) $(DESTDIR)$(PREFIX)/include/firefly/Rendering/

uninstall:
	$(info =========================================================)
	$(info Uninstalling libfirefly.so and its headers)
	$(info =========================================================)
	sudo rm $(DESTDIR)$(PREFIX)/lib/libfirefly.so
	sudo rm $(DESTDIR)$(PREFIX)/lib/libfirefly.a
	sudo rm -rf $(DESTDIR)$(PREFIX)/include/firefly/

clean: clean-cmake clean-build clean-other
clean-other:
	rm -rf libinfo.txt

clean-cmake:
	rm -rf libs/glfw/cmakeout/
	rm -rf libs/glad-rf/cmakeout/
	rm -rf libs/cglm/cmakeout/
	rm -rf libs/openal/cmakeout/
	rm -rf libs/stb/cmakeout/

clean-build:
	rm -rf libs/glfw/out/
	rm -rf libs/glad-rf/out/
	rm -rf libs/cglm/out/
	rm -rf libs/openal/out/
	rm -rf libs/stb/out/
