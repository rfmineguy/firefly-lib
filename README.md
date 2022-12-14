![GitHub](https://img.shields.io/github/license/rfmineguy/firefly-lib)
![GitHub repo size](https://img.shields.io/github/repo-size/rfmineguy/firefly-lib)

# firefly-lib
This is an intalled library
For usage of the library you can view [FireflyLibTests](https://github.com/rfmineguy/firefly-lib-tests)

The wiki page here will also be being worked on.

I will most likely **not** provide prebuilt binaries of this library as the build process is set up in a way that makes installation easy and usage easy as well.

## Build instructions
### MacOS
`git clone https://github.com/rfmineguy/firefly-lib --recursive`<br>
`cd firefly-lib`<br>
`sudo make install`<br>
*If it asks you for sudo password, its only because the install puts files in **/usr/local/lib** and **/usr/local/include***

### Linux
`git clone https://github.com/rfmineguy/firefly-lib --recursive`<br>
`cd firefly-lib`<br>
`sudo make install`<br>
*If it asks you for sudo password, its only because the install puts files in **/usr/local/lib** and **/usr/local/include***

### Windows
*UNTESTED*<br>
*Currently not planned either*<br>

## Usage instructions
Once the library is installed via `make install` you can simply link the library through gcc with `-lfirefly` <br><br>
`gcc src/main.c -lfirefly`

## Disclaimers
1. This has *ONLY* been tested on linux and macos as of now. If you have any issues with building for other platforms please notify me via the Issues tab.
2. I attempted to get it building on Windows, but failed as I'm not familiar with that build system. If someone figures out how to build it leave an issue with the details please.
3. I also have no idea if this will build successfully under the Wayland protocol.
