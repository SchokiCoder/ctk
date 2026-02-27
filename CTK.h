/* SPDX-License-Identifier: MPL-2.0
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#ifndef _CTK_H
#define _CTK_H

#include <math.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

#include "CTK_style.h"

/* Macros
 */

#ifndef ARRLEN
#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

/* Constant defines
 */

#define CTK_DEFAULT_FONTSIZE         11
#define CTK_DEFAULT_THEME            CTK_Theme_TclTk
#define CTK_DEFAULT_WINDOW_FLAGS     (SDL_WINDOW_RESIZABLE)
#define CTK_DEFAULT_MAX_FRAMERATE    60

#define CTK_PIXELFORMAT SDL_PIXELFORMAT_RGBA8888

#define CTK_TEXTUREACCESS SDL_TEXTUREACCESS_TARGET

#define CTK_VERSION "0.3.0"

/* Configuration defines
 */

#ifndef CTK_CASCADE_MAX_COMMANDS
#define CTK_CASCADE_MAX_COMMANDS 32
#endif

#ifndef CTK_INSTANCE_MAX_WIDGETS
#define CTK_INSTANCE_MAX_WIDGETS 64
#endif

#ifndef CTK_MENUBAR_MAX_CASCADES
#define CTK_MENUBAR_MAX_CASCADES 16
#endif

#ifndef calloc
#define calloc SDL_calloc
#endif

#ifndef free
#define free SDL_free
#endif

#ifndef malloc
#define malloc SDL_malloc
#endif

#ifndef realloc
#define realloc SDL_realloc
#endif

/* Types
 */

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

typedef struct CTK_Cascade {
	TTF_Text *name;
	int       name_w;
	int       name_h;

	size_t     commands;
	TTF_Text  *label[CTK_CASCADE_MAX_COMMANDS];
	void     (*command[CTK_CASCADE_MAX_COMMANDS])(void);
} CTK_Cascade;

typedef struct CTK_Menubar {
	size_t      cascades;
	CTK_Cascade cascade[CTK_MENUBAR_MAX_CASCADES];
} CTK_Menubar;

