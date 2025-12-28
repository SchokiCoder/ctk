/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025  Andy Frank Schoknecht
 */

#define CTK_IMPL
#include "CTK.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CTK_WidgetId ckb_focusable, ckb_enabled, ckb_visible;

void
btnCounterMousePress(CTK_Instance               *inst,
                     const SDL_MouseButtonEvent  e,
                     const CTK_WidgetId          widget,
                     void                       *data)
{
	(void) inst;
	(void) e;
	(void) data;

	printf("%i is about to count\n", widget);
}

void
btnCounterTrigger(CTK_Instance               *inst,
                  const CTK_WidgetId          widget,
                  void                       *data)
{
	long i;
	CTK_WidgetId lbl_counter = *((CTK_WidgetId*) (data));
	char str[CTK_MAX_TEXTLEN];

	(void) widget;

	i = strtol(inst->text[lbl_counter], NULL, 10);
	i++;
	snprintf(str, CTK_MAX_TEXTLEN, "%li", i);
	CTK_SetWidgetText(inst, lbl_counter, str);
}

void
ckbEnabledTrigger(CTK_Instance               *inst,
                  const CTK_WidgetId          widget,
                  void                       *data)
{
	int i;

	(void) data;

	for (i = 6; i < inst->count; i++) {
		CTK_SetWidgetEnabled(inst, i, inst->toggle[widget]);
	}

	if (inst->toggle[widget]) {
		CTK_SetWidgetToggle(inst, ckb_visible, true);
	} else {
		CTK_SetWidgetToggle(inst, ckb_focusable, false);
	}
}

void
ckbFocusableTrigger(CTK_Instance               *inst,
                    const CTK_WidgetId          widget,
                    void                       *data)
{
	int i;

	(void) data;

	for (i = 6; i < inst->count; i++) {
		CTK_SetWidgetFocusable(inst, i, inst->toggle[widget]);
	}

	if (inst->toggle[widget]) {
		CTK_SetWidgetToggle(inst, ckb_visible, true);
		CTK_SetWidgetToggle(inst, ckb_enabled, true);
	}
}

void
ckbVisibleTrigger(CTK_Instance               *inst,
                  const CTK_WidgetId          widget,
                  void                       *data)
{
	int i;

	(void) data;

	for (i = 6; i < inst->count; i++) {
		CTK_SetWidgetVisible(inst, i, inst->toggle[widget]);
	}

	if (!inst->toggle[widget]) {
		CTK_SetWidgetToggle(inst, ckb_enabled, false);
		CTK_SetWidgetToggle(inst, ckb_focusable, false);
	}
}

void
sclEdit(CTK_Instance               *inst,
        const CTK_WidgetId          widget,
        void                       *data)
{
	CTK_WidgetId pgb = *((CTK_WidgetId*) (data));

	(void) widget;

	CTK_SetWidgetValue(inst, pgb, inst->value[widget]);
}

void
sclMouseWheel(CTK_Instance              *inst,
              const SDL_MouseWheelEvent  e,
              const CTK_WidgetId         widget,
              void                      *data)
{
	(void) inst;
	(void) e;
	(void) widget;
	(void) data;

	printf("Uppies or downies!\n");
	/* Too lazy to find out */
}

int
main(int    argc,
     char **argv)
{
	const int MARGIN = 5;

	CTK_Instance inst;
	CTK_WidgetId lbl_focusable,
	             lbl_enabled,
	             lbl_visible;
	CTK_WidgetId btn_counter, lbl_counter;
	CTK_WidgetId txt;
	CTK_WidgetId ckb;
	CTK_WidgetId rbn_cheese, lbl_cheese;
	CTK_WidgetId rbn_pepperoni, lbl_pepperoni;
	CTK_WidgetId scl, pgb;

	(void) argc;
	(void) argv;

	srand(time(NULL));

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

	ckb_focusable = CTK_AddCheckbox(&inst);
	inst.rect[ckb_focusable].x = MARGIN;
	inst.rect[ckb_focusable].y = MARGIN;
	inst.trigger[ckb_focusable] = ckbFocusableTrigger;
	CTK_ToggleCheckbox(&inst, ckb_focusable);

	lbl_focusable = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_focusable, "Focusable");
	inst.rect[lbl_focusable].x = inst.rect[ckb_focusable].x +
	                             inst.rect[ckb_focusable].w + MARGIN;
	inst.rect[lbl_focusable].y = inst.rect[ckb_focusable].y;

	ckb_enabled = CTK_AddCheckbox(&inst);
	inst.rect[ckb_enabled].x = inst.rect[ckb_focusable].x;
	inst.rect[ckb_enabled].y = inst.rect[ckb_focusable].y +
	                           inst.rect[ckb_focusable].h + MARGIN;
	inst.trigger[ckb_enabled] = ckbEnabledTrigger;
	CTK_ToggleCheckbox(&inst, ckb_enabled);

	lbl_enabled = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_enabled, "Enabled");
	inst.rect[lbl_enabled].x = inst.rect[ckb_enabled].x +
	                           inst.rect[ckb_enabled].w + MARGIN;
	inst.rect[lbl_enabled].y = inst.rect[ckb_enabled].y;

	ckb_visible = CTK_AddCheckbox(&inst);
	inst.rect[ckb_visible].x = inst.rect[ckb_enabled].x;
	inst.rect[ckb_visible].y = inst.rect[ckb_enabled].y +
	                           inst.rect[ckb_enabled].h + MARGIN;
	inst.trigger[ckb_visible] = ckbVisibleTrigger;
	CTK_ToggleCheckbox(&inst, ckb_visible);

	lbl_visible = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_visible, "Visible");
	inst.rect[lbl_visible].x = inst.rect[ckb_visible].x +
	                           inst.rect[ckb_visible].w + MARGIN;
	inst.rect[lbl_visible].y = inst.rect[ckb_visible].y;


	btn_counter = CTK_AddButton(&inst);
	CTK_SetWidgetText(&inst, btn_counter, "Count");
	inst.rect[btn_counter].x = MARGIN;
	inst.rect[btn_counter].y = inst.rect[lbl_visible].y +
	                           inst.rect[lbl_visible].h + (MARGIN * 4);
	inst.mouse_press[btn_counter] = btnCounterMousePress;
	inst.trigger[btn_counter] = btnCounterTrigger;
	inst.trigger_data[btn_counter] = &lbl_counter;

	lbl_counter = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_counter, "0");
	inst.rect[lbl_counter].x = inst.rect[btn_counter].x +
	                           inst.rect[btn_counter].w + MARGIN;
	inst.rect[lbl_counter].y = inst.rect[btn_counter].y;

	txt = CTK_AddEntry(&inst);
	inst.rect[txt].x = MARGIN;
	inst.rect[txt].y = inst.rect[lbl_counter].y +
	                   inst.rect[lbl_counter].h + MARGIN;

	ckb = CTK_AddCheckbox(&inst);
	inst.rect[ckb].x = MARGIN;
	inst.rect[ckb].y = inst.rect[txt].y +
	                   inst.rect[txt].h + MARGIN;

	rbn_cheese = CTK_AddRadiobutton(&inst);
	inst.rect[rbn_cheese].x = MARGIN;
	inst.rect[rbn_cheese].y = inst.rect[ckb].y +
	                          inst.rect[ckb].h + MARGIN;

	lbl_cheese = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_cheese, "Pizza with extra cheese");
	inst.rect[lbl_cheese].x = inst.rect[rbn_cheese].x +
	                          inst.rect[rbn_cheese].w + MARGIN;
	inst.rect[lbl_cheese].y = inst.rect[rbn_cheese].y;

	rbn_pepperoni = CTK_AddRadiobutton(&inst);
	inst.rect[rbn_pepperoni].x = MARGIN;
	inst.rect[rbn_pepperoni].y = inst.rect[rbn_cheese].y +
	                             inst.rect[rbn_cheese].h + MARGIN;

	lbl_pepperoni = CTK_AddLabel(&inst);
	CTK_SetWidgetText(&inst, lbl_pepperoni, "Pizza with pepperoni");
	inst.rect[lbl_pepperoni].x = inst.rect[rbn_pepperoni].x +
	                             inst.rect[rbn_pepperoni].w + MARGIN;
	inst.rect[lbl_pepperoni].y = inst.rect[rbn_pepperoni].y;

	scl = CTK_AddScale(&inst);
	inst.value_max[scl] = 4;
	CTK_SetWidgetValue(&inst, scl, (rand() % inst.value_max[scl]));
	inst.rect[scl].x = MARGIN;
	inst.rect[scl].y = inst.rect[lbl_pepperoni].y +
	                   inst.rect[lbl_pepperoni].h + MARGIN;
	inst.mouse_wheel[scl] = sclMouseWheel;
	inst.edit[scl] = sclEdit;
	inst.edit_data[scl] = &pgb;

	pgb = CTK_AddProgressbar(&inst);
	inst.value_max[pgb] = inst.value_max[scl];
	CTK_SetWidgetValue(&inst, pgb, inst.value[scl]);
	inst.rect[pgb].x = inst.rect[scl].x + inst.rect[scl].w + MARGIN;
	inst.rect[pgb].y = inst.rect[scl].y;

	CTK_SetFocusedWidget(&inst, txt);

	CTK_MainloopInstance(&inst);

	CTK_DestroyInstance(&inst);
	CTK_Quit();
}
