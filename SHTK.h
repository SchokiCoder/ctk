/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#ifndef _SHTK_H
#define _SHTK_H

#include <SDL3/SDL.h>
#include <string.h>

#ifndef SHTK_MAX_TEXTLEN
#define SHTK_MAX_TEXTLEN 64
#endif

#ifndef SHTK_MAX_WIDGETS
#define SHTK_MAX_WIDGETS 64
#endif

#ifndef SHTK_MAX_TICKRATE
#define SHTK_MAX_TICKRATE 60
#endif

#define SHTK_VERSION "0.0.0"

struct SHTK_Style {
	SDL_Color bg;
	SDL_Color fg;
};

struct SHTK_Menu {
	int                active;
	SDL_Window        *win;
	struct SHTK_Style  style;

	void               (*on_quit)(struct SHTK_Menu*, void*);
	void              *on_quit_data;

	int                 count;
	int                 enabled[SHTK_MAX_WIDGETS];
	char                text[SHTK_MAX_TEXTLEN][SHTK_MAX_WIDGETS];
	int                 visible[SHTK_MAX_WIDGETS];
	SDL_Rect            rect[SHTK_MAX_WIDGETS];
};

int
SHTK_Menu_new(struct SHTK_Menu *m,
              const char *title,
              const int winw,
              const int winh,
              const SDL_WindowFlags flags);

void
SHTK_Menu_draw(struct SHTK_Menu *m);

void
SHTK_Menu_tick(struct SHTK_Menu *m);

/* Alternatively, if more control is needed,
 * you can call SHTK_Menu_draw and SHTK_Menu_tick yourself.
 */
void
SHTK_Menu_mainloop(struct SHTK_Menu *m);

void
SHTK_Menu_destroy(struct SHTK_Menu *m);

int
SHTK_Init();

void
SHTK_Quit();

const struct SHTK_Style SHTK_Theme_TclTk = {
	.bg.r = 0xda,
	.bg.g = 0xda,
	.bg.b = 0xda,
	.bg.a = 0xff,

	.fg.r = 0x00,
	.fg.g = 0x00,
	.fg.b = 0x00,
	.fg.a = 0xff,
};

#define SHTK_DEFAULT_THEME SHTK_Theme_TclTk

#ifdef SHTK_IMPL

int
SHTK_Menu_new(struct SHTK_Menu *m,
              const char *title,
              const int winw,
              const int winh,
              const SDL_WindowFlags flags)
{
	m->active = 1;
	m->count = 0;
	m->on_quit = NULL;
	m->on_quit_data = NULL;
	m->style = SHTK_DEFAULT_THEME;

	m->win = SDL_CreateWindow(title, winw, winh, flags);
	if (NULL == m->win) {
		m->active = 0;
		return 1;
	}

	return 0;
}

int
SHTK_Menu_add(struct SHTK_Menu *m)
{
	int ret = m->count;

	m->count++;
	m->enabled[ret] = 0;
	m->text[ret][0] = '\0';
	m->rect[ret].x = 0;
	m->rect[ret].y = 0;
	m->rect[ret].w = 0;
	m->rect[ret].h = 0;
	m->visible[ret] = 0;

	return ret;
}

void
SHTK_Menu_draw(struct SHTK_Menu *m)
{
	int i;
	SDL_Renderer *r;
	SDL_Surface *s;

	r = SDL_GetRenderer(m->win);
	s = SDL_GetWindowSurface(m->win);

	SDL_SetRenderDrawColor(r,
	                       m->style.bg.r,
	                       m->style.bg.g,
	                       m->style.bg.b,
	                       m->style.bg.a);
	SDL_RenderClear(r);

	for (i= 0; i < m->count; i++) {
		SDL_FillSurfaceRect(s, &m->rect[i], 0xff00ffff);
	}

	SDL_RenderPresent(r);
}

void
SHTK_Menu_tick(struct SHTK_Menu *m)
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EVENT_QUIT:
			if (NULL != m->on_quit) {
				m->on_quit(m, m->on_quit_data);
			}
			break;
		}
	}
}

void
SHTK_Menu_mainloop(struct SHTK_Menu *m)
{
	Uint64 now, last;

	while (m->active) {
		SDL_WaitEvent(NULL);

		now = SDL_GetTicks();
		if (now - last > 1000 / SHTK_MAX_TICKRATE) {
			last = now;

			SHTK_Menu_tick(m);
			SHTK_Menu_draw(m);
		}
	}
}

void
SHTK_Menu_destroy(struct SHTK_Menu *m)
{
	SDL_DestroyWindow(m->win);
}

int
SHTK_Init(const char *appname,
          const char *appversion,
          const char *appidentifier)
{
	if (!SDL_SetAppMetadata(appname, appversion, appidentifier))
		return 1;

	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO))
		return 2;

	return 0;
}

void
SHTK_Quit()
{
	SDL_Quit();
}

#endif /* SHTK_IMPL */

#endif /* _SHTK_H */
