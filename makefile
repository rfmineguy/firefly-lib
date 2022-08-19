CC = gcc
CFLAGS = -Wall

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

LIBRARY_PATHS = /opt/homebrew/Cellar/glfw/3.3.8/lib/
INCLUDE_DIRS := -I/include/ \
			   -I/opt/homebrew/Cellar/glfw/3.3.8/include/

LIB_DIR := $(PREFIX)
LIB_DIR := /lib/
LOCAL_CORE_INCLUDE = include/Core
LOCAL_IO_INCLUDE = include/IO
LOCAL_RESOURCE_INCLUDE = include/Resource
LOCAL_RENDERING_INCLUDE = include/Rendering

SOURCES = src/*.c

H_CORE = $(LOCAL_CORE_INCLUDE)/*.h
H_IO = $(LOCAL_IO_INCLUDE)/*.h
H_RESOURCE = $(LOCAL_RESOURCE_INCLUDE)/*.h
H_RENDERING = $(LOCAL_RENDERING_INCLUDE)/*.h

all: libfirefly.so

libfirefly.so: $(SOURCES)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(INCLUDE_DIRS) -L$(LIBRARY_PATHS) -lc -lglfw 

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
