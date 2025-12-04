# SPDX-License-Identifier: LGPL-2.1-only
# Copyright (C) 2025  Andy Frank Schoknecht

CC     :=cc
CFLAGS :=-std=c99 -pedantic -Wall -Wextra -fsanitize=address,undefined

.PHONY: run

run: example
	./$<

example: example.c SHTK.h
	$(CC) -o $@ $(CFLAGS) $$(pkg-config --cflags sdl3) \
		$< $$(pkg-config --libs sdl3)