typedef struct CTK_Instance {
	bool            active;
	SDL_Texture    *content;
	bool            drag;
	size_t          focused_casc;
	size_t          focused_w;
	size_t          hovered_casc;
	CTK_WidgetId    hovered_w;
	Uint64          max_framerate;
	CTK_Menubar    *menubar;
	bool            redraw;
	CTK_Style       style;
	TTF_TextEngine *tengine;
	SDL_Window     *win;

	/* instance events */
	void (*draw)(struct CTK_Instance*, void*);
	void *draw_data;
	void (*enter)(struct CTK_Instance*, void*);
	void *enter_data;
	void (*leave)(struct CTK_Instance*, void*);
	void *leave_data;
	void (*quit)(struct CTK_Instance*, void*);
	void *quit_data;

	/* widget cache */
	size_t             enabled_ws;
	CTK_WidgetId       enabled_w[CTK_INSTANCE_MAX_WIDGETS];
	size_t             focusable_ws;
	CTK_WidgetId       focusable_w[CTK_INSTANCE_MAX_WIDGETS];
	size_t             visible_ws;
	CTK_WidgetId       visible_w[CTK_INSTANCE_MAX_WIDGETS];

	/* widget data */
	size_t             widgets;
	bool               border[CTK_INSTANCE_MAX_WIDGETS];
	int                cursor[CTK_INSTANCE_MAX_WIDGETS];
	int                group[CTK_INSTANCE_MAX_WIDGETS];
	SDL_FRect          rect[CTK_INSTANCE_MAX_WIDGETS];
	int                scroll_x[CTK_INSTANCE_MAX_WIDGETS];
	int                selection[CTK_INSTANCE_MAX_WIDGETS];
	TTF_Text          *text[CTK_INSTANCE_MAX_WIDGETS];
	SDL_Texture       *texture[CTK_INSTANCE_MAX_WIDGETS];
	bool               toggle[CTK_INSTANCE_MAX_WIDGETS];
	CTK_WidgetType     type[CTK_INSTANCE_MAX_WIDGETS];
	unsigned short     value[CTK_INSTANCE_MAX_WIDGETS];
	unsigned short     value_max[CTK_INSTANCE_MAX_WIDGETS];
	CTK_WidgetStyle    wstyle[CTK_INSTANCE_MAX_WIDGETS];

	/* widget events */
	void (*edit[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                       const CTK_WidgetId,
	                                       void*);
	void *edit_data[CTK_INSTANCE_MAX_WIDGETS];
	void (*mouse_motion[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                               const SDL_MouseMotionEvent,
	                                               const CTK_WidgetId,
	                                               void*);
	void *mouse_motion_data[CTK_INSTANCE_MAX_WIDGETS];
	void (*mouse_press[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                              const SDL_MouseButtonEvent,
	                                              const CTK_WidgetId,
	                                              void*);
	void *mouse_press_data[CTK_INSTANCE_MAX_WIDGETS];
	void (*mouse_release[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                                const SDL_MouseButtonEvent,
	                                                const CTK_WidgetId,
	                                                void*);
	void *mouse_release_data[CTK_INSTANCE_MAX_WIDGETS];
	void (*mouse_wheel[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                              const SDL_MouseWheelEvent,
	                                              const CTK_WidgetId,
	                                              void*);
	void *mouse_wheel_data[CTK_INSTANCE_MAX_WIDGETS];
	void (*trigger[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                          const CTK_WidgetId,
	                                          void*);
	void *trigger_data[CTK_INSTANCE_MAX_WIDGETS];
} CTK_Instance;

/* Constants
 */

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

/* Global variables
 */

static TTF_Font *CTK_font = NULL;

/* Function declarations
 */

CTK_WidgetId
CTK_AddButton(CTK_Instance *inst);

CTK_WidgetId
CTK_AddCheckbox(CTK_Instance *inst);

CTK_WidgetId
CTK_AddEntry(CTK_Instance *inst);

CTK_WidgetId
CTK_AddLabel(CTK_Instance *inst);

bool
CTK_AddMenubarCascade(CTK_Instance *inst,
                      const char   *name);

bool
CTK_AddMenubarCascadeCommand(CTK_Instance  *inst,
                             const size_t   c,
                             const char    *label,
                             void         (*fn)());

CTK_WidgetId
CTK_AddProgressbar(CTK_Instance *inst);

CTK_WidgetId
CTK_AddRadiobutton(CTK_Instance *inst);

CTK_WidgetId
CTK_AddScale(CTK_Instance *inst);

CTK_WidgetId
CTK_AddWidget(CTK_Instance *inst);

void
CTK_ApplyTheme(CTK_Instance    *inst,
               const CTK_Style  theme,
               const bool       resize);

void
CTK_ApplyThemeToWidget(CTK_Instance       *inst,
                       const CTK_Style     theme,
                       const bool          resize,
                       const CTK_WidgetId  w);

SDL_FColor
CTK_ColorIntToFColor(const SDL_Color c);

void
CTK_CreateButtonTexture(CTK_Instance       *inst,
                        const CTK_WidgetId  btn);

void
CTK_CreateCheckboxTexture(CTK_Instance       *inst,
                          const CTK_WidgetId  ckb);

void
CTK_CreateEntryTexture(CTK_Instance       *inst,
                       const CTK_WidgetId  txt);

/* inst = Instance to initialize.
 * title = Used as window title.
 * winw = Window width.
 * winh = Window height.
 * flags = SDL window flags. May be 0 to use defaults.
 * Returns valid instance or NULL on failure.
 * Call SDL_GetError() for more information.
 */
CTK_Instance*
CTK_CreateInstance(const char            *title,
                   const int              winw,
                   const int              winh,
                   const SDL_WindowFlags  flags);

void
CTK_CreateLabelTexture(CTK_Instance       *inst,
                       const CTK_WidgetId  lbl);

CTK_Menubar*
CTK_CreateMenubar();

void
CTK_CreateProgressbarTexture(CTK_Instance       *inst,
                             const CTK_WidgetId  pgb);

void
CTK_CreateRadiobuttonTexture(CTK_Instance       *inst,
                             const CTK_WidgetId  rbn);

void
CTK_CreateScaleTexture(CTK_Instance       *inst,
                       const CTK_WidgetId  scl);

void
CTK_CreateWidgetTexture(CTK_Instance       *inst,
                        const CTK_WidgetId  widget);

void
CTK_DestroyInstance(CTK_Instance *inst);

void
CTK_DestroyMenubar(CTK_Menubar* m);

void
CTK_DrawInstance(CTK_Instance *inst);

void
CTK_DrawMenubar(CTK_Instance *inst);

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
CTK_HandleMouseMotion(CTK_Instance               *inst,
                      const SDL_MouseMotionEvent  e);

void
CTK_HandleMouseWheel(CTK_Instance              *inst,
                     const SDL_MouseWheelEvent  e);

void
CTK_HandleTextInput(CTK_Instance             *inst,
                    const SDL_TextInputEvent  e);

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst);

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

void
CTK_InstanceDefaultQuit(CTK_Instance *inst,
                        void         *dummy);

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

/* @text: TTF_Text
 * @start: position at which to start measuring the text
 * @len: amount chars that should be measured
 *
 * Returns size in pixels of a TTF_Text portion.
 */
SDL_Rect
CTK_MeasureTTFText(TTF_Text *text,
                   size_t    start,
                   size_t    len);

bool
CTK_RenderText(TTF_Text                *text,
               const SDL_FRect          rect,
               const CTK_TextAlignment  ta,
               const size_t             offset_x);

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
CTK_ShiftWidgetTextCursor(CTK_Instance       *inst,
                          const CTK_WidgetId  w,
                          const int           shift,
                          const bool          shift_selection);

void
CTK_TickInstance(CTK_Instance *inst);

void
CTK_ToggleCheckbox(CTK_Instance *inst,
                   CTK_WidgetId  widget);

void
CTK_ToggleRadiobutton(CTK_Instance *inst,
                      CTK_WidgetId  widget);

void
CTK_UpdatePrimarySelection(CTK_Instance *inst,
                           CTK_WidgetId  w);

void
CTK_Quit();

#ifdef CTK_IMPLEMENTATION

/* Function definitions
 */

CTK_WidgetId
CTK_AddButton(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;
	inst->focusable_w[inst->focusable_ws] = ret;
	inst->focusable_ws++;

	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_BUTTON;
	CTK_ApplyThemeToWidget(inst, inst->style, true, ret);
	CTK_SetWidgetVisible(inst, ret, true);

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

	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_CHECKBOX;
	CTK_ApplyThemeToWidget(inst, inst->style, true, ret);
	CTK_SetWidgetVisible(inst, ret, true);

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

	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_ENTRY;
	CTK_ApplyThemeToWidget(inst, inst->style, true, ret);
	CTK_SetWidgetVisible(inst, ret, true);

	return ret;
}

CTK_WidgetId
CTK_AddLabel(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;

	inst->type[ret] = CTK_WTYPE_LABEL;
	CTK_ApplyThemeToWidget(inst, inst->style, true, ret);
	CTK_SetWidgetVisible(inst, ret, true);

	return ret;
}

bool
CTK_AddMenubarCascade(CTK_Instance *inst,
                      const char   *name)
{
	size_t c = inst->menubar->cascades;

	if (inst->menubar->cascades >= CTK_MENUBAR_MAX_CASCADES) {
		SDL_SetError("Menubar can not hold more cascades");
		return false;
	}

	inst->menubar->cascade[c].name = TTF_CreateText(inst->tengine,
	                                                CTK_font, name, 0);
	TTF_GetTextSize(inst->menubar->cascade[c].name,
	                &inst->menubar->cascade[c].name_w,
	                &inst->menubar->cascade[c].name_h);
	inst->menubar->cascade[c].commands = 0;
	inst->menubar->cascades++;

	return true;
}

bool
CTK_AddMenubarCascadeCommand(CTK_Instance  *inst,
                             const size_t   c,
                             const char    *label,
                             void         (*fn)())
{
	size_t id;

	if (inst->menubar->cascade[c].commands >= CTK_CASCADE_MAX_COMMANDS) {
		SDL_SetError("Menubar cascade can not hold more commands");
		return false;
	}

	id = inst->menubar->cascade[c].commands;
	inst->menubar->cascade[c].label[id] = TTF_CreateText(inst->tengine,
	                                                           CTK_font,
	                                                           label, 0);
	inst->menubar->cascade[c].command[id] = fn;
	inst->menubar->cascade[c].commands++;

	return true;
}

CTK_WidgetId
CTK_AddProgressbar(CTK_Instance *inst)
{
	CTK_WidgetId ret;

	ret = CTK_AddWidget(inst);
	inst->enabled_w[inst->enabled_ws] = ret;
	inst->enabled_ws++;

	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_PROGRESSBAR;
	CTK_ApplyThemeToWidget(inst, inst->style, true, ret);
	inst->value_max[ret] = inst->rect[ret].w - 1;
	CTK_SetWidgetVisible(inst, ret, true);

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

	inst->border[ret] = true;
	inst->group[ret] = 0;
	inst->type[ret] = CTK_WTYPE_RADIOBUTTON;
	CTK_ApplyThemeToWidget(inst, inst->style, true, ret);
	CTK_SetWidgetVisible(inst, ret, true);

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

	inst->border[ret] = true;
	inst->type[ret] = CTK_WTYPE_SCALE;
	CTK_ApplyThemeToWidget(inst, inst->style, true, ret);
	inst->value_max[ret] = inst->rect[ret].w - 1;
	CTK_SetWidgetVisible(inst, ret, true);

	return ret;
}

CTK_WidgetId
CTK_AddWidget(CTK_Instance *inst)
{
	CTK_WidgetId ret = inst->widgets;

	inst->widgets++;
	if (inst->widgets > CTK_INSTANCE_MAX_WIDGETS) {
		SDL_SetError("Instance can not hold more widgets");
		return -1;
	}

	inst->border[ret] = false;
	inst->cursor[ret] = 0;
	inst->group[ret] = -1;
	inst->selection[ret] = inst->cursor[ret];
	inst->scroll_x[ret] = 0;
	inst->toggle[ret] = false;
	inst->type[ret] = CTK_WTYPE_UNKNOWN;
	inst->rect[ret].x = 0;
	inst->rect[ret].y = 0;
	inst->rect[ret].w = 0;
	inst->rect[ret].h = 0;
	inst->value[ret] = 0;
	inst->value_max[ret] = 0;
	inst->edit[ret] = NULL;
	inst->edit_data[ret] = NULL;
	inst->mouse_motion[ret] = NULL;
	inst->mouse_motion_data[ret] = NULL;
	inst->mouse_press[ret] = NULL;
	inst->mouse_press_data[ret] = NULL;
	inst->mouse_release[ret] = NULL;
	inst->mouse_release_data[ret] = NULL;
	inst->mouse_wheel[ret] = NULL;
	inst->mouse_wheel_data[ret] = NULL;
	inst->trigger[ret] = NULL;
	inst->trigger_data[ret] = NULL;

	inst->text[ret] = TTF_CreateText(inst->tengine, CTK_font, "", 0);
	TTF_SetTextWrapWhitespaceVisible(inst->text[ret], true);

	return ret;
}

void
CTK_ApplyTheme(CTK_Instance    *inst,
               const CTK_Style  theme,
               const bool       resize)
{
	size_t i;

	inst->style = theme;

	for (i = 0; i < inst->widgets; i++)
		CTK_ApplyThemeToWidget(inst, inst->style, i, resize);
}

void
CTK_ApplyThemeToWidget(CTK_Instance       *inst,
                       const CTK_Style     theme,
                       const bool          resize,
                       const CTK_WidgetId  w)
{
	switch (inst->type[w]) {
	case CTK_WTYPE_UNKNOWN:
		break;

	case CTK_WTYPE_BUTTON:
		inst->wstyle[w] = theme.button;
		break;

	case CTK_WTYPE_CHECKBOX:
		inst->wstyle[w] = theme.checkbox;
		break;

	case CTK_WTYPE_ENTRY:
		inst->wstyle[w] = theme.entry;
		break;

	case CTK_WTYPE_LABEL:
		inst->wstyle[w] = theme.label;
		break;

	case CTK_WTYPE_PROGRESSBAR:
		inst->wstyle[w] = theme.progressbar;
		break;

	case CTK_WTYPE_RADIOBUTTON:
		inst->wstyle[w] = theme.radiobutton;
		break;

	case CTK_WTYPE_SCALE:
		inst->wstyle[w] = theme.scale;
		break;
	}

	if (resize) {
		inst->rect[w].h = inst->wstyle[w].size_h;
		inst->rect[w].w = inst->wstyle[w].size_w;
	}

	CTK_CreateWidgetTexture(inst, w);
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

/* This assumes RenderTarget to be set to its own texture.
 */
void
CTK_CreateButtonTexture(CTK_Instance       *inst,
                        const CTK_WidgetId  btn)
{
	SDL_Renderer *r = NULL;
	SDL_FRect     rect;

	r = SDL_GetRenderer(inst->win);

	if (inst->hovered_w != btn) {
		SDL_SetRenderDrawColor(r,
		                       inst->wstyle[btn].bg.r,
		                       inst->wstyle[btn].bg.g,
		                       inst->wstyle[btn].bg.b,
		                       inst->wstyle[btn].bg.a);
	} else {
		SDL_SetRenderDrawColor(r,
		                       inst->wstyle[btn].bg_hovered.r,
		                       inst->wstyle[btn].bg_hovered.g,
		                       inst->wstyle[btn].bg_hovered.b,
		                       inst->wstyle[btn].bg_hovered.a);
	}
	SDL_RenderClear(r);

	rect.x = 0;
	rect.y = 0;
	rect.w = inst->rect[btn].w;
	rect.h = inst->rect[btn].h;

	if (CTK_IsWidgetEnabled(inst, btn)) {
		TTF_SetTextColor(inst->text[btn],
		                 inst->wstyle[btn].text.r,
		                 inst->wstyle[btn].text.g,
		                 inst->wstyle[btn].text.b,
		                 inst->wstyle[btn].text.a);
	} else {
		TTF_SetTextColor(inst->text[btn],
		                 inst->wstyle[btn].text_disabled.r,
		                 inst->wstyle[btn].text_disabled.g,
		                 inst->wstyle[btn].text_disabled.b,
		                 inst->wstyle[btn].text_disabled.a);
	}

	CTK_RenderText(inst->text[btn], rect, inst->wstyle[btn].text_align, 0);

	if (inst->border[btn]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[btn].w;
		rect.h = inst->rect[btn].h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[btn].border.r,
			               inst->wstyle[btn].border.g,
			               inst->wstyle[btn].border.b,
			               inst->wstyle[btn].border.a);
		SDL_RenderRect(r, &rect);
	}
}

/* This assumes RenderTarget to be set to its own texture.
 */
void
CTK_CreateCheckboxTexture(CTK_Instance       *inst,
                          const CTK_WidgetId  ckb)
{
	SDL_Color     bg_c;
	SDL_Color     body_c;
	SDL_Color     fg_c;
	SDL_Renderer *r = NULL;
	SDL_FRect     rect;

	r = SDL_GetRenderer(inst->win);

	if (inst->hovered_w != ckb) {
		bg_c = inst->wstyle[ckb].bg;
		body_c = inst->wstyle[ckb].body;
	} else {
		bg_c = inst->wstyle[ckb].bg_hovered;
		body_c = inst->wstyle[ckb].body_hovered;
	}
	fg_c = inst->wstyle[ckb].fg;
	if (!CTK_IsWidgetEnabled(inst, ckb)) {
		body_c = inst->wstyle[ckb].body_disabled;
		fg_c = inst->wstyle[ckb].fg_disabled;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	rect.x = (inst->rect[ckb].w - inst->wstyle[ckb].size_body_w) / 2;
	rect.y = (inst->rect[ckb].h - inst->wstyle[ckb].size_body_h) / 2;
	rect.w = inst->wstyle[ckb].size_body_w;
	rect.h = inst->wstyle[ckb].size_body_h;
	SDL_SetRenderDrawColor(r, body_c.r, body_c.g, body_c.b, body_c.a);
	SDL_RenderFillRect(r, &rect);

	if (inst->toggle[ckb]) {
		rect.w = inst->wstyle[ckb].size_fill_w;
		rect.h = inst->wstyle[ckb].size_fill_h;
		rect.x += inst->wstyle[ckb].size_body_w - rect.w;
		rect.y += inst->wstyle[ckb].size_body_h - rect.h;
		SDL_SetRenderDrawColor(r, fg_c.r, fg_c.g, fg_c.b, fg_c.a);
		SDL_RenderFillRect(r, &rect);
	}

	if (inst->border[ckb]) {
		rect.x = (inst->rect[ckb].w - inst->wstyle[ckb].size_body_w) / 2;
		rect.y = (inst->rect[ckb].h - inst->wstyle[ckb].size_body_h) / 2;
		rect.w = inst->wstyle[ckb].size_body_w;
		rect.h = inst->wstyle[ckb].size_body_h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[ckb].border.r,
			               inst->wstyle[ckb].border.g,
			               inst->wstyle[ckb].border.b,
			               inst->wstyle[ckb].border.a);
		SDL_RenderRect(r, &rect);
	}
}

/* This assumes RenderTarget to be set to its own texture.
 */
void
CTK_CreateEntryTexture(CTK_Instance       *inst,
                       const CTK_WidgetId  txt)
{
	size_t        a, b;
	SDL_Color     bg_c;
	SDL_Color     body_c;
	SDL_Rect      irect;
	SDL_Renderer *r = NULL;
	SDL_FRect     rect;
	SDL_Color     text_c;

	r = SDL_GetRenderer(inst->win);

	if (inst->hovered_w != txt) {
		bg_c = inst->wstyle[txt].bg;
		body_c = inst->wstyle[txt].body;
	} else {
		bg_c = inst->wstyle[txt].bg_hovered;
		body_c = inst->wstyle[txt].body_hovered;
	}
	text_c = inst->wstyle[txt].text;
	if (!CTK_IsWidgetEnabled(inst, txt)) {
		body_c = inst->wstyle[txt].body_disabled;
		text_c = inst->wstyle[txt].text_disabled;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	rect.x = 0;
	rect.y = 0;
	rect.w = inst->rect[txt].w;
	rect.h = inst->rect[txt].h;
	SDL_SetRenderDrawColor(r, body_c.r, body_c.g, body_c.b, body_c.a);
	SDL_RenderFillRect(r, &rect);

	if (inst->cursor[txt] != inst->selection[txt]) {
		if (inst->cursor[txt] > inst->selection[txt]) {
			a = inst->selection[txt];
			b = inst->cursor[txt];
		} else {
			a = inst->cursor[txt];
			b = inst->selection[txt];
		}

		irect = CTK_MeasureTTFText(inst->text[txt], a, b - a);
		rect.x = irect.x;
		rect.y = (inst->rect[txt].h - irect.h) / 2.0;
		rect.w = irect.w;
		rect.h = irect.h;

		SDL_SetRenderDrawColor(r,
				       inst->wstyle[txt].text_bg_selected.r,
				       inst->wstyle[txt].text_bg_selected.g,
				       inst->wstyle[txt].text_bg_selected.b,
				       inst->wstyle[txt].text_bg_selected.a);
		SDL_RenderFillRect(r, &rect);
	}

	rect.x = 0;
	rect.y = 0;
	rect.w = inst->rect[txt].w;
	rect.h = inst->rect[txt].h;
	TTF_SetTextColor(inst->text[txt], text_c.r, text_c.g, text_c.b, text_c.a);
	CTK_RenderText(inst->text[txt],
	               rect,
	               inst->wstyle[txt].text_align,
	               inst->scroll_x[txt]);

	if (inst->border[txt]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[txt].w;
		rect.h = inst->rect[txt].h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[txt].border.r,
			               inst->wstyle[txt].border.g,
			               inst->wstyle[txt].border.b,
			               inst->wstyle[txt].border.a);
		SDL_RenderRect(r, &rect);
	}
}

CTK_Instance*
CTK_CreateInstance(const char            *title,
                   const int              winw,
                   const int              winh,
                   const SDL_WindowFlags  flags)
{
	SDL_WindowFlags f;
	CTK_Instance *inst;
	SDL_Renderer *r;

	inst = malloc(sizeof(CTK_Instance));
	if (NULL == inst) {
		SDL_SetError("Instance could not allocate");
		return NULL;
	}

	inst->active = true;
	inst->drag = false;
	inst->focused_w = 0;
	inst->hovered_casc = -1;
	inst->hovered_w = -1;
	inst->max_framerate = CTK_DEFAULT_MAX_FRAMERATE;
	inst->menubar = NULL;
	inst->style = CTK_DEFAULT_THEME;
	inst->redraw = true;

	inst->draw = NULL;
	inst->draw_data = NULL;
	inst->enter = NULL;
	inst->enter_data = NULL;
	inst->leave = NULL;
	inst->leave_data = NULL;
	inst->quit = CTK_InstanceDefaultQuit;
	inst->quit_data = NULL;

	inst->widgets = 0;

	inst->enabled_ws = 0;
	inst->focusable_ws = 0;
	inst->visible_ws = 0;

	if (0 == flags)
		f = CTK_DEFAULT_WINDOW_FLAGS;
	else
		f = flags;

	if (!SDL_CreateWindowAndRenderer(title, winw, winh, f, &inst->win, &r)) {
		SDL_SetError("Instance could create window or renderer");
		return NULL;
	}

	inst->tengine = TTF_CreateRendererTextEngine(r);
	if (NULL == inst->tengine) {
		SDL_SetError("Instance could no create a text engine");
		return NULL;
	}

	if (!SDL_SetRenderLogicalPresentation(r, winw, winh,
	                                      SDL_LOGICAL_PRESENTATION_DISABLED)) {
		SDL_SetError("Instance could not set logical presentation");
		return NULL;
	}

	inst->content = SDL_CreateTexture(r, CTK_PIXELFORMAT, CTK_TEXTUREACCESS,
	                                  winw, winh);
	if (NULL == inst->content) {
		SDL_SetError("Instance could not create a texture");
		return NULL;
	}

	return inst;
}

/* This assumes RenderTarget to be set to its own texture.
 */
void
CTK_CreateLabelTexture(CTK_Instance       *inst,
                       const CTK_WidgetId  lbl)
{
	/* it's the same */
	CTK_CreateButtonTexture(inst, lbl);
}

CTK_Menubar*
CTK_CreateMenubar()
{
	CTK_Menubar *ret;

	ret = malloc(sizeof(CTK_Menubar));
	ret->cascades = 0;

	return ret;
}

/* This assumes RenderTarget to be set to its own texture.
 */
void
CTK_CreateProgressbarTexture(CTK_Instance       *inst,
                             const CTK_WidgetId  pgb)
{
	SDL_Color     bg_c;
	SDL_Color     fg_c;
	SDL_Renderer *r = NULL;
	SDL_FRect     rect;

	r = SDL_GetRenderer(inst->win);

	if (inst->hovered_w != pgb) {
		bg_c = inst->wstyle[pgb].bg;
	} else {
		bg_c = inst->wstyle[pgb].bg_hovered;
	}
	fg_c = inst->wstyle[pgb].fg;
	if (!CTK_IsWidgetEnabled(inst, pgb)) {
		fg_c = inst->wstyle[pgb].fg_disabled;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	rect.x = 0;
	rect.y = 0;
	rect.w = inst->rect[pgb].w *
	         ((float) inst->value[pgb] /
	          (float) inst->value_max[pgb]);
	rect.h = inst->rect[pgb].h;
	SDL_SetRenderDrawColor(r, fg_c.r, fg_c.g, fg_c.b, fg_c.a);
	SDL_RenderFillRect(r, &rect);

	if (inst->border[pgb]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[pgb].w;
		rect.h = inst->rect[pgb].h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[pgb].border.r,
			               inst->wstyle[pgb].border.g,
			               inst->wstyle[pgb].border.b,
			               inst->wstyle[pgb].border.a);
		SDL_RenderRect(r, &rect);
	}
}

/* This assumes RenderTarget to be set to its own texture.
 */
void
CTK_CreateRadiobuttonTexture(CTK_Instance       *inst,
                             const CTK_WidgetId  rbn)
{
	SDL_Color     bg_c;
	SDL_Color     body_c;
	SDL_Color     fg_c;
	SDL_FRect     rect;
	SDL_Renderer *r = NULL;
	SDL_Texture  *t;

	r = SDL_GetRenderer(inst->win);

	if (inst->hovered_w != rbn) {
		bg_c = inst->wstyle[rbn].bg;
		body_c = inst->wstyle[rbn].body;
	} else {
		bg_c = inst->wstyle[rbn].bg_hovered;
		body_c = inst->wstyle[rbn].body_hovered;
	}
	fg_c = inst->wstyle[rbn].fg;
	if (!CTK_IsWidgetEnabled(inst, rbn)) {
		body_c = inst->wstyle[rbn].body_disabled;
		fg_c = inst->wstyle[rbn].fg_disabled;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	t = SDL_CreateTexture(r,
	                      CTK_PIXELFORMAT,
	                      CTK_TEXTUREACCESS,
	                      inst->wstyle[rbn].size_body_w,
	                      inst->wstyle[rbn].size_body_h);

	SDL_SetRenderTarget(r, t);
	SDL_SetRenderDrawColor(r, body_c.r, body_c.g, body_c.b, body_c.a);
	SDL_RenderClear(r);

	if (inst->toggle[rbn]) {
		rect.w = inst->wstyle[rbn].size_fill_w;
		rect.h = inst->wstyle[rbn].size_fill_h;
		rect.x = (inst->wstyle[rbn].size_body_w - rect.w) / 2;
		rect.y = (inst->wstyle[rbn].size_body_h - rect.h) / 2;
		SDL_SetRenderDrawColor(r, fg_c.r, fg_c.g, fg_c.b, fg_c.a);
		SDL_RenderFillRect(r, &rect);
	}

	if (inst->border[rbn]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->wstyle[rbn].size_body_w;
		rect.h = inst->wstyle[rbn].size_body_h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[rbn].border.r,
			               inst->wstyle[rbn].border.g,
			               inst->wstyle[rbn].border.b,
			               inst->wstyle[rbn].border.a);
		SDL_RenderRect(r, &rect);
	}

	SDL_SetRenderTarget(r, inst->texture[rbn]);
	rect.x = (inst->rect[rbn].w - inst->wstyle[rbn].size_body_w) / 2;
	rect.y = (inst->rect[rbn].h - inst->wstyle[rbn].size_body_h) / 2;
	rect.w = inst->wstyle[rbn].size_body_w;
	rect.h = inst->wstyle[rbn].size_body_h;
	SDL_RenderTextureRotated(r,
	                         t,
	                         NULL,
	                         &rect,
	                         45.0,
	                         NULL,
	                         SDL_FLIP_NONE);

	SDL_DestroyTexture(t);
}

/* This assumes RenderTarget to be set to its own texture.
 */
void
CTK_CreateScaleTexture(CTK_Instance       *inst,
                       const CTK_WidgetId  scl)
{
	SDL_Color     bg_c;
	SDL_Color     body_c;
	SDL_Color     border_c;
	SDL_Renderer *r = NULL;
	SDL_FRect     rect;

	r = SDL_GetRenderer(inst->win);

	border_c = inst->wstyle[scl].border;
	if (inst->hovered_w != scl) {
		bg_c = inst->wstyle[scl].bg;
		body_c = inst->wstyle[scl].body;
	} else {
		bg_c = inst->wstyle[scl].bg_hovered;
		body_c = inst->wstyle[scl].body_hovered;
	}
	if (!CTK_IsWidgetEnabled(inst, scl)) {
		body_c = inst->wstyle[scl].body_disabled;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	rect.w = inst->wstyle[scl].size_body_w / 2;
	rect.h = inst->wstyle[scl].size_body_h;
	rect.x = ((float) inst->value[scl] /
	          (float) inst->value_max[scl]) *
	         (inst->rect[scl].w - (rect.w * 2));
	rect.y = 0;

	SDL_SetRenderDrawColor(r, body_c.r, body_c.g, body_c.b, body_c.a);
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r, border_c.r, border_c.g, border_c.b, border_c.a);
	SDL_RenderRect(r, &rect);

	rect.x += rect.w;

	SDL_SetRenderDrawColor(r, body_c.r, body_c.g, body_c.b, body_c.a);
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r, border_c.r, border_c.g, border_c.b, border_c.a);
	SDL_RenderRect(r, &rect);

	if (inst->border[scl]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[scl].w;
		rect.h = inst->rect[scl].h;

		SDL_SetRenderDrawColor(r,
		                       border_c.r, border_c.g, border_c.b,
		                       border_c.a);
		SDL_RenderRect(r, &rect);
	}
}

void
CTK_CreateWidgetTexture(CTK_Instance       *inst,
                        const CTK_WidgetId  widget)
{
	SDL_Renderer *r = NULL;

	r = SDL_GetRenderer(inst->win);
	SDL_DestroyTexture(inst->texture[widget]);
	inst->texture[widget] = SDL_CreateTexture(r,
	                                          CTK_PIXELFORMAT,
	                                          CTK_TEXTUREACCESS,
	                                          inst->rect[widget].w,
	                                          inst->rect[widget].h);

	SDL_SetRenderTarget(r, inst->texture[widget]);

	switch (inst->type[widget]) {
	case CTK_WTYPE_UNKNOWN:
		break;

	case CTK_WTYPE_BUTTON:
		CTK_CreateButtonTexture(inst, widget);
		break;

	case CTK_WTYPE_CHECKBOX:
		CTK_CreateCheckboxTexture(inst, widget);
		break;

	case CTK_WTYPE_ENTRY:
		CTK_CreateEntryTexture(inst, widget);
		break;

	case CTK_WTYPE_LABEL:
		CTK_CreateLabelTexture(inst, widget);
		break;

	case CTK_WTYPE_PROGRESSBAR:
		CTK_CreateProgressbarTexture(inst, widget);
		break;

	case CTK_WTYPE_RADIOBUTTON:
		CTK_CreateRadiobuttonTexture(inst, widget);
		break;

	case CTK_WTYPE_SCALE:
		CTK_CreateScaleTexture(inst, widget);
		break;
	}

	inst->redraw = true;
	SDL_SetRenderTarget(r, NULL);
}

void
CTK_DestroyInstance(CTK_Instance *inst)
{
	size_t i;

	if (NULL != inst->menubar) {
		CTK_DestroyMenubar(inst->menubar);
	}

	for (i = 0; i < inst->widgets; i++) {
		SDL_DestroyTexture(inst->texture[i]);
		TTF_DestroyText(inst->text[i]);
	}

	SDL_DestroyTexture(inst->content);
	TTF_DestroyRendererTextEngine(inst->tengine);
	SDL_DestroyWindow(inst->win);
	free(inst);
}

void
CTK_DestroyMenubar(CTK_Menubar* m)
{
	size_t a, b;

	for (a = 0; a < m->cascades; a++) {
		for (b = 0; b < m->cascade[a].commands; b++) {
			TTF_DestroyText(m->cascade[a].label[b]);
		}
		TTF_DestroyText(m->cascade[a].name);
	}

	free(m);
}

void
CTK_DrawInstance(CTK_Instance *inst)
{
	size_t        i;
	SDL_FRect     frect;
	CTK_WidgetId  fw;
	SDL_Renderer *r;
	SDL_Rect      rect;

	fw = CTK_GetFocusedWidget(inst);

	if (!inst->redraw)
		return;

	r = SDL_GetRenderer(inst->win);

	/* content: bg */
	SDL_SetRenderTarget(r, inst->content);

	SDL_SetRenderDrawColor(r,
	                       inst->style.bg.r,
	                       inst->style.bg.g,
	                       inst->style.bg.b,
	                       inst->style.bg.a);
	SDL_RenderClear(r);

	/* content: widgets */
	for (i = 0; i < inst->visible_ws; i++) {
		SDL_RenderTexture(r,
		                  inst->texture[inst->visible_w[i]],
		                  NULL,
		                  &inst->rect[inst->visible_w[i]]);
	}

	/* content: focus ring */
	SDL_SetRenderDrawColor(r,
	                       inst->style.focus.r,
	                       inst->style.focus.g,
	                       inst->style.focus.b,
	                       inst->style.focus.a);
	SDL_RenderRect(r, &inst->rect[fw]);

	/* content: text cursor */
	if (CTK_WTYPE_ENTRY == inst->type[fw]) {
		rect = CTK_MeasureTTFText(inst->text[fw], inst->cursor[fw], 0);
		rect.x -= inst->scroll_x[fw];

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[fw].text.r,
			               inst->wstyle[fw].text.g,
			               inst->wstyle[fw].text.b,
			               inst->wstyle[fw].text.a);
		SDL_RenderLine(r,
		               inst->rect[fw].x + rect.x,
		               inst->rect[fw].y + 2,
		               inst->rect[fw].x + rect.x,
		               inst->rect[fw].y + inst->rect[fw].h - 3);
	}
	SDL_SetRenderTarget(r, NULL);

	/* content */
	frect.x = 0;
	frect.y = (NULL == inst->menubar ? 0 : inst->style.menubar_h);
	frect.w = inst->content->w;
	frect.h = inst->content->h;
	SDL_RenderTexture(r, inst->content, NULL, &frect);

	/* menubar */
	if (NULL != inst->menubar) {
		CTK_DrawMenubar(inst);
	}

	/* final */
	SDL_RenderPresent(r);
	inst->redraw = false;

	if (NULL != inst->draw)
		inst->draw(inst, inst->draw_data);
}

void
CTK_DrawMenubar(CTK_Instance *inst)
{
	float         cascade_x;
	float         cascade_y;
	float         command_x;
	float         command_y;
	size_t        i;
	SDL_Renderer *r;
	SDL_FRect     frect;
	int           w, h;

	r = SDL_GetRenderer(inst->win);

	frect.x = 0;
	frect.y = 0;
	frect.w = inst->content->w;
	frect.h = inst->style.menubar_h;
	SDL_SetRenderDrawColor(r,
		               inst->style.menubar_bg_clr.r,
		               inst->style.menubar_bg_clr.g,
		               inst->style.menubar_bg_clr.b,
		               inst->style.menubar_bg_clr.a);
	SDL_RenderFillRect(r, &frect);

	cascade_x = 0;
	for (i = 0; i < inst->menubar->cascades; i++) {
		if (inst->hovered_casc == i) {
			frect.x = cascade_x;
			frect.y = 0;
			frect.w = inst->menubar->cascade[i].name_w;
			frect.h = inst->style.menubar_h;
			SDL_SetRenderDrawColor(r,
					       inst->style.menubar_bg_hovered_clr.r,
					       inst->style.menubar_bg_hovered_clr.g,
					       inst->style.menubar_bg_hovered_clr.b,
					       inst->style.menubar_bg_hovered_clr.a);
			SDL_RenderFillRect(r, &frect);

			SDL_SetRenderDrawColor(r,
					       inst->style.menubar_border_clr.r,
					       inst->style.menubar_border_clr.g,
					       inst->style.menubar_border_clr.b,
					       inst->style.menubar_border_clr.a);
			SDL_RenderRect(r, &frect);
		}

		cascade_y = (inst->style.menubar_h -
		             inst->menubar->cascade[i].name_h) /
		            2.0;
		TTF_SetTextColor(inst->menubar->cascade[i].name,
	                         inst->style.menubar_text_clr.r,
	                         inst->style.menubar_text_clr.g,
	                         inst->style.menubar_text_clr.b,
	                         inst->style.menubar_text_clr.a);
		TTF_DrawRendererText(inst->menubar->cascade[i].name,
		                     cascade_x,
		                     cascade_y);

		cascade_x += inst->menubar->cascade[i].name_w;
	}

	frect.x = 0;
	frect.y = 0;
	frect.w = inst->content->w;
	frect.h = inst->style.menubar_h;
	SDL_SetRenderDrawColor(r,
		               inst->style.menubar_border_clr.r,
		               inst->style.menubar_border_clr.g,
		               inst->style.menubar_border_clr.b,
		               inst->style.menubar_border_clr.a);
	if (inst->style.menubar_border) {
		SDL_RenderRect(r, &frect);
	}

	if (inst->focused_casc < inst->menubar->cascades) {
		frect.x = 0;
		frect.y = inst->style.menubar_h;
		for (i = 0; i < inst->focused_casc; i++) {
			TTF_GetTextSize(inst->menubar->cascade[i].name, &w, &h);
			frect.x += w;
		}

		frect.w = 0;
		frect.h = 0;
		for (i = 0;
		     i < inst->menubar->cascade[inst->focused_casc].commands;
		     i++) {
			TTF_GetTextSize(inst->menubar->cascade[inst->focused_casc].label[i],
			                &w, NULL);
			frect.h += inst->style.menubar_command_h;
			if (w > frect.w) {
				frect.w = w;
			}
		}
		SDL_SetRenderDrawColor(r,
				       inst->style.menubar_bg_clr.r,
				       inst->style.menubar_bg_clr.g,
				       inst->style.menubar_bg_clr.b,
				       inst->style.menubar_bg_clr.a);
		SDL_RenderFillRect(r, &frect);

		SDL_SetRenderDrawColor(r,
		               inst->style.menubar_border_clr.r,
		               inst->style.menubar_border_clr.g,
		               inst->style.menubar_border_clr.b,
		               inst->style.menubar_border_clr.a);
		if (inst->style.menubar_border) {
			SDL_RenderRect(r, &frect);
		}

		command_x = frect.x;
		command_y = frect.y;
		for (i = 0;
		     i < inst->menubar->cascade[inst->focused_casc].commands;
		     i++) {
			TTF_GetTextSize(inst->menubar->cascade[inst->focused_casc].label[i],
			                &w, &h);

			TTF_SetTextColor(inst->menubar->cascade[inst->focused_casc].label[i],
			                 inst->style.menubar_text_clr.r,
			                 inst->style.menubar_text_clr.g,
			                 inst->style.menubar_text_clr.b,
			                 inst->style.menubar_text_clr.a);
			TTF_DrawRendererText(inst->menubar->cascade[inst->focused_casc].label[i],
			                     command_x,
			                     command_y +
			                     ((inst->style.menubar_command_h - h) /
			                     2.0));

			command_y += inst->style.menubar_command_h;
		}
	}
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

	slider_w = inst->wstyle[fw].size_body_w;
	val_perc = 1.0 /
	           (inst->rect[fw].w - slider_w) *
	           (x - inst->rect[fw].x - (slider_w / 2.0));
	raw_v = val_perc * inst->value_max[fw];

	if (raw_v > (float) inst->value_max[fw])
		inst->value[fw] = inst->value_max[fw];
	else if (raw_v < 0.0)
		inst->value[fw] = 0;
	else
		inst->value[fw] = roundf(raw_v);

	if (inst->value[fw] > inst->value_max[fw])
		inst->value[fw] = inst->value_max[fw];

	CTK_CreateWidgetTexture(inst, fw);

	if (NULL != inst->edit[fw])
		inst->edit[fw](inst, fw, inst->edit_data[fw]);
}

void
CTK_HandleKeyDown(CTK_Instance            *inst,
                  const SDL_KeyboardEvent  e)
{
	char *buf;
	int c_shift = 0;
	size_t end;
	CTK_WidgetId fw;
	size_t start;
	char temp;

	switch (e.key) {
	case SDLK_BACKSPACE:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_ENTRY != inst->type[fw])
			return;

		if (inst->cursor[fw] < inst->selection[fw]) {
			TTF_DeleteTextString(inst->text[fw],
			                     inst->cursor[fw],
			                     inst->selection[fw] -
			                     inst->cursor[fw]);
		} else if (inst->cursor[fw] > inst->selection[fw]) {
			TTF_DeleteTextString(inst->text[fw],
			                     inst->selection[fw],
			                     inst->cursor[fw] -
			                     inst->selection[fw]);
			c_shift -= inst->cursor[fw] - inst->selection[fw];
		} else if (inst->cursor[fw] > 0) {
			TTF_DeleteTextString(inst->text[fw], inst->cursor[fw] - 1, 1);
			c_shift--;
		}

		CTK_ShiftWidgetTextCursor(inst, fw, c_shift, true);
		break;

	case SDLK_C:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_ENTRY != inst->type[fw] ||
		    !(SDL_KMOD_CTRL & e.mod) ||
		    inst->cursor[fw] == inst->selection[fw])
			break;

		if (inst->cursor[fw] > inst->selection[fw]) {
			start = inst->selection[fw];
			end = inst->cursor[fw];
		} else {
			start = inst->cursor[fw];
			end = inst->selection[fw];
		}

		temp = inst->text[fw]->text[end];
		inst->text[fw]->text[end] = '\0';
		SDL_SetClipboardText(&inst->text[fw]->text[start]);
		inst->text[fw]->text[end] = temp;
		break;

	case SDLK_DELETE:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_ENTRY != inst->type[fw])
			return;

		if (inst->cursor[fw] < inst->selection[fw]) {
			TTF_DeleteTextString(inst->text[fw],
			                     inst->cursor[fw],
			                     inst->selection[fw] -
			                     inst->cursor[fw]);
		} else if (inst->cursor[fw] > inst->selection[fw]) {
			TTF_DeleteTextString(inst->text[fw],
			                     inst->selection[fw],
			                     inst->cursor[fw] -
			                     inst->selection[fw]);
			c_shift -= inst->cursor[fw] - inst->selection[fw];
		} else {
			TTF_DeleteTextString(inst->text[fw], inst->cursor[fw], 1);
		}

		CTK_ShiftWidgetTextCursor(inst, fw, c_shift, true);
		break;

	case SDLK_END:
	case SDLK_PAGEDOWN:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_ENTRY != inst->type[fw])
			break;

		c_shift = strlen(inst->text[fw]->text) - inst->cursor[fw];
		if (!(SDL_KMOD_SHIFT & e.mod))
			inst->selection[fw] = inst->cursor[fw] + c_shift;
		else
			CTK_UpdatePrimarySelection(inst, fw);

		CTK_ShiftWidgetTextCursor(inst, fw, c_shift, false);
		break;

	case SDLK_HOME:
	case SDLK_PAGEUP:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_ENTRY != inst->type[fw])
			break;

		c_shift = 0 - inst->cursor[fw];
		if (!(SDL_KMOD_SHIFT & e.mod))
			inst->selection[fw] = 0;
		else
			CTK_UpdatePrimarySelection(inst, fw);

		CTK_ShiftWidgetTextCursor(inst, fw, c_shift, false);
		break;

	case SDLK_LEFT:
		fw = CTK_GetFocusedWidget(inst);

		switch (inst->type[fw]) {
		case CTK_WTYPE_ENTRY:
			if (inst->cursor[fw] > 0) {
				c_shift--;
			}
			if (!(SDL_KMOD_SHIFT & e.mod)) {
				inst->selection[fw] = inst->cursor[fw] + c_shift;
			}

			CTK_UpdatePrimarySelection(inst, fw);
			CTK_ShiftWidgetTextCursor(inst, fw, c_shift, false);
			break;

		case CTK_WTYPE_SCALE:
			if (inst->value[fw] <= 0) {
				break;
			}

			CTK_SetWidgetValue(inst, fw, inst->value[fw] - 1);

			if (NULL != inst->edit[fw]) {
				inst->edit[fw](inst, fw, inst->edit_data[fw]);
			}
			break;

		default:
			break;
		}
		break;

	case SDLK_RIGHT:
		fw = CTK_GetFocusedWidget(inst);

		switch (inst->type[fw]) {
		case CTK_WTYPE_ENTRY:
			if ((size_t) inst->cursor[fw] <
			    strlen(inst->text[fw]->text)) {
				c_shift++;
			}

			if (!(SDL_KMOD_SHIFT & e.mod)) {
				inst->selection[fw] = inst->cursor[fw] + c_shift;
			}

			CTK_UpdatePrimarySelection(inst, fw);
			CTK_ShiftWidgetTextCursor(inst, fw, c_shift, false);
			break;

		case CTK_WTYPE_SCALE:
			if (inst->value[fw] >= inst->value_max[fw]) {
				break;
			}

			CTK_SetWidgetValue(inst, fw, inst->value[fw] + 1);

			if (NULL != inst->edit[fw]) {
				inst->edit[fw](inst, fw, inst->edit_data[fw]);
			}
			break;

		default:
			break;
		}
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

			if (NULL != inst->edit[fw]) {
				inst->edit[fw](inst, fw, inst->edit_data[fw]);
			}
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
			if (inst->focused_w > 0) {
				inst->focused_w--;
			} else {
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

	case SDLK_V:
		fw = CTK_GetFocusedWidget(inst);

		if (CTK_WTYPE_ENTRY != inst->type[fw] ||
		    !(SDL_KMOD_CTRL & e.mod) ||
		    !SDL_HasClipboardText())
			break;

		buf = SDL_GetClipboardText();

		if (inst->cursor[fw] < inst->selection[fw]) {
			TTF_DeleteTextString(inst->text[fw],
			                     inst->cursor[fw],
			                     inst->selection[fw] -
			                     inst->cursor[fw]);
		} else if (inst->cursor[fw] > inst->selection[fw]) {
			TTF_DeleteTextString(inst->text[fw],
			                     inst->selection[fw],
			                     inst->cursor[fw] -
			                     inst->selection[fw]);
			c_shift -= inst->cursor[fw] - inst->selection[fw];
		}

		TTF_InsertTextString(inst->text[fw],
		                     inst->cursor[fw] + c_shift,
		                     buf,
		                     0);
		c_shift += strlen(buf);
		CTK_ShiftWidgetTextCursor(inst, fw, c_shift, true);

		SDL_free(buf);
		break;
	}
}

