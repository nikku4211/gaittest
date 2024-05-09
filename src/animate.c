#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <string.h>

#include "global.h"

unsigned char player_cel[768];
uint8_t double_buffer_counter = 0;

// Load metasprite tile data into VRAM, one tile at a time.
void load_player_sprite_tile_data(void) NONBANKED
{
  //copy sprite cel to VRAM
	vmemcpy(0x2000, &player_cel[0], 768);
}

void set_player_sprite_tile_data(void) NONBANKED {
	size_t i;
	for (i = 0; i < 8; i++)
	{
		if (wolfspr_tile_indexes[i] == 255) {
			break;
		}
		memcpy(&player_cel[i << 8], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4), 2);
		memcpy(&player_cel[(i << 8) + 4], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4) + 2, 2);
		memcpy(&player_cel[(i << 8) + 8], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4) + 4, 2);
		memcpy(&player_cel[(i << 8) + 12], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4) + 6, 2);
		memcpy(&player_cel[(i << 8) + 16], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4) + 8, 2);
		memcpy(&player_cel[(i << 8) + 20], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4) + 10, 2);
		memcpy(&player_cel[(i << 8) + 24], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4) + 12, 2);
		memcpy(&player_cel[(i << 8) + 28], &wolfsprprawgb_tiles + (wolfspr_tile_indexes[i] << 4) + 14, 2);
	}
}

void animate_player(void) NONBANKED{
	if (!PlayFrameCounter) {
		if (PlayMoveX) {
			PlayAnimPointer = (const unsigned char *)wolfspr_run_left_anim;
		} else {
			if (PlayMoveY) {
				if (PlayDirY > 0) {
					PlayAnimPointer = (const unsigned char *)wolfspr_run_down_anim;
				} else if (PlayDirY < 0) {
					PlayAnimPointer = (const unsigned char *)wolfspr_run_up_anim;
				} 
			} else {
				if (PlaySpdX == 0) {
					if (PlayDirY < 0) {
						PlayAnimPointer = (const unsigned char *)wolfspr_stand_up_anim;
					} else if (PlayDirY > 0) {
						PlayAnimPointer = (const unsigned char *)wolfspr_stand_down_anim;
					}
				} else {
						PlayAnimPointer = (const unsigned char *)wolfspr_stand_left_anim;
				}
			}
		}
		if (PlayAnimPointer[PlayAnimFrame << 1] < 255) {
			PlayFrameIndex = PlayAnimPointer[PlayAnimFrame << 1];
			PlayAnimFrame++;
		} else {
			PlayAnimFrame = 0;
		}
		PlayFrameDivisor = PlayAnimPointer[(PlayAnimFrame << 1) + 1];
		PlayFrameCounter = PlayFrameDivisor;
		set_player_sprite_tile_data();
	} else {
		PlayFrameCounter--;
	}
}