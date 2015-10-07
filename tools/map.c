#include "map.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

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

/*
void map_iterate(Map *map, MapIteratorCallback cb, void *data) {
  // TODO
}
*/
#define DEAD TerrainTypeEmpty
#define LIVE TerrainTypeWall
static uint8_t get_num_neighbours(Map* map, Point p) {
  uint8_t num_neighbours = 0;
  num_neighbours += map_get_terrain_at(map, Point(p.x + 1, p.y)) == LIVE ? 1 : 0;
  //num_neighbours += map_get_terrain_at(map, Point(p.x + 1, p.y + 1)) == LIVE ? 1 : 0;
  //num_neighbours += map_get_terrain_at(map, Point(p.x + 1, p.y - 1)) == LIVE ? 1 : 0;
  num_neighbours += map_get_terrain_at(map, Point(p.x, p.y + 1)) == LIVE ? 1 : 0;
  num_neighbours += map_get_terrain_at(map, Point(p.x, p.y - 1)) == LIVE ? 1 : 0;
  num_neighbours += map_get_terrain_at(map, Point(p.x - 1, p.y)) == LIVE ? 1 : 0;
  //num_neighbours += map_get_terrain_at(map, Point(p.x - 1, p.y + 1)) == LIVE ? 1 : 0;
  //num_neighbours += map_get_terrain_at(map, Point(p.x - 1, p.y - 1)) == LIVE ? 1 : 0;
  return num_neighbours;
}

static bool spawn(uint8_t state, uint8_t num_neighbours) {
  /* Nice contiguous blocks.
  if (state == DEAD) {
    return num_neighbours > 6;
  } else {
    return num_neighbours > 3;
  }
  */
  if (state == DEAD) {
    return num_neighbours > 2;
  } else {
    return num_neighbours > 1;
  }
}

void map_generate(Map *map, MapType type) {
  switch (type) {
    case MapTypeTest: ;
      Map *temp = map_create(MapTypeEmpty, MAP_WIDTH, MAP_HEIGHT);
      for (int i = 0; i < map->height; ++i) {
        for (int j = 0; j < map->width; ++j) {
          map->data[i][j] = rand() % 2 ? LIVE : DEAD;
        }
      }
      for (int i = 1; i < map->height - 1; ++i) {
        for (int j = 1; j < map->width - 1; ++j) {
          Point p = Point(j, i);
          temp->data[i][j] = spawn(map_get_terrain_at(map, p), get_num_neighbours(map, p)) ? LIVE : DEAD;
        }
      }
      for (int i = 1; i < map->height - 1; ++i) {
        for (int j = 1; j < map->width - 1; ++j) {
          Point p = Point(j, i);
          map->data[i][j] = spawn(map_get_terrain_at(temp, p), get_num_neighbours(temp, p)) ? LIVE : DEAD;
        }
      }
      for (int i = 1; i < map->height - 1; ++i) {
        for (int j = 1; j < map->width - 1; ++j) {
          Point p = Point(j, i);
          temp->data[i][j] = spawn(map_get_terrain_at(map, p), get_num_neighbours(map, p)) ? LIVE : DEAD;
        }
      }
      for (int i = 1; i < map->height - 1; ++i) {
        for (int j = 1; j < map->width - 1; ++j) {
          Point p = Point(j, i);
          map->data[i][j] = spawn(map_get_terrain_at(temp, p), get_num_neighbours(temp, p)) ? LIVE : DEAD;
        }
      }
      map_surround(map, TerrainTypeWall);
      map_destroy(temp);
      break;
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
