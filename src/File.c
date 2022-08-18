#include "../include/IO/File.h"

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
    return NULL;
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
    return -1;
}

int WriteFmt(const char* fmt, ...) {
    return -1;
}
