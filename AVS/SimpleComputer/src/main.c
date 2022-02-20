#include "main.h"

int main(void)
{
    mt_clrscr();
    srand(time(NULL));

    init();
    print_interface_boxes();
    print_memory();
    move(1);
    set_flag();
    print_flags();
    print_bigchar(nums[instructionCounter]);
    print_instructionCounter();
    print_accumulator();

    while (key != KEY_quit) {
        mt_clrscr();
        print_memory();
        print_interface_boxes();
        set_flag();
        print_flags();
        print_bigchar(nums[instructionCounter]);
        print_instructionCounter();
        print_accumulator();
        move(1);

        mt_gotoXY(30, 5);
        printf("\n\n");

        rk_readkey(&key);
        switch (key) {
        case (KEY_load):
            _LOAD_();
            break;

        case (KEY_save):
            _SAVE_();
            break;

        case (KEY_run):
            _RUN_();
            break;

        case (KEY_step):
            _STEP_();
            break;

        case (KEY_reset):
            _RESET_();
            break;

        case (KEY_f5):
            _F5_();
            break;

        case (KEY_f6):
            _F6_();
            break;

        case (KEY_down):
            _DOWN_();
            break;

        case (KEY_up):
            _UP_();
            break;

        case (KEY_left):
            _LEFT_();
            break;

        case (KEY_right):
            _RIGHT_();
            break;

        case (KEY_enter):
            _ENTER_();
            break;

        case (KEY_quit):
            exit(0);
            break;

        default:
            break;
        }
        key = KEY_other;
    }

    return 0;
}

// git ls-files src/ | xargs clang-format -i && git diff --exit-code
