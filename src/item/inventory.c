#include "inventory.h"

#include "item.h"
#include "../util/strutil.h"

#include <pebble.h>

// Check if an item is in the inventory.
bool inventory_contains(Inventory *inventory, ItemID item_id) {
  for (int i = 0; i < inventory->num_items; ++i) {
    if (inventory->items[i] == item_id) {
      return true;
    }
  }
  return false;
}

// Returns true if the inventory is full, false otherwise.
bool inventory_full(Inventory *inventory) {
  return inventory->num_items == MAX_INVENTORY_SIZE;
}

// Returns true if the inventory is empty, false otherwise.
bool inventory_empty(Inventory *inventory) {
  return inventory->num_items == 0;
}

// Add an item to the inventory.
bool inventory_add(Inventory *inventory, ItemID item_id) {
  if (inventory_full(inventory)) {
    return false;
  }
  inventory->items[inventory->num_items++] = item_id;
  return true;
}

// Remove an item from the inventory.
bool inventory_drop(Inventory *inventory, ItemID item_id) {
  for (int i = 0; i < inventory->num_items; ++i) {
    if (inventory->items[i] == item_id) {
      for (int j = i; j < inventory->num_items - 1; ++j) {
        inventory->items[j] = inventory->items[j + 1];
      }
      --inventory->num_items;
      return true;
    }
  }
  return false;
}

// Fills the buffer with a message about the contents of the inventory;
void inventory_look(Inventory *inventory, char *buffer, size_t buflen) {
  if (inventory_empty(inventory)) {
    strcpy(buffer, "Your inventory is empty.");
    return;
  }
  strcpy(buffer, "You have:\n");
  for (int i = 0; i < inventory->num_items; ++i) {
    strlcat(buffer, item_get_label(inventory->items[i]), buflen);
    strlcat(buffer, "\n", buflen);
  }
}
