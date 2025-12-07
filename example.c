/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#define CTK_IMPL
#include "CTK.h"

#include <stdio.h>
#include <stdlib.h>

void
btn_counter_on_click(struct CTK_Menu *m,
                     const int widget,
                     void *data)
{
	long i;
	int lbl_counter = *((int*) (data));
	char str[CTK_MAX_TEXTLEN];

	(void) widget;

	i = strtol(m->text[lbl_counter], NULL, 10);
	i++;
	snprintf(str, CTK_MAX_TEXTLEN, "%li", i);
	CTK_SetWidgetText(m, lbl_counter, str);
}

void
btn_state_on_click(struct CTK_Menu *m,
                   const int widget,
                   void *data)
{
	int lbl_state = *((int*) (data));

	(void) widget;

	if (m->enabled[lbl_state]) {
		CTK_SetWidgetEnabled(m, lbl_state, false);
		CTK_SetWidgetTextAndResize(m, lbl_state, "See you later");
	} else {
		CTK_SetWidgetEnabled(m, lbl_state, true);
		CTK_SetWidgetTextAndResize(m, lbl_state, "Hello again world");
	}
}

int
main(int argc,
     char **argv)
{
	struct CTK_Menu m;
	int btn_state,   lbl_state;
	int btn_counter, lbl_counter;
	int txt;

	(void) argc;
	(void) argv;

	if (!CTK_Init("CTK Example",
	              CTK_VERSION,
	              "io.github.SchokiCoder.CTK") != 0) {
		fprintf(stderr, "Could not init CTK\n");
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}

	if (!CTK_CreateMenu(&m, "test", 640, 480, 0) != 0) {
		fprintf(stderr, "Could not init CTK Menu\n");
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}

	btn_state = CTK_AddButton(&m);
	CTK_SetWidgetText(&m, btn_state, "Switch");
	m.on_click[btn_state] = btn_state_on_click;
	m.on_click_data[btn_state] = &lbl_state;

	lbl_state = CTK_AddLabel(&m);
	CTK_SetWidgetText(&m, lbl_state, "Hello world");
	m.rect[lbl_state].x = 100;

	btn_counter = CTK_AddButton(&m);
	CTK_SetWidgetText(&m, btn_counter, "Count");
	m.rect[btn_counter].y = 30;
	m.on_click[btn_counter] = btn_counter_on_click;
	m.on_click_data[btn_counter] = &lbl_counter;

	lbl_counter = CTK_AddLabel(&m);
	CTK_SetWidgetText(&m, lbl_counter, "0");
	m.rect[lbl_counter].x = 100;
	m.rect[lbl_counter].y = 30;

	txt = CTK_AddEntry(&m);
	m.rect[txt].y = 60;

	CTK_MainloopMenu(&m);

	CTK_DestroyMenu(&m);
	CTK_Quit();
}
