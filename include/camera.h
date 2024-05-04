#ifndef _CAMERA
#define _CAMERA

#include <gbdk/platform.h>

//level tileset
#include "res/map/bigmap_tiles.h"
//level tilemap
#include "res/map/bigmap_map.h"
#define bigmap_mapWidth (bigmap_map_WIDTH/bigmap_map_TILE_W)
#define bigmap_mapHeight (bigmap_map_HEIGHT/bigmap_map_TILE_H)

#if defined(SEGA)
  #define WRAP_SCROLL_Y(y) ((y) % 224u)
  // For SMS, artifacts are already invisible as screen buffer size is larger than screen size
  #define SCROLL_Y_OFFSET 0
#elif defined(NINTENDO)
  #define WRAP_SCROLL_Y(y) y
  // For GB, artifacts are already invisible as screen buffer size is larger than screen size
  #define SCROLL_Y_OFFSET 0
#else
  #define WRAP_SCROLL_Y(y) ((y) % 240u)
  // For other systems assume height of 240 and adjust Y-scroll 4 pixels down to partly hide artifacts in NTSC overscan
  #define SCROLL_Y_OFFSET 4
#endif

#if defined(SEGA)
// The "compatibility" function set_bkg_submap (=set_tile_submap_compat)
// expect maps with only 1-byte-per-tile, only containing either a tile
// index or an attribute.
// But png2asset can only produce 2-byte-per-tile maps where both tile index
// and attribute are consecutive when the -map_attributes parameter is used.
// To work around this, we redefine those functions for SMS/GG only, so
// they work like this:
// * Use set_tile_submap for tile indices, to read/write both bytes of map
// * Make set_submap_attributes a no-op, as attributes were already set
#define set_submap_indices(x, y, w, h, map, map_w) set_tile_submap(x, y, w, h, map_w, map)
#define set_submap_attributes(x, y, w, h, map, map_w)
#else
#define set_submap_indices(x, y, w, h, map, map_w) set_bkg_submap(x, y, w, h, map, map_w)
#define set_submap_attributes(x, y, w, h, map, map_w) set_bkg_submap_attributes(x, y, w, h, map, map_w)
#endif

#define MIN(A,B) ((A)<(B)?(A):(B))

inline uint8_t update_column_left(uint8_t map_pos_x)
{
#if (DEVICE_SCREEN_BUFFER_WIDTH == DEVICE_SCREEN_WIDTH)
    return map_pos_x + 1;
#else
    return map_pos_x;
#endif
}

inline uint8_t update_column_right(uint8_t map_pos_x)
{
    return map_pos_x + DEVICE_SCREEN_WIDTH;
}

inline uint8_t update_row_top(uint8_t map_pos_y)
{
#if (DEVICE_SCREEN_BUFFER_HEIGHT == DEVICE_SCREEN_HEIGHT)
    return map_pos_y + 1;
#else
    return map_pos_y;
#endif
}

inline uint8_t update_row_bottom(uint8_t map_pos_y)
{
    return map_pos_y + DEVICE_SCREEN_HEIGHT;
}

void set_camera(void) NONBANKED;

void init_camera(uint8_t x, uint8_t y) NONBANKED;
#endif