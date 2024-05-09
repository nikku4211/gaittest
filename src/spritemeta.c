#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#pragma bank 255

#define anim_end 255
#define dynam_end 255

BANKREF(wolfspr_meta)

const unsigned char padded_wolfspr_tile_indexes[] = {
	0, 2, 4, 6, 32, 34, 36, 0,
	94, 96, 0, 0, 0, 0, 0, 0,
	98, 0, 0, 0, 0, 0, 0, 0,
	0, 8, 4, 10, 12, 38, 40, 42,
	0, 14, 16, 18, 20, 44, 46, 48,
	0, 22, 62, 64, 66, 50, 52, 54,
	0, 24, 26, 82, 84, 86, 0, 0,
	68, 88, 0, 0, 0, 0, 0, 0,
	70, 58, 0, 0, 0, 0, 0, 0,
	72, 60, 0, 0, 0, 0, 0, 0,
	74, 28, 0, 0, 0, 0, 0, 0,
	76, 0, 0, 0, 0, 0, 0, 0,
	30, 0, 0, 0, 0, 0, 0, 0,
	78, 90, 0, 0, 0, 0, 0, 0,
	80, 92, 0, 0, 0, 0, 0, 0
};

const unsigned char wolfspr_tile_indexes[] = {
	0, 2, 4, 6, 32, 34, 36, dynam_end,
	94, 96, dynam_end,
	98, dynam_end,
	0, 8, 4, 10, 12, 38, 40, 42, dynam_end,
	0, 14, 16, 18, 20, 44, 46, 48, dynam_end,
	0, 22, 62, 64, 66, 50, 52, 54, dynam_end,
	0, 24, 26, 82, 84, 86, dynam_end,
	68, 88, dynam_end,
	70, 58, dynam_end,
	72, 60, dynam_end,
	74, 28, dynam_end,
	76, dynam_end,
	30, dynam_end,
	78, 90, dynam_end,
	80, 92, dynam_end
};

const metasprite_t wolfspr_stand_left[] = {
	METASPR_ITEM(-16, -16,  0, 0), METASPR_ITEM(0, 8,  2, 0), METASPR_ITEM(0, 8,  4, 0), METASPR_ITEM(0, 8, 6, 0), 
	METASPR_ITEM(16, -16, 8, 0), METASPR_ITEM(0, 8, 10, 0), METASPR_ITEM(0, 8, 12, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_stand_up[] = {
	METASPR_ITEM(-16, -4, 0, 0), METASPR_ITEM(16, 0, 2, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_stand_down[] = {
	METASPR_ITEM(0, -4, 0, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_0[] = {
	METASPR_ITEM(-16, -16,  0, 0), METASPR_ITEM(0, 8,  2, 0), METASPR_ITEM(0, 8,  4, 0), METASPR_ITEM(0, 8, 6, 0), METASPR_ITEM(0, 8, 8, 0),
	METASPR_ITEM(16, -25, 10, 0), METASPR_ITEM(0, 8, 12, 0), METASPR_ITEM(0, 8, 14, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_1[] = {
	METASPR_ITEM(-15, -16,  0, 0), METASPR_ITEM(0, 8, 2, 0), METASPR_ITEM(0, 8, 4, 0), METASPR_ITEM(12, 8, 6, 0), METASPR_ITEM(-12, 8, 8, 0),
	METASPR_ITEM(16, -32, 10, 0), METASPR_ITEM(0, 8, 12, 0), METASPR_ITEM(0, 8, 14, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_2[] = {
	METASPR_ITEM(-14, -16,  0, 0), METASPR_ITEM(4, 8, 2, 0), METASPR_ITEM(-1, 8, 4, 0), METASPR_ITEM(0, 8, 6, 0), METASPR_ITEM(4, 8, 8, 0),
	METASPR_ITEM(11, -32, 10, 0), METASPR_ITEM(0, 8, 12, 0), METASPR_ITEM(0, 16, 14, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_3[] = {
	METASPR_ITEM(-15, -16, 0, 0), METASPR_ITEM(0, 7, 2, 0), METASPR_ITEM(12, 8, 4, 0), METASPR_ITEM(-3, 8, 6, 0), METASPR_ITEM(0, 8, 8, 0),
	METASPR_ITEM(7, -24, 10, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_0[] = {
	METASPR_ITEM(-16, -4, 0, 0), METASPR_ITEM(16, 0, 2, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_1[] = {
	METASPR_ITEM(-16, -4, 0, 0), METASPR_ITEM(16, 0, 2, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_2[] = {
	METASPR_ITEM(-16, -4, 0, 0), METASPR_ITEM(16, 0, 2, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_3[] = {
	METASPR_ITEM(-16, -4, 0, 0), METASPR_ITEM(16, 0, 2, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_0[] = {
	METASPR_ITEM(0, -4, 0, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_1[] = {
	METASPR_ITEM(0, -4, 0, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_2[] = {
	METASPR_ITEM(-16, -4, 0, 0), METASPR_ITEM(16, 0, 2, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_3[] = {
	METASPR_ITEM(-16, -4, 0, 0), METASPR_ITEM(16, 0, 2, 0),
	METASPR_TERM
};

const metasprite_t* const wolfspr_meta[15] = {
	wolfspr_stand_left, wolfspr_stand_up, wolfspr_stand_down,
	wolfspr_run_left_0, wolfspr_run_left_1, wolfspr_run_left_2, wolfspr_run_left_3,
	wolfspr_run_up_0, wolfspr_run_up_1, wolfspr_run_up_2, wolfspr_run_up_3,
	wolfspr_run_down_0, wolfspr_run_down_1, wolfspr_run_down_2, wolfspr_run_down_3
};

/*
animation format:

metasprite_t list index, duration in frames
*/
const unsigned char wolfspr_stand_left_anim[] = {
	0, 8, anim_end, 0
};

const unsigned char wolfspr_stand_up_anim[] = {
	1, 8, anim_end, 0
};

const unsigned char wolfspr_stand_down_anim[] = {
	2, 8, anim_end, 0
};

const unsigned char wolfspr_run_left_anim[] = {
	3, 8,
	4, 8,
	5, 8,
	6, 8, anim_end, 0
};

const unsigned char wolfspr_run_up_anim[] = {
	7, 8,
	8, 8,
	9, 8,
	10, 8, anim_end, 0
};

const unsigned char wolfspr_run_down_anim[] = {
	11, 8,
	12, 8,
	13, 8,
	14, 8, anim_end, 0
};