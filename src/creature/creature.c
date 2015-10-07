#include "creature.h"

#include "../world/direction.h"
#include "../world/point.h"

#include <pebble.h>

// Initialize the creature.
void creature_init(Creature *creature, Point location, uint8_t health, uint8_t strength,
                   CreatureType type) {
  creature->location = location;
  creature->health = health;
  creature->strength = strength;
  creature->type = type;
}

// Create a new creature.
Creature *creature_create(Point location, uint8_t health, uint8_t strength, CreatureType type) {
  Creature *creature = (Creature *)malloc(sizeof(Creature));
  creature_init(creature, location, health, strength, type);
  return creature;
}

// Free the memory associated with this creature.
void creature_destroy(Creature *creature) {
  free(creature);
  creature = NULL;
}
