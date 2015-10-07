#include "map.h"

#include <pebble.h>

// Surround the map with a one-tile width border.
static void map_surround(Map *map, TerrainType terrain) {
  for (int i = 0; i < map->width; ++i) {
    map->data[0][i] = terrain;
    map->data[map->height - 1][i] = terrain;
  }
  for (int i = 0; i < map->height; ++i) {
    map->data[i][0] = terrain;
    map->data[i][map->width - 1] = terrain;
  }
}

void map_generate(Map *map, MapType type) {
  switch (type) {
    case MapTypeEmpty:
    default:
      for (int i = 1; i < map->height - 1; ++i) {
        for (int j = 1; j < map->width - 1; ++j) {
          map->data[i][j] = TerrainTypeEmpty;
        }
      }
      map_surround(map, TerrainTypeWall);
      break;
  }
}

Map *map_create(MapType type, uint16_t width, uint16_t height) {
  Map *map = (Map *)malloc(sizeof(Map));
  map->width = width;
  map->height = height;
  map_generate(map, type);
  return map;
}

void map_destroy(Map *map) {
  free(map);
  map = NULL;
}

TerrainType map_get_terrain_at(Map *map, Point p) {
  return map->data[p.y][p.x];
}
