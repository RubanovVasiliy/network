#ifndef __MAIN_H__
#define __MAIN_H__

#include "myBigChars.h"
#include "myReadkey.h"
#include "mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int arrP[2] = {
        0b11111111000110000001100000011000, 0b00011000000110000001100011111111};

int arr1[2] = {
        0b01100000011110000111000001100000, 0b11110000011000000110000001100000};

int arr2[2] = {
        0b11111111110000001100000011111111, 0b11111111000000110000001100000011};

int arr3[2] = {
        0b11111111110000001100000011111111, 0b11111111110000001100000011000000};

int arr4[2] = {
        0b11111111110000111100001111000011, 0b11000000110000001100000011000000};

int arr5[2] = {
        0b11111111000000110000001111111111, 0b11111111110000001100000011000000};

int arr6[2] = {
        0b11111111000000110000001111111111, 0b11111111110000111100001111000011};

int arr7[2] = {
        0b00110000011000001100000011111111, 0b00000011000001100000110000011000};

int arr8[2] = {
        0b11111111110000111100001111111111, 0b11111111110000111100001111000011};

int arr9[2] = {
        0b11111111110000111100001111111111, 0b00011000001100000110000011000000};

int arr0[2] = {
        0b11000011110000111100001111111111, 0b11111111110000111100001111000011};

int arrA[2] = {
        0b11000011011001100011110000011000, 0b11000011110000111111111111000011};

int arrB[2] = {
        0b01111111110000111100001101111111, 0b01111111110000111100001111000011};

int arrC[2] = {
        0b00000011000000110000011011111100, 0b11111100000001100000001100000011};

int arrD[2] = {
        0b01100011110000111100001100111111, 0b00111111110000111100001101100011};

int arrE[2] = {
        0b11111111000000110000001111111111, 0b11111111000000110000001100000011};

int arrF[2] = {
        0b11111111000000110000001111111111, 0b00000011000000110000001100000011};

int* bigChars[16]
        = {arr0,
           arr1,
           arr2,
           arr3,
           arr4,
           arr5,
           arr6,
           arr7,
           arr8,
           arr9,
           arrA,
           arrB,
           arrC,
           arrD,
           arrE,
           arrF};

enum keys key = KEY_other;

int instructionCounter = 0;
int accumulator = 0;
int current_num = 0;
int command = 0;
int operation = 0;

void move(int i)
{
    int rows = 2;
    int cols = 2;

    rows += current_num / 10;
    cols += current_num % 10 * 6;
    mt_gotoXY(rows, cols);

    if (i == 1) {
        mt_setbgcolor(white);
        mt_setfgcolor(black);
    } else {
        mt_setdefaultcolor();
    }

    printf("+%04x", nums[current_num]);
    mt_setdefaultcolor();
}

void print_interface_boxes()
{
    // Memory
    bc_box(1, 1, 62, 12);
    mt_gotoXY(1, 31);
    printf(" Memory ");

    // accumulator
    bc_box(63, 1, 84, 3);
    mt_gotoXY(1, 67);
    printf(" accumulator ");

    // instructionCounter
    bc_box(63, 4, 84, 6);
    mt_gotoXY(4, 64);
    printf(" instructionCounter ");

    // Operation
    bc_box(63, 7, 84, 9);
    mt_gotoXY(7, 69);
    printf(" Operation ");

    // Flags
    bc_box(63, 10, 84, 12);
    mt_gotoXY(10, 69);
    printf(" Flags ");

    // Keys:
    bc_box(47, 13, 84, 22);
    mt_gotoXY(13, 48);
    printf(" Keys: ");

    mt_gotoXY(14, 49);
    printf("l  - load");
    mt_gotoXY(15, 49);
    printf("s  - save");
    mt_gotoXY(16, 49);
    printf("r  - run");
    mt_gotoXY(17, 49);
    printf("t  - step");
    mt_gotoXY(18, 49);
    printf("i  - reset");
    mt_gotoXY(19, 49);
    printf("F5 - accumulator");
    mt_gotoXY(20, 49);
    printf("F6 - instructionCounter");

    // Input/Output:
    mt_gotoXY(24, 1);
    printf("Input/Output:");

    mt_gotoXY(25, 1);

    // Bigchar box
    bc_box(1, 13, 46, 22);
}

void print_memory()
{
    int x = 2, y = 2;
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            mt_gotoXY(y, x);
            printf("+%.4x", nums[i + j * 10]);
            x += 6;
        }
        x = 2;
        y++;
    }
}

