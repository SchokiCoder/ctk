- compatibility tests
(freebsd, abuse my relatives to test on their windows and apple machines)

- add proper click?
Right now a click is just button release event on a widget, which might confuse.

# 0.3.0

- [ ] add more themes, especially a dark one
- [ ] use `SDL_GetSystemTheme`
- do themes contain default widget sizes?
if so, move the default size values to the tcl-tk theme.
adding a widget should set the rect once and then leave them alone.
(do not restrict or interfere with later size changes.)
if so, a theme change should change them.

- [ ] add menubar
- [ ] add menubar accelerators

- [ ] add mnemonics

- [ ] update version number

# 0.2.0

- [ ] if sdl3-gfx is available yet, use it for radiobutton circles
if not, postpone this task

- [ ] make all the data needed for drawing available in a "style" property
Thus drawing will be fully declarative.
- [ ] add text drawing to checkbox and radiobutton
This also works as a hitbox of course.
Many expect the text next to a checkbox or radiobutton to register clicks too.
`text_alignment` will tell which side the text is on.

- [ ] add a way to grid widgets
- [ ] add a content fitting window resize (just initially? (upon mainloop))

- [ ] add proper borders
- [ ] make sure scale sliders are symmetric
- [ ] add button click border change

- [ ] a widget turning (un)focusable might change focused widget?

- [ ] add widget on hover callbacks
- [ ] add background colors for widgets that are hovered on
(tcl-tk = rgb(ededed))

- [ ] update version number

# 0.1.0

- [x] add proper project name, license document, and README
- [x] add font rendering
This also fixes a bug where the first draw didn't work,
which only got noticable because I also added a redraw flag for the menu.

- [x] add `Menu_add_label` function
Also add disabled fg color to style.
Also only draw widgets set to visible.

- [x] add `Menu_add_button` function
Also change `Menu_set_text` to resize if needed,
and streamline the texture per widget creation internals.

- [x] change function names to be more in line with SDL

- [x] replace int flags with bools
This is used to create equal error checking with SDL functions,
and gain readability.

- [x] add a default binding for each menu on_quit to set active to false
- [x] add missing enabled and bound checks for on_click event
- [x] add default window flags and many events that trigger a redraw

- [x] add canonical entry mock up and fix attempts to draw empty text
- [x] rename the `CTK_Menu` to `CTK_Instance`
Once menubars and menus are added, this couldn't stay anyway.
May as well get it out of the way early.
Why not call it `CTK_Window`?
"Window" implies that there is always a graphical window present for this...
instance.
This may not apply, either by lib users handcrafting it to not be, or by me
making it possible for an instance to be embedded in another instance's window.
Instance is just more generic, while not creating confusion.
I also took this as a chance to format example function names,
and general spacing.

- [x] add bare widget tabfocus system
- [x] add text input to canonical entry
- [x] add text alignment
- [x] add typedefs for all structs and enums
- [x] add label default height
This is for easier visual alignment even when just placing widgets with coords.

- [x] add proper setter function for tabfocus
- [x] fix entry border disappearing after input
It used the wrong rect, since creating the texture changes the render target.
Given that, I have no idea why the border even worked at all.

- [x] add widget property "focusable"
- [x] fix misuse of tabfocus
- [x] add drawn tabfocus ring
- [x] add tabfocus change upon mouse click
- [x] replace improper function to set a focused widget
Also add a WidgetId type for better readability.
Hopefully this will not confuse me anymore... the author of the code.

- [x] add triggering onClick of a focused widget via space key
- [x] fix missing visibility check for space key and mouse button triggering

- [x] add canonical checkbox
- [x] add canonical radiobutton
- [x] add canonical progressbar

- [x] ~~rework widget property table into structs~~
~~It just gets unwieldy and odd.
A value can be of any type *that makes sense for the widget in question.*
Float, int, string, bool, whatever, but this would force me to have one,
for each type for each widget. Ridiculous.
Now this decreases hackability a tiny bit.
Only a tiny bit, because all the structs are still open.
Now a custom widget would need to pick a sensible base to work on,
instead of just being dumped into the table.
Will this decrease performance? Maybe, but likely not to a relevant degree.~~
This would be a transition into hellfire.
Try reimplementing taborder and tabfocus,
with individual structs for each widget.
This and later optimizations not being possible anymore, makes my decision.
Semantic issues of this table approach will be fixed... once it's an issue :)

