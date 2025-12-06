/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#define CTK_IMPL
#include "CTK.h"

#include <stdio.h>
#include <stdlib.h>

void
m_on_quit(struct CTK_Menu *m,
          void* dummy)
{
	(void) dummy;

	m->active = false;
}

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

int
main(int argc,
     char **argv)
{
	struct CTK_Menu m;
	int lbl_enabled, lbl_disabled;
	int btn_counter, lbl_counter;

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

	lbl_enabled = CTK_AddLabel(&m);
	CTK_SetWidgetText(&m, lbl_enabled, "Hello world");

	lbl_disabled = CTK_AddLabel(&m);
	CTK_SetWidgetText(&m, lbl_disabled, "See you later");
	CTK_SetWidgetEnabled(&m, lbl_disabled, false);
	m.rect[lbl_disabled].x = 100;

	btn_counter = CTK_AddButton(&m);
	CTK_SetWidgetText(&m, btn_counter, "Count");
	m.rect[btn_counter].y = 30;
	m.on_click[btn_counter] = btn_counter_on_click;
	m.on_click_data[btn_counter] = &lbl_counter;

	lbl_counter = CTK_AddLabel(&m);
	CTK_SetWidgetText(&m, lbl_counter, "0");
	m.rect[lbl_counter].x = 100;
	m.rect[lbl_counter].y = 30;

	m.on_quit = m_on_quit;

	CTK_MainloopMenu(&m);

	CTK_DestroyMenu(&m);
	CTK_Quit();
}
