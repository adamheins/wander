#include "level.h"

#include <pebble.h>

void level_set_notification(Level *level, const char *notification) {
  strcpy(level->notification, notification);
}
