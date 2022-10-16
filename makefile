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

FREETYPE_LIB := $(shell pkg-config --libs freetype2)
FREETYPE_CFLAGS := $(shell pkg-config --cflags freetype2)

GLFW_LIB := $(shell pkg-config --libs glfw3)
GLFW_CFLAGS  := $(shell pkg-config --cflags glfw3)

OPENAL_LIB := $(shell pkg-config --libs openal) 
OPENAL_CFLAGS := $(shell pkg-config --cflags openal)

CGLM_LIB := $(shell pkg-config --libs cglm)
CGLM_CFLAGS := $(shell pkg-config --cflags cglm)

GLAD_C_SRC := ./libs/glad-rf/src/glad.c
GLAD_C_CFLAGS := -I/libs/glad-rf/include/

DYLIB_CMD = -Wl,-rpath,$(shell pwd)/libs/openal/out/
RESOURCES = $(wildcard example_resources/out/*.o)

.PHONY: build_static
build_static: prepare out/libfirefly.a

.PHONY: build_shared
build_shared: build_resources pkgconfig out/libfirefly.so

pkgconfig:
	$(info ==============================================================)
	$(info PACKAGE AVAILABILITY)
	$(info ==============================================================)
	$(info FreeType2)
	$(info  \___ LIBS    ==> $(FREETYPE_LIB))
	$(info  \___ CFLAGS  ==> $(FREETYPE_CFLAGS))
	$(info GLFW3)
	$(info  \___ LIBS    ==> $(GLFW_LIB))
	$(info  \___ CFLAGS  ==> $(GLFW_CFLAGS))
	$(info GLAD (local))
	$(info  \___ SRC     ==> $(GLAD_C_SRC))
	$(info  \___ CFLAGS  ==> $(GLAD_C_CFLAGS))
	$(info OpenAL)
	$(info  \___ LIBS    ==> $(OPENAL_LIB))
	$(info  \___ CFLAGS  ==> $(OPENAL_CFLAGS))
	$(info CGLM)
	$(info  \___ LIBS    ==> $(CGLM_LIB))
	$(info  \___ CFLAGS  ==> $(CGLM_CFLAGS))
	$(info ==============================================================)

prepare: build_resources
	sudo -k
	mkdir out obj; chmod 755 out obj

.PHONY: build_resources
build_resources:
	$(info =========================================================)
	$(info Building the resource files \(text files, images, etc.\))
	$(info =========================================================)
	make -C example_resources clean-build prepare
	make -C example_resources cam.fragment.o cam.vertex.o
	make -C example_resources clean-working-dir
	$(info =========================================================)

out/libfirefly.so: $(SOURCES)
	$(info =========================================================)
	$(info Building libfirefly.so to out/)
	$(info =========================================================)
	$(info )
	sudo -k
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(GLAD_C_SRC) $(GLAD_C_CFLAGS) $(FREETYPE_LIB) $(FREETYPE_CFLAGS) $(GLFW_LIB) $(GLFW_CFLAGS) $(OPENAL_LIB) $(OPENAL_CFLAGS) $(CGLM_LIB) $(CGLM_CFLAGS) $(RESOURCES)

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
	$(CC) -c $< -o $@ $(INCLUDE_DIRS)

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
	-sudo install -m 644 out/libfirefly.a $(DESTDIR)$(PREFIX)/lib/
	-sudo install -m 644 firefly.pc $(DESTDIR)$(PREFIX)/lib/pkgconfig/

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
	rm -rf libs/glad-rf/cmakeout/
	rm -rf libs/stb/cmakeout/

clean-build:
	rm -rf out/libfirefly.so
	rm -rf libs/glad-rf/out/
	rm -rf libs/stb/out/
