/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#ifndef _CTK_H
#define _CTK_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#ifndef ARRLEN
#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

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

#if defined(__linux__)
#define FONTPATH "/usr/share/fonts/truetype/"
static const char *FONTNAMES[] = {
	"dejavu/DejaVuSans.ttf",
	"liberation/LiberationSans-Regular.ttf",
	"ubuntu/Ubuntu-Th.ttf",
	"noto/NotoSans-Regular.ttf",
};
#elif defined(_WIN32)
#define FONTPATH "C:\\Windows\\Fonts\\"
static const char *FONTNAMES[] = {
	"segoeui.ttf",
};

#elif defined(__APPLE__)
#define FONTPATH "/System/Library/Fonts/"
static const char *FONTNAMES[] = {
	"SFNS.ttf",
};
#else
#define FONTPATH "/usr/share/fonts/truetype/"
static const char *FONTNAMES[] = {
	"freefont/FreeSans.ttf",
};
#endif

struct CTK_Style {
	SDL_Color bg;
	SDL_Color fg;
	SDL_Color fg_disabled;
};

struct CTK_Menu {
	int                active;
	SDL_Window        *win;
	struct CTK_Style   style;
	int                redraw;

	void              (*on_quit)(struct CTK_Menu*, void*);
	void              *on_quit_data;

	int                count;
	int                enabled[CTK_MAX_WIDGETS];
	char               text[CTK_MAX_TEXTLEN][CTK_MAX_WIDGETS];
	int                visible[CTK_MAX_WIDGETS];
	SDL_FRect          rect[CTK_MAX_WIDGETS];
	SDL_Surface       *surface[CTK_MAX_WIDGETS];
	SDL_Texture       *texture[CTK_MAX_WIDGETS];
};

int
CTK_Menu_new(struct CTK_Menu *m,
             const char *title,
             const int winw,
             const int winh,
             const SDL_WindowFlags flags);

int
CTK_Menu_add(struct CTK_Menu *m);

void
CTK_Menu_render_text(struct CTK_Menu *m,
                     const int widget);

void
CTK_Menu_set_enabled(struct CTK_Menu *m,
                     const int widget,
                     const int enabled);

void
CTK_Menu_set_text(struct CTK_Menu *m,
                  const int widget,
                  const char *text);

void
CTK_Menu_set_text_and_resize(struct CTK_Menu *m,
                             const int widget,
                             const char *text);

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

/* appname = Name of application, duh.
 * appversion = Eg. "1.2.5".
 * appidentifier = Eg. "com.brave.Browser".
 * Upon error, returns NOT 0. Call SDL_GetError() for more information.
 */
int
CTK_init(const char *appname,
         const char *appversion,
         const char *appidentifier);

void
CTK_quit();

const struct CTK_Style CTK_Theme_TclTk = {
	.bg.r = 0xda,
	.bg.g = 0xda,
	.bg.b = 0xda,
	.bg.a = 0xff,

	.fg.r = 0x00,
	.fg.g = 0x00,
	.fg.b = 0x00,
	.fg.a = 0xff,

	.fg_disabled.r = 0xa4,
	.fg_disabled.g = 0xa4,
	.fg_disabled.b = 0xa4,
	.fg_disabled.a = 0xff,
};

#define CTK_DEFAULT_FONTSIZE 11
#define CTK_DEFAULT_THEME CTK_Theme_TclTk

static TTF_Font *CTK_font = NULL;

#ifdef CTK_IMPL

