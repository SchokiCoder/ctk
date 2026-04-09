/* SPDX-License-Identifier: MPL-2.0
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#ifndef _CTK_H
#define _CTK_H

#include <ctype.h>
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

#define CTK_DEFAULT_FONTSIZE         12
#define CTK_DEFAULT_THEME            CTK_Theme_TclTk
#define CTK_DEFAULT_WINDOW_FLAGS     (SDL_WINDOW_RESIZABLE)
#define CTK_DEFAULT_MAX_FRAMERATE    60

#define CTK_PIXELFORMAT SDL_PIXELFORMAT_RGBA8888

#define CTK_TEXTUREACCESS SDL_TEXTUREACCESS_TARGET

#define CTK_VERSION "0.4.0"

/* Configuration defines
 */

#ifndef CTK_INSTANCE_MAX_WIDGETS
#define CTK_INSTANCE_MAX_WIDGETS 64
#endif

#ifndef CTK_MAX_BINDS
#define CTK_MAX_BINDS 64
#endif

#ifndef CTK_MENU_MAX_ITEMS
#define CTK_MENU_MAX_ITEMS 32
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

typedef size_t CTK_WidgetId;

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

struct CTK_Instance;
struct CTK_Menubar;
struct CTK_Menu;

typedef struct CTK_Instance {
	bool                active;
	SDL_Texture        *content;
	bool                drag;
	struct CTK_Menu    *entry_menu;
	size_t              entry_menu_cut;
	size_t              entry_menu_copy;
	size_t              focused_casc;
	size_t              focused_w;
	size_t              hovered_casc;
	size_t              hovered_cmd;
	CTK_WidgetId        hovered_w;
	Uint64              max_framerate;
	struct CTK_Menubar *menubar;
	bool                redraw;
	CTK_Style           style;
	TTF_TextEngine     *tengine;
	bool                txt_input_suspended;
	struct CTK_Menu    *visible_menu;
	SDL_Window         *win;

	/* keybinds */
	size_t        binds;
	void        (*bind_fn[CTK_MAX_BINDS])(struct CTK_Instance*, void*);
	void         *bind_fn_data[CTK_MAX_BINDS];
	SDL_Keycode   bind_key[CTK_MAX_BINDS];
	SDL_Keymod    bind_mod[CTK_MAX_BINDS];

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
	size_t             underline[CTK_INSTANCE_MAX_WIDGETS];
	unsigned short     value[CTK_INSTANCE_MAX_WIDGETS];
	unsigned short     value_max[CTK_INSTANCE_MAX_WIDGETS];
	CTK_WidgetStyle    wstyle[CTK_INSTANCE_MAX_WIDGETS];

	/* widget events */
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

	/* virtual widget events */
	void (*edit[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                       const CTK_WidgetId,
	                                       void*);
	void *edit_data[CTK_INSTANCE_MAX_WIDGETS];
	void (*trigger[CTK_INSTANCE_MAX_WIDGETS])(struct CTK_Instance*,
	                                          const CTK_WidgetId,
	                                          void*);
	void *trigger_data[CTK_INSTANCE_MAX_WIDGETS];
} CTK_Instance;

typedef struct CTK_Menu {
	SDL_FRect  rect;
	size_t     commands;
	TTF_Text  *accelerator[CTK_MENU_MAX_ITEMS];
	void     (*command[CTK_MENU_MAX_ITEMS])(CTK_Instance*, void*);
	void      *command_data[CTK_MENU_MAX_ITEMS];
	bool       enabled[CTK_MENU_MAX_ITEMS];
	size_t     h[CTK_MENU_MAX_ITEMS];
	bool       is_separator[CTK_MENU_MAX_ITEMS];
	TTF_Text  *label[CTK_MENU_MAX_ITEMS];
	size_t     underline[CTK_MENUBAR_MAX_CASCADES];
} CTK_Menu;

typedef struct CTK_Menubar {
	size_t           cascades;
	TTF_Text        *cascade[CTK_MENUBAR_MAX_CASCADES];
	int              cascade_w[CTK_MENUBAR_MAX_CASCADES];
	int              cascade_h[CTK_MENUBAR_MAX_CASCADES];
	size_t           h;
	struct CTK_Menu *menu[CTK_MENUBAR_MAX_CASCADES];
	size_t           underline[CTK_MENUBAR_MAX_CASCADES];
} CTK_Menubar;

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

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
CTK_WidgetId
CTK_AddButton(CTK_Instance *inst);

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
CTK_WidgetId
CTK_AddCheckbox(CTK_Instance *inst);

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
CTK_WidgetId
CTK_AddEntry(CTK_Instance *inst);

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
CTK_WidgetId
CTK_AddLabel(CTK_Instance *inst);

/* @inst: Instance to add to.
 * @name: Displayed name of cascade.
 * @menu: Menu to attach to.
 * @underline: Underline within name. If not used, give -1.
 *
 * Returns cascade index on success or -1 on failure.
 */
size_t
CTK_AddMenubarCascade(CTK_Instance *inst,
                      const char   *name,
                      CTK_Menu     *menu,
                      const size_t  underline);

/* @inst: Instance to add to.
 * @menu: Menu to add command to.
 * @label: Displayed name of command.
 * @fn: Function to run when command is used.
 * @fn_data: Data that is passed to fn.
 * @underline: Underline within label. If not used, give -1.
 *
 * Returns command index on success or -1 on failure.
 */
size_t
CTK_AddMenuCommand(CTK_Instance *inst,
                   CTK_Menu     *menu,
                   const char   *label,
                   void        (*fn)(CTK_Instance*, void*),
                   void         *fn_data,
                   const size_t  underline);

bool
CTK_AddMenuSeparator(CTK_Instance *inst,
                     CTK_Menu     *menu);

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
CTK_WidgetId
CTK_AddProgressbar(CTK_Instance *inst);

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
CTK_WidgetId
CTK_AddRadiobutton(CTK_Instance *inst);

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
CTK_WidgetId
CTK_AddScale(CTK_Instance *inst);

/* @inst: Instance to add to.
 *
 * Returns widget index on success or -1 on failure.
 */
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

/* @inst: Instance to initialize.
 * @keystr: Keybind definition in the strict format "KEY+KEY".
 * @fn: Function to run when bind is used.
 * @fn_data: Data that is passed to fn.
 *
 * Returns true on success or false on failure.
 */
bool
CTK_Bind(CTK_Instance  *inst,
         const char    *keystr,
         void         (*fn)(CTK_Instance*, void*),
         void          *fn_data);

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

/* @inst: Instance to initialize.
 * @title: Used as window title.
 * @winw: Window width.
 * @winh: Window height.
 * @flags: SDL window flags. May be 0 to use defaults.
 *
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

CTK_Menu*
CTK_CreateMenu();

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
CTK_DestroyMenu(CTK_Menu *m);

void
CTK_DestroyMenubar(CTK_Menubar *mb);

void
CTK_DrawInstance(CTK_Instance *inst);

void
CTK_DrawMenu(CTK_Instance *inst,
             CTK_Menu     *menu);

void
CTK_DrawMenubar(CTK_Instance *inst);

void
CTK_EntryMenuCut(CTK_Instance *inst,
                 void         *dummy);

void
CTK_EntryMenuCopy(CTK_Instance *inst,
                  void         *dummy);

void
CTK_EntryMenuPaste(CTK_Instance *inst,
                   void         *dummy);

void
CTK_FocusMenu(CTK_Instance *inst,
              CTK_Menu     *menu);

void
CTK_FocusMenubar(CTK_Instance *inst,
                 const size_t  cascade);

void
CTK_HandleDrag(CTK_Instance *inst,
               const float   x);

void
CTK_HandleKeybinds(CTK_Instance            *inst,
                   const SDL_KeyboardEvent  e);

void
CTK_HandleKeyDown(CTK_Instance            *inst,
                  const SDL_KeyboardEvent  e);

void
CTK_HandleLMBDown(CTK_Instance               *inst,
                  const SDL_MouseButtonEvent  e);

void
CTK_HandleLMBUp(CTK_Instance               *inst,
                const SDL_MouseButtonEvent  e);

void
CTK_HandleMouseMotion(CTK_Instance               *inst,
                      const SDL_MouseMotionEvent  e);

void
CTK_HandleMouseWheel(CTK_Instance              *inst,
                     const SDL_MouseWheelEvent  e);

void
CTK_HandleRMBDown(CTK_Instance               *inst,
                  const SDL_MouseButtonEvent  e);

void
CTK_HandleRMBUp(CTK_Instance               *inst,
                const SDL_MouseButtonEvent  e);

void
CTK_HandleTextInput(CTK_Instance             *inst,
                    const SDL_TextInputEvent  e);

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst);

/* @name: Name of the key.
 * @key: Resulting key is stored there. May be SDLK_UNKNOWN.
 * @mod: Resulting mod is stored there. May be SDL_KMOD_NONE.
 *
 * If both results are unknown/none the key is not valid.
 */
void
CTK_GetKeyOrModFromName(const char  *name,
                        SDL_Keycode *key,
                        SDL_Keymod  *mod);

bool
CTK_GetWidgetEnabledId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       size_t             *cacheId);

