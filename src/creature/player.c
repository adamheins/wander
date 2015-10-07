#include "player.h"

#include "creature.h"
#include "../world/point.h"

#include <pebble.h>

void player_init(Player *player, Point location, uint8_t health, uint8_t strength) {
  creature_init(&player->creature, location, health, strength, CreatureTypePlayer);
}

Player *player_create(Point location, uint8_t health, uint8_t strength) {
  Player *player = (Player *)malloc(sizeof(Player));
  player_init(player, location, health, strength);
  return player;
}

void player_destroy(Player *player) {
  free(player);
  player = NULL;
}

Point player_get_location(Player *player) {
  return player->creature.location;
}

void player_set_location(Player *player, Point location) {
  player->creature.location = location;
}
