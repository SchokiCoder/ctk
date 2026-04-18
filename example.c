/* SPDX-License-Identifier: MPL-2.0
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#define CTK_IMPLEMENTATION
#include "CTK.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CTK_EXAMPLE_NAME "C/Tk Example"

//#define SILENCE_CALLBACKS

CTK_WidgetId ckb_focusable, ckb_enabled, ckb_visible;

void
btnCounterMouseMotion(CTK_Instance         *inst,
                      SDL_MouseMotionEvent  e,
                      const CTK_WidgetId    widget,
                      void                 *data)
{
	(void) inst;
	(void) e;
	(void) data;

#ifndef SILENCE_CALLBACKS
	printf("%lu might count\n", widget);
#else
	(void) widget;
#endif
}

void
btnCounterMousePress(CTK_Instance               *inst,
                     const SDL_MouseButtonEvent  e,
                     const CTK_WidgetId          widget,
                     void                       *data)
{
	(void) inst;
	(void) e;
	(void) data;

#ifndef SILENCE_CALLBACKS
	printf("%lu is about to count\n", widget);
#else
	(void) widget;
#endif
}

void
btnCounterTrigger(CTK_Instance               *inst,
                  const CTK_WidgetId          widget,
                  void                       *data)
{
	long i;
	CTK_WidgetId lbl_counter = *((CTK_WidgetId*) (data));
	const size_t str_size = 32;
	char str[str_size];

	(void) widget;

	i = strtol(inst->text[lbl_counter]->text, NULL, 10);
	i++;
	snprintf(str, str_size, "%li", i);
	CTK_SetWidgetText(inst, lbl_counter, str);
}

void
ckbEnabledTrigger(CTK_Instance               *inst,
                  const CTK_WidgetId          widget,
                  void                       *data)
{
	size_t i;

	(void) data;

	for (i = 6; i < inst->widgets; i++) {
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
	size_t i;

	(void) data;

	for (i = 6; i < inst->widgets; i++) {
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
	size_t i;

	(void) data;

	for (i = 6; i < inst->widgets; i++) {
		CTK_SetWidgetVisible(inst, i, inst->toggle[widget]);
	}

	if (!inst->toggle[widget]) {
		CTK_SetWidgetToggle(inst, ckb_enabled, false);
		CTK_SetWidgetToggle(inst, ckb_focusable, false);
	}
}

void
genericPrintCallback(CTK_Instance *inst,
                     void         *data)
{
	(void) inst;
	(void) data;

#ifndef SILENCE_CALLBACKS
	printf("%s\n", (char*) data);
#endif
}

void
genericPrintCallbackWidget(CTK_Instance       *inst,
                           const CTK_WidgetId  w,
                           void               *data)
{
	(void) inst;
	(void) w;
	(void) data;

#ifndef SILENCE_CALLBACKS
	printf("%s\n", (char*) data);
#endif
}

void
menuFileNew(CTK_Instance *inst,
            void *data)
{
	(void) inst;
	(void) data;

	printf("Menu \"File\" Command \"New\"\n");
}

void
menuFileOpen(CTK_Instance *inst,
             void *data)
{
	(void) inst;
	(void) data;

	printf("Menu \"File\" Command \"Open\"\n");
}

void
menuFileSave(CTK_Instance *inst,
             void *data)
{
	(void) inst;
	(void) data;

	printf("Menu \"File\" Command \"Save\"\n");
}

void
menuFileSaveAs(CTK_Instance *inst,
               void *data)
{
	(void) inst;
	(void) data;

	printf("Menu \"File\" Command \"SaveAs\"\n");
}

void
menuFileQuit(CTK_Instance *inst,
             void *data)
{
	bool *active = data;

	(void) inst;

	*active = false;
}

void
menuHelpAbout(CTK_Instance *inst,
              void *data)
{
	(void) inst;
	(void) data;

	printf("The source code of \"%s\" v%i.%i.%i is available, "
	       "licensed under the %s at:\n"
	       "%s\n"
	       "\n"
	       "If you did not receive a copy of the license, see below:\n"
	       "%s\n\n",
	       CTK_EXAMPLE_NAME,
	       CTK_MAJOR_VERSION, CTK_MINOR_VERSION, CTK_PATCH_VERSION,
	       "MPL-2.0",
	       "https://github.com/schokicoder/ctk",
	       "https://mozilla.org/MPL/2.0");
}

void
menuHelpDisabled(CTK_Instance *inst,
                 void *data)
{
	(void) inst;
	(void) data;

	printf("This MUST NOT run!\n");
}

void
mnemonicMenubar(CTK_Instance *inst,
                void *data)
{
	size_t *casc = data;

	CTK_FocusMenubar(inst, *casc);
}

void
mnemonicCEV(CTK_Instance *inst,
            void         *data)
{
	CTK_WidgetId *w = data;

	CTK_ToggleCheckbox(inst, *w);
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

#ifndef SILENCE_CALLBACKS
	printf("Uppies or downies!\n");
	/* Too lazy to find out */
#endif
}

int
main(int    argc,
     char **argv)
{
	const int BUFLEN = 64;
	const int MARGIN = 5;

	CTK_Instance *inst;
	char title[BUFLEN];
	char version[BUFLEN];

	size_t cascFile;
	size_t cascHelp;
	CTK_Menu *menuFile;
	CTK_Menu *menuHelp;
	size_t menuFileCmdNew;
	size_t menuFileCmdOpen;
	size_t menuFileCmdSave;
	size_t menuFileCmdSaveAs;
	size_t menuFileCmdQuit;
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

	snprintf(version, BUFLEN, "%i.%i.%i",
	         CTK_MAJOR_VERSION, CTK_MINOR_VERSION, CTK_PATCH_VERSION);
	if (!CTK_Init("CTK Example",
	              version,
	              "io.github.SchokiCoder.CTK") != 0) {
		fprintf(stderr, "Could not init CTK\n");
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}

	snprintf(title, BUFLEN, CTK_EXAMPLE_NAME " v%s", version);
	inst = CTK_CreateInstance(title, 640, 480, 0);
	if (NULL == inst) {
		fprintf(stderr, "Could not create CTK Instance\n");
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}

	inst->draw = genericPrintCallback;
	inst->draw_data = "window draw";
	inst->enter = genericPrintCallback;
	inst->enter_data = "window enter";
	inst->leave = genericPrintCallback;
	inst->leave_data = "window leave";

	inst->menubar = CTK_CreateMenubar();

	menuFile = CTK_CreateMenu();
	menuFileCmdNew = CTK_AddMenuCommand(inst,
	                                    menuFile,
	                                    "New",
	                                    menuFileNew,
	                                    NULL,
	                                    0);
	CTK_SetMenuCommandAccelerator(inst, menuFile, menuFileCmdNew, "Ctrl+N");
	menuFileCmdOpen = CTK_AddMenuCommand(inst,
	                                     menuFile,
	                                     "Open",
	                                     menuFileOpen,
	                                     NULL,
	                                     0);
	CTK_SetMenuCommandAccelerator(inst, menuFile, menuFileCmdOpen, "Ctrl+O");
	CTK_AddMenuSeparator(inst, menuFile);
	menuFileCmdSave = CTK_AddMenuCommand(inst,
	                                     menuFile,
	                                     "Save",
	                                     menuFileSave,
	                                     NULL,
	                                     0);
	CTK_SetMenuCommandAccelerator(inst, menuFile, menuFileCmdSave, "Ctrl+S");
	menuFileCmdSaveAs = CTK_AddMenuCommand(inst,
	                                       menuFile,
	                                       "Save As",
	                                       menuFileSaveAs,
	                                       NULL,
	                                       5);
	CTK_SetMenuCommandAccelerator(inst, menuFile, menuFileCmdSaveAs, "Ctrl+Shift+S");
	CTK_AddMenuSeparator(inst, menuFile);
	menuFileCmdQuit = CTK_AddMenuCommand(inst,
	                                     menuFile,
	                                     "Quit",
	                                     menuFileQuit,
	                                     &inst->active,
	                                     0);
	CTK_SetMenuCommandAccelerator(inst, menuFile, menuFileCmdQuit, "Ctrl+Q");
	cascFile = CTK_AddMenubarCascade(inst, "File", menuFile, 0);

	menuHelp = CTK_CreateMenu();
	CTK_AddMenuCommand(inst, menuHelp, "About", menuHelpAbout, NULL, 0);
	CTK_AddMenuCommand(inst, menuHelp, "Disabled", menuHelpDisabled, NULL, 0);
	menuHelp->enabled[1] = false;
	cascHelp = CTK_AddMenubarCascade(inst, "Help", menuHelp, 0);

	ckb_focusable = CTK_AddCheckbox(inst);
	inst->rect[ckb_focusable].x = MARGIN;
	inst->rect[ckb_focusable].y = MARGIN;
	inst->trigger[ckb_focusable] = ckbFocusableTrigger;
	CTK_ToggleCheckbox(inst, ckb_focusable);

	lbl_focusable = CTK_AddLabel(inst);
	CTK_SetWidgetText(inst, lbl_focusable, "Focusable");
	CTK_SetWidgetUnderline(inst, lbl_focusable, 2);
	inst->rect[lbl_focusable].x = inst->rect[ckb_focusable].x +
	                              inst->rect[ckb_focusable].w + MARGIN;
	inst->rect[lbl_focusable].y = inst->rect[ckb_focusable].y;

	ckb_enabled = CTK_AddCheckbox(inst);
	inst->rect[ckb_enabled].x = inst->rect[ckb_focusable].x;
	inst->rect[ckb_enabled].y = inst->rect[ckb_focusable].y +
	                            inst->rect[ckb_focusable].h + MARGIN;
	inst->trigger[ckb_enabled] = ckbEnabledTrigger;
	CTK_ToggleCheckbox(inst, ckb_enabled);

	lbl_enabled = CTK_AddLabel(inst);
	CTK_SetWidgetText(inst, lbl_enabled, "Enabled");
	CTK_SetWidgetUnderline(inst, lbl_enabled, 0);
	inst->rect[lbl_enabled].x = inst->rect[ckb_enabled].x +
	                            inst->rect[ckb_enabled].w + MARGIN;
	inst->rect[lbl_enabled].y = inst->rect[ckb_enabled].y;

	ckb_visible = CTK_AddCheckbox(inst);
	inst->rect[ckb_visible].x = inst->rect[ckb_enabled].x;
	inst->rect[ckb_visible].y = inst->rect[ckb_enabled].y +
	                            inst->rect[ckb_enabled].h + MARGIN;
	inst->trigger[ckb_visible] = ckbVisibleTrigger;
	CTK_ToggleCheckbox(inst, ckb_visible);

	lbl_visible = CTK_AddLabel(inst);
	CTK_SetWidgetText(inst, lbl_visible, "Visible");
	CTK_SetWidgetUnderline(inst, lbl_visible, 0);
	inst->rect[lbl_visible].x = inst->rect[ckb_visible].x +
	                            inst->rect[ckb_visible].w + MARGIN;
	inst->rect[lbl_visible].y = inst->rect[ckb_visible].y;


	btn_counter = CTK_AddButton(inst);
	CTK_SetWidgetText(inst, btn_counter, "Count");
	inst->rect[btn_counter].x = MARGIN;
	inst->rect[btn_counter].y = inst->rect[lbl_visible].y +
	                            inst->rect[lbl_visible].h + (MARGIN * 4);
	inst->mouse_motion[btn_counter] = btnCounterMouseMotion;
	inst->mouse_press[btn_counter] = btnCounterMousePress;
	inst->edit[btn_counter] = genericPrintCallbackWidget;
	inst->edit_data[btn_counter] = "count edit";
	inst->trigger[btn_counter] = btnCounterTrigger;
	inst->trigger_data[btn_counter] = &lbl_counter;

	lbl_counter = CTK_AddLabel(inst);
	CTK_SetWidgetText(inst, lbl_counter, "0");
	inst->rect[lbl_counter].x = inst->rect[btn_counter].x +
	                            inst->rect[btn_counter].w + MARGIN;
	inst->rect[lbl_counter].y = inst->rect[btn_counter].y;
	inst->trigger[lbl_counter] = genericPrintCallbackWidget;
	inst->trigger_data[lbl_counter] = "lbl_counter trigger";

	txt = CTK_AddEntry(inst);
	CTK_SetWidgetText(inst, txt, "12345");
	inst->rect[txt].x = MARGIN;
	inst->rect[txt].y = inst->rect[lbl_counter].y +
	                    inst->rect[lbl_counter].h + MARGIN;
	inst->edit[txt] = genericPrintCallbackWidget;
	inst->edit_data[txt] = "txt edit";
	inst->trigger[txt] = genericPrintCallbackWidget;
	inst->trigger_data[txt] = "txt trigger";

	ckb = CTK_AddCheckbox(inst);
	inst->rect[ckb].x = MARGIN;
	inst->rect[ckb].y = inst->rect[txt].y +
	                    inst->rect[txt].h + MARGIN;
	inst->edit[ckb] = genericPrintCallbackWidget;
	inst->edit_data[ckb] = "ckb edit";
	inst->trigger[ckb] = genericPrintCallbackWidget;
	inst->trigger_data[ckb] = "ckb trigger";

	rbn_cheese = CTK_AddRadiobutton(inst);
	inst->rect[rbn_cheese].x = MARGIN;
	inst->rect[rbn_cheese].y = inst->rect[ckb].y +
	                           inst->rect[ckb].h + MARGIN;
	inst->edit[rbn_cheese] = genericPrintCallbackWidget;
	inst->edit_data[rbn_cheese] = "rbn_cheese edit";
	inst->trigger[rbn_cheese] = genericPrintCallbackWidget;
	inst->trigger_data[rbn_cheese] = "rbn_cheese trigger";

	lbl_cheese = CTK_AddLabel(inst);
	CTK_SetWidgetText(inst, lbl_cheese, "Pizza with extra cheese");
	inst->rect[lbl_cheese].x = inst->rect[rbn_cheese].x +
	                           inst->rect[rbn_cheese].w + MARGIN;
	inst->rect[lbl_cheese].y = inst->rect[rbn_cheese].y;
	inst->trigger[lbl_cheese] = genericPrintCallbackWidget;
	inst->trigger_data[lbl_cheese] = "lbl_cheese trigger";

	rbn_pepperoni = CTK_AddRadiobutton(inst);
	inst->rect[rbn_pepperoni].x = MARGIN;
	inst->rect[rbn_pepperoni].y = inst->rect[rbn_cheese].y +
	                              inst->rect[rbn_cheese].h + MARGIN;
	inst->edit[rbn_pepperoni] = genericPrintCallbackWidget;
	inst->edit_data[rbn_pepperoni] = "rbn_pepperoni edit";
	inst->trigger[rbn_pepperoni] = genericPrintCallbackWidget;
	inst->trigger_data[rbn_pepperoni] = "rbn_pepperoni trigger";

	lbl_pepperoni = CTK_AddLabel(inst);
	CTK_SetWidgetText(inst, lbl_pepperoni, "Pizza with pepperoni");
	inst->rect[lbl_pepperoni].x = inst->rect[rbn_pepperoni].x +
	                              inst->rect[rbn_pepperoni].w + MARGIN;
	inst->rect[lbl_pepperoni].y = inst->rect[rbn_pepperoni].y;
	inst->trigger[lbl_pepperoni] = genericPrintCallbackWidget;
	inst->trigger_data[lbl_pepperoni] = "lbl_pepperoni trigger";

	scl = CTK_AddScale(inst);
	inst->value_max[scl] = 9;
	CTK_SetWidgetValue(inst, scl, (rand() % inst->value_max[scl]));
	inst->rect[scl].x = MARGIN;
	inst->rect[scl].y = inst->rect[lbl_pepperoni].y +
	                    inst->rect[lbl_pepperoni].h + MARGIN;
	inst->mouse_wheel[scl] = sclMouseWheel;
	inst->edit[scl] = sclEdit;
	inst->edit_data[scl] = &pgb;
	inst->trigger[scl] = genericPrintCallbackWidget;
	inst->trigger_data[scl] = "scl trigger";

	pgb = CTK_AddProgressbar(inst);
	inst->value_max[pgb] = inst->value_max[scl];
	CTK_SetWidgetValue(inst, pgb, inst->value[scl]);
	inst->rect[pgb].x = inst->rect[scl].x + inst->rect[scl].w + MARGIN;
	inst->rect[pgb].y = inst->rect[scl].y;
	inst->edit[pgb] = genericPrintCallbackWidget;
	inst->edit_data[pgb] = "pgb edit";
	inst->trigger[pgb] = genericPrintCallbackWidget;
	inst->trigger_data[pgb] = "pgb trigger";

	CTK_SetFocusedWidget(inst, txt);

	CTK_Bind(inst, "Alt+F", mnemonicMenubar, &cascFile);
	CTK_Bind(inst, "Alt+H", mnemonicMenubar, &cascHelp);
	CTK_Bind(inst, "Alt+C", mnemonicCEV, &ckb_focusable);
	CTK_Bind(inst, "Alt+E", mnemonicCEV, &ckb_enabled);
	CTK_Bind(inst, "Alt+V", mnemonicCEV, &ckb_visible);

	CTK_MainloopInstance(inst);

	CTK_DestroyInstance(inst);
	CTK_Quit();
}
