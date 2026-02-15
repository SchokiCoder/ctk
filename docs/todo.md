- [ ] do we need to destroy and create texture each time we update the texture?
The size of the texture may have not changed,
which is the only reason to recreate the texture at this level.  
Decoupling that introduces another thing to keep track of.
Not sure if it's worth it.

- [ ] do we need to `TTF_SetTextColor` each time we update the texture?
The color may have not changed at all.

# 1.0.0

- [ ] update version number

# 0.11.0

- **thorough** compatibility tests
(freebsd, abuse my relatives to test on their windows and apple machines)

- [ ] add proper click?
Right now a click is just button release event on a widget, which might confuse.
- [ ] add right click

- [ ] update version number

# 0.10.0

- [ ] is it fine to leak memory when exiting the application ?

- [ ] there are many possible but ignored error cases for calling SDL functions
add verbose error printing, which gets triggered by env var or compile flag
Log function that, depending on env var, returns early?
Log function that, depending on compile flag, is empty or not?

- [ ] if sdl3-gfx is available yet, use it for radiobutton circles
if not, postpone this task

- [ ] update version number

# 0.9.0

- [ ] add tooltips
- [ ] add more themes, especially a dark one
- [ ] use `SDL_GetSystemTheme`
- [ ] do themes contain default widget sizes?
if so, move the default size values to the tcl-tk theme.
adding a widget should set the rect once and then leave them alone.
(do not restrict or interfere with later size changes.)
if so, a theme change should change them.

- [ ] update version number

# 0.8.0

- [ ] add proper borders
also move it to the widget style

- [ ] add button click border change

- [ ] a widget turning (un)focusable might change focused widget?

- [ ] update version number

# 0.7.0

- [ ] add a way to grid widgets
- [ ] add a content fitting window resize (just initially? (upon mainloop))

- [ ] update version number

# 0.6.0

- [ ] add mouse based navigation to entry
see `TTF_GetTextSubStringForPoint`
- [ ] add mouse based selection to entry
see `TTF_GetTextSubStringForLine`
- [ ] add entry primary selection text paste
- [ ] add entry primary selection text paste while selection
yes, this makes sense, you did not misread
this is down here
because it will depend on the mouse position and doesn't use the cursor at all

- [ ] update version number

# 0.5.0

- [ ] add combobox
- [ ] actually, we can have fg_selected for entries. why?
we need multiple `TTF_Text`s anyway, because combobox will need it for sure
It will just be slightly less efficient data wise because we need to copy
the real data text into three ttf texts

- [ ] update version number

# 0.4.0

- [ ] add menubar
- [ ] add menubar accelerators

- [ ] add mnemonics

- [ ] update version number

# 0.3.0

- [ ] add visual scrolling to entries

- [ ] add text drawing to checkbox and radiobutton
This also works as a hitbox of course.
Many expect the text next to a checkbox or radiobutton to register clicks too.
~~`text_alignment` will tell which side the text is on.~~ <- this is dumb

- [ ] update version number

# 0.2.0 Visual Cohesiveness Update

- [x] add defines for the malloc functions

- [x] replace instance motion callback with a widget motion callback
- [x] add alternate colors for widgets that are hovered on

- [x] rework widget text to rely on `TTF_Text`
This allows infinite text length, replaces "CTK_string.h",
and will very likely improve UTF-8 and localization support later on.
It probably also improves performance, and makes me a sandvich.

- [x] fix text selection bg being incorrectly measured
This also sets whitespace visibility, because they have no size by default.

- [x] ~~port fg_selected into the new system~~
Attention, this is where text got blurry, especially around hyphens!
I would need to create three `TTF_Text`s to split by color.
I am afraid this will create unforessen bugs with direction, language, etc.
It's way too finicky.

- [x] unify text measurement for cursor pos and selection

- [x] fix alphabetical ordering of `CTK_InstanceDefaultQuit`

- [x] remove `fg_selected` from style and adjust `bg_selected`
Due to `fg_selected` being removed,
`bg_selected` needs to be adjusted for contrast.
*Sigh*, another diversion from Tcl/Tk, but I just inverted the black value.

