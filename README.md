![GitHub](https://img.shields.io/github/license/rfmineguy/firefly-lib)
![GitHub repo size](https://img.shields.io/github/repo-size/rfmineguy/firefly-lib)

# firefly-lib
This is an intalled library

## Build instructions
### MacOS
`git clone https://github.com/rfmineguy/firefly-lib --recursive`<br>
`cd firefly-lib`<br>
`make install`<br>
*If it asks you for sudo password, its only because the install puts files in **/usr/local/lib** and **/usr/local/include***

### Windows
*UNTESTED*<br>

### Linux
`git clone https://github.com/rfmineguy/firefly-lib --recursive`<br>
`cd firefly-lib`<br>
`make install`<br>
*If it asks you for sudo password, its only because the install puts files in **/usr/local/lib** and **/usr/local/include***

## Usage instructions
Once the library is installed via `make install` you can simply link the library through gcc with `-lfirefly` <br><br>
`gcc src/main.c -lfirefly`

## Disclaimer
This has *ONLY* been tested on macos as of now. If you have any issues with building for other platforms please notify me via the Issues tab.
