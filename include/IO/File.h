#ifndef FL_IOFILE_H
#define FL_IOFILE_H
#include <stdio.h>
#include <stdlib.h>

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

#define READ                   "r"
#define WRITE                  "w"
#define APPEND                 "a"
#define READ_BIN               "rb"
#define WRITE_BIN              "wb"
#define READ_WRITE             "r+"
#define CREATE_READ_WRITE      "w+"
#define READ_WRITE_APPEND      "a+"

FILE* FileOpen(const char*, const char*);
void FileClose(FILE*);

FILE* SetReadStream(FILE*);
char* Read(long*);

FILE* SetWriteStream(FILE*);
int Write(char*);
int WriteFmt(const char*, ...);

#ifdef __cplusplus
}
#endif

#endif
