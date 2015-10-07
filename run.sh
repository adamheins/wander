#!/bin/sh
pebble build && pebble install --emulator $1 && pebble logs
