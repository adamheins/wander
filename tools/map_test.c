#include <stdio.h>
#include <time.h>

#include "map.h"

static const char terrain_chars[] = { ' ', '.', '#' };

void draw_map(Map *map) {
  for (int i = 0; i < map->height; ++i) {
    for (int j = 0; j < map->width; ++j) {
      printf("%c", terrain_chars[map->data[i][j]]);
    }
    printf("\n");
  }
}

int main() {
  srand(time(NULL));
  Map *map = map_create(MapTypeTest, MAP_WIDTH, MAP_HEIGHT);
  draw_map(map);
  map_destroy(map);
  return 0;
}
