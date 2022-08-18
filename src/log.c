#include "../include/IO/Log.h"
#include <stdio.h>

FILE* activeLogStream;

FILE* SetLogStream(FILE* stream) {
    activeLogStream = stream;
    return stream;
}

void Log(LogLevel, const char*, ...);
void LogEx(LogLevel, const char*, ...);
void LogFL(LogLevel, char*, int, const char*, ...);

void LogInfo(const char*, ...);
void LogDebug(const char*, ...);
void LogWarn(const char*, ...);
void LogError(const char*, ...);
void LogCritical(const char*, ...);
