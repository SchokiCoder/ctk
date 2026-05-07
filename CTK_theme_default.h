/* SPDX-License-Identifier: MPL-2.0
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#ifndef _CTK_THEME_DEFAULT_H
#define _CTK_THEME_DEFAULT_H

#include "CTK.h"

#define CTK_THEME_DEFAULT_TEXT_GRAY 0x00
#define CTK_THEME_DEFAULT_TEXT_A    0xff

#define CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY 0xa4
#define CTK_THEME_DEFAULT_TEXT_DISABLED_A    0xff

#define CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY 0xda
#define CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_A    0xff

#define CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY 0x83
#define CTK_THEME_DEFAULT_WIDGET_BORDER_A    0xff

#define CTK_THEME_DEFAULT_WIDGET_FG_R 0x48
#define CTK_THEME_DEFAULT_WIDGET_FG_G 0x68
#define CTK_THEME_DEFAULT_WIDGET_FG_B 0x87
#define CTK_THEME_DEFAULT_WIDGET_FG_A 0xff

#define CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY 0xa4
#define CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_A    0xff

#define CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY 0xff
#define CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A    0xff

#define CTK_THEME_DEFAULT_WIDGET_HEIGHT 27

#define CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY 0xed
#define CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_A    0xff

#define CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY 0xda
#define CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_A    0xff

void
CTK_ThemeDefaultDrawMenu(CTK_Instance     *inst,
                         const CTK_MenuId  m);

void
CTK_ThemeDefaultDrawMenubar(CTK_Instance *inst);

void
CTK_ThemeDefaultRenderButton(CTK_Instance       *inst,
                             const CTK_WidgetId  btn);

void
CTK_ThemeDefaultRenderCheckbox(CTK_Instance       *inst,
                               const CTK_WidgetId  ckb);

void
CTK_ThemeDefaultRenderEntry(CTK_Instance       *inst,
                            const CTK_WidgetId  txt);

void
CTK_ThemeDefaultRenderProgressbar(CTK_Instance       *inst,
                                  const CTK_WidgetId  pgb);

void
CTK_ThemeDefaultRenderRadiobutton(CTK_Instance       *inst,
                                  const CTK_WidgetId  rbn);

void
CTK_ThemeDefaultRenderScale(CTK_Instance       *inst,
                            const CTK_WidgetId  scl);

#ifdef CTK_IMPLEMENTATION

static const CTK_Style CTK_THEME_DEFAULT = {
	.menu_border = true,
	.menu_command_border_focused = true,

	.menubar_border = true,
	.menubar_cascade_border_focused = true,

	.menu_command_padding_left = 4,
	.menu_command_padding_top = 6,
	.menu_command_padding_right = 4,
	.menu_command_padding_bottom = 5,

	.menu_accelerator_padding_left = 10,
	.menu_accelerator_padding_right = 4,

	.menu_separator_h = 19,

	.menubar_cascade_padding_left = 4,
	.menubar_cascade_padding_top = 10,
	.menubar_cascade_padding_right = 4,
	.menubar_cascade_padding_bottom = 9,

	.bg_clr.r = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.bg_clr.g = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.bg_clr.b = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.bg_clr.a = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_A,

	.focus_clr.r = 0x48,
	.focus_clr.g = 0x68,
	.focus_clr.b = 0x87,
	.focus_clr.a = 0xff,

	.menu_bg_clr.r = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.menu_bg_clr.g = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.menu_bg_clr.b = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.menu_bg_clr.a = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_A,

	.menu_command_bg_focused_clr.r = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
	.menu_command_bg_focused_clr.g = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
	.menu_command_bg_focused_clr.b = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
	.menu_command_bg_focused_clr.a = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_A,

	.menu_border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
	.menu_border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
	.menu_border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
	.menu_border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

	.menu_text_clr.r = CTK_THEME_DEFAULT_TEXT_GRAY,
	.menu_text_clr.g = CTK_THEME_DEFAULT_TEXT_GRAY,
	.menu_text_clr.b = CTK_THEME_DEFAULT_TEXT_GRAY,
	.menu_text_clr.a = CTK_THEME_DEFAULT_TEXT_A,

	.menu_text_disabled_clr.r = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
	.menu_text_disabled_clr.g = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
	.menu_text_disabled_clr.b = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
	.menu_text_disabled_clr.a = CTK_THEME_DEFAULT_TEXT_DISABLED_A,

	.menubar_bg_clr.r = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.menubar_bg_clr.g = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.menubar_bg_clr.b = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
	.menubar_bg_clr.a = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_A,

	.menubar_cascade_bg_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
	.menubar_cascade_bg_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
	.menubar_cascade_bg_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
	.menubar_cascade_bg_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_A,

	.menubar_border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
	.menubar_border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
	.menubar_border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
	.menubar_border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

	.menubar_text_clr.r = CTK_THEME_DEFAULT_TEXT_GRAY,
	.menubar_text_clr.g = CTK_THEME_DEFAULT_TEXT_GRAY,
	.menubar_text_clr.b = CTK_THEME_DEFAULT_TEXT_GRAY,
	.menubar_text_clr.a = CTK_THEME_DEFAULT_TEXT_A,

	.button = {
		.w = 80,
		.h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.text_align = CTK_TEXT_ALIGNMENT_CENTER,

		.bg_clr.r = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.g = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.b = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.a = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_A,

		.bg_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_A,

		.border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

		.text_clr.r = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.g = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.b = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.a = CTK_THEME_DEFAULT_TEXT_A,

		.text_disabled_clr.r = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.g = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.b = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.a = CTK_THEME_DEFAULT_TEXT_DISABLED_A,

		.render = CTK_ThemeDefaultRenderButton,
	},

	.checkbox = {
		.w = CTK_THEME_DEFAULT_WIDGET_HEIGHT,
		.h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.body_w = 10,
		.body_h = 10,

		.fill_w = 10,
		.fill_h = 10,

		.bg_clr.r = 0x00,
		.bg_clr.g = 0x00,
		.bg_clr.b = 0x00,
		.bg_clr.a = 0x00,

		.bg_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_A,

		.body_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

		.fg_clr.r = CTK_THEME_DEFAULT_WIDGET_FG_R,
		.fg_clr.g = CTK_THEME_DEFAULT_WIDGET_FG_G,
		.fg_clr.b = CTK_THEME_DEFAULT_WIDGET_FG_B,
		.fg_clr.a = CTK_THEME_DEFAULT_WIDGET_FG_A,

		.fg_disabled_clr.r = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.g = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.b = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.a = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_A,

		.render = CTK_ThemeDefaultRenderCheckbox,
	},

	.entry = {
		.w = 165,
		.h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.text_align = CTK_TEXT_ALIGNMENT_LEFT,

		.bg_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.bg_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.bg_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.bg_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.bg_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.body_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

		.text_clr.r = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.g = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.b = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.a = CTK_THEME_DEFAULT_TEXT_A,

		.text_disabled_clr.r = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.g = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.b = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.a = CTK_THEME_DEFAULT_TEXT_DISABLED_A,

		.text_bg_selected_clr.r = 0x7c,
		.text_bg_selected_clr.g = 0xb0,
		.text_bg_selected_clr.b = 0xe2,
		.text_bg_selected_clr.a = 0xff,

		.render = CTK_ThemeDefaultRenderEntry,
	},

	.label = {
		.w = 80,
		.h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.text_align = CTK_TEXT_ALIGNMENT_LEFT,

		.bg_clr.r = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.g = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.b = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.a = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_A,

		.bg_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_NORMAL_BG_A,

		.border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

		.text_clr.r = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.g = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.b = CTK_THEME_DEFAULT_TEXT_GRAY,
		.text_clr.a = CTK_THEME_DEFAULT_TEXT_A,

		.text_disabled_clr.r = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.g = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.b = CTK_THEME_DEFAULT_TEXT_DISABLED_GRAY,
		.text_disabled_clr.a = CTK_THEME_DEFAULT_TEXT_DISABLED_A,

		.render = CTK_ThemeDefaultRenderButton,
	},

	.progressbar = {
		.w = 100,
		.h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.bg_clr.r = 0xc3,
		.bg_clr.g = 0xc3,
		.bg_clr.b = 0xc3,
		.bg_clr.a = 0xff,

		.bg_hovered_clr.r = 0xc3,
		.bg_hovered_clr.g = 0xc3,
		.bg_hovered_clr.b = 0xc3,
		.bg_hovered_clr.a = 0xff,

		.border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

		.fg_clr.r = CTK_THEME_DEFAULT_WIDGET_FG_R,
		.fg_clr.g = CTK_THEME_DEFAULT_WIDGET_FG_G,
		.fg_clr.b = CTK_THEME_DEFAULT_WIDGET_FG_B,
		.fg_clr.a = CTK_THEME_DEFAULT_WIDGET_FG_A,

		.fg_disabled_clr.r = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.g = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.b = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.a = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_A,

		.render = CTK_ThemeDefaultRenderProgressbar,
	},

	.radiobutton = {
		.w = CTK_THEME_DEFAULT_WIDGET_HEIGHT,
		.h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.body_w = 8,
		.body_h = 8,

		.fill_w = 8,
		.fill_h = 8,

		.bg_clr.r = 0x00,
		.bg_clr.g = 0x00,
		.bg_clr.b = 0x00,
		.bg_clr.a = 0x00,

		.bg_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_A,

		.body_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

		.fg_clr.r = CTK_THEME_DEFAULT_WIDGET_FG_R,
		.fg_clr.g = CTK_THEME_DEFAULT_WIDGET_FG_G,
		.fg_clr.b = CTK_THEME_DEFAULT_WIDGET_FG_B,
		.fg_clr.a = CTK_THEME_DEFAULT_WIDGET_FG_A,

		.fg_disabled_clr.r = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.g = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.b = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.a = CTK_THEME_DEFAULT_WIDGET_FG_DISABLED_A,

		.render = CTK_ThemeDefaultRenderRadiobutton,
	},

	.scale = {
		.w = 100,
		.h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.body_w = 30,
		.body_h = CTK_THEME_DEFAULT_WIDGET_HEIGHT,

		.bg_clr.r = 0xc3,
		.bg_clr.g = 0xc3,
		.bg_clr.b = 0xc3,
		.bg_clr.a = 0xff,

		.bg_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_HOVERED_BG_A,

		.body_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_DEFAULT_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_DEFAULT_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_DEFAULT_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_DEFAULT_WIDGET_BORDER_A,

		.render = CTK_ThemeDefaultRenderScale,
	},

	.draw_menu = CTK_ThemeDefaultDrawMenu,
	.draw_menubar = CTK_ThemeDefaultDrawMenubar,
};

void
CTK_ThemeDefaultDrawMenu(CTK_Instance     *inst,
                         const CTK_MenuId  m)
{
	SDL_Color     command_c;
	float         command_x;
	float         command_y;
	SDL_FRect     frect;
	int           h;
	size_t        i;
	CTK_Menu     *menu;
	SDL_Renderer *r;
	int           w;

	menu = &inst->menu[m];

	if (menu->cmds <= 0) {
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

	command_x = frect.x + 1;
	command_y = menu->rect.y + 1;
	for (i = 0; i < menu->cmds; i++) {
		if (menu->separates[i]) {
			frect.x = command_x + 1;
			frect.y = command_y + (inst->style.menu_separator_h / 2);
			frect.w = menu->rect.w - 2 - 2;
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

		if (menu->focused_cmd == i &&
		    menu->enabled[menu->focused_cmd]) {
			frect.x = command_x;
			frect.y = command_y;
			frect.w = menu->rect.w - 2;
			frect.h = menu->h[i];
			SDL_SetRenderDrawColor(r,
			                       inst->style.menu_command_bg_focused_clr.r,
			                       inst->style.menu_command_bg_focused_clr.g,
			                       inst->style.menu_command_bg_focused_clr.b,
			                       inst->style.menu_command_bg_focused_clr.a);
			SDL_RenderFillRect(r, &frect);

			if (inst->style.menu_command_border_focused) {
				SDL_SetRenderDrawColor(r,
					               inst->style.menu_border_clr.r,
					               inst->style.menu_border_clr.g,
					               inst->style.menu_border_clr.b,
					               inst->style.menu_border_clr.a);
				SDL_RenderRect(r, &frect);
			}
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
		frect.w = menu->rect.w -
		          frect.x -
		          inst->style.menu_accelerator_padding_right;
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
CTK_ThemeDefaultDrawMenubar(CTK_Instance *inst)
{
	float         cascade_x;
	SDL_FRect     frect;
	size_t        i;
	CTK_Menubar  *mb;
	SDL_Renderer *r;
	int           w;

	mb = inst->menubar;
	r = SDL_GetRenderer(inst->win);
	SDL_GetRenderOutputSize(r, &w, NULL);

	frect.x = 0;
	frect.y = 0;
	frect.w = w;
	frect.h = mb->h;
	SDL_SetRenderDrawColor(r,
	                       inst->style.menubar_bg_clr.r,
	                       inst->style.menubar_bg_clr.g,
	                       inst->style.menubar_bg_clr.b,
	                       inst->style.menubar_bg_clr.a);
	SDL_RenderFillRect(r, &frect);

	cascade_x = 1;
	for (i = 0; i < mb->cascades; i++) {
		if (i == mb->hovered_casc ||
		    i == mb->focused_casc) {
			frect.x = cascade_x;
			frect.y = 1;
			frect.w = inst->style.menubar_cascade_padding_left +
			          mb->cascade_w[i] +
			          inst->style.menubar_cascade_padding_right +
			          2;
			frect.h = mb->h - 2;
			SDL_SetRenderDrawColor(r,
					       inst->style.menubar_cascade_bg_hovered_clr.r,
					       inst->style.menubar_cascade_bg_hovered_clr.g,
					       inst->style.menubar_cascade_bg_hovered_clr.b,
					       inst->style.menubar_cascade_bg_hovered_clr.a);
			SDL_RenderFillRect(r, &frect);
		}

		if (i == mb->focused_casc &&
		    inst->style.menubar_cascade_border_focused) {
			frect.x = cascade_x;
			frect.y = 1;
			frect.w = inst->style.menubar_cascade_padding_left +
			          mb->cascade_w[i] +
			          inst->style.menubar_cascade_padding_right +
			          2;
			frect.h = mb->h - 2;
			SDL_SetRenderDrawColor(r,
				               inst->style.menubar_border_clr.r,
				               inst->style.menubar_border_clr.g,
				               inst->style.menubar_border_clr.b,
				               inst->style.menubar_border_clr.a);
			SDL_RenderRect(r, &frect);
		}

		TTF_SetTextColor(mb->cascade[i],
	                         inst->style.menubar_text_clr.r,
	                         inst->style.menubar_text_clr.g,
	                         inst->style.menubar_text_clr.b,
	                         inst->style.menubar_text_clr.a);
		frect.x = cascade_x + inst->style.menubar_cascade_padding_left;
		frect.y = inst->style.menubar_cascade_padding_top;
		frect.w = mb->cascade_w[i];
		frect.h = mb->cascade_h[i];

		CTK_RenderText(r,
		               mb->cascade[i],
		               frect,
		               CTK_TEXT_ALIGNMENT_LEFT,
		               mb->underline[i],
		               inst->style.menubar_text_clr);

		cascade_x += mb->cascade_w[i] +
		             inst->style.menubar_cascade_padding_right +
		             inst->style.menubar_cascade_padding_left +
		             2;
	}

	frect.x = 0;
	frect.y = 0;
	frect.w = w;
	frect.h = mb->h;
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
CTK_ThemeDefaultRenderButton(CTK_Instance       *inst,
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

void
CTK_ThemeDefaultRenderCheckbox(CTK_Instance       *inst,
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

void
CTK_ThemeDefaultRenderEntry(CTK_Instance       *inst,
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

void
CTK_ThemeDefaultRenderProgressbar(CTK_Instance       *inst,
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

void
CTK_ThemeDefaultRenderRadiobutton(CTK_Instance       *inst,
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

void
CTK_ThemeDefaultRenderScale(CTK_Instance       *inst,
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

#endif /* CTK_IMPLEMENTATION */

#ifndef CTK_DEFAULT_THEME
#define CTK_DEFAULT_THEME CTK_Theme_Default
#endif

#endif /* _CTK_THEME_DEFAULT_H */