bool
CTK_GetWidgetFocusableId(const CTK_Instance *inst,
                         const CTK_WidgetId  widget,
                         size_t             *cacheId);

bool
CTK_GetWidgetVisibleId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       size_t             *cacheId);

/* @appname: Name of application, duh.
 * @appversion: Eg. "1.2.5".
 * @appidentifier: Eg. "com.brave.Browser".
 *
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

/* @inst: Instance to mainloop of.
 *
 * Alternatively, if more control is needed,
 * you can call CTK_DrawInstance and CTK_TickInstance in a custom loop.
 */
void
CTK_MainloopInstance(CTK_Instance *inst);

/* @text: Text to measure.
 * @start: Position at which to start measuring the text.
 * @len: Amount of chars that should be measured.
 *
 * Returns size in pixels of the text portion.
 */
SDL_Rect
CTK_MeasureTTFText(TTF_Text *text,
                   size_t    start,
                   size_t    len);

/* @r: SDL Renderer.
 * @text: Text to draw.
 * @rect: Rect within the text should be.
 * @ta: Horizontal alignment within the rect.
 * @underline: Underline within text. If not used, give -1.
 * @underline_clr: Color of underline to draw.
 *
 * Returns true on success or false on failure.
 */
bool
CTK_RenderText(SDL_Renderer            *r,
               TTF_Text                *text,
               const SDL_FRect          rect,
               const CTK_TextAlignment  ta,
               const size_t             underline,
               const SDL_Color          underline_clr);

void
CTK_SetFocusedWidget(CTK_Instance       *inst,
                     const CTK_WidgetId  widget);

/* @inst: Parent instance.
 * @menu: Parent menu.
 * @cmd_id: Command index.
 * @keystr: Bind string. See CTK_Bind.
 *
 * Returns true on success or false on failure.
 */
bool
CTK_SetMenuCommandAccelerator(CTK_Instance *inst,
                              CTK_Menu     *menu,
                              const size_t  cmd_id,
                              const char   *keystr);

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

/* @inst: Parenting instance of widget.
 * @widget: Widget index.
 * @underline: Underline within text. If not used, give -1.
 */
void
CTK_SetWidgetUnderline(CTK_Instance       *inst,
                       const CTK_WidgetId  widget,
                       const size_t        underline);

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
CTK_UnfocusMenu(CTK_Instance *inst);

void
CTK_UnfocusMenubar(CTK_Instance *inst);

void
CTK_UpdateMenuSize(const CTK_Instance *inst,
                   CTK_Menu           *m);

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

size_t
CTK_AddMenubarCascade(CTK_Instance *inst,
                      const char   *name,
                      CTK_Menu     *menu,
                      const size_t  underline)
{
	size_t c, i;
	int h;
	CTK_Menubar *mb;

	mb = inst->menubar;
	c = mb->cascades;

	if (mb->cascades >= CTK_MENUBAR_MAX_CASCADES) {
		SDL_SetError("Menubar can not hold more cascades");
		return -1;
	}

	mb->cascade[c] = TTF_CreateText(inst->tengine, CTK_font, name, 0);
	TTF_GetTextSize(mb->cascade[c], &mb->cascade_w[c], &mb->cascade_h[c]);
	mb->menu[c] = menu;
	mb->underline[c] = underline;
	mb->cascades++;

	menu->rect.x = 0;
	for (i = 0; i < c; i++) {
		menu->rect.x += inst->style.menubar_cascade_padding_left +
		                mb->cascade_w[i] +
		                inst->style.menubar_cascade_padding_right;
	}

	TTF_GetTextSize(mb->cascade[c], NULL, &h);
	mb->h = inst->style.menubar_cascade_padding_top +
	        h +
	        inst->style.menubar_cascade_padding_bottom;
	menu->rect.y = mb->h;

	return c;
}

size_t
CTK_AddMenuCommand(CTK_Instance *inst,
                   CTK_Menu     *menu,
                   const char   *label,
                   void        (*fn)(CTK_Instance*, void*),
                   void         *fn_data,
                   const size_t  underline)
{
	size_t id;

	if (menu->commands >= CTK_MENU_MAX_ITEMS) {
		SDL_SetError("Menu can not hold more items");
		return -1;
	}

	id = menu->commands;
	menu->accelerator[id] = TTF_CreateText(inst->tengine, CTK_font, "", 0);
	menu->label[id] = TTF_CreateText(inst->tengine, CTK_font, label, 0);
	menu->command[id] = fn;
	menu->command_data[id] = fn_data;
	menu->enabled[id] = true;
	menu->h[id] = 0;
	menu->is_separator[id] = false;
	menu->underline[id] = underline;
	menu->commands++;

	CTK_UpdateMenuSize(inst, menu);

	return id;
}

bool
CTK_AddMenuSeparator(CTK_Instance *inst,
                     CTK_Menu     *menu)
{
	size_t id;

	if (menu->commands >= CTK_MENU_MAX_ITEMS) {
		SDL_SetError("Menu can not hold more items");
		return false;
	}

	id = menu->commands;
	menu->accelerator[id] = NULL;
	menu->label[id] = NULL;
	menu->command[id] = NULL;
	menu->command_data[id] = NULL;
	menu->enabled[id] = false;
	menu->h[id] = 0;
	menu->is_separator[id] = true;
	menu->commands++;

	CTK_UpdateMenuSize(inst, menu);

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
	inst->underline[ret] = -1;
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
		inst->rect[w].h = inst->wstyle[w].h;
		inst->rect[w].w = inst->wstyle[w].w;
	}

	CTK_CreateWidgetTexture(inst, w);
}

