#pragma once

#include "direction.h"

#include <pebble.h>

#define Point(x, y) ((Point){(x), (y)})

// A generic point structure.
typedef struct {
  uint16_t x;
  uint16_t y;
} Point;

// Check if Point p is contained in the box defined by the origin and a width and height.
bool point_in(Point p, Point origin, uint16_t width, uint16_t height);

// Get the point that is dist units away from origin in the direction dir.
Point point_get_point_toward(Point origin, Direction dir, uint16_t dist);
