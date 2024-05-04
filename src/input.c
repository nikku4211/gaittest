#include <gbdk/platform.h>

#include "global.h"
#include "input.h"

// new and previous values of the joypad input
uint8_t joy = 0, old_joy;

void handle_input(void) NONBANKED{
	INPUT_PROCESS;
		
	if(INPUT_KEY(J_UP)){
		PlaySpdY -= Y_ACCELERATION_IN_SUBPIXELS;
		if (PlaySpdY < -MAX_Y_SPEED_IN_SUBPIXELS) PlaySpdY = -MAX_Y_SPEED_IN_SUBPIXELS;
		PlayDirY = 0;
	} else if(INPUT_KEY(J_DOWN)){
		PlaySpdY += Y_ACCELERATION_IN_SUBPIXELS;
		if (PlaySpdY > MAX_Y_SPEED_IN_SUBPIXELS) PlaySpdY = MAX_Y_SPEED_IN_SUBPIXELS;
		PlayDirY = 1;
	}
	if(INPUT_KEY(J_LEFT)){
		PlaySpdX -= X_ACCELERATION_IN_SUBPIXELS;
		if (PlaySpdX < -MAX_X_SPEED_IN_SUBPIXELS) PlaySpdX = -MAX_X_SPEED_IN_SUBPIXELS;
		PlayDirX = 0;
	} else if(INPUT_KEY(J_RIGHT)){
		PlaySpdX += X_ACCELERATION_IN_SUBPIXELS;
		if (PlaySpdX > MAX_X_SPEED_IN_SUBPIXELS) PlaySpdX = MAX_X_SPEED_IN_SUBPIXELS;
		PlayDirX = 1;
	}
}