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

typedef struct CTK_Style {
	SDL_Color bg;
	SDL_Color bg_button;
	SDL_Color bg_entry;
	SDL_Color bg_label;
	SDL_Color bg_progressbar;
	SDL_Color bg_scale;
	SDL_Color bg_widget;
	SDL_Color border;
	SDL_Color fg;
	SDL_Color fg_disabled;
	SDL_Color focus;
	SDL_Color scale_slider;
} CTK_Style;

typedef struct CTK_Instance {
	bool               active;
	bool               redraw;
	CTK_Style          style;
	int                tabfocus;
	CTK_WidgetId       taborder[CTK_MAX_WIDGETS];
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
	int                group[CTK_MAX_WIDGETS];
	int                scroll[CTK_MAX_WIDGETS];
	char               text[CTK_MAX_TEXTLEN][CTK_MAX_WIDGETS];
	CTK_TextAlignment  text_alignment[CTK_MAX_WIDGETS];
	CTK_WidgetType     type[CTK_MAX_WIDGETS];
	float              value[CTK_MAX_WIDGETS];
	bool               visible[CTK_MAX_WIDGETS];
	SDL_FRect          rect[CTK_MAX_WIDGETS];
	SDL_Texture       *texture[CTK_MAX_WIDGETS];

	/* widget events */
	void              (*on_click[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                               const CTK_WidgetId,
	                                               void*);
	void              *on_click_data[CTK_MAX_WIDGETS];
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

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst);

float
CTK_GetScaleSliderWidth(const CTK_Instance *inst,
                        const CTK_WidgetId widget);

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
CTK_SetFocusedWidget(CTK_Instance       *inst,
                     const CTK_WidgetId  widget);

void
CTK_SetWidgetEnabled(CTK_Instance       *inst,
                     const CTK_WidgetId  widget,
                     const bool          enabled);

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
CTK_SetWidgetValue(CTK_Instance       *inst,
                   const CTK_WidgetId  widget,
                   const float         value);

void
CTK_TickInstance(CTK_Instance *inst);

void
CTK_ToggleRadiobutton(CTK_Instance *inst,
                      CTK_WidgetId  widget);

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

	.bg_progressbar.r = 0xc3,
	.bg_progressbar.g = 0xc3,
	.bg_progressbar.b = 0xc3,
	.bg_progressbar.a = 0xff,

	.bg_scale.r = 0xc3,
	.bg_scale.g = 0xc3,
	.bg_scale.b = 0xc3,
	.bg_scale.a = 0xff,

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

	.focus.r = 0x48,
	.focus.g = 0x68,
	.focus.b = 0x87,
	.focus.a = 0xff,

	.scale_slider.r = 0xda,
	.scale_slider.g = 0xda,
	.scale_slider.b = 0xda,
	.scale_slider.a = 0xff,
};

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
	inst->bg[ret] = &inst->style.bg_button;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->focusable[ret] = true;
	inst->text_alignment[ret] = CTK_TEXT_ALIGNMENT_CENTER;
	inst->type[ret] = CTK_WTYPE_BUTTON;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_BUTTON_W;
	inst->rect[ret].h = CTK_DEFAULT_BUTTON_H;

	return ret;
}

