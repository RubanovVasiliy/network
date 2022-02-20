#ifndef __MYREADKEY_H__
#define __MYREADKEY_H__

#include <termios.h>

enum keys {
    KEY_load,
    KEY_save,
    KEY_run,
    KEY_step,
    KEY_reset,
    KEY_f5,
    KEY_f6,
    KEY_down,
    KEY_up,
    KEY_left,
    KEY_right,
    KEY_quit,
    KEY_other,
    KEY_enter,
};

static struct termios settings;

int rk_readkey(enum keys* key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif