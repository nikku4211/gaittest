#ifndef _INPUT
#define _INPUT

#include <gbdk/platform.h>

// update user input macro
#define INPUT_PROCESS (old_joy=joy,joy=joypad())
// check button down
#define INPUT_KEY(key) (joy&(key))
// check button press
#define INPUT_KEYPRESS(key) ((joy & ~old_joy) & (key))

extern uint8_t joy, old_joy;

void handle_input(void) NONBANKED;

#endif