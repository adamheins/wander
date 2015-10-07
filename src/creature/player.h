#pragma once

#include "creature.h"
#include "../item/inventory.h"

#include <pebble.h>

// A Player is the character that the user controls.
typedef struct {
  Creature creature;
  Inventory inventory;
} Player;

// Create a new player, on the heap/
Player *player_create(Point location, uint8_t health, uint8_t strength);

// Free the memory associated with a player.
void player_destroy(Player *player);

// Get the current location of the player.
Point player_get_location(Player *player);

// Set the current location of the player.
void player_set_location(Player *player, Point location);
