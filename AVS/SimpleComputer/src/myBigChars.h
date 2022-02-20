#ifndef __MYBIGCHARS_H__
#define __MYBIGCHARS_H__
#include "myTerm.h"

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printBigChar(
        int a[2], int x, int y, enum colors fontcolor, enum colors backcolor);
int bc_setBigCharPos(int* big, int x, int y, int value);
int bc_getBigCharPos(int* big, int x, int y, int* value);
int bc_bigCharWrite(int fd, int* big, int count);
int bc_bigCharRead(int fd, int* big, int need_count, int* count);

#endif

//    acs_chars = ``aaffggiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}}~~
//                ◆◆▒▒°°±±␋␋┘┘┐┐┌┌└└┼┼⎺⎺⎻⎻──⎼⎼⎽⎽├├┤┤┴┴┬┬││≤≤≥≥ππ≠≠££··

//    enter_alt_charset_mode = \E(0

//    exit_alt_charset_mode = \E(B