void
CTK_HandleMouseButtonDown(CTK_Instance               *inst,
                          const SDL_MouseButtonEvent  e)
{
	size_t       i;
	size_t       new_focused_casc;
	SDL_FPoint   p;
	CTK_WidgetId w;
	int          x;

	if (NULL != inst->menubar &&
	    e.y < inst->style.menubar_h) {
		new_focused_casc = -1;
		x = 0;
		for (i = 0; i < inst->menubar->cascades; i++) {
			if (e.x > x &&
			    e.x < x + inst->menubar->cascade[i].name_w) {
				new_focused_casc = i;
				break;
			}
			x += inst->menubar->cascade[i].name_w;
		}
	}

	if (new_focused_casc != inst->focused_casc) {
		inst->focused_casc = new_focused_casc;
		inst->redraw = true;
	}

	p.x = e.x;
	p.y = e.y - (inst->menubar ? inst->style.menubar_h : 0);

	for (i = 0; i < inst->enabled_ws; i++) {
		w = inst->enabled_w[i];

		if (SDL_PointInRectFloat(&p, &inst->rect[w])) {
			CTK_SetFocusedWidget(inst, w);

			if (CTK_WTYPE_SCALE == inst->type[w]) {
				inst->drag = true;
				CTK_HandleDrag(inst, p.x);
			}

			if (NULL != inst->mouse_press[w]) {
				inst->mouse_press[w](inst,
				                     e,
				                     w,
				                     inst->mouse_press_data[w]);
			}
			break;
		}
	}
}