int
CTK_Menu_new(struct CTK_Menu *m,
             const char *title,
             const int winw,
             const int winh,
             const SDL_WindowFlags flags)
{
	SDL_Renderer *r;

	m->active = 1;
	m->count = 0;
	m->on_quit = NULL;
	m->on_quit_data = NULL;
	m->style = CTK_DEFAULT_THEME;
	m->redraw = 1;

	if (!SDL_CreateWindowAndRenderer(title, winw, winh, flags, &m->win, &r)) {
		m->active = 0;
		return 1;
	}

	if (!SDL_SetRenderLogicalPresentation(r, winw, winh,
	                                      SDL_LOGICAL_PRESENTATION_DISABLED)) {
		m->active = 0;
		return 2;
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
	m->surface[ret] = NULL;
	m->visible[ret] = 0;

	return ret;
}

int
CTK_Menu_add_label(struct CTK_Menu *m)
{
	int ret = m->count;

	ret = CTK_Menu_add(m);
	m->enabled[ret] = 1;
	m->visible[ret] = 1;

	return ret;
}

void
CTK_Menu_render_text(struct CTK_Menu *m,
                     const int widget)
{
	SDL_Color fg;
	SDL_Renderer *r;

	SDL_DestroySurface(m->surface[widget]);
	SDL_DestroyTexture(m->texture[widget]);

	r = SDL_GetRenderer(m->win);

	if (m->enabled[widget])
		fg = m->style.fg;
	else
		fg = m->style.fg_disabled;

	m->surface[widget] = TTF_RenderText_LCD(CTK_font,
	                                        m->text[widget],
	                                        0,
	                                        fg,
	                                        m->style.bg);
	m->texture[widget] = SDL_CreateTextureFromSurface(r, m->surface[widget]);
	m->redraw = 1;
}

void
CTK_Menu_set_enabled(struct CTK_Menu *m,
                     const int widget,
                     const int enabled)
{
	m->enabled[widget] = enabled;
	CTK_Menu_render_text(m, widget);
}

void
CTK_Menu_set_text(struct CTK_Menu *m,
                  const int widget,
                  const char *text)
{
	strncpy(m->text[widget], text, CTK_MAX_TEXTLEN - 1);
	CTK_Menu_render_text(m, widget);
}

void
CTK_Menu_set_text_and_resize(struct CTK_Menu *m,
                             const int widget,
                             const char *text)
{
	CTK_Menu_set_text(m, widget, text);
	m->rect[widget].w = m->surface[widget]->w;
	m->rect[widget].h = m->surface[widget]->h;
}

void
CTK_Menu_draw(struct CTK_Menu *m)
{
	int i;
	SDL_Renderer *r;

	if (!m->redraw)
		return;

	r = SDL_GetRenderer(m->win);

	SDL_SetRenderDrawColor(r,
	                       m->style.bg.r,
	                       m->style.bg.g,
	                       m->style.bg.b,
	                       m->style.bg.a);
	SDL_RenderClear(r);

	for (i = 0; i < m->count; i++) {
		if (!m->visible[i])
			continue;

		SDL_RenderTexture(r, m->texture[i], NULL, &m->rect[i]);
	}

	SDL_RenderPresent(r);
	m->redraw = 0;
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
	int i;

	for (i = 0; i < m->count; i++) {
		SDL_DestroySurface(m->surface[i]);
		SDL_DestroyTexture(m->texture[i]);
	}
	SDL_DestroyWindow(m->win);
}

int
CTK_init(const char *appname,
         const char *appversion,
         const char *appidentifier)
{
	long unsigned i;
	const int pathlen = 256;
	char path[pathlen];

	if (!SDL_SetAppMetadata(appname, appversion, appidentifier))
		return 1;

	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO))
		return 2;

	if (!TTF_Init())
		return 3;

	for (i = 0; i < ARRLEN(FONTNAMES); i++) {
		snprintf(path, pathlen - 1, "%s%s", FONTPATH, FONTNAMES[i]);
		CTK_font = TTF_OpenFont(path, CTK_DEFAULT_FONTSIZE);
		if (NULL != CTK_font)
			break;
	}
	if (NULL == CTK_font)
		return 4;

	return 0;
}

void
CTK_quit()
{
	TTF_CloseFont(CTK_font);
	TTF_Quit();
	SDL_Quit();
}

#endif /* CTK_IMPL */

#endif /* _CTK_H */