void print_flags()
{
    mt_gotoXY(11, 68);
    if (registr & OVERFLOW) {
        printf("P ");
    } else {
        printf("  ");
    }

    if (registr & DIVISION_BY_ZERO) {
        printf("O ");
    } else {
        printf("  ");
    }

    if (registr & OUT_OF_BOUNDS) {
        printf("M ");
    } else {
        printf("  ");
    }

    if (registr & IGNOREING_CLOCK_PULSES) {
        printf("T ");
    } else {
        printf("  ");
    }

    if (registr & INVALID_COMMAND) {
        printf("E ");
    } else {
        printf("  ");
    }
}

void print_instructionCounter()
{
    mt_gotoXY(5, 71);
    printf("+%.4x", instructionCounter);
    mt_gotoXY(8, 69);
    printf("+%02x : %02x", command, operation);
}

void print_accumulator()
{
    mt_gotoXY(2, 71);
    printf("+%.4x", accumulator);
}

void print_bigchar(int num)
{
    int digits[4];

    digits[0] = num % 16;
    digits[1] = num / 16 % 16;
    digits[2] = num / 256 % 16;
    digits[3] = num / 4096 % 16;

    bc_printBigChar(arrP, 2, 14, 1, 2);
    bc_printBigChar(bigChars[digits[3]], 11, 14, 1, 2);
    bc_printBigChar(bigChars[digits[2]], 20, 14, 1, 2);
    bc_printBigChar(bigChars[digits[1]], 29, 14, 1, 2);
    bc_printBigChar(bigChars[digits[0]], 38, 14, 1, 2);
}

void set_flag()
{
    command = 0;
    operation = 0;
    sc_regInit();

    int res = sc_commandDecode(nums[instructionCounter], &command, &operation);
    if (res == -7 || res == -3) {
        sc_regSet(INVALID_COMMAND, 1);
    } else {
        sc_regSet(INVALID_COMMAND, 0);
    }
}

void init()
{
    sc_memoryInit();
    sc_regInit();
    instructionCounter = 0;
    accumulator = 0;
    current_num = 0;
    command = 0;
    operation = 0;

    for (int i = 0; i < 100; i++) {
        sc_memorySet(i, rand() % 65000);
    }
}

void clean_input()
{
    int rows, cols;
    mt_getscreensize(&rows, &cols);
    for (int i = 26; i <= 31; i++) {
        for (int j = 1; j < cols; j++) {
            mt_gotoXY(i, j);
            printf(" ");
        }
    }
}

void _LOAD_()
{
    char* filename = malloc(sizeof(char) * 20);
    mt_gotoXY(26, 1);
    printf("Enter the file name to load: \n$ ");
    scanf("%s", filename);
    sc_memoryLoad(filename);
    clean_input();
}

void _SAVE_()
{
    char* filename = malloc(sizeof(char) * 20);
    mt_gotoXY(26, 1);
    printf("Enter the file name to save: \n$ ");
    scanf("%s", filename);
    sc_memorySave(filename);
    clean_input();
}

void _RUN_(void)
{
}

void _STEP_(void)
{
    if (current_num < 90) {
        move(0);
        current_num += 10;
        move(1);
    }
}

void _RESET_(void)
{
    init();
}

void _ENTER_(void)
{
    int value = 0, temp = 0;
    mt_gotoXY(26, 1);
    printf("Enter new value:\n$ ");

    if (scanf("%x", &value) && value < 65535) {
        if (!sc_commandEncode((value >> 7) & 0x7F, value & 0x7F, &temp)) {
            if (sc_memorySet(current_num, value)) {
                printf("Out of memory border!");
                sleep(1);
            }
        } else {
            printf("Wrong command!");
            sc_regSet(INVALID_COMMAND, 1);
            sleep(1);
        }
    } else {
        sc_regSet(OVERFLOW, 1);
    }
    printf("\n");
    clean_input();
}

void _F5_(void)
{
    accumulator = nums[current_num];
}

void _F6_(void)
{
    instructionCounter = current_num;
}

void _DOWN_(void)
{
    if (current_num < 90) {
        move(0);
        current_num += 10;
        move(1);
    }
}

void _UP_(void)
{
    if (current_num > 9) {
        move(0);
        current_num -= 10;
        move(1);
    }
}

void _LEFT_(void)
{
    if (current_num % 10 != 0) {
        move(0);
        current_num--;
        move(1);
    }
}

void _RIGHT_(void)
{
    if (current_num % 10 != 9) {
        move(0);
        current_num++;
        move(1);
    }
}

#endif