//highest length substring using manachers algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

void getarray(char* str, int p[])
{
    int n = strlen(str), i;
    int c = 0, r = -1, rad; //c for centre of palllindrom,r for rightmost pos and rad is radius pallindrom
    for (i = 0; i < n; i++) {
        if (i <= r) {
            rad = min((r - i), p[2 * c - i]);
        } else
            rad = 0;
        while (i + rad < n && i - rad >= 0 && str[i - rad] == str[i + rad]) //condition of pallindrom
            rad++;
        p[i] = rad - 1;
        if ((i + rad - 1) > r) {
            c = i;
            r = i + rad - 1;
        }
    }
}

int generate(char* str)
{
    int len = 2 * strlen(str) + 1;
    char* mod = calloc(len, 1);
    int i = 0;
    int k = 0;
    for (i = 0; i < len; i++) {
        if (i % 2 == 0)
            mod[i] = '#';
        else {
            mod[i] = str[k];
            k++;
        }
    }
    mod[i] = '\0';

    int l = strlen(mod);
    int p[l], temp, max = 3;
    getarray(mod, p);

    int count = 0;
    int m = 0;

    for (i = 0; i < l; i++) {
        if (p[i] >= m) {
            m = p[i];
            temp = i;
        } else if (!p[i] && m >= max) {
            char* s = strdup(str);
            s = s + (temp / 2) - (m / 2);
            s[m] = '\0';
            m = 0;
            count++;
            //printf("%s\n", s);
        }
    }
    free(mod);
    return count;
}

char* sdup(const char* s)
{
    size_t len = strlen(s) + 1;
    char* new = calloc(len, 1);
    if (new == NULL)
        return NULL;
    for (size_t i = 0; i < len - 1; i++) {
        new[i] = s[i];
    }
    return (char*)s;
}

int main()
{
    char str[10000] = { "aaabaa" };
    //printf("enter the string\n"); //user input

    generate(str);
}