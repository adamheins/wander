#include "action/look.h"
#include "action/move.h"
#include "creature/player.h"
#include "item/inventory.h"
#include "item/item.h"
#include "game/level.h"
#include "world/map.h"
#include "world/point.h"

#include <pebble.h>

static Level *level;

static Window *window;
static TextLayer *s_title_layer;
static TextLayer *s_text_layer;
static GBitmap *s_action_bitmap;
static GBitmap *s_redo_bitmap;

static ActionBarLayer *s_action_bar;
static ActionMenu *s_action_menu;
static ActionMenuLevel *s_root_level,
                       *s_move_level,
                       *s_look_level,
                       *s_craft_level,
                       *s_take_level,
                       *s_fight_level;

/*** Action menu ***/

static void init_action_menu() {
  s_root_level = action_menu_level_create(5);

  s_move_level = action_menu_level_create(4);
  s_look_level = action_menu_level_create(7);
  s_craft_level = action_menu_level_create(1);
  s_take_level = action_menu_level_create(1);
  s_fight_level = action_menu_level_create(1);

  action_menu_level_add_child(s_root_level, s_move_level, "Move");
  action_menu_level_add_child(s_root_level, s_look_level, "Look");
  action_menu_level_add_child(s_root_level, s_craft_level, "Craft");
  action_menu_level_add_child(s_root_level, s_take_level, "Take");
  action_menu_level_add_child(s_root_level, s_fight_level, "Fight");

  init_move_sub_menu(s_move_level);
  init_look_sub_menu(s_look_level);
}

/*** Click Config ***/

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  ActionMenuConfig config = (ActionMenuConfig) {
    .root_level = s_root_level,
    .context = level,
    .colors = {
      .background = GColorBlack,
      .foreground = GColorWhite,
    },
    .align = ActionMenuAlignTop,
  };
  s_action_menu = action_menu_open(&config);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (level->prev_action_callback) {
    level->prev_action_callback(s_action_menu, level->prev_action, level);
  } else {
    level_set_notification(level, "No action to repeat");
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

/*** Window handlers ***/

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_action_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ACTION);
  s_redo_bitmap = gbitmap_create_with_resource(RESOURCE_ID_REDO);

  // Action bar.
  s_action_bar = action_bar_layer_create();
  action_bar_layer_set_background_color(s_action_bar, GColorOxfordBlue);
  action_bar_layer_set_click_config_provider(s_action_bar, click_config_provider);
  action_bar_layer_set_icon(s_action_bar, BUTTON_ID_SELECT, s_action_bitmap);
  action_bar_layer_set_icon(s_action_bar, BUTTON_ID_DOWN, s_redo_bitmap);
  action_bar_layer_add_to_window(s_action_bar, window);

  // Title.
#ifdef PBL_DISP_SHAPE_ROUND
  s_title_layer = text_layer_create(GRect(20, 20, bounds.size.w - ACTION_BAR_WIDTH, 30));
#else
  s_title_layer = text_layer_create(GRect(0, 0, bounds.size.w - ACTION_BAR_WIDTH, 30));
#endif
  text_layer_set_text(s_title_layer, "Adamventure");
  text_layer_set_font(s_title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_color(s_title_layer, GColorWhite);
  text_layer_set_background_color(s_title_layer, GColorClear);
  text_layer_set_text_alignment(s_title_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(s_title_layer));

  // Notification text.
#ifdef PBL_DISP_SHAPE_ROUND
  s_text_layer = text_layer_create(GRect(20, 50, bounds.size.w - ACTION_BAR_WIDTH,
                                    bounds.size.h - 30));
#else
  s_text_layer = text_layer_create(GRect(0, 30, bounds.size.w - ACTION_BAR_WIDTH,
                                    bounds.size.h - 30));
#endif
  text_layer_set_text(s_text_layer, level->notification);
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_color(s_text_layer, GColorWhite);
  text_layer_set_background_color(s_text_layer, GColorClear);
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_title_layer);
  text_layer_destroy(s_text_layer);
  action_bar_layer_destroy(s_action_bar);
  action_menu_hierarchy_destroy(s_root_level, NULL, NULL);
  gbitmap_destroy(s_action_bitmap);
  gbitmap_destroy(s_redo_bitmap);
}

/*** App boilerplate ***/

static void init(void) {
  srand(time(NULL));

  window = window_create();
  window_set_background_color(window, GColorBlack);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  // Create the game level.
  level = (Level *)malloc(sizeof(Level));
  level_set_notification(level, "(Working title)");
  level->map = map_create(MapTypeEmpty, MAP_WIDTH, MAP_HEIGHT);
  level->player = player_create(Point(1, 1), 10, 10);
  inventory_add(&level->player->inventory, ItemIDSword);
  inventory_add(&level->player->inventory, ItemIDCoin);
  level->prev_action_callback = NULL;
  level->prev_action = NULL;

  const bool animated = true;
  window_stack_push(window, animated);
  init_action_menu();
}

static void deinit(void) {
  map_destroy(level->map);
  player_destroy(level->player);
  free(level);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
