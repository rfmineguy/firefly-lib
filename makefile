CC = gcc
CFLAGS = -Wall

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

LIBRARY_DEPENDENCIES = -lc -lglfw -lcglm

# this will make the library not able to compiled on another system with this source
GLAD_SOURCE = $(PREFIX)/include/glad/glad.c

# external lib details
LIBRARY_PATHS = /opt/homebrew/lib/
INCLUDE_DIRS := -I/include/ \
			   -I/opt/homebrew/include/

# INCLUDE DIRECTORIES FOR THIS LIBRARY
LOCAL_CORE_INCLUDE = include/Core
LOCAL_IO_INCLUDE = include/IO
LOCAL_RESOURCE_INCLUDE = include/Resource
LOCAL_RENDERING_INCLUDE = include/Rendering

SOURCES = src/*.c
H_CORE = $(LOCAL_CORE_INCLUDE)/*.h
H_IO = $(LOCAL_IO_INCLUDE)/*.h
H_RESOURCE = $(LOCAL_RESOURCE_INCLUDE)/*.h
H_RENDERING = $(LOCAL_RENDERING_INCLUDE)/*.h
HEADERS = $(H_CORE) $(H_IO) $(H_RESOURCE) $(H_RENDERING)

all: libfirefly.so

libfirefly.so: glad.o $(SOURCES)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(INCLUDE_DIRS) -L$(LIBRARY_PATHS) $(LIBRARY_DEPENDENCIES)

glad.o: $(GLAD_SOURCE)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o glad.o $(GLAD_SOURCE)

#
# The make code below this line is pivotal that it does not change
#    if you change anything you *may* break other locally installed
#    libraries
#
install: libfirefly.so
	sudo install -d $(DESTDIR)$(PREFIX)/lib/
	sudo install -m 644 libfirefly.so $(DESTDIR)$(PREFIX)/lib/

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

clean:
	rm *.o *.so
