#include <gbdk/platform.h>

#include "global.h"
#include "camera.h"

// current and old positions of the camera in pixels
int16_t camera_x, camera_y, old_camera_x, old_camera_y;
// current and old position of the map in tiles
uint8_t map_pos_x, map_pos_y, old_map_pos_x, old_map_pos_y;
// redraw flag, indicates that camera position was changed
uint8_t redraw;

void set_camera(void) NONBANKED {
	if (camera_y < 0) {
		camera_y = 0;
	} else if (camera_y > camera_max_y) {
		camera_y = camera_max_y;
	}
	if (camera_x < 0) {
		camera_x = 0;
	} else if (camera_x > camera_max_x) {
		camera_x = camera_max_x;
	}
	// update hardware scroll position
  move_bkg(SUBPIXELS_TO_PIXELS(camera_x), WRAP_SCROLL_Y(SUBPIXELS_TO_PIXELS(camera_y) + SCROLL_Y_OFFSET));
	// up or down
    map_pos_y = (uint8_t)(SUBPIXELS_TO_PIXELS(camera_y) >> 3u);
    if (map_pos_y != old_map_pos_y)
    { 
        if (camera_y < old_camera_y)
        {
            set_submap_indices(
                map_pos_x,
                update_row_top(map_pos_y),
                MIN(DEVICE_SCREEN_WIDTH + 1, bigmap_mapWidth-map_pos_x),
                1,
                bigmap_map_map,
                bigmap_mapWidth);
            set_submap_attributes(
                map_pos_x,
                update_row_top(map_pos_y),
                MIN(DEVICE_SCREEN_WIDTH + 1, bigmap_mapWidth-map_pos_x),
                1,
                bigmap_map_map_attributes,
                bigmap_mapWidth);
        }
        else
        {
            if ((bigmap_mapHeight - DEVICE_SCREEN_HEIGHT) > map_pos_y)
            {
                set_submap_indices(
                    map_pos_x,
                    update_row_bottom(map_pos_y),
                    MIN(DEVICE_SCREEN_WIDTH + 1, bigmap_mapWidth-map_pos_x),
                    1,
                    bigmap_map_map,
                    bigmap_mapWidth);
                set_submap_attributes(
                    map_pos_x,
                    update_row_bottom(map_pos_y),
                    MIN(DEVICE_SCREEN_WIDTH + 1, bigmap_mapWidth-map_pos_x),
                    1,
                    bigmap_map_map_attributes,
                    bigmap_mapWidth);
            }
        }
        old_map_pos_y = map_pos_y; 
    }
    // left or right
    map_pos_x = (uint8_t)(SUBPIXELS_TO_PIXELS(camera_x) >> 3u);
    if (map_pos_x != old_map_pos_x)
    {
        if (camera_x < old_camera_x)
        {
            set_submap_indices(
                update_column_left(map_pos_x),
                map_pos_y,
                1,
                MIN(DEVICE_SCREEN_HEIGHT + 1, bigmap_mapHeight - map_pos_y),
                bigmap_map_map,
                bigmap_mapWidth);
            set_submap_attributes(
                update_column_left(map_pos_x),
                map_pos_y,
                1,
                MIN(DEVICE_SCREEN_HEIGHT + 1, bigmap_mapHeight - map_pos_y),
                bigmap_map_map_attributes,
                bigmap_mapWidth);
        }
        else
        {
            if ((bigmap_mapWidth - DEVICE_SCREEN_WIDTH) > map_pos_x)
            {
                set_submap_indices(
                    update_column_right(map_pos_x),
                    map_pos_y,
                    1,
                    MIN(DEVICE_SCREEN_HEIGHT + 1, bigmap_mapHeight - map_pos_y),
                    bigmap_map_map,
                    bigmap_mapWidth);
                set_submap_attributes(
                    update_column_right(map_pos_x),
                    map_pos_y,
                    1,
                    MIN(DEVICE_SCREEN_HEIGHT + 1, bigmap_mapHeight - map_pos_y),
                    bigmap_map_map_attributes,
                    bigmap_mapWidth);
            }
        }
        old_map_pos_x = map_pos_x;
    }
    // set old camera position to current camera position
    old_camera_x = camera_x, old_camera_y = camera_y;
}

void init_camera(uint8_t x, uint8_t y) NONBANKED {
	// Set up tile data
  set_native_tile_data(0, bigmap_tiles_TILE_COUNT, bigmap_tiles_tiles);
	
	// Set up color palettes
	#if defined(SEGA)
			__WRITE_VDP_REG(VDP_R2, R2_MAP_0x3800);
			__WRITE_VDP_REG(VDP_R5, R5_SAT_0x3F00);
			set_palette(0, bigmap_tiles_PALETTE_COUNT, bigmap_tiles_palettes);
	#endif
	
	// Initial camera position in pixels set here.
	camera_x = PIXELS_TO_SUBPIXELS(x);
	camera_y = PIXELS_TO_SUBPIXELS(y);
	// Enforce map limits on initial camera position
	if (camera_x > camera_max_x) camera_x = camera_max_x;
	if (camera_y > camera_max_y) camera_y = camera_max_y;
	old_camera_x = camera_x; old_camera_y = camera_y;

	map_pos_x = SUBPIXELS_TO_PIXELS(camera_x) >> 3;
	map_pos_y = SUBPIXELS_TO_PIXELS(camera_y) >> 3;
	old_map_pos_x = old_map_pos_y = 255;
	move_bkg(SUBPIXELS_TO_PIXELS(camera_x), WRAP_SCROLL_Y(SUBPIXELS_TO_PIXELS(camera_y) + SCROLL_Y_OFFSET));
	
	// Draw the initial map view for the whole screen
	set_submap_indices(
			map_pos_x,
			map_pos_y,
			MIN(DEVICE_SCREEN_WIDTH + 1u, bigmap_mapWidth - map_pos_x),
			MIN(DEVICE_SCREEN_HEIGHT + 1u, bigmap_mapHeight - map_pos_y),
			bigmap_map_map,
			bigmap_mapWidth);

	set_submap_attributes(
			map_pos_x,
			map_pos_y,
			MIN(DEVICE_SCREEN_WIDTH + 1u, bigmap_mapWidth - map_pos_x),
			MIN(DEVICE_SCREEN_HEIGHT + 1u, bigmap_mapHeight - map_pos_y),
			bigmap_map_map_attributes,
			bigmap_mapWidth);

	redraw = FALSE;

	move_bkg(SUBPIXELS_TO_PIXELS(camera_x), WRAP_SCROLL_Y(SUBPIXELS_TO_PIXELS(camera_y) + SCROLL_Y_OFFSET));
}