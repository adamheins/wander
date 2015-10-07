#pragma once

// Identifiers for each item in the game.
typedef enum {
  ItemIDNull,
  ItemIDSword,
  ItemIDCoin,
  ItemIDGem,
  NumItemIDs,
} ItemID;

// Get the string label associated with the item ID.
const char *item_get_label(ItemID id);
