# SPDX-License-Identifier: LGPL-2.1-only
# Copyright (C) 2025  Andy Frank Schoknecht

CC     :=cc
CFLAGS :=-std=c99 -pedantic -Wall -Wextra -fsanitize=address,undefined -g

.PHONY: clean run

build: example

clean:
	rm -f example

run: clean example
	./example

example: example.c CTK.h
	$(CC) -o $@ $(CFLAGS) $$(pkg-config --cflags sdl3 sdl3-ttf) \
		$< $$(pkg-config --libs sdl3 sdl3-ttf) -lm
