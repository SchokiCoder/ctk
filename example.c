/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#define SHTK_IMPL
#include "SHTK.h"

#include <stdio.h>

void
m_on_quit(struct SHTK_Menu *m,
          void* dummy)
{
	(void) dummy;

	m->active = false;
}

int
main(int argc,
     char **argv)
{
	struct SHTK_Menu m;

	(void) argc;
	(void) argv;

	if (SHTK_Init("SHTK Example",
	              SHTK_VERSION,
	              "io.github.SchokiCoder.SHTK") != 0) {
		fprintf(stderr, "Could not init SHTK\n");
		return 0;
	}

	if (SHTK_Menu_new(&m, "test", 640, 480, 0) != 0) {
		fprintf(stderr, "Could not init SHTK Menu\n");
		return 0;
	}

	m.on_quit = m_on_quit;

	SHTK_Menu_mainloop(&m);

	SHTK_Menu_destroy(&m);
	SHTK_Quit();
}
