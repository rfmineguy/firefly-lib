#include "../include/IO/File.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static FILE* activeWriteStream = NULL;
static FILE* activeReadStream = NULL;

FILE* FileOpen(const char* path, const char* openPerms) {
    FILE* f = fopen(path, openPerms);
    if (f == NULL) {
        fprintf(stderr, "Failed to open file [%s]\n", path);
        return NULL;
    }
    return f;
}

void FileClose(FILE* fPtr) {
    fclose(fPtr);
    fPtr = NULL;
}

FILE* SetReadStream(FILE* stream) {
    if (!stream) {
        fprintf(stderr, "Stream supplied for read is NULL\n");
        return NULL;
    }
    activeReadStream = stream;
    return stream;
}

char* Read(long* pFileSize) {
    if (activeReadStream == NULL)
        return NULL;

    fseek(activeReadStream, 0, SEEK_END);
    long f_size = ftell(activeReadStream);
    fseek(activeReadStream, 0, SEEK_SET);
    char* buf = (char*) malloc(f_size);

    fread(buf, sizeof(char), f_size, activeReadStream);

    return buf;
}

FILE* SetWriteStream(FILE* stream) {
    if (!stream) {
        fprintf(stderr, "Stream supplied for write is NULL\n");
        return NULL;
    }
    activeWriteStream = stream;
    return stream;
}

int Write(char* str) {
    if (activeWriteStream == NULL)
        return 0;
    return fprintf(activeWriteStream, "%s", str);
}

int WriteFmt(const char* fmt, ...) {
    char msgbuffer[255];
    va_list args;
    va_start(args, fmt);
    vsprintf(msgbuffer, fmt, args);
    va_end(args);
    return Write(msgbuffer);
}
