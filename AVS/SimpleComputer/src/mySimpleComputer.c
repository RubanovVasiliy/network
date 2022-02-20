#include "mySimpleComputer.h"
#include <stdio.h>

int sc_memoryInit()
{
    for (int i = 0; i < 100; i++) {
        nums[i] = 0;
    }

    return 0;
}

int sc_memorySet(int address, int value)
{
    if (address < 0 || address >= MEMORY_SIZE) {
        sc_regSet(OUT_OF_BOUNDS, 1);
        return ERROR_OUT_OF_BOUNDS;
    }

    nums[address] = value;
    return 0;
}

int sc_memoryGet(int address, int* value)
{
    if (address < 0 || address >= MEMORY_SIZE) {
        sc_regSet(OUT_OF_BOUNDS, 1);
        return ERROR_OUT_OF_BOUNDS;
    }

    value = &nums[address];
    return 0;
}

int sc_memorySave(char* filename)
{
    FILE* f;
    if ((f = fopen(filename, "wb")) == NULL) {
        return ERROR_OPEN_FILE;
    }

    fwrite(&nums, sizeof(int), 100, f);
    fclose(f);
    return 0;
}

int sc_memoryLoad(char* filename)
{
    FILE* f;
    if ((f = fopen(filename, "rb")) == NULL) {
        return ERROR_OPEN_FILE;
    }

    fread(&nums, sizeof(int), 100, f);
    fclose(f);
    return 0;
}

int sc_regInit(void)
{
    registr = 0;

    return 0;
}

int sc_regSet(int reg, int value)
{
    if (value != 0 && value != 1) {
        return ERROR_INVALID_REGISTER_VALUE;
    }

    if (reg == OVERFLOW || reg == DIVISION_BY_ZERO || reg == OUT_OF_BOUNDS
        || reg == IGNOREING_CLOCK_PULSES || reg == INVALID_COMMAND) {
        registr = value == 0 ? registr & (~reg) : registr | reg;
        return 0;
    }

    return ERROR_INVALID_MASK;
}

int sc_regGet(int reg, int* value)
{
    if (reg == OVERFLOW || reg == DIVISION_BY_ZERO || reg == OUT_OF_BOUNDS
        || reg == IGNOREING_CLOCK_PULSES || reg == INVALID_COMMAND) {
        *value = (registr & reg) == 0 ? 0 : 1;
        return 0;
    }

    return ERROR_INVALID_MASK;
}

int sc_commandEncode(int command, int operand, int* value)
{
    if ((command != 10 && command != 11 && command != 20 && command != 21)
        && !(command >= 30 && command <= 33)
        && !(command >= 40 && command <= 76)) {
        return ERROR_INVALID_COMMAND;
    }

    if (operand < 0 || operand > 0x7f) {
        return ERROR_INVALID_OPERAND;
    }

    *value = (command << 7) | operand;
    return 0;
}

int sc_commandDecode(int value, int* command, int* operand)
{
    if (value & 0x4000) {
        return ERROR_NOT_COMMAND;
    }
    int temp_command = (value >> 7) & 0x7F;

    if ((temp_command != 10 && temp_command != 11 && temp_command != 20
         && temp_command != 21)
        && !(temp_command >= 30 && temp_command <= 33)
        && !(temp_command >= 40 && temp_command <= 76)) {
        sc_regSet(INVALID_COMMAND, 1);
        return ERROR_INVALID_COMMAND;
    }
    *command = temp_command;
    *operand = value & 0x7F;

    return 0;
}