void
CTK_HandleMouseButtonUp(CTK_Instance               *inst,
                        const SDL_MouseButtonEvent  e)
{
	size_t i;
	SDL_FPoint p;
	CTK_WidgetId w;

	inst->drag = false;

	for (i = 0; i < inst->enabled_ws; i++) {
		w = inst->enabled_w[i];
		p.x = e.x;
		p.y = e.y - (inst->menubar ? inst->style.menubar_h : 0);

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

			if (NULL != inst->edit[w]) {
				inst->edit[w](inst, w, inst->edit_data[w]);
			}
			break;

		case CTK_WTYPE_RADIOBUTTON:
			CTK_ToggleRadiobutton(inst, w);
			break;
		}

		if (NULL != inst->mouse_release[w]) {
			inst->mouse_release[w](inst,
			                       e,
			                       w,
			                       inst->mouse_release_data[w]);
		}
		if (NULL != inst->trigger[w]) {
			inst->trigger[w](inst,
			                 w,
			                 inst->trigger_data[w]);
		}
	}
}

void
CTK_HandleMouseMotion(CTK_Instance               *inst,
                      const SDL_MouseMotionEvent  e)
{
	size_t       i;
	size_t       new_focused_casc = inst->focused_casc;
	size_t       new_hovered_casc = -1;
	CTK_WidgetId old_hov_w;
	SDL_FPoint   p;
	CTK_WidgetId w;
	int          x;

	old_hov_w = inst->hovered_w;
	inst->hovered_w = -1;

	if (NULL != inst->menubar &&
	    e.y < inst->style.menubar_h) {
		new_focused_casc = inst->focused_casc;
		new_hovered_casc = -1;

		x = 0;
		for (i = 0; i < inst->menubar->cascades; i++) {
			if (e.x > x &&
			    e.x < x + inst->menubar->cascade[i].name_w) {
				new_focused_casc = i;
				new_hovered_casc = i;
				break;
			}
			x += inst->menubar->cascade[i].name_w;
		}
	}

	if (new_focused_casc != inst->focused_casc &&
	    inst->focused_casc < inst->menubar->cascades) {
		inst->focused_casc = new_focused_casc;
		inst->redraw = true;
	}

	if (new_hovered_casc != inst->hovered_casc) {
		inst->hovered_casc = new_hovered_casc;
		inst->redraw = true;
	}

	for (i = 0; i < inst->enabled_ws; i++) {
		w = inst->enabled_w[i];
		p.x = e.x;
		p.y = e.y - (inst->menubar ? inst->style.menubar_h : 0);

		if (!SDL_PointInRectFloat(&p, &inst->rect[w]))
			continue;

		inst->hovered_w = w;

		if (inst->mouse_motion[w]) {
			inst->mouse_motion[w](inst,
			                      e,
			                      w,
			                      inst->mouse_motion_data);
		}
		break;
	}

	if (old_hov_w == inst->hovered_w)
		return;

	if (-1 != inst->hovered_w)
		CTK_CreateWidgetTexture(inst, inst->hovered_w);

	if (-1 != old_hov_w)
		CTK_CreateWidgetTexture(inst, old_hov_w);
}

