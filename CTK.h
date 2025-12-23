/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#ifndef _CTK_H
#define _CTK_H

#include "CTK_style.h"

#include <math.h>
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

typedef int CTK_WidgetId;

typedef enum CTK_WidgetType {
	CTK_WTYPE_UNKNOWN,
	CTK_WTYPE_BUTTON,
	CTK_WTYPE_CHECKBOX,
	CTK_WTYPE_ENTRY,
	CTK_WTYPE_LABEL,
	CTK_WTYPE_PROGRESSBAR,
	CTK_WTYPE_RADIOBUTTON,
	CTK_WTYPE_SCALE,
} CTK_WidgetType;

typedef enum CTK_TextAlignment {
	CTK_TEXT_ALIGNMENT_LEFT,
	CTK_TEXT_ALIGNMENT_CENTER,
	CTK_TEXT_ALIGNMENT_RIGHT,
} CTK_TextAlignment;

typedef struct CTK_Instance {
	bool        active;
	bool        drag;
	int         focused_w;
	bool        redraw;
	CTK_Style   style;
	SDL_Window *win;

	/* instance events */
	void (*on_quit)(struct CTK_Instance*, void*);
	void *on_quit_data;

	/* widget cache */
	int                enabled_ws;
	CTK_WidgetId       enabled_w[CTK_MAX_WIDGETS];
	int                focusable_ws;
	CTK_WidgetId       focusable_w[CTK_MAX_WIDGETS];
	int                visible_ws;
	CTK_WidgetId       visible_w[CTK_MAX_WIDGETS];

	/* widget data */
	int                count;
	SDL_Color         *bg[CTK_MAX_WIDGETS];
	bool               border[CTK_MAX_WIDGETS];
	int                cursor[CTK_MAX_WIDGETS];
	int                group[CTK_MAX_WIDGETS];
	int                scroll[CTK_MAX_WIDGETS];
	char               text[CTK_MAX_TEXTLEN][CTK_MAX_WIDGETS];
	CTK_TextAlignment  text_alignment[CTK_MAX_WIDGETS];
	bool               toggle[CTK_MAX_WIDGETS];
	CTK_WidgetType     type[CTK_MAX_WIDGETS];
	unsigned int       value[CTK_MAX_WIDGETS];
	unsigned int       value_max[CTK_MAX_WIDGETS];
	SDL_FRect          rect[CTK_MAX_WIDGETS];
	SDL_Texture       *texture[CTK_MAX_WIDGETS];

	/* widget events */
	void (*button_press[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                      const SDL_MouseButtonEvent,
	                                      const CTK_WidgetId,
	                                      void*);
	void *button_press_data[CTK_MAX_WIDGETS];
	void (*button_release[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                        const SDL_MouseButtonEvent,
	                                        const CTK_WidgetId,
	                                        void*);
	void *button_release_data[CTK_MAX_WIDGETS];
	void (*trigger[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                 const CTK_WidgetId,
	                                 void*);
	void *trigger_data[CTK_MAX_WIDGETS];
} CTK_Instance;

CTK_WidgetId
CTK_AddButton(CTK_Instance *inst);

CTK_WidgetId
CTK_AddCheckbox(CTK_Instance *inst);

CTK_WidgetId
CTK_AddEntry(CTK_Instance *inst);

CTK_WidgetId
CTK_AddLabel(CTK_Instance *inst);

CTK_WidgetId
CTK_AddProgressbar(CTK_Instance *inst);

CTK_WidgetId
CTK_AddRadiobutton(CTK_Instance *inst);

CTK_WidgetId
CTK_AddScale(CTK_Instance *inst);

CTK_WidgetId
CTK_AddWidget(CTK_Instance *inst);

SDL_FColor
CTK_ColorIntToFColor(const SDL_Color c);

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
CTK_CreateWidgetTexture(CTK_Instance       *inst,
                        const CTK_WidgetId  widget);

void
CTK_DestroyInstance(CTK_Instance *inst);

void
CTK_DrawInstance(CTK_Instance *inst);

void
CTK_HandleDrag(CTK_Instance *inst,
               const float   x);

void
CTK_HandleKeyDown(CTK_Instance            *inst,
                  const SDL_KeyboardEvent  e);

void
CTK_HandleMouseButtonDown(CTK_Instance               *inst,
                          const SDL_MouseButtonEvent  e);

void
CTK_HandleMouseButtonUp(CTK_Instance               *inst,
                        const SDL_MouseButtonEvent  e);

void
CTK_HandleMouseWheel(CTK_Instance *inst,
                     const SDL_MouseWheelEvent e);

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst);

float
CTK_GetScaleSliderWidth(const CTK_Instance *inst,
                        const CTK_WidgetId widget);

bool
CTK_GetWidgetEnabledId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       int                *cacheId);

bool
CTK_GetWidgetFocusableId(const CTK_Instance *inst,
                         const CTK_WidgetId  widget,
                         int                *cacheId);

bool
CTK_GetWidgetVisibleId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       int                *cacheId);

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

