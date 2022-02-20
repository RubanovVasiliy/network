#include "string.h"

int slen(char* str)
{
    int count = 0;

    while (str[count] != '\0') {
        count++;
    }
    return count;
}

int s_tok(char* str, char delim, char* ptr[])
{
    char* suf = str;
    ptr[0] = str; // первое поле – начало str
    int i, j = 1; // j – счетчик полей
    while ((i = schr(suf, delim)) >= 0) {
        suf[i] = '\0';
        suf = suf + i + 1;
        ptr[j] = suf;
        j++;
    }
    return j;
}

int schr(char* str, char ch)
{
    int i, index = -1;
    for (i = 0; (str[i] != '\0') && (str[i] != ch); i++) {
        if (str[i] == ch)
            index = i;
    }

    return index;
}

int scopy(char* s1, char* s2)
{
    int i = 0;
    while ((*s2++ = *s1++) != '\0')
        ;
    if (slen(s2) == (slen(s1) + slen((s2)))) {
        i = 1;
        return i;
    } else {
        return i;
    }
}

int s_cmp(char* str_1, char* str_2)
{
    size_t count;
    size_t length, length_1 = slen(str_1), length_2 = slen(str_2);

    if (length_1 >= length_2) {
        length = length_1;
    } else {
        length = length_2;
    }
    for (count = 0; count < length; count++) {
        if (str_1[count] != str_2[count]) {
            if (str_1[count] > str_2[count]) {
                return 1;
            } else if (str_1[count] < str_2[count]) {
                return -1;
            }
        }
    }
    return 0;
}

int str_chr(char* str, char* ch)
{
    int i, j;

    for (i = 0; i < slen(str); i++) {
        for (j = 0; j < slen(ch); j++) {
            if (str[i] == ch[j]) {
                return i;
            }
        }
    }
    return -1;
}

int main(int argc, char* argv[])
{
    setlocale(0, "");
    int ch, prev, row, col;
    prev = EOF;
    FILE* fp;
    int y, x;
    if (argc != 2) {
        printf("Usage: %s <a c file name>\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Cannot open input file");
        exit(1);
    }
    initscr(); /* Start curses mode */
    getmaxyx(stdscr, row, col); /* find the boundaries of the screeen */
    while ((ch = fgetc(fp)) != EOF) /* read the file till we reach the end */
    {
        getyx(stdscr, y, x); /* get the current curser position */
        if (y == (row - 1)) /* are we are at the end of the screen */
        {
            printw("<−Press Any Key−>"); /* tell the user to press a key */
            getch();
            clear(); /* clear the screen */
            move(0, 0); /* start at the beginning of the screen */
        }
        if (prev == '/' && ch == '*') /* If it is / and * then only
 * switch bold on */
        {
            attron(A_BOLD); /* cut bold on */
            getyx(stdscr, y, x); /* get the current curser position */
            move(y, x - 1); /* back up one space */
            printw("%c%c", '/', ch); /* The actual printing is done here */
        } else
            printw("%c", ch);
        refresh();
        if (prev == '*' && ch == '/')
            attroff(A_BOLD); /* Switch it off once we got *
 * and then / */
        prev = ch;
    }
    endwin(); /* End curses mode */
    fclose(fp);
    return 0;
}

int str_tok(char* str, char* delim, char** ptr)
{
    int i, j = 1;
    char* suf = str;

    ptr[0] = str;
    while ((i = str_chr(suf, delim)) >= 0) {
        suf[i] = '\0';
        suf = suf + i + 1;
        ptr[j] = suf;
        j++;
    }
    return j;
}
