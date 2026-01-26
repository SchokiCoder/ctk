/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#ifndef _CTK_STYLE_H
#define _CTK_STYLE_H

#include <SDL3/SDL_pixels.h>

typedef struct CTK_Style {
	SDL_Color bg;
	SDL_Color bg_button;
	SDL_Color bg_checkbox;
	SDL_Color bg_entry;
	SDL_Color bg_label;
	SDL_Color bg_progressbar;
	SDL_Color bg_radiobutton;
	SDL_Color bg_scale;
	SDL_Color bg_selected;
	SDL_Color bg_widget;
	SDL_Color border;
	SDL_Color fg;
	SDL_Color fg_disabled;
	SDL_Color fg_selected;
	SDL_Color focus;
	SDL_Color radiobutton;
	SDL_Color scale_slider;
} CTK_Style;

#define CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY 0xda
#define CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A    0xff

#define CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY 0xff
#define CTK_THEME_TCLTK_WIDGET_INPUT_BG_A    0xff

static const CTK_Style CTK_Theme_TclTk = {
	.bg.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.bg_button.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_button.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_button.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_button.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.bg_checkbox.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.bg_entry.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.bg_label.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.bg_progressbar.r = 0xc3,
	.bg_progressbar.g = 0xc3,
	.bg_progressbar.b = 0xc3,
	.bg_progressbar.a = 0xff,

	.bg_radiobutton.r = 0x00,
	.bg_radiobutton.g = 0x00,
	.bg_radiobutton.b = 0x00,
	.bg_radiobutton.a = 0x00,

	.bg_scale.r = 0xc3,
	.bg_scale.g = 0xc3,
	.bg_scale.b = 0xc3,
	.bg_scale.a = 0xff,

	.bg_selected.r = 0x48,
	.bg_selected.g = 0x68,
	.bg_selected.b = 0x87,
	.bg_selected.a = 0xff,

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

	.fg_selected.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.fg_selected.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.fg_selected.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.fg_selected.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.focus.r = 0x48,
	.focus.g = 0x68,
	.focus.b = 0x87,
	.focus.a = 0xff,

	.radiobutton.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.radiobutton.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.radiobutton.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.radiobutton.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.scale_slider.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.scale_slider.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.scale_slider.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.scale_slider.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,
};

#endif /* _CTK_STYLE_H */
