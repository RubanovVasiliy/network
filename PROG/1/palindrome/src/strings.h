#ifndef STRINGS
#define STRINGS

#include <stddef.h>

char incorrect_sym[] = " .,!?-+=\"'\\/():;*<>[]{}#$%^&@_|\n\t";

int scmp(const char* str1, const char* str2);
size_t slen(const char* str);
void* mem_cpy(void* dest, const void* src, size_t len);

#endif