bool
CTK_Bind(CTK_Instance  *inst,
         const char    *keystr,
         void         (*fn)(CTK_Instance*, void*),
         void          *fn_data)
{
	size_t       begin = 0;
	size_t       i;
	SDL_Keycode  key = SDLK_UNKNOWN;
	SDL_Keymod   mod = SDL_KMOD_NONE;
	const size_t strsize = 32;
	char         str[strsize];
	char         temp;
	SDL_Keycode  temp_key;
	SDL_Keymod   temp_mod;

	if (strlen(keystr) > strsize) {
		SDL_SetError("Bind-string is too long");
		return false;
	}
	strncpy(str, keystr, strsize);

	/* this only accepts "$KEY+$KEY", no spaces or nonsense */
	for (i = 0; i < strlen(str); i++) {
		if (str[i + 1] == '\0' ||
		    str[i + 1] == '+') {
			temp = str[i + 1];
			str[i + 1] = '\0';

			CTK_GetKeyOrModFromName(&str[begin],
			                        &temp_key,
			                        &temp_mod);

			if (SDLK_UNKNOWN == temp_key &&
			    SDL_KMOD_NONE == temp_mod) {
				SDL_SetError("Bind tried to set invalid keys");
				return false;
			}
			if (SDLK_UNKNOWN != temp_key) {
				if (SDLK_UNKNOWN != key) {
					SDL_SetError("Bind tried to set multiple keys");
					return false;
				}
				key = temp_key;
			}
			if (SDL_KMOD_NONE != temp_mod) {
				mod |= temp_mod;
			}

			str[i + 1] = temp;
			begin = i + 2;
		}
	}

	for (i = 0; i < inst->binds; i++) {
		if (key == inst->bind_key[i] &&
		    mod == inst->bind_mod[i]) {
			SDL_SetError("Bind tried to reassign shortcut");
			return false;
		}
	}

	inst->bind_key[inst->binds] = key;
	inst->bind_mod[inst->binds] = mod;
	inst->bind_fn[inst->binds] = fn;
	inst->bind_fn_data[inst->binds] = fn_data;
	inst->binds++;

	return true;
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
		                       inst->wstyle[btn].bg_clr.r,
		                       inst->wstyle[btn].bg_clr.g,
		                       inst->wstyle[btn].bg_clr.b,
		                       inst->wstyle[btn].bg_clr.a);
	} else {
		SDL_SetRenderDrawColor(r,
		                       inst->wstyle[btn].bg_hovered_clr.r,
		                       inst->wstyle[btn].bg_hovered_clr.g,
		                       inst->wstyle[btn].bg_hovered_clr.b,
		                       inst->wstyle[btn].bg_hovered_clr.a);
	}
	SDL_RenderClear(r);

	rect.x = 0;
	rect.y = 0;
	rect.w = inst->rect[btn].w;
	rect.h = inst->rect[btn].h;

	if (CTK_IsWidgetEnabled(inst, btn)) {
		TTF_SetTextColor(inst->text[btn],
		                 inst->wstyle[btn].text_clr.r,
		                 inst->wstyle[btn].text_clr.g,
		                 inst->wstyle[btn].text_clr.b,
		                 inst->wstyle[btn].text_clr.a);
	} else {
		TTF_SetTextColor(inst->text[btn],
		                 inst->wstyle[btn].text_disabled_clr.r,
		                 inst->wstyle[btn].text_disabled_clr.g,
		                 inst->wstyle[btn].text_disabled_clr.b,
		                 inst->wstyle[btn].text_disabled_clr.a);
	}

	CTK_RenderText(r,
	               inst->text[btn],
	               rect,
	               inst->wstyle[btn].text_align,
	               inst->underline[btn],
	               inst->wstyle[btn].text_clr);

	if (inst->border[btn]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[btn].w;
		rect.h = inst->rect[btn].h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[btn].border_clr.r,
			               inst->wstyle[btn].border_clr.g,
			               inst->wstyle[btn].border_clr.b,
			               inst->wstyle[btn].border_clr.a);
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
		bg_c = inst->wstyle[ckb].bg_clr;
		body_c = inst->wstyle[ckb].body_clr;
	} else {
		bg_c = inst->wstyle[ckb].bg_hovered_clr;
		body_c = inst->wstyle[ckb].body_hovered_clr;
	}
	fg_c = inst->wstyle[ckb].fg_clr;
	if (!CTK_IsWidgetEnabled(inst, ckb)) {
		body_c = inst->wstyle[ckb].body_disabled_clr;
		fg_c = inst->wstyle[ckb].fg_disabled_clr;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	rect.x = (inst->rect[ckb].w - inst->wstyle[ckb].body_w) / 2;
	rect.y = (inst->rect[ckb].h - inst->wstyle[ckb].body_h) / 2;
	rect.w = inst->wstyle[ckb].body_w;
	rect.h = inst->wstyle[ckb].body_h;
	SDL_SetRenderDrawColor(r, body_c.r, body_c.g, body_c.b, body_c.a);
	SDL_RenderFillRect(r, &rect);

	if (inst->toggle[ckb]) {
		rect.w = inst->wstyle[ckb].fill_w;
		rect.h = inst->wstyle[ckb].fill_h;
		rect.x += inst->wstyle[ckb].body_w - rect.w;
		rect.y += inst->wstyle[ckb].body_h - rect.h;
		SDL_SetRenderDrawColor(r, fg_c.r, fg_c.g, fg_c.b, fg_c.a);
		SDL_RenderFillRect(r, &rect);
	}

	if (inst->border[ckb]) {
		rect.x = (inst->rect[ckb].w - inst->wstyle[ckb].body_w) / 2;
		rect.y = (inst->rect[ckb].h - inst->wstyle[ckb].body_h) / 2;
		rect.w = inst->wstyle[ckb].body_w;
		rect.h = inst->wstyle[ckb].body_h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[ckb].border_clr.r,
			               inst->wstyle[ckb].border_clr.g,
			               inst->wstyle[ckb].border_clr.b,
			               inst->wstyle[ckb].border_clr.a);
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
		bg_c = inst->wstyle[txt].bg_clr;
		body_c = inst->wstyle[txt].body_clr;
	} else {
		bg_c = inst->wstyle[txt].bg_hovered_clr;
		body_c = inst->wstyle[txt].body_hovered_clr;
	}
	text_c = inst->wstyle[txt].text_clr;
	if (!CTK_IsWidgetEnabled(inst, txt)) {
		body_c = inst->wstyle[txt].body_disabled_clr;
		text_c = inst->wstyle[txt].text_disabled_clr;
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
				       inst->wstyle[txt].text_bg_selected_clr.r,
				       inst->wstyle[txt].text_bg_selected_clr.g,
				       inst->wstyle[txt].text_bg_selected_clr.b,
				       inst->wstyle[txt].text_bg_selected_clr.a);
		SDL_RenderFillRect(r, &rect);
	}

	rect.x = 0 - inst->scroll_x[txt];
	rect.y = 0;
	rect.w = inst->rect[txt].w;
	rect.h = inst->rect[txt].h;
	TTF_SetTextColor(inst->text[txt], text_c.r, text_c.g, text_c.b, text_c.a);
	CTK_RenderText(r,
	               inst->text[txt],
	               rect,
	               inst->wstyle[txt].text_align,
	               -1, /* no underlines for entries */
	               text_c);

	if (inst->border[txt]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->rect[txt].w;
		rect.h = inst->rect[txt].h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[txt].border_clr.r,
			               inst->wstyle[txt].border_clr.g,
			               inst->wstyle[txt].border_clr.b,
			               inst->wstyle[txt].border_clr.a);
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
	inst->hovered_cmd = -1;
	inst->hovered_w = -1;
	inst->max_framerate = CTK_DEFAULT_MAX_FRAMERATE;
	inst->menubar = NULL;
	inst->style = CTK_DEFAULT_THEME;
	inst->txt_input_suspended = false;
	inst->visible_menu = NULL;
	inst->redraw = true;

	inst->binds = 0;

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
		SDL_SetError("Instance could not create a text engine");
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

	inst->entry_menu = CTK_CreateMenu();
	inst->entry_menu_cut = CTK_AddMenuCommand(inst,
	                                          inst->entry_menu,
	                                          "Cut",
	                                          CTK_EntryMenuCut,
	                                          NULL,
	                                          -1);
	inst->entry_menu_copy = CTK_AddMenuCommand(inst,
	                                           inst->entry_menu,
	                                           "Copy",
	                                           CTK_EntryMenuCopy,
	                                           NULL,
	                                           -1);
	CTK_AddMenuCommand(inst,
	                   inst->entry_menu,
	                   "Paste",
	                   CTK_EntryMenuPaste,
	                   NULL,
	                   -1);

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

