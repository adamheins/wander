#pragma once

#include "item.h"

#include <pebble.h>

#define MAX_INVENTORY_SIZE 10

typedef struct {
  ItemID items[MAX_INVENTORY_SIZE];
  uint8_t num_items;
} Inventory;


// Check if an item is in the inventory.
bool inventory_contains(Inventory *inventory, ItemID item_id);

// Returns true if the inventory is full, false otherwise.
bool inventory_full(Inventory *inventory);

// Returns true if the inventory is empty, false otherwise.
bool inventory_empty(Inventory *inventory);

// Add an item to the inventory.
bool inventory_add(Inventory *inventory, ItemID item_id);

// Remove an item from the inventory.
bool inventory_drop(Inventory *inventory, ItemID item_id);

// Fills the buffer with a message about the contents of the inventory;
void inventory_look(Inventory *inventory, char *buffer, size_t buflen);
