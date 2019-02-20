#ifndef COPY_INCLUDES_SYSTEM_H_
#define COPY_INCLUDES_SYSTEM_H_

#if defined (__linux__) || defined(__unix__)
#include <unistd.h>
#include <sys/stat.h>
#endif

#if defined (_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#endif // COPY_INCLUDES_SYSTEM_H_
