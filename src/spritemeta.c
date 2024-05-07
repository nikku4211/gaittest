#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#pragma bank 255

#define anim_end 255

BANKREF(wolfspr_meta)

const metasprite_t wolfspr_stand_left[] = {
	METASPR_ITEM(0, 0,  0, 0), METASPR_ITEM(0, 8,  2, 0), METASPR_ITEM(0, 8,  4, 0), METASPR_ITEM(0, 8, 6, 0), 
	METASPR_ITEM(16, -16, 32, 0), METASPR_ITEM(0, 8, 34, 0), METASPR_ITEM(0, 8, 36, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_stand_up[] = {
	METASPR_ITEM(0, 12, 94, 0), METASPR_ITEM(16, 0, 96, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_stand_down[] = {
	METASPR_ITEM(16, 12, 98, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_0[] = {
	METASPR_ITEM(0, 0,  0, 0), METASPR_ITEM(0, 8,  8, 0), METASPR_ITEM(0, 8,  4, 0), METASPR_ITEM(0, 8, 10, 0), METASPR_ITEM(0, 8, 12, 0),
	METASPR_ITEM(16, -25, 38, 0), METASPR_ITEM(0, 8, 40, 0), METASPR_ITEM(0, 8, 42, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_1[] = {
	METASPR_ITEM(1, 0,  0, 0), METASPR_ITEM(0, 8, 14, 0), METASPR_ITEM(0, 8, 16, 0), METASPR_ITEM(12, 8, 18, 0), METASPR_ITEM(-12, 8, 20, 0),
	METASPR_ITEM(16, -32, 44, 0), METASPR_ITEM(0, 8, 46, 0), METASPR_ITEM(0, 8, 48, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_2[] = {
	METASPR_ITEM(2, 0,  0, 0), METASPR_ITEM(4, 8, 22, 0), METASPR_ITEM(-1, 8, 62, 0), METASPR_ITEM(0, 8, 64, 0), METASPR_ITEM(4, 8, 66, 0),
	METASPR_ITEM(11, -32, 50, 0), METASPR_ITEM(0, 8, 52, 0), METASPR_ITEM(0, 16, 54, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_left_3[] = {
	METASPR_ITEM(1, 0, 0, 0), METASPR_ITEM(0, 8, 24, 0), METASPR_ITEM(12, 8, 26, 0), METASPR_ITEM(-3, 8, 82, 0), METASPR_ITEM(0, 8, 84, 0),
	METASPR_ITEM(7, -24, 86, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_0[] = {
	METASPR_ITEM(0, 12, 68, 0), METASPR_ITEM(16, 0, 88, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_1[] = {
	METASPR_ITEM(0, 12, 70, 0), METASPR_ITEM(16, 0, 58, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_2[] = {
	METASPR_ITEM(0, 12, 72, 0), METASPR_ITEM(16, 0, 60, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_up_3[] = {
	METASPR_ITEM(0, 12, 74, 0), METASPR_ITEM(16, 0, 28, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_0[] = {
	METASPR_ITEM(16, 12, 76, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_1[] = {
	METASPR_ITEM(16, 12, 30, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_2[] = {
	METASPR_ITEM(0, 12, 78, 0), METASPR_ITEM(16, 0, 90, 0),
	METASPR_TERM
};

const metasprite_t wolfspr_run_down_3[] = {
	METASPR_ITEM(0, 12, 80, 0), METASPR_ITEM(16, 0, 92, 0),
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