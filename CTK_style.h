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

typedef struct CTK_Style {
	SDL_Color         bg;
	SDL_Color         bg_button;
	SDL_Color         bg_button_hovered;
	SDL_Color         bg_checkbox;
	SDL_Color         bg_checkbox_hovered;
	SDL_Color         bg_entry;
	SDL_Color         bg_entry_hovered;
	SDL_Color         bg_label;
	SDL_Color         bg_label_hovered;
	SDL_Color         bg_progressbar;
	SDL_Color         bg_progressbar_hovered;
	SDL_Color         bg_radiobutton;
	SDL_Color         bg_radiobutton_hovered;
	SDL_Color         bg_scale;
	SDL_Color         bg_scale_hovered;
	SDL_Color         bg_selected;
	SDL_Color         bg_widget;
	SDL_Color         bg_widget_hovered;
	SDL_Color         border;
	SDL_Color         fg;
	SDL_Color         fg_disabled;
	SDL_Color         focus;
	SDL_Color         radiobutton;
	SDL_Color         scale_slider;
	SDL_Color         scale_slider_hovered;
	CTK_TextAlignment txt_align_button;
	CTK_TextAlignment txt_align_entry;
	CTK_TextAlignment txt_align_label;
} CTK_Style;

typedef struct CTK_WidgetStyle {
	SDL_Color         bg;
	SDL_Color         bg_hovered;
	SDL_Color         bg_selected;
	SDL_Color         border;
	SDL_Color         fg;
	SDL_Color         fg_disabled;
	SDL_Color         radiobutton;
	SDL_Color         scale_slider;
	SDL_Color         scale_slider_hovered;
	CTK_TextAlignment txt_align;
} CTK_WidgetStyle;

#define CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY 0xff
#define CTK_THEME_TCLTK_WIDGET_INPUT_BG_A    0xff

#define CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY 0xed
#define CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A    0xff

#define CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY 0xda
#define CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A    0xff

static const CTK_Style CTK_Theme_TclTk = {
	.bg.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.bg_button.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_button.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_button.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_button.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.bg_button_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.bg_button_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.bg_button_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.bg_button_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

	.bg_checkbox.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.bg_checkbox_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_checkbox_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.bg_entry.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.bg_entry_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.bg_entry_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.bg_label.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.bg_label_hovered.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label_hovered.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label_hovered.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.bg_label_hovered.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.bg_progressbar.r = 0xc3,
	.bg_progressbar.g = 0xc3,
	.bg_progressbar.b = 0xc3,
	.bg_progressbar.a = 0xff,

	.bg_progressbar_hovered.r = 0xc3,
	.bg_progressbar_hovered.g = 0xc3,
	.bg_progressbar_hovered.b = 0xc3,
	.bg_progressbar_hovered.a = 0xff,

	.bg_radiobutton.r = 0x00,
	.bg_radiobutton.g = 0x00,
	.bg_radiobutton.b = 0x00,
	.bg_radiobutton.a = 0x00,

	.bg_radiobutton_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.bg_radiobutton_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.bg_radiobutton_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.bg_radiobutton_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

	.bg_scale.r = 0xc3,
	.bg_scale.g = 0xc3,
	.bg_scale.b = 0xc3,
	.bg_scale.a = 0xff,

	.bg_scale_hovered.r = 0xc3,
	.bg_scale_hovered.g = 0xc3,
	.bg_scale_hovered.b = 0xc3,
	.bg_scale_hovered.a = 0xff,

	.bg_selected.r = 0x7c,
	.bg_selected.g = 0xb0,
	.bg_selected.b = 0xe2,
	.bg_selected.a = 0xff,

	.bg_widget.r = 0x00,
	.bg_widget.g = 0x00,
	.bg_widget.b = 0x00,
	.bg_widget.a = 0x00,

	.bg_widget_hovered.r = 0x00,
	.bg_widget_hovered.g = 0x00,
	.bg_widget_hovered.b = 0x00,
	.bg_widget_hovered.a = 0x00,

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

	.radiobutton.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.radiobutton.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.radiobutton.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.radiobutton.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.scale_slider.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.scale_slider.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.scale_slider.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.scale_slider.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.scale_slider_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.scale_slider_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.scale_slider_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.scale_slider_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

	.txt_align_button = CTK_TEXT_ALIGNMENT_CENTER,
	.txt_align_entry = CTK_TEXT_ALIGNMENT_LEFT,
	.txt_align_label = CTK_TEXT_ALIGNMENT_LEFT,
};

#endif /* _CTK_STYLE_H */
