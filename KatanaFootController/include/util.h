#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


extern "C" inline void errorf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("ERROR: ");
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
    exit(1);
}