CTK_Menu*
CTK_CreateMenu()
{
	CTK_Menu *ret;

	ret = malloc(sizeof(CTK_Menu));
	ret->rect.x = 0;
	ret->rect.y = 0;
	ret->rect.w = 0;
	ret->rect.h = 0;
	ret->commands = 0;

	return ret;
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
		bg_c = inst->wstyle[pgb].bg_clr;
	} else {
		bg_c = inst->wstyle[pgb].bg_hovered_clr;
	}
	fg_c = inst->wstyle[pgb].fg_clr;
	if (!CTK_IsWidgetEnabled(inst, pgb)) {
		fg_c = inst->wstyle[pgb].fg_disabled_clr;
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
			               inst->wstyle[pgb].border_clr.r,
			               inst->wstyle[pgb].border_clr.g,
			               inst->wstyle[pgb].border_clr.b,
			               inst->wstyle[pgb].border_clr.a);
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
		bg_c = inst->wstyle[rbn].bg_clr;
		body_c = inst->wstyle[rbn].body_clr;
	} else {
		bg_c = inst->wstyle[rbn].bg_hovered_clr;
		body_c = inst->wstyle[rbn].body_hovered_clr;
	}
	fg_c = inst->wstyle[rbn].fg_clr;
	if (!CTK_IsWidgetEnabled(inst, rbn)) {
		body_c = inst->wstyle[rbn].body_disabled_clr;
		fg_c = inst->wstyle[rbn].fg_disabled_clr;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	t = SDL_CreateTexture(r,
	                      CTK_PIXELFORMAT,
	                      CTK_TEXTUREACCESS,
	                      inst->wstyle[rbn].body_w,
	                      inst->wstyle[rbn].body_h);

	SDL_SetRenderTarget(r, t);
	SDL_SetRenderDrawColor(r, body_c.r, body_c.g, body_c.b, body_c.a);
	SDL_RenderClear(r);

	if (inst->toggle[rbn]) {
		rect.w = inst->wstyle[rbn].fill_w;
		rect.h = inst->wstyle[rbn].fill_h;
		rect.x = (inst->wstyle[rbn].body_w - rect.w) / 2;
		rect.y = (inst->wstyle[rbn].body_h - rect.h) / 2;
		SDL_SetRenderDrawColor(r, fg_c.r, fg_c.g, fg_c.b, fg_c.a);
		SDL_RenderFillRect(r, &rect);
	}

	if (inst->border[rbn]) {
		rect.x = 0;
		rect.y = 0;
		rect.w = inst->wstyle[rbn].body_w;
		rect.h = inst->wstyle[rbn].body_h;

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[rbn].border_clr.r,
			               inst->wstyle[rbn].border_clr.g,
			               inst->wstyle[rbn].border_clr.b,
			               inst->wstyle[rbn].border_clr.a);
		SDL_RenderRect(r, &rect);
	}

	SDL_SetRenderTarget(r, inst->texture[rbn]);
	rect.x = (inst->rect[rbn].w - inst->wstyle[rbn].body_w) / 2;
	rect.y = (inst->rect[rbn].h - inst->wstyle[rbn].body_h) / 2;
	rect.w = inst->wstyle[rbn].body_w;
	rect.h = inst->wstyle[rbn].body_h;
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

	border_c = inst->wstyle[scl].border_clr;
	if (inst->hovered_w != scl) {
		bg_c = inst->wstyle[scl].bg_clr;
		body_c = inst->wstyle[scl].body_clr;
	} else {
		bg_c = inst->wstyle[scl].bg_hovered_clr;
		body_c = inst->wstyle[scl].body_hovered_clr;
	}
	if (!CTK_IsWidgetEnabled(inst, scl)) {
		body_c = inst->wstyle[scl].body_disabled_clr;
	}

	SDL_SetRenderDrawColor(r, bg_c.r, bg_c.g, bg_c.b, bg_c.a);
	SDL_RenderClear(r);

	rect.w = inst->wstyle[scl].body_w / 2;
	rect.h = inst->wstyle[scl].body_h;
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

	if (NULL != inst->entry_menu) {
		CTK_DestroyMenu(inst->entry_menu);
	}

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
CTK_DestroyMenu(CTK_Menu *m)
{
	size_t i;

	for (i = 0; i < m->commands; i++) {
		TTF_DestroyText(m->accelerator[i]);
		TTF_DestroyText(m->label[i]);
	}

	free(m);
}

void
CTK_DestroyMenubar(CTK_Menubar *mb)
{
	size_t i;

	for (i = 0; i < mb->cascades; i++) {
		CTK_DestroyMenu(mb->menu[i]);
		TTF_DestroyText(mb->cascade[i]);
	}

	free(mb);
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

	/* bg */
	SDL_SetRenderDrawColor(r,
	                       inst->style.bg_clr.r,
	                       inst->style.bg_clr.g,
	                       inst->style.bg_clr.b,
	                       inst->style.bg_clr.a);
	SDL_RenderClear(r);

	/* content: clear */
	SDL_SetRenderTarget(r, inst->content);
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
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
	                       inst->style.focus_clr.r,
	                       inst->style.focus_clr.g,
	                       inst->style.focus_clr.b,
	                       inst->style.focus_clr.a);
	SDL_RenderRect(r, &inst->rect[fw]);

	/* content: text cursor */
	if (CTK_WTYPE_ENTRY == inst->type[fw]) {
		rect = CTK_MeasureTTFText(inst->text[fw], inst->cursor[fw], 0);
		rect.x -= inst->scroll_x[fw];

		SDL_SetRenderDrawColor(r,
			               inst->wstyle[fw].text_clr.r,
			               inst->wstyle[fw].text_clr.g,
			               inst->wstyle[fw].text_clr.b,
			               inst->wstyle[fw].text_clr.a);
		SDL_RenderLine(r,
		               inst->rect[fw].x + rect.x,
		               inst->rect[fw].y + 2,
		               inst->rect[fw].x + rect.x,
		               inst->rect[fw].y + inst->rect[fw].h - 3);
	}
	SDL_SetRenderTarget(r, NULL);

	/* content */
	frect.x = 0;
	frect.y = (NULL == inst->menubar ? 0 : inst->menubar->h);
	frect.w = inst->content->w;
	frect.h = inst->content->h;
	SDL_RenderTexture(r, inst->content, NULL, &frect);

	/* menubar, menu */
	if (NULL != inst->menubar) {
		CTK_DrawMenubar(inst);
	}
	if (NULL != inst->visible_menu) {
		CTK_DrawMenu(inst, inst->visible_menu);
	}

	/* final */
	SDL_RenderPresent(r);
	inst->redraw = false;

	if (NULL != inst->draw)
		inst->draw(inst, inst->draw_data);
}

