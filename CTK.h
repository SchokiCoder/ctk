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

typedef enum CTK_TextAlignment {
	CTK_TEXT_ALIGNMENT_LEFT,
	CTK_TEXT_ALIGNMENT_CENTER,
	CTK_TEXT_ALIGNMENT_RIGHT,
} CTK_TextAlignment;

typedef struct CTK_Style {
	SDL_Color bg;
	SDL_Color bg_button;
	SDL_Color bg_entry;
	SDL_Color bg_label;
	SDL_Color bg_widget;
	SDL_Color border;
	SDL_Color fg;
	SDL_Color fg_disabled;
} CTK_Style;

typedef struct CTK_Instance {
	bool               active;
	bool               redraw;
	CTK_Style          style;
	int                tabfocus;
	int                taborder[CTK_MAX_WIDGETS];
	SDL_Window        *win;

	/* instance events */
	void              (*on_quit)(struct CTK_Instance*, void*);
	void              *on_quit_data;

	/* widget data */
	int                count;
	SDL_Color         *bg[CTK_MAX_WIDGETS];
	bool               border[CTK_MAX_WIDGETS];
	int                cursor[CTK_MAX_WIDGETS];
	bool               enabled[CTK_MAX_WIDGETS];
	bool               focusable[CTK_MAX_WIDGETS];
	int                scroll[CTK_MAX_WIDGETS];
	char               text[CTK_MAX_TEXTLEN][CTK_MAX_WIDGETS];
	CTK_TextAlignment  text_alignment[CTK_MAX_WIDGETS];
	bool               text_editable[CTK_MAX_WIDGETS];
	bool               visible[CTK_MAX_WIDGETS];
	SDL_FRect          rect[CTK_MAX_WIDGETS];
	SDL_Texture       *texture[CTK_MAX_WIDGETS];

	/* widget events */
	void              (*on_click[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                               const int,
	                                               void*);
	void              *on_click_data[CTK_MAX_WIDGETS];
} CTK_Instance;

int
CTK_AddButton(CTK_Instance *inst);

int
CTK_AddEntry(CTK_Instance *inst);

int
CTK_AddLabel(CTK_Instance *inst);

int
CTK_AddWidget(CTK_Instance *inst);

/* inst = Instance to initialize.
 * title = Used as window title.
 * winw = Window width.
 * winh = Window height.
 * flags = SDL window flags. May be 0 to use defaults.
 * Returns true on success or false on failure.
 * Call SDL_GetError() for more information.
 */
bool
CTK_CreateInstance(CTK_Instance          *inst,
                   const char            *title,
                   const int              winw,
                   const int              winh,
                   const SDL_WindowFlags  flags);

void
CTK_CreateWidgetTexture(CTK_Instance *inst,
                        const int     widget);

void
CTK_DestroyInstance(CTK_Instance *inst);

void
CTK_DrawInstance(CTK_Instance *inst);

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
 * you can call CTK_DrawInstance and CTK_TickInstance yourself.
 */
void
CTK_MainloopInstance(CTK_Instance *inst);

void
CTK_InstanceDefaultOnQuit(CTK_Instance *inst,
                          void         *dummy);

void
CTK_SetTabfocus(CTK_Instance *inst,
                const int     widget);

void
CTK_SetWidgetEnabled(CTK_Instance *inst,
                     const int     widget,
                     const bool    enabled);

void
CTK_SetWidgetText(CTK_Instance *inst,
                  const int     widget,
                  const char   *text);

void
CTK_SetWidgetTextAndResize(CTK_Instance *inst,
                           const int     widget,
                           const char   *text);

void
CTK_TickInstance(CTK_Instance *inst);

void
CTK_Quit();

const CTK_Style CTK_Theme_TclTk = {
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
#define CTK_DEFAULT_LABEL_H      CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_THEME        CTK_Theme_TclTk
#define CTK_DEFAULT_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)

static TTF_Font *CTK_font = NULL;

#ifdef CTK_IMPL

int
CTK_AddButton(CTK_Instance *inst)
{
	int ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_button;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->focusable[ret] = true;
	inst->text_alignment[ret] = CTK_TEXT_ALIGNMENT_CENTER;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_BUTTON_W;
	inst->rect[ret].h = CTK_DEFAULT_BUTTON_H;

	return ret;
}

int
CTK_AddEntry(CTK_Instance *inst)
{
	int ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_entry;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->focusable[ret] = true;
	inst->text_editable[ret] = true;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_ENTRY_W;
	inst->rect[ret].h = CTK_DEFAULT_ENTRY_H;
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

int
CTK_AddLabel(CTK_Instance *inst)
{
	int ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_label;
	inst->enabled[ret] = true;
	inst->visible[ret] = true;
	inst->rect[ret].h = CTK_DEFAULT_LABEL_H;

	return ret;
}

int
CTK_AddWidget(CTK_Instance *inst)
{
	int ret = inst->count;

	inst->taborder[inst->count] = ret;
	inst->count++;

	inst->bg[ret] = &inst->style.bg_widget;
	inst->border[ret] = false;
	inst->cursor[ret] = 0;
	inst->enabled[ret] = false;
	inst->focusable[ret] = false;
	inst->scroll[ret] = 0;
	inst->text[ret][0] = '\0';
	inst->text_alignment[ret] = CTK_TEXT_ALIGNMENT_LEFT;
	inst->text_editable[ret] = false;
	inst->rect[ret].x = 0;
	inst->rect[ret].y = 0;
	inst->rect[ret].w = 0;
	inst->rect[ret].h = 0;
	inst->visible[ret] = false;
	inst->on_click[ret] = NULL;
	inst->on_click_data[ret] = NULL;

	return ret;
}

bool
CTK_CreateInstance(CTK_Instance          *inst,
                   const char            *title,
                   const int              winw,
                   const int              winh,
                   const SDL_WindowFlags  flags)
{
	SDL_WindowFlags f;
	SDL_Renderer *r;

	inst->active = true;
	inst->tabfocus = 0;
	inst->count = 0;
	inst->on_quit = CTK_InstanceDefaultOnQuit;
	inst->on_quit_data = NULL;
	inst->style = CTK_DEFAULT_THEME;
	inst->redraw = true;

	if (0 == flags)
		f = CTK_DEFAULT_WINDOW_FLAGS;
	else
		f = flags;

	if (!SDL_CreateWindowAndRenderer(title, winw, winh, f, &inst->win, &r)) {
		inst->active = false;
		return false;
	}

	if (!SDL_SetRenderLogicalPresentation(r, winw, winh,
	                                      SDL_LOGICAL_PRESENTATION_DISABLED)) {
		inst->active = false;
		return false;
	}

	return true;
}

void
CTK_CreateWidgetTexture(CTK_Instance *inst,
                        const int     widget)
{
	SDL_Color fg;
	SDL_Renderer *r = NULL;
	SDL_FRect    rect;
	SDL_Surface *text_s = NULL;
	SDL_Texture *text_t = NULL;

	r = SDL_GetRenderer(inst->win);

	SDL_DestroyTexture(inst->texture[widget]);

	if (inst->enabled[widget])
		fg = inst->style.fg;
	else
		fg = inst->style.fg_disabled;

	inst->texture[widget] = SDL_CreateTexture(r,
	                                       SDL_PIXELFORMAT_RGBA8888,
	                                       SDL_TEXTUREACCESS_TARGET,
	                                       inst->rect[widget].w,
	                                       inst->rect[widget].h);
	SDL_SetRenderTarget(r, inst->texture[widget]);
	SDL_SetRenderDrawColor(r,
	                       inst->bg[widget]->r,
	                       inst->bg[widget]->g,
	                       inst->bg[widget]->b,
	                       inst->bg[widget]->a);
	SDL_RenderClear(r);

	if (strlen(inst->text[widget]) != 0) {
		text_s = TTF_RenderText_LCD(CTK_font,
			                    inst->text[widget],
			                    0,
			                    fg,
			                    *inst->bg[widget]);
		text_t = SDL_CreateTextureFromSurface(r, text_s);

		switch (inst->text_alignment[widget]) {
		case CTK_TEXT_ALIGNMENT_LEFT:
			rect.x = 0;
			break;

		case CTK_TEXT_ALIGNMENT_CENTER:
			rect.x = (inst->rect[widget].w - text_s->w) / 2.0;
			break;

		case CTK_TEXT_ALIGNMENT_RIGHT:
			rect.x = inst->rect[widget].w - text_s->w;
			break;
		}
		rect.y = (inst->rect[widget].h - text_s->h) / 2.0;
		rect.w = text_s->w;
		rect.h = text_s->h;

		SDL_RenderTexture(r, text_t, NULL, &rect);
	}

	if (inst->border[widget]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[widget].w;
		rect.h = inst->rect[widget].h;

		SDL_SetRenderDrawColor(r,
			               inst->style.border.r,
			               inst->style.border.g,
			               inst->style.border.b,
			               inst->style.border.a);
		SDL_RenderRect(r, &rect);
	}

	inst->redraw = true;
	SDL_SetRenderTarget(r, NULL);
	SDL_DestroySurface(text_s);
	SDL_DestroyTexture(text_t);
}

void
CTK_DestroyInstance(CTK_Instance *inst)
{
	int i;

	for (i = 0; i < inst->count; i++) {
		SDL_DestroyTexture(inst->texture[i]);
	}
	SDL_DestroyWindow(inst->win);
}

void
CTK_DrawInstance(CTK_Instance *inst)
{
	int i;
	SDL_Renderer *r;

	if (!inst->redraw)
		return;

	r = SDL_GetRenderer(inst->win);

	SDL_SetRenderDrawColor(r,
	                       inst->style.bg.r,
	                       inst->style.bg.g,
	                       inst->style.bg.b,
	                       inst->style.bg.a);
	SDL_RenderClear(r);

	for (i = 0; i < inst->count; i++) {
		if (!inst->visible[i])
			continue;

		SDL_RenderTexture(r, inst->texture[i], NULL, &inst->rect[i]);
	}

	SDL_RenderPresent(r);
	inst->redraw = false;
}

int
CTK_GetFocusedWidget(const CTK_Instance *inst)
{
	return inst->taborder[inst->tabfocus];
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
CTK_MainloopInstance(CTK_Instance *inst)
{
	Uint64 now, last;

	while (inst->active) {
		SDL_WaitEvent(NULL);

		now = SDL_GetTicks();
		if (now - last > 1000 / CTK_MAX_TICKRATE) {
			last = now;

			CTK_TickInstance(inst);
			CTK_DrawInstance(inst);
		}
	}
}

void
CTK_InstanceDefaultOnQuit(CTK_Instance *inst,
                          void         *dummy)
{
	(void) dummy;

	inst->active = false;
}

void
CTK_SetTabfocus(CTK_Instance *inst,
                const int     widget)
{
	inst->tabfocus = widget;

	if (inst->text_editable[inst->tabfocus]) {
		SDL_StartTextInput(inst->win);
	} else {
		SDL_StopTextInput(inst->win);
	}
}

void
CTK_SetWidgetEnabled(CTK_Instance *inst,
                     const int     widget,
                     const bool    enabled)
{
	inst->enabled[widget] = enabled;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetText(CTK_Instance *inst,
                  const int     widget,
                  const char   *text)
{
	int w, h;

	strncpy(inst->text[widget], text, CTK_MAX_TEXTLEN - 1);
	TTF_GetStringSize(CTK_font,
	                  inst->text[widget],
	                  strlen(inst->text[widget]),
	                  &w, &h);
	if (inst->border[widget]) {
		w++;
		h++;
	}
	if (w > inst->rect[widget].w)
		inst->rect[widget].w = w;
	if (h > inst->rect[widget].h)
		inst->rect[widget].h = h;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetTextAlignment(CTK_Instance            *inst,
                           const int                widget,
                           const CTK_TextAlignment  alignment)
{
	inst->text_alignment[widget] = alignment;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetTextAndResize(CTK_Instance *inst,
                           const int     widget,
                           const char   *text)
{
	int w, h;

	strncpy(inst->text[widget], text, CTK_MAX_TEXTLEN - 1);
	TTF_GetStringSize(CTK_font,
	                  inst->text[widget],
	                  strlen(inst->text[widget]),
	                  &w, &h);
	if (inst->border[widget]) {
		w++;
		h++;
	}
	inst->rect[widget].w = w;
	inst->rect[widget].h = h;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_TickInstance(CTK_Instance *inst)
{
	SDL_Event e;
	int fw;
	int i;
	SDL_FPoint p;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EVENT_MOUSE_BUTTON_UP:
			for (i = 0; i < inst->count; i++) {
				p.x = e.button.x;
				p.y = e.button.y;
				if (SDL_PointInRectFloat(&p, &inst->rect[i]) &&
				    inst->enabled[i] &&
				    NULL != inst->on_click[i]) {
					inst->on_click[i](inst,
					                  i,
					                  inst->on_click_data[i]);
					break;
				}
			}
			break;

		case SDL_EVENT_KEY_DOWN:
			if (SDLK_TAB == e.key.key) {
				if (SDL_KMOD_SHIFT & e.key.mod) {
					do {
						inst->tabfocus--;
						if (inst->tabfocus < 0) {
							inst->tabfocus = inst->count - 1;
						}
						fw = CTK_GetFocusedWidget(inst);
					} while (!inst->focusable[fw]);
				} else {
					do {
						inst->tabfocus++;
						if (inst->tabfocus >= inst->count) {
							inst->tabfocus = 0;
						}
						fw = CTK_GetFocusedWidget(inst);
					} while (!inst->focusable[fw]);
				}

				CTK_SetTabfocus(inst, inst->tabfocus);
			}
			break;

		case SDL_EVENT_TEXT_INPUT:
			fw = CTK_GetFocusedWidget(inst);
			if (inst->cursor[fw] < CTK_MAX_TEXTLEN) {
				inst->text[fw][inst->cursor[fw]] = e.text.text[0];
				inst->cursor[fw]++;
				CTK_CreateWidgetTexture(inst, fw);
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
			inst->redraw = true;
			break;

		case SDL_EVENT_QUIT:
			if (NULL != inst->on_quit) {
				inst->on_quit(inst, inst->on_quit_data);
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
