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
	SDL_Color bg_button;
	SDL_Color bg_entry;
	SDL_Color bg_label;
	SDL_Color bg_widget;
	SDL_Color border;
	SDL_Color fg;
	SDL_Color fg_disabled;
};

struct CTK_Menu {
	bool               active;
	SDL_Window        *win;
	struct CTK_Style   style;
	bool               redraw;

	void              (*on_quit)(struct CTK_Menu*, void*);
	void              *on_quit_data;

	int                count;
	SDL_Color         *bg[CTK_MAX_WIDGETS];
	bool               border[CTK_MAX_WIDGETS];
	int                cursor[CTK_MAX_WIDGETS];
	bool               enabled[CTK_MAX_WIDGETS];
	int                scroll[CTK_MAX_WIDGETS];
	char               text[CTK_MAX_TEXTLEN][CTK_MAX_WIDGETS];
	bool               visible[CTK_MAX_WIDGETS];
	SDL_FRect          rect[CTK_MAX_WIDGETS];
	SDL_Texture       *texture[CTK_MAX_WIDGETS];
	void              (*on_click[CTK_MAX_WIDGETS])(struct CTK_Menu*,
	                                               const int,
	                                               void*);
	void              *on_click_data[CTK_MAX_WIDGETS];
};

int
CTK_AddButton(struct CTK_Menu *m);

int
CTK_AddEntry(struct CTK_Menu *m);

int
CTK_AddLabel(struct CTK_Menu *m);

int
CTK_AddWidget(struct CTK_Menu *m);

/* m = Menu to initialize.
 * title = Used as window title.
 * winw = Window width.
 * winh = Window height.
 * flags = SDL window flags. May be 0 to use defaults.
 * Returns true on success or false on failure.
 * Call SDL_GetError() for more information.
 */
bool
CTK_CreateMenu(struct CTK_Menu *m,
               const char *title,
               const int winw,
               const int winh,
               const SDL_WindowFlags flags);

void
CTK_CreateWidgetTexture(struct CTK_Menu *m,
                        const int widget);

void
CTK_DestroyMenu(struct CTK_Menu *m);

void
CTK_DrawMenu(struct CTK_Menu *m);

/* appname = Name of application, duh.
 * appversion = Eg. "1.2.5".
 * appidentifier = Eg. "com.brave.Browser".
 * Returns true on success or false on failure.
 * Call SDL_GetError() for more information.
 */
bool
CTK_Init(const char *appname,
         const char *appversion,
         const char *appidentifier);

/* Alternatively, if more control is needed,
 * you can call CTK_DrawMenu and CTK_TickMenu yourself.
 */
void
CTK_MainloopMenu(struct CTK_Menu *m);

void
CTK_MenuDefaultOnQuit(struct CTK_Menu *m,
                      void            *dummy);

void
CTK_SetWidgetEnabled(struct CTK_Menu *m,
                     const int widget,
                     const bool enabled);

void
CTK_SetWidgetText(struct CTK_Menu *m,
                  const int widget,
                  const char *text);

void
CTK_SetWidgetTextAndResize(struct CTK_Menu *m,
                           const int widget,
                           const char *text);

void
CTK_TickMenu(struct CTK_Menu *m);

void
CTK_Quit();

const struct CTK_Style CTK_Theme_TclTk = {
	.bg.r = 0xda,
	.bg.g = 0xda,
	.bg.b = 0xda,
	.bg.a = 0xff,

	.bg_button.r = 0xda,
	.bg_button.g = 0xda,
	.bg_button.b = 0xda,
	.bg_button.a = 0xff,

	.bg_entry.r = 0xff,
	.bg_entry.g = 0xff,
	.bg_entry.b = 0xff,
	.bg_entry.a = 0xff,

	.bg_label.r = 0xda,
	.bg_label.g = 0xda,
	.bg_label.b = 0xda,
	.bg_label.a = 0xff,

	.bg_widget.r = 0x00,
	.bg_widget.g = 0x00,
	.bg_widget.b = 0x00,
	.bg_widget.a = 0x00,

	.border.r = 0x83,
	.border.g = 0x83,
	.border.b = 0x83,
	.border.a = 0xff,

	.fg.r = 0x00,
	.fg.g = 0x00,
	.fg.b = 0x00,
	.fg.a = 0xff,

	.fg_disabled.r = 0xa4,
	.fg_disabled.g = 0xa4,
	.fg_disabled.b = 0xa4,
	.fg_disabled.a = 0xff,
};

#define CTK_DEFAULT_BUTTON_W     80
#define CTK_DEFAULT_BUTTON_H     27
#define CTK_DEFAULT_ENTRY_W      165
#define CTK_DEFAULT_ENTRY_H      CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_FONTSIZE     11
#define CTK_DEFAULT_THEME        CTK_Theme_TclTk
#define CTK_DEFAULT_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)

