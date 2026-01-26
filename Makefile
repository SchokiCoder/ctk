# SPDX-License-Identifier: LGPL-2.1-only
# Copyright (C) 2025  Andy Frank Schoknecht

CC      :=cc
CFLAGS  :=-std=c99 -pedantic -Wall -Wextra -fsanitize=address,undefined -g

.PHONY: clean run

build: lib

clean:
	rm -f example *.so

libs: libCTK.so libSTR.so

libCTK.so: CTK.c CTK.h CTK_style.h
	$(CC) -o $@ -c -fPIC -shared $(CFLAGS) $<

libSTR.so: STR.c STR.h
	$(CC) -o $@ -c -fPIC -shared $(CFLAGS) $<

run: clean example
	./example

example: example.c libs
	$(CC) -o $@ $(CFLAGS) $$(pkg-config --cflags sdl3 sdl3-ttf) \
		$< $$(pkg-config --libs sdl3 sdl3-ttf) -lm -L . -lCTK -lSTR
