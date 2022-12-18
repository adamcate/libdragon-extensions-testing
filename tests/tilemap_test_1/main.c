#include <libdragon.h>
#include "../../libdragon-extensions/include/mem_pool.h"
#include "../../libdragon-extensions/include/tiled.h"

static sprite_t *tileset;
static sprite_t *tileset2;

static const resolution_t display_resolution = {320, 240, false};

int main() {
	display_init(display_resolution, DEPTH_16_BPP, 3, GAMMA_CORRECT_DITHER, ANTIALIAS_RESAMPLE);

	dfs_init(DFS_DEFAULT_LOCATION);
	rdp_init();

	rdpq_mode_antialias(false);
	rdpq_mode_filter(FILTER_POINT);
	rdpq_mode_dithering(DITHER_SQUARE_SQUARE);

	controller_init();

	tileset = sprite_load("rom:/tileset_CI4.sprite");
	tileset2 = sprite_load("rom:/tileset.sprite");

	MemZone zone;
	mem_zone_init(&zone, 64 * 1024);

	Tiled *tilemap = tiled_init(&zone, tileset, "/maps/map_ci4.csv", new_size(20, 15),
								new_size_same(16));
	Tiled *tilemap2 = tiled_init(&zone, tileset2, "/maps/test_map.csv", new_size(20, 15),
								 new_size_same(16));

	Rect screen_rect = {.pos = new_position(0.f, 0.f),
						.size = new_size(display_resolution.width, display_resolution.height)};

	Position view_position = {.x = 0.f, .y = 0.f};

	while (1) {
		surface_t *disp = display_lock();
		if (!disp)
			continue;

		rdp_attach(disp);
		tiled_render_rdp(tilemap, screen_rect, view_position);
		tiled_render_rdp(tilemap2, screen_rect, view_position);

		rdp_detach_show(disp);
	}

	return 0;
}