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
	SDL_Color         bg_widget;
	SDL_Color         bg_widget_hovered;
	SDL_Color         body_radiobutton;
	SDL_Color         body_radiobutton_hovered;
	SDL_Color         body_scale;
	SDL_Color         body_scale_hovered;
	SDL_Color         border;
	SDL_Color         fg_checkbox;
	SDL_Color         fg_progressbar;
	SDL_Color         fg_radiobutton;
	SDL_Color         fg_scale;
	SDL_Color         focus;
	float             size_fillratio_checkbox;
	float             size_fillratio_radiobutton;
	size_t            size_h_button;
	size_t            size_h_checkbox;
	size_t            size_h_entry;
	size_t            size_h_label;
	size_t            size_h_progressbar;
	size_t            size_h_radiobutton;
	size_t            size_h_scale;
	size_t            size_w_button;
	size_t            size_w_checkbox;
	size_t            size_w_entry;
	size_t            size_w_label;
	size_t            size_w_progressbar;
	size_t            size_w_radiobutton;
	size_t            size_w_scale;
	CTK_TextAlignment text_align_button;
	CTK_TextAlignment text_align_entry;
	CTK_TextAlignment text_align_label;
	SDL_Color         text_bg_selected;
	SDL_Color         text_button;
	SDL_Color         text_button_disabled;
	SDL_Color         text_entry;
	SDL_Color         text_entry_disabled;
	SDL_Color         text_label;
	SDL_Color         text_label_disabled;
} CTK_Style;

typedef struct CTK_WidgetStyle {
	SDL_Color         bg;
	SDL_Color         bg_hovered;
	SDL_Color         body;
	SDL_Color         body_hovered;
	SDL_Color         border;
	SDL_Color         fg;
	float             size_fillratio;
	CTK_TextAlignment text_align;
	SDL_Color         text;
	SDL_Color         text_bg_selected;
	SDL_Color         text_disabled;
} CTK_WidgetStyle;

#define CTK_THEME_TCLTK_TEXT_GRAY 0x00
#define CTK_THEME_TCLTK_TEXT_A    0xff

#define CTK_THEME_TCLTK_TEXT_DISABLED_GRAY 0xa4
#define CTK_THEME_TCLTK_TEXT_DISABLED_A    0xff

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

	.bg_widget.r = 0x00,
	.bg_widget.g = 0x00,
	.bg_widget.b = 0x00,
	.bg_widget.a = 0x00,

	.bg_widget_hovered.r = 0x00,
	.bg_widget_hovered.g = 0x00,
	.bg_widget_hovered.b = 0x00,
	.bg_widget_hovered.a = 0x00,

	.body_radiobutton.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.body_radiobutton.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.body_radiobutton.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.body_radiobutton.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.body_radiobutton_hovered.r = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.body_radiobutton_hovered.g = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.body_radiobutton_hovered.b = CTK_THEME_TCLTK_WIDGET_INPUT_BG_GRAY,
	.body_radiobutton_hovered.a = CTK_THEME_TCLTK_WIDGET_INPUT_BG_A,

	.body_scale.r = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.body_scale.g = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.body_scale.b = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_GRAY,
	.body_scale.a = CTK_THEME_TCLTK_WIDGET_NORMAL_BG_A,

	.body_scale_hovered.r = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.body_scale_hovered.g = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.body_scale_hovered.b = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_GRAY,
	.body_scale_hovered.a = CTK_THEME_TCLTK_WIDGET_HOVERED_BG_A,

	.border.r = 0x83,
	.border.g = 0x83,
	.border.b = 0x83,
	.border.a = 0xff,

	.fg_checkbox.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_checkbox.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_checkbox.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_checkbox.a = CTK_THEME_TCLTK_TEXT_A,

	.fg_progressbar.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_progressbar.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_progressbar.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_progressbar.a = CTK_THEME_TCLTK_TEXT_A,

	.fg_radiobutton.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_radiobutton.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_radiobutton.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_radiobutton.a = CTK_THEME_TCLTK_TEXT_A,

	.fg_scale.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_scale.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_scale.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.fg_scale.a = CTK_THEME_TCLTK_TEXT_A,

	.focus.r = 0x48,
	.focus.g = 0x68,
	.focus.b = 0x87,
	.focus.a = 0xff,

	.size_fillratio_checkbox = 0.7,
	.size_fillratio_radiobutton = 0.7,
	.size_h_button = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_h_checkbox = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_h_entry = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_h_label = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_h_progressbar = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_h_radiobutton = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_h_scale = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_w_button = 80,
	.size_w_checkbox = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_w_entry = 165,
	.size_w_label = 80,
	.size_w_progressbar = 100,
	.size_w_radiobutton = CTK_THEME_TCLTK_WIDGET_HEIGHT,
	.size_w_scale = 100,

	.text_align_button = CTK_TEXT_ALIGNMENT_CENTER,
	.text_align_entry = CTK_TEXT_ALIGNMENT_LEFT,
	.text_align_label = CTK_TEXT_ALIGNMENT_LEFT,

	.text_bg_selected.r = 0x7c,
	.text_bg_selected.g = 0xb0,
	.text_bg_selected.b = 0xe2,
	.text_bg_selected.a = 0xff,

	.text_button.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_button.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_button.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_button.a = CTK_THEME_TCLTK_TEXT_A,

	.text_button_disabled.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_button_disabled.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_button_disabled.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_button_disabled.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,

	.text_entry.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_entry.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_entry.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_entry.a = CTK_THEME_TCLTK_TEXT_A,

	.text_entry_disabled.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_entry_disabled.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_entry_disabled.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_entry_disabled.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,

	.text_label.r = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_label.g = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_label.b = CTK_THEME_TCLTK_TEXT_GRAY,
	.text_label.a = CTK_THEME_TCLTK_TEXT_A,

	.text_label_disabled.r = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_label_disabled.g = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_label_disabled.b = CTK_THEME_TCLTK_TEXT_DISABLED_GRAY,
	.text_label_disabled.a = CTK_THEME_TCLTK_TEXT_DISABLED_A,
};

#endif /* _CTK_STYLE_H */