bool
CTK_IsWidgetEnabled(const CTK_Instance *inst,
                    const CTK_WidgetId  widget);

bool
CTK_IsWidgetFocusable(const CTK_Instance *inst,
                      const CTK_WidgetId  widget);

bool
CTK_IsWidgetVisible(const CTK_Instance *inst,
                    const CTK_WidgetId  widget);

/* Alternatively, if more control is needed,
 * you can call CTK_DrawInstance and CTK_TickInstance yourself.
 */
void
CTK_MainloopInstance(CTK_Instance *inst);

void
CTK_InstanceDefaultOnQuit(CTK_Instance *inst,
                          void         *dummy);

void
CTK_SetFocusedWidget(CTK_Instance       *inst,
                     const CTK_WidgetId  widget);

void
CTK_SetWidgetEnabled(CTK_Instance       *inst,
                     const CTK_WidgetId  widget,
                     const bool          enabled);

void
CTK_SetWidgetFocusable(CTK_Instance       *inst,
                       const CTK_WidgetId  widget,
                       const bool          focusable);

void
CTK_SetWidgetText(CTK_Instance       *inst,
                  const CTK_WidgetId  widget,
                  const char         *text);

void
CTK_SetWidgetTextAlignment(CTK_Instance            *inst,
                           const CTK_WidgetId       widget,
                           const CTK_TextAlignment  alignment);

void
CTK_SetWidgetTextAndResize(CTK_Instance       *inst,
                           const CTK_WidgetId  widget,
                           const char         *text);

void
CTK_SetWidgetToggle(CTK_Instance       *inst,
                    const CTK_WidgetId  widget,
                    const bool          toggle);

void
CTK_SetWidgetValue(CTK_Instance       *inst,
                   const CTK_WidgetId  widget,
                   const unsigned int  value);

void
CTK_SetWidgetVisible(CTK_Instance       *inst,
                     const CTK_WidgetId  widget,
                     const bool          visible);

void
CTK_TickInstance(CTK_Instance *inst);

void
CTK_ToggleCheckbox(CTK_Instance *inst,
                   CTK_WidgetId  widget);

void
CTK_ToggleRadiobutton(CTK_Instance *inst,
                      CTK_WidgetId  widget);

void
CTK_Quit();

#define CTK_DEFAULT_BUTTON_W           80
#define CTK_DEFAULT_BUTTON_H           27
#define CTK_DEFAULT_CHECKBOX_W         CTK_DEFAULT_BUTTON_H - 4
#define CTK_DEFAULT_CHECKBOX_H         CTK_DEFAULT_BUTTON_H - 4
#define CTK_DEFAULT_CHECKBOX_FILL      0.7
#define CTK_DEFAULT_ENTRY_W            165
#define CTK_DEFAULT_ENTRY_H            CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_FONTSIZE           11
#define CTK_DEFAULT_LABEL_H            CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_PROGRESSBAR_W      CTK_DEFAULT_BUTTON_W
#define CTK_DEFAULT_PROGRESSBAR_H      CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_RADIOBUTTON_W      CTK_DEFAULT_CHECKBOX_W
#define CTK_DEFAULT_RADIOBUTTON_H      CTK_DEFAULT_CHECKBOX_H
#define CTK_DEFAULT_SCALE_W            CTK_DEFAULT_BUTTON_W
#define CTK_DEFAULT_SCALE_H            CTK_DEFAULT_BUTTON_H
#define CTK_SCALE_SLIDER_SIZE_FRACTION 0.3

