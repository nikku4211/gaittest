#include <stdint.h>
#include <stdio.h>

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include "global.h"

#include "res/map/bigmap_map.h"
#include "res/map/bigmap_tiles.h"

#define bigmap_mapWidth (bigmap_map_WIDTH/bigmap_map_TILE_W)
#define bigmap_mapHeight (bigmap_map_HEIGHT/bigmap_map_TILE_H)

// object coords
int16_t PlayPosX, PlayPosY;
uint8_t PlayScreenPosX, PlayScreenPosY;
int8_t PlayDirX, PlayDirY;
uint8_t PlayFlip, PlayMoveX, PlayMoveY;
// object speeds
int16_t PlaySpdX, PlaySpdY;
// object frame
uint8_t PlayFrameIndex, PlayAnimFrame, PlayFrameCounter, PlayFrameDivisor;
const unsigned char * PlayAnimPointer;

// sprite vars

// Constants for tile dimensions
#define TILE_WIDTH          8
#define TILE_HEIGHT         8
#define NUM_BYTES_PER_TILE  16

uint8_t flipped_data[NUM_BYTES_PER_TILE];

size_t num_tiles;

// Table for fast reversing of bits in a byte - used for flipping in X
const uint8_t reverse_bits[256] = {
    0x00,0x80,0x40,0xC0,0x20,0xA0,0x60,0xE0,0x10,0x90,0x50,0xD0,0x30,0xB0,0x70,0xF0,
    0x08,0x88,0x48,0xC8,0x28,0xA8,0x68,0xE8,0x18,0x98,0x58,0xD8,0x38,0xB8,0x78,0xF8,
    0x04,0x84,0x44,0xC4,0x24,0xA4,0x64,0xE4,0x14,0x94,0x54,0xD4,0x34,0xB4,0x74,0xF4,
    0x0C,0x8C,0x4C,0xCC,0x2C,0xAC,0x6C,0xEC,0x1C,0x9C,0x5C,0xDC,0x3C,0xBC,0x7C,0xFC,
    0x02,0x82,0x42,0xC2,0x22,0xA2,0x62,0xE2,0x12,0x92,0x52,0xD2,0x32,0xB2,0x72,0xF2,
    0x0A,0x8A,0x4A,0xCA,0x2A,0xAA,0x6A,0xEA,0x1A,0x9A,0x5A,0xDA,0x3A,0xBA,0x7A,0xFA,
    0x06,0x86,0x46,0xC6,0x26,0xA6,0x66,0xE6,0x16,0x96,0x56,0xD6,0x36,0xB6,0x76,0xF6,
    0x0E,0x8E,0x4E,0xCE,0x2E,0xAE,0x6E,0xEE,0x1E,0x9E,0x5E,0xDE,0x3E,0xBE,0x7E,0xFE,
    0x01,0x81,0x41,0xC1,0x21,0xA1,0x61,0xE1,0x11,0x91,0x51,0xD1,0x31,0xB1,0x71,0xF1,
    0x09,0x89,0x49,0xC9,0x29,0xA9,0x69,0xE9,0x19,0x99,0x59,0xD9,0x39,0xB9,0x79,0xF9,
    0x05,0x85,0x45,0xC5,0x25,0xA5,0x65,0xE5,0x15,0x95,0x55,0xD5,0x35,0xB5,0x75,0xF5,
    0x0D,0x8D,0x4D,0xCD,0x2D,0xAD,0x6D,0xED,0x1D,0x9D,0x5D,0xDD,0x3D,0xBD,0x7D,0xFD,
    0x03,0x83,0x43,0xC3,0x23,0xA3,0x63,0xE3,0x13,0x93,0x53,0xD3,0x33,0xB3,0x73,0xF3,
    0x0B,0x8B,0x4B,0xCB,0x2B,0xAB,0x6B,0xEB,0x1B,0x9B,0x5B,0xDB,0x3B,0xBB,0x7B,0xFB,
    0x07,0x87,0x47,0xC7,0x27,0xA7,0x67,0xE7,0x17,0x97,0x57,0xD7,0x37,0xB7,0x77,0xF7,
    0x0F,0x8F,0x4F,0xCF,0x2F,0xAF,0x6F,0xEF,0x1F,0x9F,0x5F,0xDF,0x3F,0xBF,0x7F,0xFF
};

// Helper function to flip tile in X/Y
// Note this assumes 2BPP tile in GB format, where bitplanes are interleaved.
// Currently all platforms use GB format for 2BPP tile data storage, irrespective
// of what their native tile format is, as set_sprite_data handles the conversion.
void set_tile(uint8_t tile_idx, uint8_t* data, uint8_t flip_x, uint8_t flip_y) NONBANKED
{
    size_t i;
    for(i = 0; i < TILE_HEIGHT; i++)
    {
        size_t y = flip_y ? (TILE_HEIGHT-1-i) : i; 
        flipped_data[2*i] = flip_x ? reverse_bits[data[2*y]] : data[2*y];
        flipped_data[2*i+1] = flip_x ? reverse_bits[data[2*y+1]] : data[2*y+1];
    }
    set_sprite_data(tile_idx, 1, flipped_data);
}

