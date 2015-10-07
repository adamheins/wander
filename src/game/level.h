#pragma once

#include "../creature/player.h"
#include "../world/map.h"

#include <pebble.h>

#define MAX_NOTIFICATION_LENGTH 140

// Contains the information for the current state of the game level.
typedef struct {
  Map *map;
  Player *player;
  char notification[MAX_NOTIFICATION_LENGTH];
  ActionMenuPerformActionCb prev_action_callback;
  ActionMenuItem *prev_action;
} Level;

// Set the current notification.
void level_set_notification(Level *level, const char *notification);
