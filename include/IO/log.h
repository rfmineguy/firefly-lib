#ifndef FL_IOLOG_H
#define FL_IOLOG_H
#include <stdio.h>

typedef enum {
    DEBUG, INFO, WARN, ERROR, CRITICAL
} LogLevel;

#define NDEBUG      //      
#ifndef NDEBUG
#define LOG_DEBUG(x, ...) LogFL(DEBUG, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_INFO(x, ...) LogFL(INFO, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_WARN(x, ...) LogFL(WARN, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_ERROR(x, ...) LogFL(ERROR, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_CRITICAL(x, ...) LogFL(CRITICAL, __FILE__, __LINE__, x, ##__VA_ARGS__)
#endif
#ifdef NDEBUG
#define LOG_INFO(x, ...)
#define LOG_DEBUG(x, ...)
#define LOG_WARN(x, ...)
#define LOG_ERROR(x, ...)
#define LOG_CRITICAL(x, ...)
#endif

FILE* SetLogStream(FILE*);

void Log(LogLevel, const char*, ...);
void LogEx(LogLevel, const char*, ...);
void LogFL(LogLevel, char*, int, const char*, ...);

void LogInfo(const char*, ...);
void LogDebug(const char*, ...);
void LogWarn(const char*, ...);
void LogError(const char*, ...);
void LogCritical(const char*, ...);

#endif
