#include "../include/IO/Log.h"
#include <stdio.h>
#include <string.h>

#define TEXT_BLACK 

FILE* activeLogStream = NULL;

FILE* SetLogStream(FILE* stream) {
    activeLogStream = stream;
    return stream;
}

// format: [LEVEL, FILE, LINE]: MSG
void LogFL(LogLevel lvl, char* file, int line, const char* msg, ...) {
    if (activeLogStream == NULL)
        return;

    char buffer[255] = {};
    char levelStr[12] = {};
    if (lvl == DEBUG)    strcat(levelStr, "DEBUG");
    if (lvl == INFO)     strcat(levelStr, "INFO");
    if (lvl == WARN)     strcat(levelStr, "WARN");
    if (lvl == ERROR)    strcat(levelStr, "ERROR");
    if (lvl == CRITICAL) strcat(levelStr, "CRITICAL");
    
    sprintf(buffer, "[%s, %s, %d]: %s", levelStr, file, line, msg);
    fprintf(activeLogStream, "%s\n", buffer);
}
