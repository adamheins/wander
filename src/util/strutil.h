#pragma once

#include <pebble.h>

// Questionable implementation of strlcat.
size_t strlcat(char *dst, const char *src, size_t dstsize) {
  size_t i = 0, j = 0;
  while (dst[i]) {
    ++i;
  }
  while (src[j] && i < dstsize - 1) {
    dst[i++] = src[j++];
  }
  dst[i] = '\0';
  return i;
}