#define CTK_DEFAULT_RADIOBUTTON_FILL CTK_DEFAULT_CHECKBOX_FILL
#define CTK_DEFAULT_THEME            CTK_Theme_TclTk
#define CTK_DEFAULT_WINDOW_FLAGS     (SDL_WINDOW_RESIZABLE)

static TTF_Font *CTK_font = NULL;

#ifdef CTK_IMPL

CTK_WidgetId
CTK_AddButton(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;
	inst->focusable_w[inst->focusable_ws] = ret;
	inst->focusable_ws++;

	inst->bg[ret] = &inst->style.bg_button;
	inst->border[ret] = true;
	inst->text_alignment[ret] = CTK_TEXT_ALIGNMENT_CENTER;
	inst->type[ret] = CTK_WTYPE_BUTTON;
	inst->rect[ret].w = CTK_DEFAULT_BUTTON_W;
	inst->rect[ret].h = CTK_DEFAULT_BUTTON_H;
	CTK_SetWidgetVisible(inst, ret, true);
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddCheckbox(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;
	inst->focusable_w[inst->focusable_ws] = ret;
	inst->focusable_ws++;

	inst->bg[ret] = &inst->style.bg_checkbox;
	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_CHECKBOX;
	inst->rect[ret].w = CTK_DEFAULT_CHECKBOX_W;
	inst->rect[ret].h = CTK_DEFAULT_CHECKBOX_H;
	CTK_SetWidgetVisible(inst, ret, true);
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddEntry(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;
	inst->focusable_w[inst->focusable_ws] = ret;
	inst->focusable_ws++;

	inst->bg[ret] = &inst->style.bg_entry;
	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_ENTRY;
	inst->rect[ret].w = CTK_DEFAULT_ENTRY_W;
	inst->rect[ret].h = CTK_DEFAULT_ENTRY_H;
	CTK_SetWidgetVisible(inst, ret, true);
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddLabel(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;

	inst->bg[ret] = &inst->style.bg_label;
	inst->type[ret] = CTK_WTYPE_LABEL;
	inst->rect[ret].h = CTK_DEFAULT_LABEL_H;
	CTK_SetWidgetVisible(inst, ret, true);

	return ret;
}

CTK_WidgetId
CTK_AddProgressbar(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;

	inst->bg[ret] = &inst->style.bg_progressbar;
	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_PROGRESSBAR;
	inst->value_max[ret] = 100;
	inst->rect[ret].w = CTK_DEFAULT_PROGRESSBAR_W;
	inst->rect[ret].h = CTK_DEFAULT_PROGRESSBAR_H;
	CTK_SetWidgetVisible(inst, ret, true);
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddRadiobutton(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;
	inst->focusable_w[inst->focusable_ws] = ret;
	inst->focusable_ws++;

	inst->bg[ret] = &inst->style.bg_radiobutton;
	inst->border[ret] = true;
	inst->group[ret] = 0;
	inst->type[ret] = CTK_WTYPE_RADIOBUTTON;
	inst->rect[ret].w = CTK_DEFAULT_RADIOBUTTON_W;
	inst->rect[ret].h = CTK_DEFAULT_RADIOBUTTON_H;
	CTK_SetWidgetVisible(inst, ret, true);
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddScale(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;
	inst->focusable_w[inst->focusable_ws] = ret;
	inst->focusable_ws++;

	inst->bg[ret] = &inst->style.bg_scale;
	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_SCALE;
	inst->value_max[ret] = 100;
	inst->rect[ret].w = CTK_DEFAULT_SCALE_W;
	inst->rect[ret].h = CTK_DEFAULT_SCALE_H;
	CTK_SetWidgetVisible(inst, ret, true);
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddWidget(CTK_Instance *inst)
{
	CTK_WidgetId ret = inst->count;

	inst->count++;

	inst->bg[ret] = &inst->style.bg_widget;
	inst->border[ret] = false;
	inst->cursor[ret] = 0;
	inst->group[ret] = -1;
	inst->scroll[ret] = 0;
	inst->text[ret][0] = '\0';
	inst->text_alignment[ret] = CTK_TEXT_ALIGNMENT_LEFT;
	inst->toggle[ret] = false;
	inst->type[ret] = CTK_WTYPE_UNKNOWN;
	inst->rect[ret].x = 0;
	inst->rect[ret].y = 0;
	inst->rect[ret].w = 0;
	inst->rect[ret].h = 0;
	inst->value[ret] = 0;
	inst->value_max[ret] = 0;
	inst->button_press[ret] = NULL;
	inst->button_press_data[ret] = NULL;
	inst->button_release[ret] = NULL;
	inst->button_release_data[ret] = NULL;
	inst->trigger[ret] = NULL;
	inst->trigger_data[ret] = NULL;

	return ret;
}

SDL_FColor
CTK_ColorIntToFColor(const SDL_Color c)
{
	SDL_FColor ret = {
		.r = c.r / 255.0,
		.g = c.g / 255.0,
		.b = c.b / 255.0,
		.a = c.a / 255.0,
	};

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
	inst->drag = false;
	inst->focused_w = 0;
	inst->style = CTK_DEFAULT_THEME;
	inst->redraw = true;

	inst->on_quit = CTK_InstanceDefaultOnQuit;
	inst->on_quit_data = NULL;

	inst->enabled_ws = 0;
	inst->focusable_ws = 0;
	inst->visible_ws = 0;

	inst->count = 0;

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
CTK_CreateWidgetTexture(CTK_Instance       *inst,
                        const CTK_WidgetId  widget)
{
	SDL_Color fg;
	SDL_Renderer *r = NULL;
	SDL_FRect    rect;
	SDL_Surface *text_s = NULL;
	SDL_Texture *text_t = NULL;
	const int    numv = 3;
	SDL_Vertex   v[numv];

	r = SDL_GetRenderer(inst->win);

	SDL_DestroyTexture(inst->texture[widget]);

	if (CTK_IsWidgetEnabled(inst, widget))
		fg = inst->style.fg;
	else
		fg = inst->style.fg_disabled;

	inst->texture[widget] = SDL_CreateTexture(r,
	                                       SDL_PIXELFORMAT_RGBA8888,
	                                       SDL_TEXTUREACCESS_TARGET,
	                                       inst->rect[widget].w,
	                                       inst->rect[widget].h);
	SDL_SetRenderTarget(r, inst->texture[widget]);

	/* background */
	SDL_SetRenderDrawColor(r,
	                       inst->bg[widget]->r,
	                       inst->bg[widget]->g,
	                       inst->bg[widget]->b,
	                       inst->bg[widget]->a);
	SDL_RenderClear(r);

	/* content */
	switch (inst->type[widget]) {
	case CTK_WTYPE_UNKNOWN:
	case CTK_WTYPE_BUTTON:
	case CTK_WTYPE_ENTRY:
	case CTK_WTYPE_LABEL:
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
		break;

	case CTK_WTYPE_CHECKBOX:
		if (inst->toggle[widget]) {
			rect.x = (inst->rect[widget].w -
			          inst->rect[widget].w *
			          CTK_DEFAULT_CHECKBOX_FILL) / 2.0;
			rect.y = (inst->rect[widget].h -
			          inst->rect[widget].h *
			          CTK_DEFAULT_CHECKBOX_FILL) / 2.0;
			rect.w = inst->rect[widget].w * CTK_DEFAULT_CHECKBOX_FILL;
			rect.h = inst->rect[widget].h * CTK_DEFAULT_CHECKBOX_FILL;
			SDL_SetRenderDrawColor(r,
					       inst->style.fg.r,
					       inst->style.fg.g,
					       inst->style.fg.b,
					       inst->style.fg.a);
			SDL_RenderFillRect(r, &rect);
		}
		break;

	case CTK_WTYPE_PROGRESSBAR:
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[widget].w *
		         ((float) inst->value[widget] /
		          (float) inst->value_max[widget]);
		rect.h = inst->rect[widget].h;
		SDL_SetRenderDrawColor(r,
				       inst->style.fg.r,
				       inst->style.fg.g,
				       inst->style.fg.b,
				       inst->style.fg.a);
		SDL_RenderFillRect(r, &rect);
		break;

	case CTK_WTYPE_RADIOBUTTON:
		v[0].position.x = 0;
		v[0].position.y = 0;
		v[0].color = CTK_ColorIntToFColor(inst->style.border);
		v[0].tex_coord.x = 0;
		v[0].tex_coord.y = 0;
		v[1].position.x = inst->rect[widget].w;
		v[1].position.y = 0;
		v[1].color = CTK_ColorIntToFColor(inst->style.border);
		v[1].tex_coord.x = 0;
		v[1].tex_coord.y = 0;
		v[2].position.x = inst->rect[widget].w / 2.0;
		v[2].position.y = inst->rect[widget].h;
		v[2].color = CTK_ColorIntToFColor(inst->style.border);
		v[2].tex_coord.x = 0;
		v[2].tex_coord.y = 0;
		SDL_RenderGeometry(r, NULL, v, numv, 0, 0);

		v[0].position.x++;
		v[0].position.y++;
		v[0].color = CTK_ColorIntToFColor(inst->style.radiobutton);
		v[1].position.x--;
		v[1].position.y++;
		v[1].color = CTK_ColorIntToFColor(inst->style.radiobutton);
		v[2].position.y--;
		v[2].color = CTK_ColorIntToFColor(inst->style.radiobutton);
		SDL_RenderGeometry(r, NULL, v, numv, 0, 0);

		if (inst->toggle[widget]) {
			v[0].position.x = (inst->rect[widget].w -
			                  inst->rect[widget].w *
			                  CTK_DEFAULT_RADIOBUTTON_FILL) / 2.0;
			v[0].position.y = (inst->rect[widget].h -
			                  inst->rect[widget].h *
			                  CTK_DEFAULT_RADIOBUTTON_FILL) / 2.0;
			v[0].color = CTK_ColorIntToFColor(inst->style.fg);
			v[1].position.x = v[0].position.x +
			                  (inst->rect[widget].w *
			                  CTK_DEFAULT_RADIOBUTTON_FILL);
			v[1].position.y = v[0].position.y;
			v[1].color = CTK_ColorIntToFColor(inst->style.fg);
			v[2].position.y = inst->rect[widget].h *
			                  CTK_DEFAULT_RADIOBUTTON_FILL;
			v[2].color = CTK_ColorIntToFColor(inst->style.fg);
			SDL_RenderGeometry(r, NULL, v, numv, 0, 0);
		}
		goto cleanup;
		break;

	case CTK_WTYPE_SCALE:
		rect.w = CTK_GetScaleSliderWidth(inst, widget);
		rect.h = inst->rect[widget].h;
		rect.x = ((float) inst->value[widget] /
		          (float) inst->value_max[widget]) *
		         (inst->rect[widget].w - rect.w);
		rect.y = 0;

		SDL_SetRenderDrawColor(r,
				       inst->style.scale_slider.r,
				       inst->style.scale_slider.g,
				       inst->style.scale_slider.b,
				       inst->style.scale_slider.a);
		SDL_RenderFillRect(r, &rect);

		rect.x += rect.w / 2.0;
		rect.w = 1.0;

		SDL_SetRenderDrawColor(r,
				       inst->style.border.r,
				       inst->style.border.g,
				       inst->style.border.b,
				       inst->style.border.a);
		SDL_RenderFillRect(r, &rect);
		break;
	}

	/* generic border */
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

cleanup:
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
	CTK_WidgetId fw;
	SDL_Renderer *r;

	fw = CTK_GetFocusedWidget(inst);

	if (!inst->redraw)
		return;

	r = SDL_GetRenderer(inst->win);

	SDL_SetRenderDrawColor(r,
	                       inst->style.bg.r,
	                       inst->style.bg.g,
	                       inst->style.bg.b,
	                       inst->style.bg.a);
	SDL_RenderClear(r);

	for (i = 0; i < inst->visible_ws; i++) {
		SDL_RenderTexture(r,
		                  inst->texture[inst->visible_w[i]],
		                  NULL,
		                  &inst->rect[inst->visible_w[i]]);
	}

	SDL_SetRenderDrawColor(r,
	                       inst->style.focus.r,
	                       inst->style.focus.g,
	                       inst->style.focus.b,
	                       inst->style.focus.a);
	SDL_RenderRect(r, &inst->rect[fw]);

	SDL_RenderPresent(r);
	inst->redraw = false;
}

void
CTK_HandleDrag(CTK_Instance *inst,
               const float   x)
{
	CTK_WidgetId fw;
	float raw_v;
	float slider_w;
	float val_perc;

	fw = CTK_GetFocusedWidget(inst);

	if (inst->type[fw] != CTK_WTYPE_SCALE)
		return;

	slider_w = CTK_GetScaleSliderWidth(inst, fw);
	val_perc = 1.0 /
	           (inst->rect[fw].w - slider_w) *
	           (x - inst->rect[fw].x - (slider_w / 2.0));
	raw_v = val_perc * inst->value_max[fw];

	if (raw_v > 0.0)
		inst->value[fw] = roundf(raw_v);
	else
		inst->value[fw] = 0.0;

	if (inst->value[fw] > inst->value_max[fw])
		inst->value[fw] = inst->value_max[fw];

	CTK_CreateWidgetTexture(inst, fw);
}

void
CTK_HandleKeyDown(CTK_Instance            *inst,
                  const SDL_KeyboardEvent  e)
{
	CTK_WidgetId fw;

	switch (e.key) {
	case SDLK_LEFT:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_SCALE == inst->type[fw] &&
		    inst->value[fw] > 0)
			CTK_SetWidgetValue(inst, fw, inst->value[fw] - 1);
		break;

	case SDLK_RIGHT:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_SCALE == inst->type[fw])
			CTK_SetWidgetValue(inst, fw, inst->value[fw] + 1);
		break;

	case SDLK_SPACE:
		fw = CTK_GetFocusedWidget(inst);

		switch (inst->type[fw]) {
		case CTK_WTYPE_UNKNOWN:
		case CTK_WTYPE_BUTTON:
		case CTK_WTYPE_ENTRY:
		case CTK_WTYPE_LABEL:
		case CTK_WTYPE_PROGRESSBAR:
		case CTK_WTYPE_SCALE:
			break;

		case CTK_WTYPE_CHECKBOX:
			if (inst->toggle[fw] != true)
				inst->toggle[fw] = true;
			else
				inst->toggle[fw] = false;
			CTK_CreateWidgetTexture(inst, fw);
			break;

		case CTK_WTYPE_RADIOBUTTON:
			CTK_ToggleRadiobutton(inst, fw);
			break;
		}

		if (NULL != inst->trigger[fw]) {
			inst->trigger[fw](inst,
				          fw,
				          inst->trigger_data[fw]);
		}
		break;

	case SDLK_TAB:
		if (SDL_KMOD_SHIFT & e.mod) {
			inst->focused_w--;
			if (inst->focused_w < 0) {
				inst->focused_w = inst->focusable_ws - 1;
			}
		} else {
			inst->focused_w++;
			if (inst->focused_w >= inst->focusable_ws) {
				inst->focused_w = 0;
			}
		}

		CTK_SetFocusedWidget(inst,
		                     CTK_GetFocusedWidget(inst));
		break;
	}
}

void
CTK_HandleMouseButtonDown(CTK_Instance               *inst,
                          const SDL_MouseButtonEvent  e)
{
	int i;
	SDL_FPoint p;
	CTK_WidgetId w;

	for (i = 0; i < inst->enabled_ws; i++) {
		w = inst->enabled_w[i];

		p.x = e.x;
		p.y = e.y;
		if (SDL_PointInRectFloat(&p, &inst->rect[w])) {
			CTK_SetFocusedWidget(inst, w);

			if (CTK_WTYPE_SCALE == inst->type[w]) {
				inst->drag = true;
				CTK_HandleDrag(inst, p.x);
			}

			if (NULL != inst->button_press[w]) {
				inst->button_press[w](inst,
				                      e,
				                      w,
				                      inst->button_press_data[w]);
			}
			break;
		}
	}
}

void
CTK_HandleMouseButtonUp(CTK_Instance               *inst,
                        const SDL_MouseButtonEvent  e)
{
	int i;
	SDL_FPoint p;
	CTK_WidgetId w;

	inst->drag = false;

	for (i = 0; i < inst->enabled_ws; i++) {
		w = inst->enabled_w[i];
		p.x = e.x;
		p.y = e.y;

		if (!SDL_PointInRectFloat(&p, &inst->rect[w]))
			continue;

		switch (inst->type[w]) {
		case CTK_WTYPE_UNKNOWN:
		case CTK_WTYPE_BUTTON:
		case CTK_WTYPE_ENTRY:
		case CTK_WTYPE_LABEL:
		case CTK_WTYPE_PROGRESSBAR:
		case CTK_WTYPE_SCALE:
			break;

		case CTK_WTYPE_CHECKBOX:
			if (inst->toggle[w] != true)
				inst->toggle[w] = true;
			else
				inst->toggle[w] = false;
			CTK_CreateWidgetTexture(inst, w);
			break;

		case CTK_WTYPE_RADIOBUTTON:
			CTK_ToggleRadiobutton(inst, w);
			break;
		}

		if (NULL != inst->button_release[w]) {
			inst->button_release[w](inst,
			                        e,
			                        w,
			                        inst->button_release_data[w]);
		}
		if (NULL != inst->trigger[w]) {
			inst->trigger[w](inst,
			                 w,
			                 inst->trigger_data[w]);
		}
	}
}

void
CTK_HandleMouseWheel(CTK_Instance *inst,
                     const SDL_MouseWheelEvent e)
{
	int i;
	SDL_FPoint p;
	CTK_WidgetId w;

	for (i = 0; i < inst->enabled_ws; i++) {
		w = inst->enabled_w[i];
		p.x = e.mouse_x;
		p.y = e.mouse_y;

		if (!SDL_PointInRectFloat(&p, &inst->rect[w]))
			continue;

		if (inst->type[w] == CTK_WTYPE_SCALE) {
			if (e.x > 0 || e.y > 0) {
				if (inst->value[w] > 0) {
					CTK_SetWidgetValue(inst,
					                   w,
					                   inst->value[w] - 1);
				}
			} else {
				CTK_SetWidgetValue(inst, w, inst->value[w] + 1);
			}
		}
	}
}

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst)
{
	return inst->focusable_w[inst->focused_w];
}

float
CTK_GetScaleSliderWidth(const CTK_Instance *inst,
                        const CTK_WidgetId widget)
{
	return inst->rect[widget].w * CTK_SCALE_SLIDER_SIZE_FRACTION;
}

bool
CTK_GetWidgetEnabledId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       int                *cacheId)
{
	int i;

	for (i = 0; i < inst->enabled_ws; i++) {
		if (widget == inst->enabled_w[i]) {
			*cacheId = i;
			return true;
		}
	}

	return false;
}

bool
CTK_GetWidgetFocusableId(const CTK_Instance *inst,
                         const CTK_WidgetId  widget,
                         int                *cacheId)
{
	int i;

	for (i = 0; i < inst->focusable_ws; i++) {
		if (widget == inst->focusable_w[i]) {
			*cacheId = i;
			return true;
		}
	}

	return false;
}

bool
CTK_GetWidgetVisibleId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       int                *cacheId)
{
	int i;

	for (i = 0; i < inst->visible_ws; i++) {
		if (widget == inst->visible_w[i]) {
			*cacheId = i;
			return true;
		}
	}

	return false;
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

bool
CTK_IsWidgetEnabled(const CTK_Instance *inst,
                    const CTK_WidgetId  widget)
{
	int dummy;

	return CTK_GetWidgetEnabledId(inst, widget, &dummy);
}

bool
CTK_IsWidgetFocusable(const CTK_Instance *inst,
                      const CTK_WidgetId  widget)
{
	int dummy;

	return CTK_GetWidgetFocusableId(inst, widget, &dummy);
}

bool
CTK_IsWidgetVisible(const CTK_Instance *inst,
                    const CTK_WidgetId  widget)
{
	int dummy;

	return CTK_GetWidgetVisibleId(inst, widget, &dummy);
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
CTK_SetFocusedWidget(CTK_Instance       *inst,
                     const CTK_WidgetId  widget)
{
	int i;

	for (i = 0; i < inst->focusable_ws; i++) {
		if (widget == inst->focusable_w[i] &&
		    CTK_IsWidgetVisible(inst, widget)) {
			inst->focused_w = i;
			break;
		}
	}

	if (CTK_WTYPE_ENTRY == inst->type[CTK_GetFocusedWidget(inst)]) {
		SDL_StartTextInput(inst->win);
	} else {
		SDL_StopTextInput(inst->win);
	}
	inst->redraw = true;
}

void
CTK_SetWidgetEnabled(CTK_Instance       *inst,
                     const CTK_WidgetId  widget,
                     const bool          enabled)
{
	int i;
	bool is_enabled;
	int enabledId;

	is_enabled = CTK_GetWidgetEnabledId(inst, widget, &enabledId);

	if (enabled == is_enabled) {
		return;
	}

	if (true == enabled) {
		inst->enabled_w[inst->enabled_ws] = widget;
		inst->enabled_ws++;

		CTK_SetWidgetVisible(inst, widget, true);
	} else {
		for (i = enabledId; i < inst->enabled_ws - 1; i++) {
			inst->enabled_w[i] = inst->enabled_w[i + 1];
		}
		inst->enabled_ws--;

		CTK_SetWidgetFocusable(inst, widget, false);
	}

	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetFocusable(CTK_Instance       *inst,
                       const CTK_WidgetId  widget,
                       const bool          focusable)
{
	int i;
	bool is_focusable;
	int focusableId;

	is_focusable = CTK_GetWidgetFocusableId(inst, widget, &focusableId);

	if (focusable == is_focusable) {
		return;
	}

	if (true == focusable) {
		inst->focusable_w[inst->focusable_ws] = widget;
		inst->focusable_ws++;

		CTK_SetWidgetVisible(inst, widget, true);
		CTK_SetWidgetEnabled(inst, widget, true);
	} else {
		for (i = focusableId; i < inst->focusable_ws - 1; i++) {
			inst->focusable_w[i] = inst->focusable_w[i + 1];
		}
		inst->focusable_ws--;
	}

	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetText(CTK_Instance       *inst,
                  const CTK_WidgetId  widget,
                  const char         *text)
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
                           const CTK_WidgetId       widget,
                           const CTK_TextAlignment  alignment)
{
	inst->text_alignment[widget] = alignment;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetTextAndResize(CTK_Instance       *inst,
                           const CTK_WidgetId  widget,
                           const char         *text)
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
CTK_SetWidgetToggle(CTK_Instance       *inst,
                    const CTK_WidgetId  widget,
                    const bool          toggle)
{
	inst->toggle[widget] = toggle;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetValue(CTK_Instance       *inst,
                   const CTK_WidgetId  widget,
                   const unsigned int  value)
{
	if (value > inst->value_max[widget])
		inst->value[widget] = inst->value_max[widget];
	else
		inst->value[widget] = value;

	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetVisible(CTK_Instance       *inst,
                     const CTK_WidgetId  widget,
                     const bool          visible)
{
	int i;
	bool is_visible;
	int visibleId;

	is_visible = CTK_GetWidgetVisibleId(inst, widget, &visibleId);

	if (visible == is_visible) {
		return;
	}

	if (true == visible) {
		inst->visible_w[inst->visible_ws] = widget;
		inst->visible_ws++;
	} else {
		for (i = visibleId; i < inst->visible_ws - 1; i++) {
			inst->visible_w[i] = inst->visible_w[i + 1];
		}
		inst->visible_ws--;

		CTK_SetWidgetFocusable(inst, widget, false);
		CTK_SetWidgetEnabled(inst, widget, false);
	}
}

void
CTK_TickInstance(CTK_Instance *inst)
{
	SDL_Event e;
	CTK_WidgetId fw;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			CTK_HandleMouseButtonDown(inst, e.button);
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			CTK_HandleMouseButtonUp(inst, e.button);
			break;

		case SDL_EVENT_MOUSE_MOTION:
			if (inst->drag)
				CTK_HandleDrag(inst, e.motion.x);
			break;

		case SDL_EVENT_MOUSE_WHEEL:
			CTK_HandleMouseWheel(inst, e.wheel);
			break;

		case SDL_EVENT_KEY_DOWN:
			CTK_HandleKeyDown(inst, e.key);
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
CTK_ToggleCheckbox(CTK_Instance *inst,
                   CTK_WidgetId  widget)
{
	if (true == inst->toggle[widget])
		inst->toggle[widget] = false;
	else
		inst->toggle[widget] = true;

	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_ToggleRadiobutton(CTK_Instance *inst,
                      CTK_WidgetId  widget)
{
	int i;

	if (inst->toggle[widget])
		return;

	for (i = 0; i < inst->count; i++) {
		if (inst->group[i] == inst->group[widget]) {
			inst->toggle[i] = false;
			CTK_CreateWidgetTexture(inst, i);
		}
	}
	inst->toggle[widget] = true;
	CTK_CreateWidgetTexture(inst, widget);
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