void
CTK_DrawMenu(CTK_Instance *inst,
             CTK_Menu     *menu)
{
	SDL_Color     command_c;
	float         command_x;
	float         command_y;
	SDL_FRect     frect;
	int           h;
	size_t        i;
	SDL_Renderer *r;
	int           w;

	if (menu->commands <= 0) {
		return;
	}

	r = SDL_GetRenderer(inst->win);

	frect.x = menu->rect.x;
	frect.y = menu->rect.y;
	frect.w = menu->rect.w;
	frect.h = menu->rect.h;
	SDL_SetRenderDrawColor(r,
			       inst->style.menu_bg_clr.r,
			       inst->style.menu_bg_clr.g,
			       inst->style.menu_bg_clr.b,
			       inst->style.menu_bg_clr.a);
	SDL_RenderFillRect(r, &frect);

	command_x = frect.x;
	command_y = menu->rect.y;
	for (i = 0; i < menu->commands; i++) {
		if (menu->is_separator[i]) {
			frect.x = menu->rect.x + 2;
			frect.y = command_y + (inst->style.menu_separator_h / 2);
			frect.w = menu->rect.w - 4;
			frect.h = 2;
			SDL_SetRenderDrawColor(r,
	                                       inst->style.menu_border_clr.r,
	                                       inst->style.menu_border_clr.g,
	                                       inst->style.menu_border_clr.b,
	                                       inst->style.menu_border_clr.a);
			SDL_RenderRect(r, &frect);

			command_y += inst->style.menu_separator_h;
			continue;
		}

		if (inst->hovered_cmd == i &&
		    menu->enabled[inst->hovered_cmd]) {
			frect.x = command_x;
			frect.y = command_y;
			frect.w = menu->rect.w;
			frect.h = menu->h[i];
			SDL_SetRenderDrawColor(r,
			                       inst->style.menu_bg_hovered_clr.r,
			                       inst->style.menu_bg_hovered_clr.g,
			                       inst->style.menu_bg_hovered_clr.b,
			                       inst->style.menu_bg_hovered_clr.a);
			SDL_RenderFillRect(r, &frect);
		}

		if (menu->enabled[i]) {
			command_c = inst->style.menu_text_clr;
		} else {
			command_c = inst->style.menu_text_disabled_clr;
		}

		TTF_GetTextSize(menu->label[i], &w, &h);
		frect.x = command_x + inst->style.menu_command_padding_left;
		frect.y = command_y + inst->style.menu_command_padding_top;
		frect.w = w;
		frect.h = h;

		TTF_SetTextColor(menu->label[i],
		                 command_c.r,
				 command_c.g,
				 command_c.b,
				 command_c.a);
		CTK_RenderText(r,
		               menu->label[i],
		               frect,
		               CTK_TEXT_ALIGNMENT_LEFT,
		               menu->underline[i],
		               inst->style.menu_text_clr);

		frect.x += w + inst->style.menu_command_padding_right;
		frect.w = menu->rect.w - frect.x;
		frect.h = h;

		TTF_SetTextColor(menu->accelerator[i],
		                 command_c.r,
				 command_c.g,
				 command_c.b,
				 command_c.a);
		CTK_RenderText(r,
		               menu->accelerator[i],
		               frect,
		               CTK_TEXT_ALIGNMENT_RIGHT,
		               -1,
		               inst->style.menu_text_clr);

		command_y += menu->h[i];
	}

	if (inst->style.menu_border) {
		frect.x = menu->rect.x;
		frect.y = menu->rect.y;
		frect.w = menu->rect.w;
		frect.h = menu->rect.h;

		SDL_SetRenderDrawColor(r,
	                               inst->style.menu_border_clr.r,
	                               inst->style.menu_border_clr.g,
	                               inst->style.menu_border_clr.b,
	                               inst->style.menu_border_clr.a);
		SDL_RenderRect(r, &frect);
	}
}

void
CTK_DrawMenubar(CTK_Instance *inst)
{
	float         cascade_x;
	size_t        i;
	SDL_Renderer *r;
	SDL_FRect     frect;
	int           w;

	r = SDL_GetRenderer(inst->win);
	SDL_GetRenderOutputSize(r, &w, NULL);

	frect.x = 0;
	frect.y = 0;
	frect.w = w;
	frect.h = inst->menubar->h;
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
			frect.w = inst->style.menubar_cascade_padding_left +
			          inst->menubar->cascade_w[i] +
			          inst->style.menubar_cascade_padding_right;
			frect.h = inst->menubar->h;
			SDL_SetRenderDrawColor(r,
					       inst->style.menubar_bg_hovered_clr.r,
					       inst->style.menubar_bg_hovered_clr.g,
					       inst->style.menubar_bg_hovered_clr.b,
					       inst->style.menubar_bg_hovered_clr.a);
			SDL_RenderFillRect(r, &frect);
		}

		TTF_SetTextColor(inst->menubar->cascade[i],
	                         inst->style.menubar_text_clr.r,
	                         inst->style.menubar_text_clr.g,
	                         inst->style.menubar_text_clr.b,
	                         inst->style.menubar_text_clr.a);
		frect.x = cascade_x + inst->style.menubar_cascade_padding_left;
		frect.y = inst->style.menubar_cascade_padding_top;
		frect.w = inst->menubar->cascade_w[i];
		frect.h = inst->menubar->cascade_h[i];

		CTK_RenderText(r,
		               inst->menubar->cascade[i],
		               frect,
		               CTK_TEXT_ALIGNMENT_LEFT,
		               inst->menubar->underline[i],
		               inst->style.menubar_text_clr);

		cascade_x += inst->menubar->cascade_w[i] +
		             inst->style.menubar_cascade_padding_right +
		             inst->style.menubar_cascade_padding_left;
	}

	frect.x = 0;
	frect.y = 0;
	frect.w = w;
	frect.h = inst->menubar->h;
	SDL_SetRenderDrawColor(r,
		               inst->style.menubar_border_clr.r,
		               inst->style.menubar_border_clr.g,
		               inst->style.menubar_border_clr.b,
		               inst->style.menubar_border_clr.a);
	if (inst->style.menubar_border) {
		SDL_RenderRect(r, &frect);
	}
}

void
CTK_EntryMenuCut(CTK_Instance *inst,
                 void         *dummy)
{
	size_t a, b;
	int c_shift = 0;
	CTK_WidgetId fw;
	char temp;

	(void) dummy;

	fw = CTK_GetFocusedWidget(inst);

	if (CTK_WTYPE_ENTRY != inst->type[fw] ||
	    inst->cursor[fw] == inst->selection[fw])
		return;

	if (inst->cursor[fw] < inst->selection[fw]) {
		a = inst->cursor[fw];
		b = inst->selection[fw];
	} else {
		a = inst->selection[fw];
		b = inst->cursor[fw];
		c_shift -= inst->cursor[fw] - inst->selection[fw];
	}

	temp = inst->text[fw]->text[b];
	inst->text[fw]->text[b] = '\0';
	SDL_SetClipboardText(&inst->text[fw]->text[a]);
	inst->text[fw]->text[b] = temp;

	TTF_DeleteTextString(inst->text[fw], a, b - a);
	CTK_ShiftWidgetTextCursor(inst, fw, c_shift, true);

	if (NULL != inst->edit[fw]) {
		inst->edit[fw](inst, fw, inst->edit_data[fw]);
	}
}

void
CTK_EntryMenuCopy(CTK_Instance *inst,
                  void         *dummy)
{
	size_t a, b;
	CTK_WidgetId fw;
	char temp;

	(void) dummy;

	fw = CTK_GetFocusedWidget(inst);

	if (CTK_WTYPE_ENTRY != inst->type[fw] ||
	    inst->cursor[fw] == inst->selection[fw])
		return;

	if (inst->cursor[fw] > inst->selection[fw]) {
		a = inst->selection[fw];
		b = inst->cursor[fw];
	} else {
		a = inst->cursor[fw];
		b = inst->selection[fw];
	}

	temp = inst->text[fw]->text[b];
	inst->text[fw]->text[b] = '\0';
	SDL_SetClipboardText(&inst->text[fw]->text[a]);
	inst->text[fw]->text[b] = temp;
}