CTK_WidgetId
CTK_AddCheckbox(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_entry;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->focusable[ret] = true;
	inst->type[ret] = CTK_WTYPE_CHECKBOX;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_CHECKBOX_W;
	inst->rect[ret].h = CTK_DEFAULT_CHECKBOX_H;
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddEntry(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_entry;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->focusable[ret] = true;
	inst->type[ret] = CTK_WTYPE_ENTRY;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_ENTRY_W;
	inst->rect[ret].h = CTK_DEFAULT_ENTRY_H;
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddLabel(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_label;
	inst->enabled[ret] = true;
	inst->type[ret] = CTK_WTYPE_LABEL;
	inst->visible[ret] = true;
	inst->rect[ret].h = CTK_DEFAULT_LABEL_H;

	return ret;
}

CTK_WidgetId
CTK_AddProgressbar(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_progressbar;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->type[ret] = CTK_WTYPE_PROGRESSBAR;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_PROGRESSBAR_W;
	inst->rect[ret].h = CTK_DEFAULT_PROGRESSBAR_H;

	return ret;
}

CTK_WidgetId
CTK_AddRadiobutton(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_entry;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->focusable[ret] = true;
	inst->group[ret] = 0;
	inst->type[ret] = CTK_WTYPE_RADIOBUTTON;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_RADIOBUTTON_W;
	inst->rect[ret].h = CTK_DEFAULT_RADIOBUTTON_H;
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddScale(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->bg[ret] = &inst->style.bg_scale;
	inst->border[ret] = true;
	inst->enabled[ret] = true;
	inst->focusable[ret] = true;
	inst->type[ret] = CTK_WTYPE_SCALE;
	inst->visible[ret] = true;
	inst->rect[ret].w = CTK_DEFAULT_SCALE_W;
	inst->rect[ret].h = CTK_DEFAULT_SCALE_H;
	CTK_CreateWidgetTexture(inst, ret);

	return ret;
}

CTK_WidgetId
CTK_AddWidget(CTK_Instance *inst)
{
	CTK_WidgetId ret = inst->count;

	inst->taborder[inst->count] = ret;
	inst->count++;

	inst->bg[ret] = &inst->style.bg_widget;
	inst->border[ret] = false;
	inst->cursor[ret] = 0;
	inst->enabled[ret] = false;
	inst->focusable[ret] = false;
	inst->group[ret] = -1;
	inst->scroll[ret] = 0;
	inst->text[ret][0] = '\0';
	inst->text_alignment[ret] = CTK_TEXT_ALIGNMENT_LEFT;
	inst->type[ret] = CTK_WTYPE_UNKNOWN;
	inst->rect[ret].x = 0;
	inst->rect[ret].y = 0;
	inst->rect[ret].w = 0;
	inst->rect[ret].h = 0;
	inst->value[ret] = 0.0;
	inst->visible[ret] = false;
	inst->on_click[ret] = NULL;
	inst->on_click_data[ret] = NULL;

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

	/* radiobuttons specifically */
	if (CTK_WTYPE_RADIOBUTTON == inst->type[widget]) {
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
		v[0].color = CTK_ColorIntToFColor(*inst->bg[widget]);
		v[1].position.x--;
		v[1].position.y++;
		v[1].color = CTK_ColorIntToFColor(*inst->bg[widget]);
		v[2].position.y--;
		v[2].color = CTK_ColorIntToFColor(*inst->bg[widget]);
		SDL_RenderGeometry(r, NULL, v, numv, 0, 0);

		if (inst->text[widget][0]) {
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
	}

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
		if (inst->text[widget][0]) {
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
		rect.w = inst->rect[widget].w * inst->value[widget];
		rect.h = inst->rect[widget].h;
		SDL_SetRenderDrawColor(r,
				       inst->style.fg.r,
				       inst->style.fg.g,
				       inst->style.fg.b,
				       inst->style.fg.a);
		SDL_RenderFillRect(r, &rect);
		break;

	case CTK_WTYPE_RADIOBUTTON:
		/* should have been handled before */
		break;

	case CTK_WTYPE_SCALE:
		rect.w = CTK_GetScaleSliderWidth(inst, widget);
		rect.h = inst->rect[widget].h;
		rect.x = inst->value[widget] * (inst->rect[widget].w - rect.w);
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

	/* border */
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

	for (i = 0; i < inst->count; i++) {
		if (!inst->visible[i])
			continue;

		SDL_RenderTexture(r, inst->texture[i], NULL, &inst->rect[i]);
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

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst)
{
	return inst->taborder[inst->tabfocus];
}

float
CTK_GetScaleSliderWidth(const CTK_Instance *inst,
                        const CTK_WidgetId widget)
{
	return inst->rect[widget].w * CTK_SCALE_SLIDER_SIZE_FRACTION;
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
CTK_SetFocusedWidget(CTK_Instance       *inst,
                     const CTK_WidgetId  widget)
{
	int i;

	for (i = 0; i < inst->count; i++) {
		if (widget == inst->taborder[i]) {
			inst->tabfocus = i;
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
	inst->enabled[widget] = enabled;
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
CTK_SetWidgetValue(CTK_Instance       *inst,
                   const CTK_WidgetId  widget,
                   const float         value)
{
	inst->value[widget] = value;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_TickInstance(CTK_Instance *inst)
{
	SDL_Event e;
	CTK_WidgetId fw;
	int i;
	SDL_FPoint p;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			for (i = 0; i < inst->count; i++) {
				p.x = e.button.x;
				p.y = e.button.y;
				if (SDL_PointInRectFloat(&p, &inst->rect[i]) &&
				    inst->visible[i] &&
				    inst->enabled[i] &&
				    inst->focusable[i]) {
					CTK_SetFocusedWidget(inst, i);

					if (CTK_WTYPE_SCALE == inst->type[i]) {
						inst->value[i] = 1.0 /
						                 (inst->rect[i].w - CTK_GetScaleSliderWidth(inst, i)) *
						                 (p.x - inst->rect[i].x - (CTK_GetScaleSliderWidth(inst, i) / 2.0));
						if (inst->value[i] < 0.0)
							inst->value[i] = 0.0;
						else if (inst->value[i] > 1.0)
							inst->value[i] = 1.0;

						CTK_CreateWidgetTexture(inst, i);
					}
					break;
				}
			}
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			for (i = 0; i < inst->count; i++) {
				p.x = e.button.x;
				p.y = e.button.y;
				if (SDL_PointInRectFloat(&p, &inst->rect[i]) &&
				    inst->visible[i] &&
				    inst->enabled[i]) {
					if (NULL != inst->on_click[i]) {
						inst->on_click[i](inst,
						                  i,
						                  inst->on_click_data[i]);
					}
					switch (inst->type[i]) {
					case CTK_WTYPE_UNKNOWN:
					case CTK_WTYPE_BUTTON:
					case CTK_WTYPE_ENTRY:
					case CTK_WTYPE_LABEL:
					case CTK_WTYPE_PROGRESSBAR:
					case CTK_WTYPE_SCALE:
						break;

					case CTK_WTYPE_CHECKBOX:
						if (inst->text[i][0] != true)
							inst->text[i][0] = true;
						else
							inst->text[i][0] = false;
						CTK_CreateWidgetTexture(inst, i);
						break;

					case CTK_WTYPE_RADIOBUTTON:
						CTK_ToggleRadiobutton(inst, i);
						break;
					}
				}
			}
			break;

		case SDL_EVENT_KEY_DOWN:
			switch (e.key.key) {
			case SDLK_SPACE:
				fw = CTK_GetFocusedWidget(inst);

				if (inst->visible[fw] &&
				    inst->enabled[fw]) {
					if (NULL != inst->on_click[fw]) {
						inst->on_click[fw](inst,
							           fw,
							           inst->on_click_data[fw]);
					}
					switch (inst->type[fw]) {
					case CTK_WTYPE_UNKNOWN:
					case CTK_WTYPE_BUTTON:
					case CTK_WTYPE_ENTRY:
					case CTK_WTYPE_LABEL:
					case CTK_WTYPE_PROGRESSBAR:
					case CTK_WTYPE_SCALE:
						break;

					case CTK_WTYPE_CHECKBOX:
						if (inst->text[fw][0] != true)
							inst->text[fw][0] = true;
						else
							inst->text[fw][0] = false;
						CTK_CreateWidgetTexture(inst, fw);
						break;

					case CTK_WTYPE_RADIOBUTTON:
						CTK_ToggleRadiobutton(inst, fw);
						break;
					}
				}
				break;

			case SDLK_TAB:
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

				CTK_SetFocusedWidget(inst,
				                     CTK_GetFocusedWidget(inst));
				break;
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
CTK_ToggleRadiobutton(CTK_Instance *inst,
                      CTK_WidgetId  widget)
{
	int i;

	if (inst->text[widget][0])
		return;

	for (i = 0; i < inst->count; i++) {
		if (inst->group[i] == inst->group[widget]) {
			inst->text[i][0] = false;
			CTK_CreateWidgetTexture(inst, i);
		}
	}
	inst->text[widget][0] = true;
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
