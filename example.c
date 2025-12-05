/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#define CTK_IMPL
#include "CTK.h"

#include <stdio.h>

void
m_on_quit(struct CTK_Menu *m,
          void* dummy)
{
	(void) dummy;

	m->active = false;
}

int
main(int argc,
     char **argv)
{
	struct CTK_Menu m;
	int lbl_enabled;
	int lbl_disabled;

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
	CTK_Menu_set_text_and_resize(&m, lbl_enabled, "Hello world");
	lbl_disabled = CTK_Menu_add_label(&m);
	CTK_Menu_set_text_and_resize(&m, lbl_disabled, "See you later");
	CTK_Menu_set_enabled(&m, lbl_disabled, 0);
	m.rect[lbl_disabled].y = 20;

	m.on_quit = m_on_quit;

	CTK_Menu_mainloop(&m);

	CTK_Menu_destroy(&m);
	CTK_quit();
}
