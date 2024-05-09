#ifndef _GLOBAL
#define _GLOBAL

#include <gbdk/platform.h>
#include <gbdk/incbin.h>

#include "camera.h"
#include "input.h"
#include "animate.h"

#include "res/spr/wolfsprprawgb.h"
#include "spritemeta.h"

//camera values
#define camera_max_y PIXELS_TO_SUBPIXELS((bigmap_mapHeight - DEVICE_SCREEN_HEIGHT) * 8) 
#define camera_max_x PIXELS_TO_SUBPIXELS((bigmap_mapWidth - DEVICE_SCREEN_WIDTH) * 8)

//player size constants
#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 32

//player camera constants
#define PLAYER_LEFT_CAMERA_BOUND 80
#define PLAYER_RIGHT_CAMERA_BOUND 80
#define PLAYER_UP_CAMERA_BOUND 72
#define PLAYER_DOWN_CAMERA_BOUND 72
#define PLAYER_MAX_Y PIXELS_TO_SUBPIXELS((bigmap_mapHeight * 8) - (PLAYER_HEIGHT >> 1)) 
#define PLAYER_MAX_X PIXELS_TO_SUBPIXELS((bigmap_mapWidth * 8) - (PLAYER_WIDTH >> 1))

// physics constants
#define MAX_X_SPEED_IN_SUBPIXELS 64
#define X_ACCELERATION_IN_SUBPIXELS 2
#define X_DECELERATION_IN_SUBPIXELS 1
#define MAX_Y_SPEED_IN_SUBPIXELS 64
#define Y_ACCELERATION_IN_SUBPIXELS 2
#define Y_DECELERATION_IN_SUBPIXELS 1
#define JUMP_ACCELERATION_IN_SUBPIXELS 32

// coordinate translation macros
#define SUBPIXELS_TO_PIXELS(v) (v >> 4)
#define PIXELS_TO_SUBPIXELS(v) (v << 4)

// current and old positions of the camera in pixels
extern int16_t camera_x, camera_y, old_camera_x, old_camera_y;
// redraw flag, indicates that camera position was changed
extern uint8_t redraw;

// object coords
extern int16_t PlayPosX, PlayPosY;
extern uint8_t PlayScreenPosX, PlayScreenPosY;
extern int8_t PlayDirX, PlayDirY;
extern uint8_t PlayFlip, PlayMoveX, PlayMoveY;
// object speeds
extern int16_t PlaySpdX, PlaySpdY;
// object frame
extern uint8_t PlayFrameIndex, PlayAnimFrame, PlayFrameCounter, PlayFrameDivisor;
extern const unsigned char *PlayAnimPointer;

#endif