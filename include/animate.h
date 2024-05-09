#ifndef _ANIMATE
#define _ANIMATE

#include <gbdk/platform.h>
#include <string.h>

extern unsigned char player_cel[768];
extern uint8_t double_buffer_counter;

extern void load_player_sprite_tile_data(void) NONBANKED;
extern void set_player_sprite_tile_data(void) NONBANKED;
extern void animate_player(void) NONBANKED;
#endif