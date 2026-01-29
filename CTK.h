/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#ifndef _CTK_H
#define _CTK_H

#include <SDL3/SDL.h>
#include <stddef.h>

#include "CTK_style.h"
#include "CTK_version.h"

#ifndef ARRLEN
#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#define CTK_DEFAULT_BUTTON_W         80
#define CTK_DEFAULT_BUTTON_H         27
#define CTK_DEFAULT_CHECKBOX_W       CTK_DEFAULT_BUTTON_H - 4
#define CTK_DEFAULT_CHECKBOX_H       CTK_DEFAULT_BUTTON_H - 4
#define CTK_DEFAULT_CHECKBOX_FILL    0.7
#define CTK_DEFAULT_ENTRY_W          165
#define CTK_DEFAULT_ENTRY_H          CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_FONTSIZE         11
#define CTK_DEFAULT_LABEL_H          CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_PROGRESSBAR_W    CTK_DEFAULT_BUTTON_W
#define CTK_DEFAULT_PROGRESSBAR_H    CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_RADIOBUTTON_W    CTK_DEFAULT_CHECKBOX_W
#define CTK_DEFAULT_RADIOBUTTON_H    CTK_DEFAULT_CHECKBOX_H
#define CTK_DEFAULT_RADIOBUTTON_FILL CTK_DEFAULT_CHECKBOX_FILL
#define CTK_DEFAULT_SCALE_W          CTK_DEFAULT_BUTTON_W
#define CTK_DEFAULT_SCALE_H          CTK_DEFAULT_BUTTON_H
#define CTK_DEFAULT_THEME            CTK_Theme_TclTk
#define CTK_DEFAULT_WINDOW_FLAGS     (SDL_WINDOW_RESIZABLE)
#define CTK_DEFAULT_MAX_FRAMERATE    60

#define CTK_MAX_WIDGETS 64

#define CTK_SCALE_SLIDER_SIZE_FRACTION 0.3

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
	Uint64      max_framerate;
	bool        redraw;
	CTK_Style   style;
	SDL_Window *win;

	/* instance events */
	void (*draw)(struct CTK_Instance*, void*);
	void *draw_data;
	void (*enter)(struct CTK_Instance*, void*);
	void *enter_data;
	void (*leave)(struct CTK_Instance*, void*);
	void *leave_data;
	void (*motion)(struct CTK_Instance*,
	               const float x,
	               const float y,
	               void*);
	void *motion_data;
	void (*quit)(struct CTK_Instance*, void*);
	void *quit_data;

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
	int                selection[CTK_MAX_WIDGETS];
	int                scroll[CTK_MAX_WIDGETS];
	char              *text[CTK_MAX_WIDGETS];
	size_t             textsize[CTK_MAX_WIDGETS];
	CTK_TextAlignment  text_alignment[CTK_MAX_WIDGETS];
	bool               toggle[CTK_MAX_WIDGETS];
	CTK_WidgetType     type[CTK_MAX_WIDGETS];
	unsigned int       value[CTK_MAX_WIDGETS];
	unsigned int       value_max[CTK_MAX_WIDGETS];
	SDL_FRect          rect[CTK_MAX_WIDGETS];
	SDL_Texture       *texture[CTK_MAX_WIDGETS];

	/* widget events */
	void (*edit[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                              const CTK_WidgetId,
	                              void*);
	void *edit_data[CTK_MAX_WIDGETS];
	void (*mouse_press[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                     const SDL_MouseButtonEvent,
	                                     const CTK_WidgetId,
	                                     void*);
	void *mouse_press_data[CTK_MAX_WIDGETS];
	void (*mouse_release[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                       const SDL_MouseButtonEvent,
	                                       const CTK_WidgetId,
	                                       void*);
	void *mouse_release_data[CTK_MAX_WIDGETS];
	void (*mouse_wheel[CTK_MAX_WIDGETS])(struct CTK_Instance*,
	                                     const SDL_MouseWheelEvent,
	                                     const CTK_WidgetId,
	                                     void*);
	void *mouse_wheel_data[CTK_MAX_WIDGETS];
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
 * Returns valid instance or NULL on failure.
 * Call SDL_GetError() for more information.
 */
CTK_Instance*
CTK_CreateInstance(const char            *title,
                   const int              winw,
                   const int              winh,
                   const SDL_WindowFlags  flags);

SDL_Texture*
CTK_CreateText(SDL_Renderer            *r,
               const char              *str,
               const size_t             str_len,
               const SDL_Color          fg,
               const SDL_Color          bg);

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
CTK_HandleMouseWheel(CTK_Instance              *inst,
                     const SDL_MouseWheelEvent  e);

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
CTK_InstanceDefaultQuit(CTK_Instance *inst,
                        void         *dummy);

bool
CTK_RenderText(SDL_Renderer            *r,
               const char              *str,
               const size_t             str_len,
               const SDL_FRect          rect,
               const CTK_TextAlignment  ta,
               const SDL_Color          fg,
               const SDL_Color          bg);

bool
CTK_RenderSelectedText(SDL_Renderer            *r,
                       char                    *str,
                       const size_t             str_len,
                       const SDL_FRect          rect,
                       const int                cursor,
                       const int                selection,
                       const CTK_TextAlignment  ta,
                       const SDL_Color          fg,
                       const SDL_Color          fg_selected,
                       const SDL_Color          bg,
                       const SDL_Color          bg_selected);

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

#endif /* _CTK_H */
