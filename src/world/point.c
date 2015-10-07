#include "point.h"

#include <pebble.h>

bool point_in(Point p, Point origin, uint16_t width, uint16_t height) {
  return p.x < origin.x || p.y < origin.y || p.x > origin.x + width - 1
      || p.y > origin.y + height - 1;
}

Point point_get_point_toward(Point origin, Direction dir, uint16_t dist) {
  Point p = { .x = origin.x, .y = origin.y };
  switch(dir) {
    case North:
      p.y += dist;
      break;
    case East:
      p.x += dist;
      break;
    case South:
      p.y -= dist;
      break;
    case West:
      p.x -= dist;
      break;
  }
  return p;
}
