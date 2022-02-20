#include <stdio.h>
#include <stdlib.h>

int scmp(const char* str1, const char* str2)
{
    for (; *str1 && *str1 == *str2; str1++, str2++)
        ;
    return *str1 - *str2;
}

size_t slen(const char* str)
{
    size_t i = 0;
    while (*str++) {
        i++;
    }
    return i;
}

void* mem_cpy(void* dest, const void* src, size_t len)
{
    char* d = dest;
    const char* s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}
