/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#define CTK_IMPL
#include "CTK.h"

#include <stdio.h>
#include <stdlib.h>

void
btnCounterOnClick(struct CTK_Instance *inst,
                  const int            widget,
                  void                *data)
{
	long i;
	int lbl_counter = *((int*) (data));
	char str[CTK_MAX_TEXTLEN];

	(void) widget;

	i = strtol(inst->text[lbl_counter], NULL, 10);
	i++;
	snprintf(str, CTK_MAX_TEXTLEN, "%li", i);
	CTK_SetWidgetText(inst, lbl_counter, str);
}

void
btnStateOnClick(struct CTK_Instance *inst,
                const int            widget,
                void                *data)
{
	int lbl_state = *((int*) (data));

	(void) widget;

	if (inst->enabled[lbl_state]) {
		CTK_SetWidgetEnabled(inst, lbl_state, false);
		CTK_SetWidgetTextAndResize(inst, lbl_state, "See you later");
	} else {
		CTK_SetWidgetEnabled(inst, lbl_state, true);
		CTK_SetWidgetTextAndResize(inst, lbl_state, "Hello again world");
	}
}

int
main(int    argc,
     char **argv)
{
	struct CTK_Instance inst;
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

	if (!CTK_CreateInstance(&inst, "test", 640, 480, 0) != 0) {
		fprintf(stderr, "Could not init CTK Menu\n");
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}

	btn_state = CTK_AddButton(&inst);
	CTK_SetWidgetText(&inst, btn_state, "Switch");
	CTK_SetWidgetTextAlignment(&inst, btn_state, CTK_TEXT_ALIGNMENT_LEFT);
	inst.on_click[btn_state] = btnStateOnClick;
	inst.on_click_data[btn_state] = &lbl_state;

	lbl_state = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_state, "Hello world");
	inst.rect[lbl_state].x = 100;

	btn_counter = CTK_AddButton(&inst);
	CTK_SetWidgetText(&inst, btn_counter, "Count");
	inst.rect[btn_counter].y = 30;
	inst.on_click[btn_counter] = btnCounterOnClick;
	inst.on_click_data[btn_counter] = &lbl_counter;

	lbl_counter = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_counter, "0");
	inst.rect[lbl_counter].x = 100;
	inst.rect[lbl_counter].y = 30;

	txt = CTK_AddEntry(&inst);
	inst.rect[txt].y = 60;

	CTK_MainloopInstance(&inst);

	CTK_DestroyInstance(&inst);
	CTK_Quit();
}
