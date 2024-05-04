#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#pragma bank 255

BANKREF(wolfspr_meta)

const metasprite_t wolfspr_stand_left[] = {
	METASPR_ITEM( -16,  -16, 0, 0), METASPR_ITEM( -16,   -8, 2, 0), METASPR_ITEM( -16,  0, 4, 0), METASPR_ITEM( -16,  8, 6, 0), 
	METASPR_ITEM( 0,  -16, 32, 0), METASPR_ITEM( 0,   -8, 34, 0), METASPR_ITEM( 0,  0, 36, 0), METASPR_ITEM( 0,  8, 38, 0), 
	METASPR_TERM
};

const metasprite_t* const wolfspr_meta[1] = {
	wolfspr_stand_left
};