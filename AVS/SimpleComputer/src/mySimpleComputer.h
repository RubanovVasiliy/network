#ifndef __MYSIMPLECOMPUTER_H__
#define __MYSIMPLECOMPUTER_H__

#define OVERFLOW 0b00000001               // P
#define DIVISION_BY_ZERO 0b00000010       // O
#define OUT_OF_BOUNDS 0b00000100          // M
#define IGNOREING_CLOCK_PULSES 0b00001000 // T
#define INVALID_COMMAND 0b00010000        // E

#define ERROR_INVALID_REGISTER_VALUE -1
#define ERROR_OUT_OF_BOUNDS -2
#define ERROR_INVALID_COMMAND -3
#define ERROR_INVALID_OPERAND -4
#define ERROR_OPEN_FILE -5
#define ERROR_INVALID_MASK -6
#define ERROR_NOT_COMMAND -7

#define MEMORY_SIZE 100

int registr;
int nums[MEMORY_SIZE];

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int register, int value);
int sc_regGet(int register, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);

#endif