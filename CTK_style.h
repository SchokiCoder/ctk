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
	SDL_Color         bg;
	SDL_Color         bg_hovered;
	SDL_Color         body;
	SDL_Color         body_disabled;
	SDL_Color         body_hovered;
	SDL_Color         border;
	SDL_Color         fg;
	SDL_Color         fg_disabled;
	size_t            size_body_h;
	size_t            size_body_w;
	size_t            size_fill_h;
	size_t            size_fill_w;
	size_t            size_h;
	size_t            size_w;
	CTK_TextAlignment text_align;
	SDL_Color         text;
	SDL_Color         text_bg_selected;
	SDL_Color         text_disabled;
} CTK_WidgetStyle;

typedef struct CTK_Style {
	SDL_Color       bg;
	SDL_Color       focus;
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
	.bg.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.focus.r = 0x48,
	.focus.g = 0x68,
	.focus.b = 0x87,
	.focus.a = 0xff,

	.button = {
		.bg.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

		.bg_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.border.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.size_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_w = 80,

		.text_align = CTK_TEXT_ALIGNMENT_CENTER,

		.text.r = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.g = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.b = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.a = CTK_THEME_TCLTK_TEXT_A,
		.text_disabled.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,

		.text_disabled.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,
	},

	.checkbox = {
		.bg.r = 0x00,
		.bg.g = 0x00,
		.bg.b = 0x00,
		.bg.a = 0x00,

		.bg_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.body.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.fg.r = CTK_THEME_TCLTK_WIDGET_FG_R,
		.fg.g = CTK_THEME_TCLTK_WIDGET_FG_G,
		.fg.b = CTK_THEME_TCLTK_WIDGET_FG_B,
		.fg.a = CTK_THEME_TCLTK_WIDGET_FG_A,

		.fg_disabled.r = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.g = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.b = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.a = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_A,

		.size_body_h = 10,
		.size_body_w = 10,

		.size_fill_h = 10,
		.size_fill_w = 10,

		.size_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_w = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	},

	.entry = {
		.bg.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.bg_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.bg_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.size_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_w = 165,

		.text_align = CTK_TEXT_ALIGNMENT_LEFT,

		.text.r = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.g = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.b = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.a = CTK_THEME_TCLTK_TEXT_A,

		.text_disabled.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,

		.text_bg_selected.r = 0x7c,
		.text_bg_selected.g = 0xb0,
		.text_bg_selected.b = 0xe2,
		.text_bg_selected.a = 0xff,
	},

	.label = {
		.bg.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

		.bg_hovered.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
		.bg_hovered.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

		.border.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.size_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_w = 80,

		.text_align = CTK_TEXT_ALIGNMENT_LEFT,

		.text.r = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.g = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.b = CTK_THEME_TCLTK_TEXT_GRAY,
		.text.a = CTK_THEME_TCLTK_TEXT_A,

		.text_disabled.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
		.text_disabled.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,
	},

	.progressbar = {
		.bg.r = 0xc3,
		.bg.g = 0xc3,
		.bg.b = 0xc3,
		.bg.a = 0xff,

		.bg_hovered.r = 0xc3,
		.bg_hovered.g = 0xc3,
		.bg_hovered.b = 0xc3,
		.bg_hovered.a = 0xff,

		.border.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.fg.r = CTK_THEME_TCLTK_WIDGET_FG_R,
		.fg.g = CTK_THEME_TCLTK_WIDGET_FG_G,
		.fg.b = CTK_THEME_TCLTK_WIDGET_FG_B,
		.fg.a = CTK_THEME_TCLTK_WIDGET_FG_A,

		.fg_disabled.r = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.g = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.b = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.a = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_A,

		.size_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_w = 100,
	},

	.radiobutton = {
		.bg.r = 0x00,
		.bg.g = 0x00,
		.bg.b = 0x00,
		.bg.a = 0x00,

		.bg_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.body.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.fg.r = CTK_THEME_TCLTK_WIDGET_FG_R,
		.fg.g = CTK_THEME_TCLTK_WIDGET_FG_G,
		.fg.b = CTK_THEME_TCLTK_WIDGET_FG_B,
		.fg.a = CTK_THEME_TCLTK_WIDGET_FG_A,

		.fg_disabled.r = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.g = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.b = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_GRAY,
		.fg_disabled.a = CTK_THEME_TCLTK_WIDGET_FG_DISABLED_A,

		.size_body_h = 8,
		.size_body_w = 8,

		.size_fill_h = 8,
		.size_fill_w = 8,

		.size_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_w = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	},

	.scale = {
		.bg.r = 0xc3,
		.bg.g = 0xc3,
		.bg.b = 0xc3,
		.bg.a = 0xff,

		.bg_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
		.bg_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

		.body.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.body_disabled.r = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.g = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.b = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_GRAY,
		.body_disabled.a = CTK_THEME_TCLTK_WIDGET_BODY_DISABLED_A,

		.body_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
		.body_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

		.border.r = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.g = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.b = CTK_THEME_TCLTK_WIDGET_BORDER_GRAY,
		.border.a = CTK_THEME_TCLTK_WIDGET_BORDER_A,

		.size_body_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_body_w = 30,

		.size_h = CTK_THEME_TCLTK_WIDGET_HEIGHT,
		.size_w = 100,
	},
};

#endif /* _CTK_STYLE_H */
