#ifndef FL_IOLOG_H
#define FL_IOLOG_H
#include <stdio.h>

typedef enum {
    DEBUG, INFO, WARN, ERROR, CRITICAL
} LogLevel;

FILE* SetLogStream(FILE*);

void Log(LogLevel, const char*, ...);
void LogInfo(const char*, ...);
void LogDebug(const char*, ...);
void LogWarn(const char*, ...);
void LogError(const char*, ...);
void LogCritical(const char*, ...);

#endif
