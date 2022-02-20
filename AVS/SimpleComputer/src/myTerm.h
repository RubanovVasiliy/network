#ifndef __MYTERM_H__
#define __MYTERM_H__

enum colors {
    black = 0,
    red = 1,
    green = 2,
    orange = 3,
    blue = 4,
    purple = 5,
    cyan = 6,
    white = 7,
    def = 9,
};

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);
int mt_setdefaultcolor();

#endif

//   clear_screen
//   clear= \E[H\E[2J

//   cursor_address
//   cup= \E[%i%p1%d;%p2%dH

//   set_a_foreground
//   setaf=\E[%?%p1%{8}%<%t3%p1%d%e%p1%{16}%<%t9%p1%{8}%-%d%e38;5;%p1%d%;m

//   set_a_background
//   setab=\E[%?%p1%{8}%<%t4%p1%d%e%p1%{16}%<%t10%p1%{8}%-%d%e48;5;%p1%d%;m

//   cursor_invisible
//   civis=\E[?25l

//   cursor_visible
//   cvvis=\E[?12;25h
