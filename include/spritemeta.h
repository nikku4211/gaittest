#include <gbdk/metasprites.h>

#pragma bank 255

#ifndef _SPRITEMETA
#define _SPRITEMETA

BANKREF_EXTERN(wolfspr_meta)

extern const unsigned char wolfspr_tile_indexes[];

extern const metasprite_t wolfspr_stand_left[];
extern const metasprite_t wolfspr_stand_up[];
extern const metasprite_t wolfspr_stand_down[];

extern const metasprite_t wolfspr_run_left_0[];
extern const metasprite_t wolfspr_run_left_1[];
extern const metasprite_t wolfspr_run_left_2[];
extern const metasprite_t wolfspr_run_left_3[];

extern const metasprite_t wolfspr_run_up_0[];
extern const metasprite_t wolfspr_run_up_1[];
extern const metasprite_t wolfspr_run_up_2[];
extern const metasprite_t wolfspr_run_up_3[];

extern const metasprite_t wolfspr_run_down_0[];
extern const metasprite_t wolfspr_run_down_1[];
extern const metasprite_t wolfspr_run_down_2[];
extern const metasprite_t wolfspr_run_down_3[];

extern const metasprite_t* const wolfspr_meta[15];

extern const unsigned char wolfspr_stand_left_anim[];
extern const unsigned char wolfspr_stand_up_anim[];
extern const unsigned char wolfspr_stand_down_anim[];

extern const unsigned char wolfspr_run_left_anim[];
extern const unsigned char wolfspr_run_up_anim[];
extern const unsigned char wolfspr_run_down_anim[];

extern const unsigned char wolfspr_stand_left_tile_index[];
extern const unsigned char wolfspr_stand_up_tile_index[];
extern const unsigned char wolfspr_stand_down_tile_index[];

extern const unsigned char wolfspr_run_left_0_tile_index[];
extern const unsigned char wolfspr_run_left_1_tile_index[];
extern const unsigned char wolfspr_run_left_2_tile_index[];
extern const unsigned char wolfspr_run_left_3_tile_index[];

extern const unsigned char wolfspr_run_up_0_tile_index[];
extern const unsigned char wolfspr_run_up_1_tile_index[];
extern const unsigned char wolfspr_run_up_2_tile_index[];
extern const unsigned char wolfspr_run_up_3_tile_index[];

extern const unsigned char wolfspr_run_down_0_tile_index[];
extern const unsigned char wolfspr_run_down_1_tile_index[];
extern const unsigned char wolfspr_run_down_2_tile_index[];
extern const unsigned char wolfspr_run_down_3_tile_index[];

extern const unsigned char * const wolfspr_tile_pointers[15];

#endif