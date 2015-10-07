#pragma once

#include "point.h"

#include <pebble.h>

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

typedef struct {
  uint16_t width;
  uint16_t height;
  uint8_t data[MAP_WIDTH][MAP_HEIGHT];
} Map;

// Different types of terrain on the map.
typedef enum {
  TerrainTypeNull,
  TerrainTypeEmpty,
  TerrainTypeWall,
  /* TerrainValueRock,
  TerrainValueBush,
  TerrainValueTree, */
  NumTerrainTypes,
} TerrainType;

// Different types of map.
typedef enum {
  MapTypeEmpty,
  MapTypeTest,
  /* MapTypePlains,
  MapTypeForest, */
  NumMapTypes,
} MapType;

// Generate the map.
void map_generate(Map *map, MapType type);

// Create a new map.
Map *map_create(MapType type, uint16_t width, uint16_t height);

// Destroy the map.
void map_destroy(Map *map);

// Get the terrain type at a certain location on the map.
TerrainType map_get_terrain_at(Map *map, Point p);