- [x] ~~make all the data needed for drawing available in properties~~
~~Thus drawing will be fully declarative.
Generate a "content" texture.
This will be drawn on the bg rect.
It may be offset by padding and scroll values.
On that, with the outer pixels, will be the border.~~  
I tried to do it fully declarative, but man is this complex.
I tried to add an array of visuals, which is an enum/struct type,
differentiating between texts, rects, filled rects, circles, etc.  
So this would really just add a step to the create texture process,
where based on the widget, we create or update visuals,
and then create or update the texture.
We would take data, to create data, to create a texture,
whereas now we take data, to create a texture.  
I think this effort stems from the feeling that `CTK_CreateWidgetTexture` got
unwieldy, large, and ugly. This is why we:  

- [x] tidy drawing by having a createTexture function for each widget type
This giant ass switch sure allows to DRY,
but man this will get nastier and nastier by the day.

- [x] clean up `CTK_Instance` a bit
Fix some alphabetical order violations on instance's widget data,
and rename "count" to "widgets" for consistency and clarity.

- [x] add style data for each widget
Fg colors, bg colors, border, offsets, etc. will be used from here for its draw.
The instance's style just brings the data down when a theme is applied.
After that each widget's look is on its own.

- [x] rename some style properties and add text color variants
Buttons, entries, labels, have their own text color in `CTK_Style` now.
`fg` has been mostly for text. It is now explicity `text`,
but the other cases keep `fg`.
`bg_selected` was misleading since it didn't chane the entire bg area.
It is now `text_bg_selected`.
`radiobutton` and `scale_slider` are now `body_`.

- [x] add initial widget sizes to style struct
This also moves the default values to the default theme then. Duh.

- [x] fix coloring of some disabled widgets
For this checkbox, and entry have been granted a body rect,
which in default theme functionally replace each bg.
Entries body (was bg), checkbox body, and radiobutton body were too bright.
Also radiobutton now actually cares about its body color.

- [x] change some Tcl/Tk theme fg coloring for parity
Use dark blue, not black.
Also remove unused fg from scale

- [x] change enabled style of scale
Scales have no visual difference when disabled in OG Tcl/Tk.
Enabled things also tend to be brighter, which it wasn't in the OG.
This is one of these times were I don't mind diverging from the OG,
since that is just visually broken.

- [ ] add disabled fg color?

- [ ] make sure scale sliders are symmetric
by just drawing two rects with borders around the point of value.

- [ ] change checkbox and radiobutton to be a bit smaller but with the same hitbox,
making them similar to the Tcl/Tk variant
checkbox will need a "body" color variant in style struct.

- [ ] update version number

-----

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

- [x] add entry text input case while selection
- [x] add entry backspace key case while selection
- [x] add entry delete key support
- [x] add entry delete key case while selection
- [x] add entry text paste via ctrl + v
- [x] add entry text paste case while selection
- [x] add entry text copy via ctrl + c
- [x] add entry primary selection text setting

- [x] rework from single header to classic lib design
- [x] update copyright
- [x] change fixed size string arrays to heap arrays
- [x] add string growth to STR_Insert, if needed
- [x] add instance growth to CTK_AddWidget, if needed


- [x] change back to header only library
This is necessary for the next step.
- [x] change back to `#define` based config and fixed size arrays
We can't and don't want to compete with big bloated toolkits like GTK and Qt.
Array growth adds questionable value, while adding definite brittleness.
Let apps set their own limits, while having beefy enough defaults.
- [x] change license to MPL-2.0
This is necessary, since it's all headers now,
because the LGPL very likely brings library users into some legal gray areas,
just for using the library as intended.

- [x] fix string insert failing with large sources
- [x] remove invalid text free from `CTK_DestroyInstance`
- [x] fix entry cursor moving incorrectly upon text paste
- [x] fix backspace on entry deleting infinitely out of left bound

- [x] add entry navigation and selection via home key
- [x] add entry navigation and selection via end key
- [x] add entry navigation and selection via pgup key
- [x] add entry navigation and selection via pgdn key
- [x] add primary selection support to home, end, pgup, pgdn keys
- [x] fix entry selection not dropping when using arrows on the start or end

- [x] replace useless return type from `CTK_StrCut` with success bool

- [x] update version number
Also update README with some quick facts and dependencies.
