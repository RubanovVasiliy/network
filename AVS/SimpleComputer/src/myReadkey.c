#include "myReadkey.h"
#include <string.h>
#include <termios.h>
#include <unistd.h>

int rk_readkey(enum keys* key)
{
    rk_mytermregime(1, 0, 1, 1, 1);
    char buf[8];
    read(STDIN_FILENO, buf, 8);
    if (buf[0] == 'w') {
        *key = KEY_up;
    } else if (buf[0] == 's') {
        *key = KEY_down;
    } else if (buf[0] == 'd') {
        *key = KEY_right;
    } else if (buf[0] == 'a') {
        *key = KEY_left;
    } else if (buf[0] == '.') {
        *key = KEY_f5;
    } else if (buf[0] == '/') {
        *key = KEY_f6;
    } else if (buf[0] == 'l') {
        *key = KEY_load;
    } else if (buf[0] == 'k') {
        *key = KEY_save;
    } else if (buf[0] == 'r') {
        *key = KEY_run;
    } else if (buf[0] == 't') {
        *key = KEY_step;
    } else if (buf[0] == 'i') {
        *key = KEY_reset;
    } else if (buf[0] == '\n') {
        *key = KEY_enter;
    } else if (buf[0] == 'q')
        *key = KEY_quit;

    rk_mytermrestore();
    return 0;
}

int rk_mytermsave(void)
{
    if (!tcgetattr(0, &settings)) {
        return 1;
    }

    return 0;
}

int rk_mytermrestore(void)
{
    if (!tcsetattr(0, TCSANOW, &settings)) {
        return 1;
    }
    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios new_settings;

    rk_mytermsave();
    new_settings = settings;

    if (regime) {
        new_settings.c_lflag &= (~ICANON);
        new_settings.c_cc[VTIME] = vtime;
        new_settings.c_cc[VMIN] = vmin;

        if (sigint)
            new_settings.c_lflag &= (~ECHO);
        else
            new_settings.c_lflag |= ECHO;

        if (echo == 1)
            new_settings.c_lflag &= (~ISIG);
        else
            new_settings.c_lflag |= ISIG;
    } else {
        new_settings.c_lflag |= ICANON;
    }

    if (!tcsetattr(STDIN_FILENO, TCSANOW, &new_settings))
        return -1;

    return 0;
}