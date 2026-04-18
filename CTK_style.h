/* SPDX-License-Identifier: MPL-2.0
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#ifndef _CTK_STYLE_H
#define _CTK_STYLE_H

#include <SDL3/SDL_pixels.h>

typedef enum CTK_TextAlignment {
	CTK_TEXT_ALIGNMENT_LEFT,
	CTK_TEXT_ALIGNMENT_CENTER,
	CTK_TEXT_ALIGNMENT_RIGHT,
} CTK_TextAlignment;

typedef struct CTK_WidgetStyle {
	size_t            w;
	size_t            h;
	size_t            body_w;
	size_t            body_h;
	size_t            fill_w;
	size_t            fill_h;
	CTK_TextAlignment text_align;
	SDL_Color         bg_clr;
	SDL_Color         bg_hovered_clr;
	SDL_Color         body_clr;
	SDL_Color         body_disabled_clr;
	SDL_Color         body_hovered_clr;
	SDL_Color         border_clr;
	SDL_Color         fg_clr;
	SDL_Color         fg_disabled_clr;
	SDL_Color         text_clr;
	SDL_Color         text_bg_selected_clr;
	SDL_Color         text_disabled_clr;
} CTK_WidgetStyle;

typedef struct CTK_Style {
	bool            menu_border;
	bool            menu_command_border;
	size_t          menu_command_padding_left;
	size_t          menu_command_padding_top;
	size_t          menu_command_padding_right;
	size_t          menu_command_padding_bottom;
	size_t          menu_accelerator_padding_left;
	size_t          menu_accelerator_padding_right;
	size_t          menu_separator_h;
	bool            menubar_border;
	bool            menubar_cascade_border;
	size_t          menubar_cascade_padding_left;
	size_t          menubar_cascade_padding_top;
	size_t          menubar_cascade_padding_right;
	size_t          menubar_cascade_padding_bottom;
	SDL_Color       bg_clr;
	SDL_Color       focus_clr;
	SDL_Color       menu_bg_clr;
	SDL_Color       menu_bg_hovered_clr;
	SDL_Color       menu_border_clr;
	SDL_Color       menu_text_clr;
	SDL_Color       menu_text_disabled_clr;
	SDL_Color       menubar_bg_clr;
	SDL_Color       menubar_bg_hovered_clr;
	SDL_Color       menubar_border_clr;
	SDL_Color       menubar_text_clr;
	CTK_WidgetStyle button;
	CTK_WidgetStyle checkbox;
	CTK_WidgetStyle entry;
	CTK_WidgetStyle label;
	CTK_WidgetStyle progressbar;
	CTK_WidgetStyle radiobutton;
	CTK_WidgetStyle scale;
} CTK_Style;

#define CTK_THEME_TCLTK_TEXT_GRAY 0x00
#define CTK_THEME_TCLTK_TEXT_A    0xff

#define CTK_THEME_TCLTK_TEXT_DISABLED_GRAY 0xa4
#define CTK_THEME_TCLTK_TEXT_DISABLED_A    0xff

#define CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY 0xda
#define CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A    0xff

#define CTK_THEME_TCLTK_WIDGET_BORDER_GRAY 0x83
#define CTK_THEME_TCLTK_WIDGET_BORDER_A    0xff

#define CTK_THEME_TCLTK_WIDGET_FG_R 0x48
#define CTK_THEME_TCLTK_WIDGET_FG_G 0x68
#define CTK_THEME_TCLTK_WIDGET_FG_B 0x87
#define CTK_THEME_TCLTK_WIDGET_FG_A 0xff

#define CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY 0xa4
#define CTK_THEME_TCLTK_WIDGET_FG_DISABLED_A    0xff

#define CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY 0xff
#define CTK_THEME_TCLTK_WIDGET_INPUT_BG_A    0xff

#define CTK_THEME_TCLTK_WIDGET_HEIGHT 27

#define CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY 0xed
#define CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A    0xff

#define CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY 0xda
#define CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A    0xff

static const CTK_Style CTK_Theme_TclTk = {
	.menu_border = true,

	.menu_command_border = true,

	.menu_command_padding_left = 4,
	.menu_command_padding_top = 6,
	.menu_command_padding_right = 4,
	.menu_command_padding_bottom = 5,

	.menu_accelerator_padding_left = 10,
	.menu_accelerator_padding_right = 4,

	.menu_separator_h = 19,

	.menubar_border = true,

	.menubar_cascade_border = true,

	.menubar_cascade_padding_left = 4,
	.menubar_cascade_padding_top = 10,
	.menubar_cascade_padding_right = 4,
	.menubar_cascade_padding_bottom = 9,

	.bg_clr.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_clr.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_clr.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_clr.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.focus_clr.r = 0x48,
	.focus_clr.g = 0x68,
	.focus_clr.b = 0x87,
	.focus_clr.a = 0xff,

	.menu_bg_clr.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.menu_bg_clr.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.menu_bg_clr.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.menu_bg_clr.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.menu_bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.menu_bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.menu_bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.menu_bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

	.menu_border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
	.menu_border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
	.menu_border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
	.menu_border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

	.menu_text_clr.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.menu_text_clr.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.menu_text_clr.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.menu_text_clr.a = CTK_THEME_TCLTK_TEXT_A,

	.menu_text_disabled_clr.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.menu_text_disabled_clr.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.menu_text_disabled_clr.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.menu_text_disabled_clr.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,

	.menubar_bg_clr.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.menubar_bg_clr.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.menubar_bg_clr.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.menubar_bg_clr.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.menubar_bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.menubar_bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.menubar_bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.menubar_bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

	.menubar_border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
	.menubar_border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
	.menubar_border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
	.menubar_border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

	.menubar_text_clr.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.menubar_text_clr.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.menubar_text_clr.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.menubar_text_clr.a = CTK_THEME_TCLTK_TEXT_A,

	.button = {
		.w = 80,
		.h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.text_align = CTK_TEXT_ALIGNMENT_CENTER,

		.bg_clr.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

		.bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.text_clr.r = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.g = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.b = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.a = CTK_THEME_TCLTK_TEXT_A,

		.text_disabled_clr.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,
	},

	.checkbox = {
		.w = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.body_w = 10,
		.body_h = 10,

		.fill_w = 10,
		.fill_h = 10,

		.bg_clr.r = 0x00,
		.bg_clr.g = 0x00,
		.bg_clr.b = 0x00,
		.bg_clr.a = 0x00,

		.bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.body_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.fg_clr.r = CTK_THEME_TCLTK_WIDGET_FG_R,
		.fg_clr.g = CTK_THEME_TCLTK_WIDGET_FG_G,
		.fg_clr.b = CTK_THEME_TCLTK_WIDGET_FG_B,
		.fg_clr.a = CTK_THEME_TCLTK_WIDGET_FG_A,

		.fg_disabled_clr.r = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.g = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.b = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.a = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_A,
	},

	.entry = {
		.w = 165,
		.h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.text_align = CTK_TEXT_ALIGNMENT_LEFT,

		.bg_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.text_clr.r = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.g = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.b = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.a = CTK_THEME_TCLTK_TEXT_A,

		.text_disabled_clr.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,

		.text_bg_selected_clr.r = 0x7c,
		.text_bg_selected_clr.g = 0xb0,
		.text_bg_selected_clr.b = 0xe2,
		.text_bg_selected_clr.a = 0xff,
	},

	.label = {
		.w = 80,
		.h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.text_align = CTK_TEXT_ALIGNMENT_LEFT,

		.bg_clr.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_clr.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

		.bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

		.border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.text_clr.r = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.g = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.b = CTK_THEME_TCLTK_TEXT_GRAY,
		.text_clr.a = CTK_THEME_TCLTK_TEXT_A,

		.text_disabled_clr.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled_clr.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,
	},

	.progressbar = {
		.w = 100,
		.h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.bg_clr.r = 0xc3,
		.bg_clr.g = 0xc3,
		.bg_clr.b = 0xc3,
		.bg_clr.a = 0xff,

		.bg_hovered_clr.r = 0xc3,
		.bg_hovered_clr.g = 0xc3,
		.bg_hovered_clr.b = 0xc3,
		.bg_hovered_clr.a = 0xff,

		.border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.fg_clr.r = CTK_THEME_TCLTK_WIDGET_FG_R,
		.fg_clr.g = CTK_THEME_TCLTK_WIDGET_FG_G,
		.fg_clr.b = CTK_THEME_TCLTK_WIDGET_FG_B,
		.fg_clr.a = CTK_THEME_TCLTK_WIDGET_FG_A,

		.fg_disabled_clr.r = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.g = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.b = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.a = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_A,
	},

	.radiobutton = {
		.w = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.body_w = 8,
		.body_h = 8,

		.fill_w = 8,
		.fill_h = 8,

		.bg_clr.r = 0x00,
		.bg_clr.g = 0x00,
		.bg_clr.b = 0x00,
		.bg_clr.a = 0x00,

		.bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.body_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.fg_clr.r = CTK_THEME_TCLTK_WIDGET_FG_R,
		.fg_clr.g = CTK_THEME_TCLTK_WIDGET_FG_G,
		.fg_clr.b = CTK_THEME_TCLTK_WIDGET_FG_B,
		.fg_clr.a = CTK_THEME_TCLTK_WIDGET_FG_A,

		.fg_disabled_clr.r = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.g = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.b = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled_clr.a = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_A,
	},

	.scale = {
		.w = 100,
		.h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.body_w = 30,
		.body_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,

		.bg_clr.r = 0xc3,
		.bg_clr.g = 0xc3,
		.bg_clr.b = 0xc3,
		.bg_clr.a = 0xff,

		.bg_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.body_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled_clr.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled_clr.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered_clr.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered_clr.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border_clr.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border_clr.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,
	},
};

#endif /* _CTK_STYLE_H */