static TTF_Font *CTK_font = NULL;

#ifdef CTK_IMPL

int
CTK_AddButton(struct CTK_Menu *m)
{
	int ret;

	ret = CTK_AddWidget(m);
	m->bg[ret] = &m->style.bg_button;
	m->border[ret] = true;
	m->enabled[ret] = true;
	m->visible[ret] = true;
	m->rect[ret].w = CTK_DEFAULT_BUTTON_W;
	m->rect[ret].h = CTK_DEFAULT_BUTTON_H;

	return ret;
}

int
CTK_AddEntry(struct CTK_Menu *m)
{
	int ret;

	ret = CTK_AddWidget(m);
	m->bg[ret] = &m->style.bg_entry;
	m->border[ret] = true;
	m->enabled[ret] = true;
	m->visible[ret] = true;
	m->rect[ret].w = CTK_DEFAULT_ENTRY_W;
	m->rect[ret].h = CTK_DEFAULT_ENTRY_H;
	CTK_CreateWidgetTexture(m, ret);

	return ret;
}

int
CTK_AddLabel(struct CTK_Menu *m)
{
	int ret;

	ret = CTK_AddWidget(m);
	m->bg[ret] = &m->style.bg_label;
	m->enabled[ret] = true;
	m->visible[ret] = true;

	return ret;
}

int
CTK_AddWidget(struct CTK_Menu *m)
{
	int ret = m->count;

	m->count++;
	m->bg[ret] = &m->style.bg_widget;
	m->border[ret] = false;
	m->cursor[ret] = 0;
	m->enabled[ret] = false;
	m->scroll[ret] = 0;
	m->text[ret][0] = '\0';
	m->rect[ret].x = 0;
	m->rect[ret].y = 0;
	m->rect[ret].w = 0;
	m->rect[ret].h = 0;
	m->visible[ret] = false;
	m->on_click[ret] = NULL;
	m->on_click_data[ret] = NULL;

	return ret;
}

bool
CTK_CreateMenu(struct CTK_Menu *m,
               const char *title,
               const int winw,
               const int winh,
               const SDL_WindowFlags flags)
{
	SDL_WindowFlags f;
	SDL_Renderer *r;

	m->active = true;
	m->count = 0;
	m->on_quit = CTK_MenuDefaultOnQuit;
	m->on_quit_data = NULL;
	m->style = CTK_DEFAULT_THEME;
	m->redraw = true;

	if (0 == flags)
		f = CTK_DEFAULT_WINDOW_FLAGS;
	else
		f = flags;

	if (!SDL_CreateWindowAndRenderer(title, winw, winh, f, &m->win, &r)) {
		m->active = false;
		return false;
	}

	if (!SDL_SetRenderLogicalPresentation(r, winw, winh,
	                                      SDL_LOGICAL_PRESENTATION_DISABLED)) {
		m->active = false;
		return false;
	}

	return true;
}

void
CTK_CreateWidgetTexture(struct CTK_Menu *m,
                        const int widget)
{
	SDL_Color fg;
	SDL_Renderer *r = NULL;
	SDL_FRect    text_r;
	SDL_Surface *text_s = NULL;
	SDL_Texture *text_t = NULL;

	r = SDL_GetRenderer(m->win);

	SDL_DestroyTexture(m->texture[widget]);

	if (m->enabled[widget])
		fg = m->style.fg;
	else
		fg = m->style.fg_disabled;

	m->texture[widget] = SDL_CreateTexture(r,
	                                       SDL_PIXELFORMAT_RGBA8888,
	                                       SDL_TEXTUREACCESS_TARGET,
	                                       m->rect[widget].w,
	                                       m->rect[widget].h);
	SDL_SetRenderTarget(r, m->texture[widget]);
	SDL_SetRenderDrawColor(r,
	                       m->bg[widget]->r,
	                       m->bg[widget]->g,
	                       m->bg[widget]->b,
	                       m->bg[widget]->a);
	SDL_RenderClear(r);

	if (strlen(m->text[widget]) != 0) {
		text_s = TTF_RenderText_LCD(CTK_font,
			                    m->text[widget],
			                    0,
			                    fg,
			                    *m->bg[widget]);
		text_t = SDL_CreateTextureFromSurface(r, text_s);

		text_r.x = (m->rect[widget].w - text_s->w) / 2.0;
		text_r.y = (m->rect[widget].h - text_s->h) / 2.0;
		text_r.w = text_s->w;
		text_r.h = text_s->h;
		SDL_RenderTexture(r, text_t, NULL, &text_r);
	}

	if (m->border[widget]) {
		SDL_SetRenderDrawColor(r,
			               m->style.border.r,
			               m->style.border.g,
			               m->style.border.b,
			               m->style.border.a);
		SDL_RenderRect(r, &m->rect[widget]);
	}

	m->redraw = true;
	SDL_SetRenderTarget(r, NULL);
	SDL_DestroySurface(text_s);
	SDL_DestroyTexture(text_t);
}

