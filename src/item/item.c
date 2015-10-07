#include "item.h"

static const char *item_labels[] = {
  "NULL",
  "Sword",
  "Coin",
  "Gem",
};

const char *item_get_label(ItemID id) {
  return item_labels[id];
}
