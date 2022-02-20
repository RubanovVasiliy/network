#include <math.h>
#include <stdio.h>
#include <stdlib.h>

size_t slen(const char* str)
{
    size_t i = 0;
    while (*str++) {
        i++;
    }
    return i;
}

int sspn(char* str, char ch)
{
    int i = 0;
    for (; str[i] != '\0' && str[i] != ch; i++)
        ;
    if (str[i] == ch)
        return i;
    return -1;
}

int stok(char* str, char delim, char* ptr[])
{
    char* suf = str;
    ptr[0] = str;
    int pos, j = 1;
    while ((pos = sspn(suf, delim)) >= 0) {
        suf[pos] = '\0';
        suf = suf + pos + 1;
        ptr[j] = suf;
        j++;
    }
    return j;
}

int scmp(const char* str1, const char* str2)
{
    for (; *str1 && *str1 == *str2; str1++, str2++)
        ;
    return *str1 - *str2;
}

char* scpy(char* dest, const char* src)
{
    char* tmp = dest;

    while ((*dest++ = *src++) != '\0')
        ;
    return tmp;
}

char* scat(char* dest, const char* src)
{
    char* tmp = dest;
    while (*dest)
        dest++;
    while ((*dest++ = *src++) != '\0')
        ;
    return tmp;
}

int m_atoi(char* str, int sum)
{
    if (*str == '\0') {
        return sum;
    }
    sum = sum + (*str - 48) * pow(10, slen(str) - 1);
    return m_atoi(str + 1, sum);
}