- [x] add canonical scale

- [x] use value for radiobuttons and checkboxes instead of text
This replaces the hacky use of text... with a slightly less hacky use.

- [x] clean up `CTK_TickInstance`
It had too many indentations.

- [x] fix vram garbage showing in the bg of radiobuttons

- [x] add instance cache for visible widgets
This eliminates the if in `CTK_DrawInstance` for each widget.

- [x] add instance cache for focusable widgets
This practically merges the focusable property and taborder

- [x] add instance cache for enabled widgets
This eliminates the if in `CTK_TickInstance` for each widget.

- [x] add cache kick-outs
A widget turning invisible can't stay enabled.
A widget turning invisible can't stay focusable.
A widget turning disabled can't stay focusable.
A widget turning disabled can't stay focused.

- [x] add cache kick-ins
A widget turning focusable is expected to turn enabled.
A widget turning focusable is expected to turn visible.
A widget turning enabled is expected to turn visible.

- [x] add proper bool toggle for widgets and switch order of event handling
First process the event *then* start any associated callbacks.

- [x] fix progressbar and button being invisible when value and text are unset
Respectively that is.

- [x] add dedicated bg color for chechboxes

- [x] add `value_max` variable for widgets
Thus also update mouse input handling of scale to only accept implied steps.
This also replaced floats with ints as far as values are concerned.
Fuck floats.
Me and my homies hate floats.

- [x] add arrow key handling for scale
- [x] add proper drag for scale

- [x] replace widget "on click" with "button release" callback
- [x] add widget "button press" callback

- [x] add sdl event of type as param to button callbacks
- [x] add scale value editing upon mouse wheel
- [x] fix `CTK_HandleMouseButtonUp` not using enabled widget cache array
Also do a bit of rearranging for a dedent.
- [x] fix older event handler funcs using SDL_Event* instead of typed event
`CTK_HandleKeyDown`, `CTK_HandleMouseButtonUp` and `CTK_HandleMouseButtonDown`
in particular.

- [x] add widget "trigger" callback
Which replaces the old triggering of "button release" upon space key
- [x] add widget "mouse wheel" callback
- [x] rename "button" callbacks into "mouse"
This is for consistency with "mouse wheel",
and to not confuse with the button widget.
- [x] add widget "edit" callback

- [x] rename instance "on quit" to "quit" callback
- [x] add instance "draw" callback
- [x] add instance "motion" callback
Having this callback per instance rather than per widget should save us a loop.
That's why it's not per widget.
It should also be more fine since binding motion is already special...
You can feel special if you read this :)

- [x] add instance "enter" callback
- [x] add instance "leave" callback

- [x] ~~purge floats from long term storage~~
~~In drawing, it's all definitive pixels anyway.
SDL_FRect is needed by some Render functions.
How can this be circumvented?~~
Only drawing is left, which is heavily based on the SDL backend.
Removing this doesn't do any good.
We don't gain precision, since it needs to fit into the SDL mold anyway.

- [x] change `CTK_CreateInstance` to return instance pointer
This eliminiates `.` vs `->` case and is more inline with the SDL environment.

- [x] add "max_framerate" variable to instance

- [x] fix entry input not terminating the string
- [x] add backspace key support to entry input handling
This also touches the previous string termination fix.

- [x] add cursor drawing to entry
- [x] add cursor navigation to entry
- [x] fix cursor drawing at entry end, when cursor 0 and text not empty
`TTF_GetStringSize` uses the entire string when len parameter (cursor) is 0.
Fixed.

- [x] add keyboard based selection to entry
- [x] fix selection drawing when selection starts at text start

- [ ] add entry text input case while selection
- [ ] add entry backspace key case while selection
- [ ] add entry delete key support
- [ ] add entry delete key case while selection
- [ ] add entry text paste via ctrl + v
- [ ] add entry text copy via ctrl + c

- [ ] fix entry cursor going past right border
So we need to scroll text then

- [ ] add mouse based selection to entry

- [ ] set version to 0.1.0