void
CTK_DestroyMenu(struct CTK_Menu *m)
{
	int i;

	for (i = 0; i < m->count; i++) {
		SDL_DestroyTexture(m->texture[i]);
	}
	SDL_DestroyWindow(m->win);
}

void
CTK_DrawMenu(struct CTK_Menu *m)
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
	m->redraw = false;
}

bool
CTK_Init(const char *appname,
         const char *appversion,
         const char *appidentifier)
{
	long unsigned i;
	const int pathlen = 256;
	char path[pathlen];

	if (!SDL_SetAppMetadata(appname, appversion, appidentifier))
		return false;

	if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO))
		return false;

	if (!TTF_Init())
		return false;

	for (i = 0; i < ARRLEN(FONTNAMES); i++) {
		snprintf(path, pathlen - 1, "%s%s", FONTPATH, FONTNAMES[i]);
		CTK_font = TTF_OpenFont(path, CTK_DEFAULT_FONTSIZE);
		if (NULL != CTK_font)
			break;
	}
	if (NULL == CTK_font)
		return false;

	return true;
}

void
CTK_MainloopMenu(struct CTK_Menu *m)
{
	Uint64 now, last;

	while (m->active) {
		SDL_WaitEvent(NULL);

		now = SDL_GetTicks();
		if (now - last > 1000 / CTK_MAX_TICKRATE) {
			last = now;

			CTK_TickMenu(m);
			CTK_DrawMenu(m);
		}
	}
}

void
CTK_MenuDefaultOnQuit(struct CTK_Menu *m,
                      void            *dummy)
{
	(void) dummy;

	m->active = false;
}

void
CTK_SetWidgetEnabled(struct CTK_Menu *m,
                     const int widget,
                     const bool enabled)
{
	m->enabled[widget] = enabled;
	CTK_CreateWidgetTexture(m, widget);
}

void
CTK_SetWidgetText(struct CTK_Menu *m,
                  const int widget,
                  const char *text)
{
	int w, h;

	strncpy(m->text[widget], text, CTK_MAX_TEXTLEN - 1);
	TTF_GetStringSize(CTK_font,
	                  m->text[widget],
	                  strlen(m->text[widget]),
	                  &w, &h);
	if (m->border[widget]) {
		w++;
		h++;
	}
	if (w > m->rect[widget].w)
		m->rect[widget].w = w;
	if (h > m->rect[widget].h)
		m->rect[widget].h = h;
	CTK_CreateWidgetTexture(m, widget);
}

void
CTK_SetWidgetTextAndResize(struct CTK_Menu *m,
                           const int widget,
                           const char *text)
{
	int w, h;

	strncpy(m->text[widget], text, CTK_MAX_TEXTLEN - 1);
	TTF_GetStringSize(CTK_font,
	                  m->text[widget],
	                  strlen(m->text[widget]),
	                  &w, &h);
	if (m->border[widget]) {
		w++;
		h++;
	}
	m->rect[widget].w = w;
	m->rect[widget].h = h;
	CTK_CreateWidgetTexture(m, widget);
}

void
CTK_TickMenu(struct CTK_Menu *m)
{
	SDL_Event e;
	int i;
	SDL_FPoint p;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EVENT_MOUSE_BUTTON_UP:
			for (i = 0; i < m->count; i++) {
				p.x = e.button.x;
				p.y = e.button.y;
				if (SDL_PointInRectFloat(&p, &m->rect[i]) &&
				    m->enabled[i] &&
				    NULL != m->on_click[i]) {
					m->on_click[i](m, i, m->on_click_data[i]);
					break;
				}
			}
			break;

		case SDL_EVENT_WINDOW_SHOWN:
		case SDL_EVENT_WINDOW_EXPOSED:
		case SDL_EVENT_WINDOW_RESIZED:
		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
		case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
		case SDL_EVENT_WINDOW_MAXIMIZED:
		case SDL_EVENT_WINDOW_RESTORED:
		case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
		case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
		case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
		case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
		case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
			m->redraw = true;
			break;

		case SDL_EVENT_QUIT:
			if (NULL != m->on_quit) {
				m->on_quit(m, m->on_quit_data);
			}
			break;
		}
	}
}

void
CTK_Quit()
{
	TTF_CloseFont(CTK_font);
	TTF_Quit();
	SDL_Quit();
}

#endif /* CTK_IMPL */

#endif /* _CTK_H */
