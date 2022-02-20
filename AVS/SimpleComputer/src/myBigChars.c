#include "myBigChars.h"
#include "myTerm.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int bc_printA(char* str)
{
    printf("\E(0");
    printf("%s", str);
    printf("\E(B");

    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
    int rows, cols;
    mt_getscreensize(&rows, &cols);

    if (x1 > x2 || y1 > y2 || x1 < 1 || x2 > cols || y1 < 1 || y2 > rows) {
        return -1;
    }

    printf("\E[?25l");

    mt_gotoXY(y1, x1);
    bc_printA("l");
    for (int i = x1 + 1; x2 > i; i++) {
        bc_printA("q");
    }
    bc_printA("k");

    for (int i = y1 + 1; y2 > i; i++) {
        mt_gotoXY(i, x1);
        bc_printA("x");

        mt_gotoXY(i, x2);
        bc_printA("x");
    }

    mt_gotoXY(y2, x1);
    bc_printA("m");
    for (int i = x1 + 1; x2 > i; i++) {
        bc_printA("q");
    }
    bc_printA("j");

    printf("\E[?12;25h");

    return 0;
}

int bc_printBigChar(
        int a[2], int x, int y, enum colors fontcolor, enum colors backcolor)
{
    printf("\E[?25l");
    int temp;

    mt_gotoXY(y, x);
    for (int k = 0; 2 > k; k++) {
        temp = a[k];
        for (int i = 0; 4 > i; i++) {
            for (int j = 0; 8 > j; j++) {
                if (temp & 1) {
                    bc_printA("a");
                } else {
                    bc_printA(" ");
                }
                temp = temp >> 1;
            }
            y++;
            mt_gotoXY(y, x);
        }
    }

    mt_gotoXY(23, 1);

    printf("\E[?12;25h");

    return 0;
}

int bc_setBigCharPos(int* big, int x, int y, int value)
{
    if ((value != 0 && value != 1) || x < 1 || x > 8 || y < 1 || y > 8) {
        return -1;
    }

    int temp = 1;
    temp = (temp << ((y - 1) * 8 + x - 1));
    if (y < 4) {
        *big = !value ? *big & (~temp) : *big | temp;
    } else {
        *(big + 1) = !value ? *(big + 1) & (~temp) : *(big + 1) | temp;
    }

    return 0;
}

int bc_getBigCharPos(int* big, int x, int y, int* value)
{
    if (x < 1 || x > 8 || y < 1 || y > 8) {
        return -1;
    }

    int temp = 1;
    temp = (temp << ((y - 1) * 8 + x - 1));
    if (y < 4) {
        *value = (*big & temp) == 0 ? 0 : 1;
    } else {
        *value = (*(big + 1) & temp) == 0 ? 0 : 1;
    }

    return 0;
}

int bc_bigCharWrite(int fd, int* big, int count)
{
    if (write(fd, &count, sizeof(count)) == -1) {
        return -1;
    }

    for (int i = 0; i < count; i++)
        if (write(fd, big, (sizeof(int)) * 2) == -1) {
            return -1;
        }

    return 0;
}

int bc_bigCharRead(int fd, int* big, int need_count, int* count)
{
    int n, cnt, err;

    err = read(fd, &n, sizeof(n));
    if (err == -1 || (err != sizeof(n))) {
        *count = 0;
        return -1;
    }
    cnt = read(fd, big, need_count * sizeof(int) * 2);
    if (cnt == -1)
        return -1;
    *count = cnt / (sizeof(int) * 2);

    return 0;
}
