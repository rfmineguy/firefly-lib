CC = gcc
CFLAGS = -Wall

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

LIBRARY_DEPENDENCIES = -lc -lglfw -lcglm -lglad -lopenal

# external lib details (in addition to the default search paths)
LIBRARY_PATHS = -L/opt/homebrew/lib/ \
				-Llibs/glad-rf/out/ \
				-Llibs/glfw/out/ \
				-Llibs/cglm/out/ \
				-Llibs/openal/out/

DYLIB_PATH = $(shell pwd)/libs/openal/out/

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
SOURCES = src/*.c
H_CORE = $(LOCAL_CORE_INCLUDE)/*.h
H_IO = $(LOCAL_IO_INCLUDE)/*.h
H_RESOURCE = $(LOCAL_RESOURCE_INCLUDE)/*.h
H_RENDERING = $(LOCAL_RENDERING_INCLUDE)/*.h
HEADERS = $(H_CORE) $(H_IO) $(H_RESOURCE) $(H_RENDERING)

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

OPENAL_LIB_BUILD = libs/openal/out/libopenal.1.dylib
OPENAL_LIB_DIR = libs/openal/out/
OPENAL_LIB = openal.1

DYLIB_CMD = -rpath $(shell pwd)/libs/openal/out/

#
# NOTE: The OpenAL linking problem is mostly likely due to the dylib not being in a standard location.
#

build: prepare out/libfirefly.so

build_libs: $(GLFW_LIB_BUILD) $(GLAD_LIB_BUILD) $(CGLM_LIB_BUILD) $(OPENAL_LIB_BUILD)
$(GLFW_LIB_BUILD):
	cmake -S libs/glfw/ -B libs/glfw/cmakeout/ && cd libs/glfw/cmakeout && make
	-mkdir libs/glfw/out/ && cp libs/glfw/cmakeout/src/libglfw3.a libs/glfw/out/
	
$(GLAD_LIB_BUILD):
	cmake -S libs/glad-rf/ -B libs/glad-rf/cmakeout/ && cd libs/glad-rf/cmakeout && make
	-mkdir libs/glad-rf/out/ && cp libs/glad-rf/cmakeout/libglad.a libs/glad-rf/out/

$(CGLM_LIB_BUILD):
	cmake -S libs/cglm/ -B libs/cglm/cmakeout/ && cd libs/cglm/cmakeout && make
	-mkdir libs/cglm/out/ && cp libs/cglm/cmakeout/libcglm.dylib libs/cglm/out/

$(OPENAL_LIB_BUILD):
	cmake -S libs/openal/ -B libs/openal/cmakeout/ && cd libs/openal/cmakeout && make
	-mkdir libs/openal/out/ && cp libs/openal/cmakeout/libopenal.dylib libs/openal/out/

prepare: build_libs
	rm -rf out
	mkdir out

out/libfirefly.so: $(SOURCES)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(INCLUDE_DIRS) $(LIBRARY_PATHS) $(LIBRARY_DEPENDENCIES) $(DYLIB_CMD)

libinfo:
	nm out/libfirefly.so >> libinfo.txt
	echo "wrote info to 'libinfo.txt'"

linked_libraries:
	otool -L out/libfirefly.so
	
#
# The make code below this line is pivotal that it does not change
#    if you change anything you *may* break other locally installed
#    libraries
#
install: build
	sudo install -d $(DESTDIR)$(PREFIX)/lib/
	sudo install -m 644 out/libfirefly.so $(DESTDIR)$(PREFIX)/lib/

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
	sudo rm $(DESTDIR)$(PREFIX)/lib/libfirefly.so
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
	rm -rf out
