#pragma once

#include "../world/direction.h"
#include "../world/point.h"

#include <pebble.h>

// Different types of creatures.
typedef enum {
  CreatureTypePlayer,
  CreatureTypeMontster,
  NumCreatureTypes,
} CreatureType;

// A creature is a being, such as a player or a monster.
typedef struct {
  Point location;
  uint8_t health;
  uint8_t strength;
  CreatureType type;
} Creature;

// Initialize an existing creature.
void creature_init(Creature *creature, Point location, uint8_t health, uint8_t strength,
                   CreatureType type);

// Create a new creature.
Creature *creature_create(Point location, uint8_t health, uint8_t strength, CreatureType type);

// Destroy a creature.
void creature_destroy(Creature *creature);
