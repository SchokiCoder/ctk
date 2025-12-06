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
	CTK_Menu_set_text(m, lbl_counter, str);
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

	if (CTK_init("CTK Example",
	              CTK_VERSION,
	              "io.github.SchokiCoder.CTK") != 0) {
		fprintf(stderr, "Could not init CTK\n");
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}

	if (CTK_Menu_new(&m, "test", 640, 480, 0) != 0) {
		fprintf(stderr, "Could not init CTK Menu\n");
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}

	lbl_enabled = CTK_Menu_add_label(&m);
	CTK_Menu_set_text(&m, lbl_enabled, "Hello world");

	lbl_disabled = CTK_Menu_add_label(&m);
	CTK_Menu_set_text(&m, lbl_disabled, "See you later");
	CTK_Menu_set_enabled(&m, lbl_disabled, 0);
	m.rect[lbl_disabled].x = 100;

	btn_counter = CTK_Menu_add_button(&m);
	CTK_Menu_set_text(&m, btn_counter, "Count");
	m.rect[btn_counter].y = 30;
	m.on_click[btn_counter] = btn_counter_on_click;
	m.on_click_data[btn_counter] = &lbl_counter;

	lbl_counter = CTK_Menu_add_label(&m);
	CTK_Menu_set_text(&m, lbl_counter, "0");
	m.rect[lbl_counter].x = 100;
	m.rect[lbl_counter].y = 30;

	m.on_quit = m_on_quit;

	CTK_Menu_mainloop(&m);

	CTK_Menu_destroy(&m);
	CTK_quit();
}
