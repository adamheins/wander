#include "move.h"

#include "../creature/player.h"
#include "../game/level.h"
#include "../util/error.h"
#include "../world/direction.h"
#include "../world/map.h"
#include "../world/point.h"

#include <pebble.h>

typedef struct {
  Direction dir;
} MoveActionData;

static void move_player(Level *level, Direction dir, const char *success_notification) {
  Player *player = level->player;
  Map *map = level->map;
  Point p = point_get_point_toward(player_get_location(player), dir, 1);

  if (map_get_terrain_at(map, p) == TerrainTypeEmpty) {
    player_set_location(player, p);
    level_set_notification(level, success_notification);
  } else {
    level_set_notification(level, "You can't go that way.");
  }
}

static void move_action_callback(ActionMenu *action_menu, const ActionMenuItem *action, void *context) {
  Level *level = (Level *)context;
  level->prev_action_callback = move_action_callback;
  level->prev_action = (ActionMenuItem *)action;
  Direction dir = ((MoveActionData *)action_menu_item_get_action_data(action))->dir;

  switch (dir) {
    case North:
      move_player(level, North, "You move north.");
      break;
    case East:
      move_player(level, East, "You move east.");
      break;
    case South:
      move_player(level, South, "You move south.");
      break;
    case West:
      move_player(level, West, "You move west.");
      break;
    default:
      level_set_notification(level, GENERIC_ERROR_MESSAGE);
  }
  action_menu_close(action_menu, false);
}

static void add_move_action(ActionMenuLevel *move_level, const char *label, Direction dir) {
  MoveActionData *data = (MoveActionData *)malloc(sizeof(MoveActionData));
  data->dir = dir;
  action_menu_level_add_action(move_level, label, move_action_callback, data);
}

void init_move_sub_menu(ActionMenuLevel *move_level) {
  add_move_action(move_level, "North", North);
  add_move_action(move_level, "East", East);
  add_move_action(move_level, "South", South);
  add_move_action(move_level, "West", West);
}
