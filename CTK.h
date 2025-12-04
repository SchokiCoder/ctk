/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#ifndef _CTK_H
#define _CTK_H

#include <SDL3/SDL.h>
#include <string.h>

#ifndef CTK_MAX_TEXTLEN
#define CTK_MAX_TEXTLEN 64
#endif

#ifndef CTK_MAX_WIDGETS
#define CTK_MAX_WIDGETS 64
#endif

#ifndef CTK_MAX_TICKRATE
#define CTK_MAX_TICKRATE 60
#endif

#define CTK_VERSION "0.0.0"

struct CTK_Style {
	SDL_Color bg;
	SDL_Color fg;
};

struct CTK_Menu {
	int                active;
	SDL_Window        *win;
	struct CTK_Style  style;

	void               (*on_quit)(struct CTK_Menu*, void*);
	void              *on_quit_data;

	int                 count;
	int                 enabled[CTK_MAX_WIDGETS];
	char                text[CTK_MAX_TEXTLEN][CTK_MAX_WIDGETS];
	int                 visible[CTK_MAX_WIDGETS];
	SDL_Rect            rect[CTK_MAX_WIDGETS];
};

int
CTK_Menu_new(struct CTK_Menu *m,
             const char *title,
             const int winw,
             const int winh,
             const SDL_WindowFlags flags);

void
CTK_Menu_draw(struct CTK_Menu *m);

void
CTK_Menu_tick(struct CTK_Menu *m);

/* Alternatively, if more control is needed,
 * you can call CTK_Menu_draw and CTK_Menu_tick yourself.
 */
void
CTK_Menu_mainloop(struct CTK_Menu *m);

void
CTK_Menu_destroy(struct CTK_Menu *m);

int
CTK_Init();

void
CTK_Quit();

const struct CTK_Style CTK_Theme_TclTk = {
	.bg.r = 0xda,
	.bg.g = 0xda,
	.bg.b = 0xda,
	.bg.a = 0xff,

	.fg.r = 0x00,
	.fg.g = 0x00,
	.fg.b = 0x00,
	.fg.a = 0xff,
};

#define CTK_DEFAULT_THEME CTK_Theme_TclTk

#ifdef CTK_IMPL

int
CTK_Menu_new(struct CTK_Menu *m,
             const char *title,
             const int winw,
             const int winh,
             const SDL_WindowFlags flags)
{
	m->active = 1;
	m->count = 0;
	m->on_quit = NULL;
	m->on_quit_data = NULL;
	m->style = CTK_DEFAULT_THEME;

	m->win = SDL_CreateWindow(title, winw, winh, flags);
	if (NULL == m->win) {
		m->active = 0;
		return 1;
	}

	return 0;
}

int
CTK_Menu_add(struct CTK_Menu *m)
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
CTK_Menu_draw(struct CTK_Menu *m)
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
CTK_Menu_tick(struct CTK_Menu *m)
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
CTK_Menu_mainloop(struct CTK_Menu *m)
{
	Uint64 now, last;

	while (m->active) {
		SDL_WaitEvent(NULL);

		now = SDL_GetTicks();
		if (now - last > 1000 / CTK_MAX_TICKRATE) {
			last = now;

			CTK_Menu_tick(m);
			CTK_Menu_draw(m);
		}
	}
}

void
CTK_Menu_destroy(struct CTK_Menu *m)
{
	SDL_DestroyWindow(m->win);
}

int
CTK_Init(const char *appname,
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
CTK_Quit()
{
	SDL_Quit();
}

#endif /* CTK_IMPL */

#endif /* _CTK_H */