void
CTK_EntryMenuPaste(CTK_Instance *inst,
                   void         *dummy)
{
	char *buf;
	int c_shift = 0;
	CTK_WidgetId fw;

	(void) dummy;

	fw = CTK_GetFocusedWidget(inst);

	if (CTK_WTYPE_ENTRY != inst->type[fw] ||
	    !SDL_HasClipboardText())
		return;

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

	if (NULL != inst->edit[fw]) {
		inst->edit[fw](inst, fw, inst->edit_data[fw]);
	}

	SDL_free(buf);
}

void
CTK_FocusMenu(CTK_Instance *inst,
              CTK_Menu     *menu)
{
	if (SDL_TextInputActive(inst->win)) {
		SDL_StopTextInput(inst->win);
		inst->txt_input_suspended = true;
	}

	inst->visible_menu = menu;
	inst->redraw = true;
}

void
CTK_FocusMenubar(CTK_Instance *inst,
                 const size_t  cascade)
{
	if (cascade >= CTK_MENUBAR_MAX_CASCADES ||
	    cascade == inst->focused_casc) {
		return;
	}

	inst->focused_casc = cascade;

	if (cascade < inst->menubar->cascades) {
		CTK_FocusMenu(inst, inst->menubar->menu[cascade]);
	} else {
		CTK_UnfocusMenubar(inst);
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

	slider_w = inst->wstyle[fw].body_w;
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
CTK_HandleKeybinds(CTK_Instance            *inst,
                   const SDL_KeyboardEvent  e)
{
	SDL_Keymod comp;
	size_t     comp_match;
	size_t     i;
	size_t     bindmatch = -1;
	size_t     bindmatch_comp_match = 0;

	for (i = 0; i < inst->binds; i++) {
		if (inst->bind_key[i] == e.key &&
		    inst->bind_mod[i] & e.mod) {
			comp = inst->bind_mod[i] & e.mod;
			comp_match = 0;
			while (comp) { /* cheers, Brian Kernighan */
				comp &= (comp -1);
				comp_match++;
			}

			if (bindmatch == (size_t) -1) {
				bindmatch = i;
				bindmatch_comp_match = comp_match;
			} else if (comp_match > bindmatch_comp_match) {
				bindmatch = i;
				bindmatch_comp_match = comp_match;
			}
		}
	}

	if ((size_t) -1 != bindmatch)
		inst->bind_fn[bindmatch](inst, inst->bind_fn_data[bindmatch]);
}

void
CTK_HandleKeyDown(CTK_Instance            *inst,
                  const SDL_KeyboardEvent  e)
{
	int           c_shift = 0;
	size_t        i;
	CTK_WidgetId  fw;
	char          temp;

	if (NULL != inst->visible_menu &&
	    ((e.key >= SDLK_A && e.key <= SDLK_Z) ||
	     (e.key >= SDLK_0 && e.key <= SDLK_9))) {
		for (i = 0; i < inst->visible_menu->commands; i++) {
			if (!inst->visible_menu->enabled[i] ||
			    inst->visible_menu->is_separator[i]) {
				continue;
			}

			temp = inst->visible_menu->label[i]->text[inst->visible_menu->underline[i]];
			temp = toupper(temp);

			if (SDL_GetKeyName(e.key)[0] == temp) {
				inst->visible_menu->command[i](inst,
				                               inst->visible_menu->command_data[i]);
				CTK_UnfocusMenubar(inst);
				break;
			}
		}

		return;
	}

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

		if (NULL != inst->edit[fw]) {
			inst->edit[fw](inst, fw, inst->edit_data[fw]);
		}
		break;

	case SDLK_C:
		fw = CTK_GetFocusedWidget(inst);

		if (!(SDL_KMOD_CTRL & e.mod))
			break;

		CTK_EntryMenuCopy(inst, NULL);
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

		if (NULL != inst->edit[fw]) {
			inst->edit[fw](inst, fw, inst->edit_data[fw]);
		}
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
			if (NULL != inst->trigger[fw]) {
				inst->trigger[fw](inst,
					          fw,
					          inst->trigger_data[fw]);
			}
			break;

		case CTK_WTYPE_CHECKBOX:
			CTK_ToggleCheckbox(inst, fw);
			break;

		case CTK_WTYPE_RADIOBUTTON:
			CTK_ToggleRadiobutton(inst, fw);
			break;
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

		if (!(SDL_KMOD_CTRL & e.mod))
			break;

		CTK_EntryMenuPaste(inst, NULL);
		break;

	case SDLK_X:
		fw = CTK_GetFocusedWidget(inst);

		if (!(SDL_KMOD_CTRL & e.mod))
			break;

		CTK_EntryMenuCut(inst, NULL);
		break;
	}
}

void
CTK_HandleLMBDown(CTK_Instance               *inst,
                  const SDL_MouseButtonEvent  e)
{
	size_t       i;
	CTK_Menubar *mb;
	size_t       new_focused_casc;
	SDL_FPoint   p;
	CTK_WidgetId w;
	int          x;

	mb = inst->menubar;

	if (NULL != inst->visible_menu) {
		p.x = e.x;
		p.y = e.y;
		if (!SDL_PointInRectFloat(&p, &inst->visible_menu->rect)) {
			CTK_UnfocusMenubar(inst);
		}
		return;
	}

	if (NULL != mb &&
	    e.y < inst->menubar->h) {
		new_focused_casc = -1;
		x = 0;
		for (i = 0; i < mb->cascades; i++) {
			if (e.x > x &&
			    e.x < x + mb->cascade_w[i]) {
				new_focused_casc = i;
				break;
			}
			x += mb->cascade_w[i];
		}
	}

	CTK_FocusMenubar(inst, new_focused_casc);

	p.x = e.x;
	p.y = e.y - (mb ? inst->menubar->h : 0);

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
CTK_HandleLMBUp(CTK_Instance               *inst,
                const SDL_MouseButtonEvent  e)
{
	size_t       command_y;
	size_t       i;
	SDL_FPoint   p;
	CTK_WidgetId wid;

	inst->drag = false;

	p.x = e.x;
	p.y = e.y;
	if (NULL != inst->visible_menu &&
	    inst->visible_menu->commands > 0 &&
	    SDL_PointInRectFloat(&p, &inst->visible_menu->rect)) {
		command_y = inst->visible_menu->rect.y;

		for (i = 0; i < inst->visible_menu->commands; i++) {
			if (p.y >= command_y &&
			    p.y <= command_y + inst->visible_menu->h[i]) {
				if (NULL != inst->visible_menu->command[i] &&
				    inst->visible_menu->enabled[i]) {
					inst->visible_menu->command[i](inst,
					                               inst->visible_menu->command_data[i]);
				}
				CTK_UnfocusMenubar(inst);
				return;
			}
			command_y += inst->visible_menu->h[i];
		}
	}

	for (i = 0; i < inst->enabled_ws; i++) {
		wid = inst->enabled_w[i];
		p.x = e.x;
		p.y = e.y - (inst->menubar ? inst->menubar->h : 0);

		if (!SDL_PointInRectFloat(&p, &inst->rect[wid]))
			continue;

		switch (inst->type[wid]) {
		case CTK_WTYPE_UNKNOWN:
		case CTK_WTYPE_BUTTON:
		case CTK_WTYPE_ENTRY:
		case CTK_WTYPE_LABEL:
		case CTK_WTYPE_PROGRESSBAR:
		case CTK_WTYPE_SCALE:
			if (NULL != inst->trigger[wid]) {
				inst->trigger[wid](inst,
					           wid,
					           inst->trigger_data[wid]);
			}
			break;

		case CTK_WTYPE_CHECKBOX:
			CTK_ToggleCheckbox(inst, wid);
			break;

		case CTK_WTYPE_RADIOBUTTON:
			CTK_ToggleRadiobutton(inst, wid);
			break;
		}

		if (NULL != inst->mouse_release[wid]) {
			inst->mouse_release[wid](inst,
			                         e,
			                         wid,
			                         inst->mouse_release_data[wid]);
		}
	}
}

void
CTK_HandleMouseMotion(CTK_Instance               *inst,
                      const SDL_MouseMotionEvent  e)
{
	int          casc_x;
	int          casc_w;
	size_t       command_y;
	size_t       i;
	SDL_FPoint   p;
	CTK_Menubar *mb;
	size_t       new_focused_casc = inst->focused_casc;
	size_t       new_hovered_casc = -1;
	size_t       new_hovered_cmd = -1;
	CTK_WidgetId old_hov_wid;
	CTK_WidgetId wid;

	mb = inst->menubar;
	old_hov_wid = inst->hovered_w;
	inst->hovered_w = -1;

	if (NULL != mb &&
	    e.y < inst->menubar->h) {
		new_hovered_casc = -1;

		casc_x = 0;
		for (i = 0; i < mb->cascades; i++) {
			casc_w = inst->style.menubar_cascade_padding_left +
			         mb->cascade_w[i] +
			         inst->style.menubar_cascade_padding_right;
			if (e.x >= casc_x &&
			    e.x <= casc_x + casc_w ) {
				new_focused_casc = i;
				new_hovered_casc = i;
				break;
			}
			casc_x += casc_w;
		}
	}

	if (inst->focused_casc < CTK_MENUBAR_MAX_CASCADES)
		CTK_FocusMenubar(inst, new_focused_casc);

	if (new_hovered_casc != inst->hovered_casc) {
		inst->hovered_casc = new_hovered_casc;
		inst->redraw = true;
	}

	p.x = e.x;
	p.y = e.y;
	if (NULL != inst->visible_menu &&
	    inst->visible_menu->commands > 0 &&
	    SDL_PointInRectFloat(&p, &inst->visible_menu->rect)) {
		command_y = inst->visible_menu->rect.y;

		for (i = 0; i < inst->visible_menu->commands; i++) {
			if (p.y >= command_y &&
			    p.y <= command_y + inst->visible_menu->h[i]) {
				new_hovered_cmd = i;
				break;
			}
			command_y += inst->visible_menu->h[i];
		}
	}

	if (new_hovered_cmd != inst->hovered_cmd) {
		inst->hovered_cmd = new_hovered_cmd;
		inst->redraw = true;
	}

	if (NULL == inst->visible_menu) {
		for (i = 0; i < inst->enabled_ws; i++) {
			wid = inst->enabled_w[i];
			p.x = e.x;
			p.y = e.y - (mb ? inst->menubar->h : 0);

			if (!SDL_PointInRectFloat(&p, &inst->rect[wid]))
				continue;

			inst->hovered_w = wid;

			if (inst->mouse_motion[wid]) {
				inst->mouse_motion[wid](inst,
					                e,
					                wid,
					                inst->mouse_motion_data);
			}
			break;
		}
	}

	if (old_hov_wid == inst->hovered_w)
		return;

	if (inst->hovered_w < inst->widgets)
		CTK_CreateWidgetTexture(inst, inst->hovered_w);

	if (old_hov_wid  < inst->widgets)
		CTK_CreateWidgetTexture(inst, old_hov_wid);
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
		p.y = e.mouse_y - (inst->menubar ? inst->menubar->h : 0);

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

		if (NULL != inst->mouse_wheel[w]) {
			inst->mouse_wheel[w](inst,
			                     e,
			                     w,
			                     inst->mouse_wheel_data[w]);
		}
	}
}

void
CTK_HandleRMBDown(CTK_Instance               *inst,
                  const SDL_MouseButtonEvent  e)
{
	bool all_cmds = false;
	size_t i;
	SDL_FPoint p;

	for (i = 0; i < inst->widgets; i++) {
		p.x = e.x;
		p.y = e.y - (inst->menubar ? inst->menubar->h : 0);

		if (CTK_WTYPE_ENTRY == inst->type[i] &&
		    SDL_PointInRectFloat(&p, &inst->rect[i])) {
			inst->entry_menu->rect.x = e.x + 1;
			inst->entry_menu->rect.y = e.y + 1;

			if (inst->cursor[i] != inst->selection[i]) {
				all_cmds = true;
			}
			inst->entry_menu->enabled[inst->entry_menu_cut] = all_cmds;
			inst->entry_menu->enabled[inst->entry_menu_copy] = all_cmds;

			CTK_FocusMenu(inst, inst->entry_menu);
			break;
		}
	}
}

void
CTK_HandleRMBUp(CTK_Instance               *inst,
                const SDL_MouseButtonEvent  e)
{
	CTK_HandleLMBUp(inst, e);
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

	if (NULL != inst->edit[fw]) {
		inst->edit[fw](inst, fw, inst->edit_data[fw]);
	}
}

CTK_WidgetId
CTK_GetFocusedWidget(const CTK_Instance *inst)
{
	return inst->focusable_w[inst->focused_w];
}

void
CTK_GetKeyOrModFromName(const char  *name,
                        SDL_Keycode *key,
                        SDL_Keymod  *mod)
{
	*key = SDLK_UNKNOWN;
	*mod = SDL_KMOD_NONE;

	if (strcmp(name, "1") == 0) {
		*key = SDLK_1;
	} else if (strcmp(name, "2") == 0) {
		*key = SDLK_2;
	} else if (strcmp(name, "3") == 0) {
		*key = SDLK_3;
	} else if (strcmp(name, "4") == 0) {
		*key = SDLK_4;
	} else if (strcmp(name, "5") == 0) {
		*key = SDLK_5;
	} else if (strcmp(name, "6") == 0) {
		*key = SDLK_6;
	} else if (strcmp(name, "7") == 0) {
		*key = SDLK_7;
	} else if (strcmp(name, "8") == 0) {
		*key = SDLK_8;
	} else if (strcmp(name, "9") == 0) {
		*key = SDLK_9;
	} else if (strcmp(name, "0") == 0) {
		*key = SDLK_0;
	} else if (strcmp(name, "A") == 0) {
		*key = SDLK_A;
	} else if (strcmp(name, "B") == 0) {
		*key = SDLK_B;
	} else if (strcmp(name, "C") == 0) {
		*key = SDLK_C;
	} else if (strcmp(name, "D") == 0) {
		*key = SDLK_D;
	} else if (strcmp(name, "E") == 0) {
		*key = SDLK_E;
	} else if (strcmp(name, "F") == 0) {
		*key = SDLK_F;
	} else if (strcmp(name, "G") == 0) {
		*key = SDLK_G;
	} else if (strcmp(name, "H") == 0) {
		*key = SDLK_H;
	} else if (strcmp(name, "I") == 0) {
		*key = SDLK_I;
	} else if (strcmp(name, "J") == 0) {
		*key = SDLK_J;
	} else if (strcmp(name, "K") == 0) {
		*key = SDLK_K;
	} else if (strcmp(name, "L") == 0) {
		*key = SDLK_L;
	} else if (strcmp(name, "M") == 0) {
		*key = SDLK_M;
	} else if (strcmp(name, "N") == 0) {
		*key = SDLK_N;
	} else if (strcmp(name, "O") == 0) {
		*key = SDLK_O;
	} else if (strcmp(name, "P") == 0) {
		*key = SDLK_P;
	} else if (strcmp(name, "Q") == 0) {
		*key = SDLK_Q;
	} else if (strcmp(name, "R") == 0) {
		*key = SDLK_R;
	} else if (strcmp(name, "S") == 0) {
		*key = SDLK_S;
	} else if (strcmp(name, "T") == 0) {
		*key = SDLK_T;
	} else if (strcmp(name, "U") == 0) {
		*key = SDLK_U;
	} else if (strcmp(name, "V") == 0) {
		*key = SDLK_V;
	} else if (strcmp(name, "W") == 0) {
		*key = SDLK_W;
	} else if (strcmp(name, "X") == 0) {
		*key = SDLK_X;
	} else if (strcmp(name, "Y") == 0) {
		*key = SDLK_Y;
	} else if (strcmp(name, "Z") == 0) {
		*key = SDLK_Z;
	} else if (strcmp(name, "Space") == 0) {
		*key = SDLK_SPACE;
	} else if (strcmp(name, "Tab") == 0) {
		*key = SDLK_TAB;
	} else if (strcmp(name, "Control") == 0 ||
	           strcmp(name, "Ctrl") == 0) {
		*mod = SDL_KMOD_CTRL;
	} else if (strcmp(name, "Shift") == 0) {
		*mod = SDL_KMOD_SHIFT;
	} else if (strcmp(name, "Capslock") == 0 ||
	           strcmp(name, "Caps") == 0) {
		*mod = SDL_KMOD_CAPS;
	} else if (strcmp(name, "Meta") == 0) {
		*mod = SDL_KMOD_GUI;
	} else if (strcmp(name, "Alt") == 0) {
		*mod = SDL_KMOD_LALT;
	} else if (strcmp(name, "AltGr") == 0) {
		*mod = SDL_KMOD_RALT;
	}
}

bool
CTK_GetWidgetEnabledId(const CTK_Instance *inst,
                       const CTK_WidgetId  widget,
                       size_t             *cacheId)
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
                         size_t             *cacheId)
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
                       size_t             *cacheId)
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
	size_t dummy;

	return CTK_GetWidgetEnabledId(inst, widget, &dummy);
}

