CC = gcc
CFLAGS = -Wall -g

ifeq ($(PREFIX),)
	PREFIX := /usr/local
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
GLFW_CFLAGS := $(shell pkg-config --cflags glfw3)

OPENAL_LIB := $(shell pkg-config --libs openal) 
OPENAL_CFLAGS := $(shell pkg-config --cflags openal)

CGLM_LIB := $(shell pkg-config --libs cglm)
CGLM_CFLAGS := $(shell pkg-config --cflags cglm)

GLAD_C_SRC := ./libs/glad-rf/src/glad.c
GLAD_C_CFLAGS := -I/libs/glad-rf/include/

HARFBUZZ_LIB := $(shell pkg-config --libs harfbuzz)
HARFBUZZ_CFLAGS := $(shell pkg-config --cflags harfbuzz)

DYLIB_CMD = -Wl,-rpath,$(shell pwd)/libs/openal/out/
RESOURCES = $(wildcard example_resources/out/*.o)

define colored_echo
	@tput setaf $1
	@echo $2
	@tput sgr0
endef

default:
	$(info Default make target not a valid target)
	$(info Choose the following: )
	$(info  default)
	$(info  \__ Display make targets)
	$(info  build_shared)
	$(info  \__ Ensure that the required resource files are included)
	$(info  \__ Shows the availability of required libraries)
	$(info  \__ Builds the library)
	$(info  install)
	$(info  \__ Installs the built library to $(PREFIX)/lib and $(PREFIX)/include)
	$(info  pkgconfig)
	$(info  \__ Display package availability)

.PHONY: build_shared
build_shared: build_resources pkgconfig out/libfirefly.so

pkgconfig:
	$(info ==============================================================)
	$(info PACKAGE AVAILABILITY)
	$(info ==============================================================)
	$(call colored_echo, 9, "FreeType2")
	$(call colored_echo, 6, "\___ LIBS    ==> $(FREETYPE_LIB)")
	$(call colored_echo, 6, "\___ CFLAGS  ==> $(FREETYPE_CFLAGS)")
	$(call colored_echo, 9, "GLFW3")
	$(call colored_echo, 6, "\___ LIBS    ==> $(GLFW_LIB)")
	$(call colored_echo, 6, "\___ CFLAGS  ==> $(GLFW_CFLAGS)")
	$(call colored_echo, 9, "GLAD")
	$(call colored_echo, 6, "\___ SRC     ==> $(GLAD_C_SRC)")
	$(call colored_echo, 6, "\___ CFLAGS  ==> $(GLAD_C_CFLAGS)")
	$(call colored_echo, 9, "OpenAL")
	$(call colored_echo, 6, "\___ LIBS    ==> $(OPENAL_LIB)")
	$(call colored_echo, 6, "\___ CFLAGS  ==> $(OPENAL_CFLAGS)")
	$(call colored_echo, 9, "CGLM")
	$(call colored_echo, 6, "\___ LIBS    ==> $(CGLM_LIB)")
	$(call colored_echo, 6, "\___ CFLAGS  ==> $(CGLM_CFLAGS)")
	$(call colored_echo, 9, "Harfbuzz")
	$(call colored_echo, 6, "\___ LIBS    ==> $(HARFBUZZ_LIB)")
	$(call colored_echo, 6, "\___ CFLAGS  ==> $(HARFBUZZ_CFLAGS)")
	$(info ==============================================================)

prepare: build_resources
	sudo -k
	mkdir out; chmod 755 out

.PHONY: build_resources
build_resources:
	sudo -k
	$(info =========================================================)
	$(info Building the resource files \(text files, images, etc.\))
	$(info =========================================================)
	make -C example_resources clean-build prepare
	make -C example_resources cam.fragment.o cam.vertex.o
	make -C example_resources text.fragment.o text.vertex.o
	make -C example_resources clean-working-dir
	$(info =========================================================)

out/libfirefly.so: $(SOURCES)
	$(info =========================================================)
	$(info Building libfirefly.so to out/)
	$(info =========================================================)
	$(info )
	sudo -k
	$(CC) \
		$(CFLAGS) -fPIC -shared \
		-o $@ $^ \
		$(GLAD_C_SRC) $(GLAD_C_CFLAGS) \
		$(FREETYPE_LIB) $(FREETYPE_CFLAGS) \
		$(GLFW_LIB) $(GLFW_CFLAGS) \
		$(OPENAL_LIB) $(OPENAL_CFLAGS) \
		$(CGLM_LIB) $(CGLM_CFLAGS) \
		$(HARFBUZZ_LIB) $(HARFBUZZ_CFLAGS) \
		$(RESOURCES)

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