void
CTK_HandleMouseWheel(CTK_Instance              *inst,
                     const SDL_MouseWheelEvent  e)
{
	size_t i;
	SDL_FPoint p;
	CTK_WidgetId w;

	for (i = 0; i < inst->enabled_ws; i++) {
		w = inst->enabled_w[i];
		p.x = e.mouse_x;
		p.y = e.mouse_y - (inst->menubar ? inst->style.menubar_h : 0);

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

			if (NULL != inst->edit[w]) {
				inst->edit[w](inst, w, inst->edit_data[w]);
			}
		}

		if (NULL != inst->mouse_wheel[w]) {
			inst->mouse_wheel[w](inst,
			                     e,
			                     w,
			                     inst->mouse_wheel_data[w]);
		}
	}
}

void
CTK_HandleTextInput(CTK_Instance             *inst,
                    const SDL_TextInputEvent  e)
{
	int c_shift = 0;
	CTK_WidgetId fw;

	fw = CTK_GetFocusedWidget(inst);

	if (inst->cursor[fw] < inst->selection[fw]) {
		TTF_DeleteTextString(inst->text[fw],
		                     inst->cursor[fw],
		                     inst->selection[fw] -
		                     inst->cursor[fw]);
	} else if (inst->cursor[fw] > inst->selection[fw]) {
		TTF_DeleteTextString(inst->text[fw],
		                     inst->selection[fw],
		                     inst->cursor[fw] -
		                     inst->selection[fw]);
		c_shift -= inst->cursor[fw] - inst->selection[fw];
	}

	TTF_InsertTextString(inst->text[fw],
	                     inst->cursor[fw] + c_shift,
	                     e.text, 0);
	c_shift += strlen(e.text);

	CTK_ShiftWidgetTextCursor(inst, fw, c_shift, true);
}

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst)
{
	return inst->focusable_w[inst->focused_w];
}