bool
CTK_IsWidgetFocusable(const CTK_Instance *inst,
                      const CTK_WidgetId  widget)
{
	size_t dummy;

	return CTK_GetWidgetFocusableId(inst, widget, &dummy);
}

bool
CTK_IsWidgetVisible(const CTK_Instance *inst,
                    const CTK_WidgetId  widget)
{
	size_t dummy;

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
CTK_RenderText(SDL_Renderer            *r,
               TTF_Text                *text,
               const SDL_FRect          rect,
               const CTK_TextAlignment  ta,
               const size_t             underline,
               const SDL_Color          underline_clr)
{
	int      text_w;
	int      text_h;
	SDL_Rect underline_r;
	int      x, y;

	if (NULL == text ||
	    NULL == text->text) {
		return false;
	}

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

	x += rect.x;
	y = (rect.h - text_h) / 2.0;
	y += rect.y;

	if (!TTF_DrawRendererText(text, x, y))
		return false;

	if (underline < strlen(text->text)) {
		SDL_SetRenderDrawColor(r,
                                       underline_clr.r,
                                       underline_clr.g,
                                       underline_clr.b,
                                       underline_clr.a);
		underline_r = CTK_MeasureTTFText(text, underline, 1);

		SDL_RenderLine(r,
		               x + underline_r.x,
		               y + text_h,
		               x + underline_r.x + underline_r.w,
		               y + text_h);
	}

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

bool
CTK_SetMenuCommandAccelerator(CTK_Instance *inst,
                              CTK_Menu     *menu,
                              const size_t  cmd_id,
                              const char   *keystr)
{
	if (cmd_id >= menu->commands ||
	   !CTK_Bind(inst,
	             keystr,
	             menu->command[cmd_id],
	             menu->command_data[cmd_id]))
		return false;

	TTF_AppendTextString(menu->accelerator[cmd_id], keystr, 0);

	return true;
}

void
CTK_SetWidgetEnabled(CTK_Instance       *inst,
                     const CTK_WidgetId  widget,
                     const bool          enabled)
{
	size_t i;
	bool is_enabled;
	size_t enabledId;

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
	size_t focusableId;

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
		if (widget == inst->focusable_w[inst->focused_w]) {
			inst->focused_w++;
			if (inst->focused_w >= inst->focusable_ws) {
				inst->focused_w = 0;
			}
		}

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
CTK_SetWidgetUnderline(CTK_Instance       *inst,
                       const CTK_WidgetId  widget,
                       const size_t        underline)
{
	inst->underline[widget] = underline;
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

	if (NULL != inst->edit[widget]) {
		inst->edit[widget](inst, widget, inst->edit_data[widget]);
	}
}

void
CTK_SetWidgetVisible(CTK_Instance       *inst,
                     const CTK_WidgetId  widget,
                     const bool          visible)
{
	size_t i;
	bool is_visible;
	size_t visibleId;

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
			if (SDL_BUTTON_LEFT == e.button.button) {
				CTK_HandleLMBDown(inst, e.button);
			} else if (SDL_BUTTON_RIGHT == e.button.button) {
				CTK_HandleRMBDown(inst, e.button);
			}
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (SDL_BUTTON_LEFT == e.button.button) {
				CTK_HandleLMBUp(inst, e.button);
			} else if (SDL_BUTTON_RIGHT == e.button.button) {
				CTK_HandleRMBUp(inst, e.button);
			}
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
			CTK_HandleKeybinds(inst, e.key);
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

	if (NULL != inst->edit[widget]) {
		inst->edit[widget](inst, widget, inst->edit_data[widget]);
	}
	if (NULL != inst->trigger[widget]) {
		inst->trigger[widget](inst, widget, inst->trigger_data[widget]);
	}
}

void
CTK_ToggleRadiobutton(CTK_Instance *inst,
                      CTK_WidgetId  widget)
{
	size_t i;

	if (inst->toggle[widget])
		return;

	for (i = 0; i < inst->widgets; i++) {
		if (inst->group[i] == inst->group[widget] &&
		    i != widget) {
			inst->toggle[i] = false;
			CTK_CreateWidgetTexture(inst, i);

			if (NULL != inst->edit[i]) {
				inst->edit[i](inst, i, inst->edit_data[i]);
			}
		}
	}
	inst->toggle[widget] = true;
	CTK_CreateWidgetTexture(inst, widget);

	if (NULL != inst->edit[widget]) {
		inst->edit[widget](inst, widget, inst->edit_data[widget]);
	}
	if (NULL != inst->trigger[widget]) {
		inst->trigger[widget](inst, widget, inst->trigger_data[widget]);
	}
}

void
CTK_UnfocusMenu(CTK_Instance *inst)
{
	if (inst->txt_input_suspended) {
		SDL_StartTextInput(inst->win);
		inst->txt_input_suspended = false;
	}

	inst->visible_menu = NULL;
	inst->redraw = true;
}

void
CTK_UnfocusMenubar(CTK_Instance *inst)
{
	CTK_UnfocusMenu(inst);
	inst->focused_casc = -1;
}

void
CTK_UpdateMenuSize(const CTK_Instance *inst,
                   CTK_Menu           *m)
{
	size_t i;
	int h, h1, h2;
	int w, w1, w2;

	m->rect.w = 0;
	m->rect.h = 0;
	for (i = 0; i < m->commands; i++) {
		if (m->is_separator[i]) {
			m->h[i] = inst->style.menu_separator_h;
			m->rect.h += m->h[i];

			continue;
		}

		TTF_GetTextSize(m->accelerator[i], &w1, &h1);
		TTF_GetTextSize(m->label[i], &w2, &h2);
		w = inst->style.menu_command_padding_left +
		    w1 +
		    inst->style.menu_command_padding_right +
		    w2;
		h = (h1 > h2 ? h1 : h2);

		m->h[i] = inst->style.menu_command_padding_top +
		          h +
		          inst->style.menu_command_padding_bottom;
		m->rect.h += m->h[i];
		if (w > m->rect.w) {
			m->rect.w = w;
		}
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
