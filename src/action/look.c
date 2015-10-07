#include "look.h"

#include "../creature/player.h"
#include "../game/level.h"
#include "../util/error.h"
#include "../world/direction.h"
#include "../world/map.h"
#include "../world/point.h"

#include <pebble.h>

typedef struct {
  LookDirection dir;
} LookActionData;

static void look_action_callback(ActionMenu *action_menu, const ActionMenuItem *action,
                                 void *context) {
  Level *level = (Level *)context;
  level->prev_action_callback = look_action_callback;
  level->prev_action = (ActionMenuItem *)action;
  Player *player = level->player;
  Map *map = level->map;

  LookDirection dir = ((LookActionData *)action_menu_item_get_action_data(action))->dir;
  switch (dir) {
    case LookDirectionNorth:
    case LookDirectionEast:
    case LookDirectionSouth:
    case LookDirectionWest: ;
      Point p = point_get_point_toward(player_get_location(player), dir, 1);
      TerrainType terrain = map_get_terrain_at(map, p);
      switch (terrain) {
        case TerrainTypeEmpty:
          level_set_notification(level, "You see empty plains.");
          break;
        case TerrainTypeWall:
          level_set_notification(level, "You see an impassable wall.");
          break;
        default:
          level_set_notification(level, GENERIC_ERROR_MESSAGE);
      }
      break;
    case LookDirectionUp:
      level_set_notification(level, "You see a clear sky.");
      break;
    case LookDirectionDown:
      level_set_notification(level, "You see hard-packed dirt.");
      break;
    case LookDirectionInventory:
      inventory_look(&player->inventory, level->notification, MAX_NOTIFICATION_LENGTH);
      break;
  }
  action_menu_close(action_menu, false);
}

// Add a look action to the sub-menu.
static void add_look_action(ActionMenuLevel *look_level, const char *label, LookDirection dir) {
  LookActionData *data = (LookActionData *)malloc(sizeof(LookActionData));
  data->dir = dir;
  action_menu_level_add_action(look_level, label, look_action_callback, data);
}

void init_look_sub_menu(ActionMenuLevel *look_level) {
  add_look_action(look_level, "North", LookDirectionNorth);
  add_look_action(look_level, "East", LookDirectionEast);
  add_look_action(look_level, "South", LookDirectionSouth);
  add_look_action(look_level, "West", LookDirectionWest);
  add_look_action(look_level, "Down", LookDirectionDown);
  add_look_action(look_level, "Up", LookDirectionUp);
  add_look_action(look_level, "Inventory", LookDirectionInventory);
}