bool
CTK_GetWidgetEnabledId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       int                *cacheId)
{
	size_t i;

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
	size_t i;

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
	size_t i;

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

	TTF_SetFontDirection(CTK_font, TTF_DIRECTION_LTR);
	TTF_SetFontLanguage(CTK_font, "en");

	return true;
}

void
CTK_InstanceDefaultQuit(CTK_Instance *inst,
                        void         *dummy)
{
	(void) dummy;

	inst->active = false;
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
		if (now - last > 1000 / inst->max_framerate) {
			last = now;

			CTK_TickInstance(inst);
			CTK_DrawInstance(inst);
		}
	}
}

/* @text: TTF_Text
 * @start: position at which to start measuring the text
 * @len: amount chars that should be measured
 *
 * Returns size in pixels of a TTF_Text portion.
 */
SDL_Rect
CTK_MeasureTTFText(TTF_Text *text,
                   size_t    start,
                   size_t    len)
{
	SDL_Rect      ret;
	TTF_SubString ss;

	TTF_GetTextSubString(text, start - 1, &ss);
	ret.x = ss.rect.x + ss.rect.w;
	ret.y = ss.rect.y;

	TTF_GetTextSubString(text, start + len - 1, &ss);
	ret.w = (ss.rect.x + ss.rect.w) - ret.x;
	ret.h = (ss.rect.y + ss.rect.h) - ret.y;

	return ret;
}