uint8_t get_tile_offset(uint8_t flipx, uint8_t flipy) NONBANKED
{
    flipx; flipy; // suppress compiler warnings
    uint8_t offset = 0;
#if !HARDWARE_SPRITE_CAN_FLIP_Y
    offset += flipy ? num_tiles : 0;
#endif
#if !HARDWARE_SPRITE_CAN_FLIP_X
    offset <<= 1;
    offset += flipx ? num_tiles : 0;
#endif
    return offset;
}

void main(void) NONBANKED {
	
	DISPLAY_OFF;
	init_camera(0, 0);
	PlayPosX = 0;
	PlayPosY = 0;
	
	PlayFrameIndex = 0;
	PlayAnimFrame = 0;
	PlayFrameCounter = 0;
	PlayFrameDivisor = 0;
	PlayAnimPointer = (const unsigned char *)wolfspr_run_left_anim;
	
	//memset(&player_cel, 0x00, 768);
	
	SWITCH_ROM(BANK(wolfsprprawsms));
	
	//load_and_duplicate_sprite_tile_data();
	// __critical{
		// add_VBL(load_player_sprite_tile_data);
	// }

	SHOW_BKG; SHOW_SPRITES;
	SPRITES_8x16;
	DISPLAY_ON;
	
	while(TRUE){
		handle_input();
		
		// change coordinates of the player
    PlayPosX += PlaySpdX, PlayPosY += PlaySpdY;
		
		if (PlayPosX < 0){
			PlayPosX = 0;
		} else if (PlayPosX > PLAYER_MAX_X) {
			PlayPosX = PLAYER_MAX_X;
		}
		
		if (PlayPosY < 0){
			PlayPosY = 0;
		} else if (PlayPosY > PLAYER_MAX_Y) {
			PlayPosY = PLAYER_MAX_Y;
		}
		
		// decelerate Y and X
    if (PlaySpdY < 0) {
			PlaySpdY++;
		} else if (PlaySpdY) {
			PlaySpdY--;
		}
		if (PlaySpdX < 0) {
			PlaySpdX++;
		} else if (PlaySpdX){
			PlaySpdX--;
		}
		
		//player screen position is separate from player map position
		PlayScreenPosX = SUBPIXELS_TO_PIXELS(PlayPosX - camera_x)+48;
		PlayScreenPosY = SUBPIXELS_TO_PIXELS(PlayPosY - camera_y)+24;
		
		if(PlayScreenPosX > PLAYER_RIGHT_CAMERA_BOUND){
			camera_x = PlayPosX - PIXELS_TO_SUBPIXELS(PLAYER_RIGHT_CAMERA_BOUND);
			redraw = TRUE;
		}else if(PlayScreenPosX < PLAYER_LEFT_CAMERA_BOUND){
			camera_x = PlayPosX - PIXELS_TO_SUBPIXELS(PLAYER_LEFT_CAMERA_BOUND);
			redraw = TRUE;
		}
		if(PlayScreenPosY > PLAYER_DOWN_CAMERA_BOUND){
			camera_y = PlayPosY - PIXELS_TO_SUBPIXELS(PLAYER_DOWN_CAMERA_BOUND);
			redraw = TRUE;
		}else if(PlayScreenPosY < PLAYER_UP_CAMERA_BOUND){
			camera_y = PlayPosY - PIXELS_TO_SUBPIXELS(PLAYER_UP_CAMERA_BOUND);
			redraw = TRUE;
		}
		
		uint8_t PlayMetasprite = 0;
		SWITCH_ROM(BANK(wolfsprprawsms));
		animate_player();
		
		SWITCH_ROM(BANK(wolfspr_meta));
		if (!PlayFlip) {
			PlayMetasprite = move_metasprite_ex(wolfspr_meta[PlayFrameIndex], 0, 0, 0, PlayScreenPosX, PlayScreenPosY);
		} else {
			PlayMetasprite = move_metasprite_flipx(wolfspr_meta[PlayFrameIndex], 0, 0, 0, PlayScreenPosX, PlayScreenPosY);
		}
		// Hide rest of the hardware sprites, because amount of sprites differ between animation frames.
    hide_sprites_range(PlayMetasprite, MAX_HARDWARE_SPRITES);
		
		if (redraw) {
			vsync();
			SWITCH_ROM(BANK(bigmap_map));
			set_camera();
			redraw = FALSE;
		} else vsync();
		
	}
}