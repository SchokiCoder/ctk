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

	(void) argc;
	(void) argv;

	if (CTK_Init("CTK Example",
	              CTK_VERSION,
	              "io.github.SchokiCoder.CTK") != 0) {
		fprintf(stderr, "Could not init CTK\n");
		return 0;
	}

	if (CTK_Menu_new(&m, "test", 640, 480, 0) != 0) {
		fprintf(stderr, "Could not init CTK Menu\n");
		return 0;
	}

	m.on_quit = m_on_quit;

	CTK_Menu_mainloop(&m);

	CTK_Menu_destroy(&m);
	CTK_Quit();
}