bool
CTK_RenderText(TTF_Text                *text,
               const SDL_FRect          rect,
               const CTK_TextAlignment  ta,
               const size_t             offset_x)
{
	int text_w;
	int text_h;
	float x, y;

	if (!TTF_GetTextSize(text, &text_w, &text_h))
		return false;

	switch (ta) {
	case CTK_TEXT_ALIGNMENT_LEFT:
		x = 0;
		break;

	case CTK_TEXT_ALIGNMENT_CENTER:
		x = (rect.w - text_w) / 2.0;
		break;

	case CTK_TEXT_ALIGNMENT_RIGHT:
		x = rect.w - text_w;
		break;
	}

	x -= offset_x;
	y = (rect.h - text_h) / 2.0;

	if (!TTF_DrawRendererText(text, x, y))
		return false;

	return true;
}

void
CTK_SetFocusedWidget(CTK_Instance       *inst,
                     const CTK_WidgetId  widget)
{
	size_t i;

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
	size_t i;
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
	size_t i;
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

	TTF_SetTextString(inst->text[widget], text, 0);
	TTF_GetTextSize(inst->text[widget], &w, &h);
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
	inst->wstyle[widget].text_align = alignment;
	CTK_CreateWidgetTexture(inst, widget);
}

void
CTK_SetWidgetTextAndResize(CTK_Instance       *inst,
                           const CTK_WidgetId  widget,
                           const char         *text)
{
	int w, h;

	TTF_SetTextString(inst->text[widget], text, 0);
	TTF_GetTextSize(inst->text[widget], &w, &h);
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
	size_t i;
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
CTK_ShiftWidgetTextCursor(CTK_Instance       *inst,
                          const CTK_WidgetId  w,
                          const int           shift,
                          const bool          shift_selection)
{
	int           new_cursor_x;
	int           old_cursor_x;
	int           shift_real;
	TTF_SubString ss;
	int           text_len;
	int           text_w;

	text_len = strlen(inst->text[w]->text);

	if (inst->cursor[w] + shift < 0)
		shift_real = shift - (inst->cursor[w] - shift);
	else if (inst->cursor[w] + shift > text_len)
		shift_real = shift + (inst->cursor[w] - text_len);
	else
		shift_real = shift;

	TTF_GetTextSubString(inst->text[w], inst->cursor[w] - 1, &ss);
	old_cursor_x = ss.rect.x + ss.rect.w;
	inst->cursor[w] += shift_real;
	TTF_GetTextSubString(inst->text[w], inst->cursor[w] - 1, &ss);
	new_cursor_x = ss.rect.x + ss.rect.w;

	if (new_cursor_x - inst->scroll_x[w] >= inst->rect[w].w ||
	    new_cursor_x - inst->scroll_x[w] <= 0)
		inst->scroll_x[w] += new_cursor_x - old_cursor_x;

	TTF_GetTextSize(inst->text[w], &text_w, NULL);

	if (inst->scroll_x[w] < 0)
		inst->scroll_x[w] = 0;
	else if (inst->scroll_x[w] > text_w - 1)
		inst->scroll_x[w] = text_w - 1;

	if (shift_selection)
		inst->selection[w] = inst->cursor[w];

	CTK_CreateWidgetTexture(inst, w);
}

void
CTK_TickInstance(CTK_Instance *inst)
{
	SDL_Event e;

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

			CTK_HandleMouseMotion(inst, e.motion);
			break;

		case SDL_EVENT_MOUSE_WHEEL:
			CTK_HandleMouseWheel(inst, e.wheel);
			break;

		case SDL_EVENT_KEY_DOWN:
			CTK_HandleKeyDown(inst, e.key);
			break;

		case SDL_EVENT_TEXT_INPUT:
			CTK_HandleTextInput(inst, e.text);
			break;

		case SDL_EVENT_WINDOW_MOUSE_ENTER:
			if (inst->enter)
				inst->enter(inst, inst->enter_data);
			break;

		case SDL_EVENT_WINDOW_MOUSE_LEAVE:
			if (inst->leave)
				inst->leave(inst, inst->leave_data);
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
			if (NULL != inst->quit) {
				inst->quit(inst, inst->quit_data);
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
	size_t i;

	if (inst->toggle[widget])
		return;

	for (i = 0; i < inst->widgets; i++) {
		if (inst->group[i] == inst->group[widget]) {
			inst->toggle[i] = false;
			CTK_CreateWidgetTexture(inst, i);
		}
	}
	inst->toggle[widget] = true;
	CTK_CreateWidgetTexture(inst, widget);

	if (NULL != inst->edit[widget]) {
		inst->edit[widget](inst, widget, inst->edit_data[widget]);
	}
}

void
CTK_UpdatePrimarySelection(CTK_Instance *inst,
                           CTK_WidgetId  w)
{
	size_t end;
	size_t start;
	char   temp;

	if (inst->cursor[w] > inst->selection[w]) {
		start = inst->selection[w];
		end = inst->cursor[w];
		temp = inst->text[w]->text[end];
		inst->text[w]->text[end] = '\0';
		SDL_SetPrimarySelectionText(&inst->text[w]->text[start]);
		inst->text[w]->text[end] = temp;
	} else if (inst->cursor[w] < inst->selection[w]) {
		start = inst->cursor[w];
		end = inst->selection[w];
		temp = inst->text[w]->text[end];
		inst->text[w]->text[end] = '\0';
		SDL_SetPrimarySelectionText(&inst->text[w]->text[start]);
		inst->text[w]->text[end] = temp;
	}
}

void
CTK_Quit()
{
	TTF_CloseFont(CTK_font);
	TTF_Quit();
	SDL_Quit();
}

#endif /* CTK_IMPLEMENTATION */

#endif /* _CTK_H */
