#include "func.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc == 2) {
        read_file(argv[1], 1);
    } else if (argc == 3) {
        int p_len = atoi(argv[2]);

        if (p_len > 1 && p_len < 1000) {
            read_file(argv[1], p_len);
        } else {
        	printf("%s\n","Incorrect input. \nThird arg must be: 1<[arg]<1000");
        }
    } else {
        return -1;
    }

    return 0;
}
