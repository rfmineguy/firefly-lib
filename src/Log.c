#include "../include/IO/Log.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define LOG_DEBUG_COLOR_CYAN     "\x1B[36m"
#define LOG_INFO_COLOR_GREEN     "\x1B[32m"
#define LOG_WARN_COLOR_YELLOW    "\x1B[33m"
#define LOG_ERROR_COLOR_RED      "\x1B[31m"
#define LOG_CRITICAL_COLOR_MAG   "\x1B[35m"

#define LOG_RESET_COLOR          "\x1B[0m"

static FILE* activeLogStream = NULL;

FILE* SetLogStream(FILE* stream) {
    activeLogStream = stream;
    return stream;
}

// format: [LEVEL, FILE, LINE]: MSG
void LogFL(LogLevel lvl, char* file, int line, const char* msg, ...) {
    if (activeLogStream == NULL)
        return;

    char buffer[500] = {};
    char msgbuffer[255] = {};
    char levelStr[12] = {};
    char color[9] = {};
    switch (lvl) {
    case DEBUG:
        strcat(color, LOG_DEBUG_COLOR_CYAN);
        strcat(levelStr, "DEBUG");
        break;
    case INFO:
        strcat(color, LOG_INFO_COLOR_GREEN);
        strcat(levelStr, "INFO");
        break;
    case WARN:
        strcat(color, LOG_WARN_COLOR_YELLOW);
        strcat(levelStr, "WARN");
        break;
    case ERROR:
        strcat(color, LOG_ERROR_COLOR_RED);
        strcat(levelStr, "ERROR");
        break;
    case CRITICAL:
        strcat(color, LOG_CRITICAL_COLOR_MAG);
        strcat(levelStr, "CRIT");
        break;
    }    

    va_list args;
    va_start(args, msg);
    vsprintf(msgbuffer, msg, args);
    va_end(args);

    sprintf(buffer, "%s[%s, %s, %d]: %s%s", color, levelStr, file, line, msgbuffer, LOG_RESET_COLOR);
    fprintf(activeLogStream, "%s\n", buffer);
}
