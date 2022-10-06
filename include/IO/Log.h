#ifndef FL_IOLOG_H
#define FL_IOLOG_H
#include <stdio.h>

typedef enum {
    DEBUG_, INFO_, WARN_, ERROR_, CRITICAL_
} LogLevel;

#ifndef NDEBUG
#define LOG_DEBUG(x, ...)    LogFL(DEBUG_, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_INFO(x, ...)     LogFL(INFO_, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_WARN(x, ...)     LogFL(WARN_, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_ERROR(x, ...)    LogFL(ERROR_, __FILE__, __LINE__, x, ##__VA_ARGS__)
#define LOG_CRITICAL(x, ...) LogFL(CRITICAL_, __FILE__, __LINE__, x, ##__VA_ARGS__)
#endif
#ifdef NDEBUG
#define LOG_INFO(x, ...)
#define LOG_DEBUG(x, ...)
#define LOG_WARN(x, ...)
#define LOG_ERROR(x, ...)
#define LOG_CRITICAL(x, ...)
#endif

FILE* SetLogStream(FILE*);
void LogFL(LogLevel, char*, int, const char*, ...);

#endif
