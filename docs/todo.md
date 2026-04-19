- [ ] do we need to destroy and create texture each time we update the texture?
The size of the texture may have not changed,
which is the only reason to recreate the texture at this level.  
Decoupling that introduces another thing to keep track of.
Not sure if it's worth it.

- [ ] do we need to `TTF_SetTextColor` each time we update the texture?
The color may have not changed at all.

# 1.0.0

- [ ] create documentation with examples
- [ ] set version number to 1.0.0

# 0.12.0

- **thorough** compatibility tests
(freebsd, abuse my relatives to test on their windows and apple machines)

- [ ] add proper click?
Right now a click is just button release event on a widget, which might confuse.
- [ ] add right click

- [ ] set version number to 0.

# 0.11.0

- [ ] is it fine to leak memory when exiting the application ?

- [ ] there are many possible but ignored error cases for calling SDL functions
add verbose error printing, which gets triggered by env var or compile flag
Log function that, depending on env var, returns early?
Log function that, depending on compile flag, is empty or not?

- [ ] set version number to 0.

# 0.10.0

- [ ] add tooltips
- [ ] move default theme to its own header,
and add to README that there will be infinite sloc for themes
I like theming, unlike... we shall not name it :)

- [ ] add more themes, especially a dark one
- [ ] use `SDL_GetSystemTheme`
- [ ] do themes contain default widget sizes?
if so, move the default size values to the tcl-tk theme.
adding a widget should set the rect once and then leave them alone.
(do not restrict or interfere with later size changes.)
if so, a theme change should change them.

- [ ] set version number to 0.

# 0.9.0

- [ ] test UTF-8 and locale stuff
- [ ] a widget turning (un)focusable might change focused widget?

- [ ] update version number

# 0.8.0

- [ ] add a way to grid widgets
- [ ] add a content fitting window resize (just initially? (upon mainloop))

- [ ] set version number to 0.

# 0.7.0

- [ ] add mouse based navigation to entry
see `TTF_GetTextSubStringForPoint`
- [ ] add mouse based selection to entry
see `TTF_GetTextSubStringForLine`
- [ ] add entry primary selection text paste
- [ ] add entry primary selection text paste while selection
yes, this makes sense, you did not misread
this is down here
because it will depend on the mouse position and doesn't use the cursor at all

- [ ] set version number to 0.7.0

# 0.6.0

- [ ] add combobox
Use a CTK_Menu as its drop down?
In that case, the next point is uh gonna fall flat :)

- [ ] actually, we can have fg_selected for entries. why?
we need multiple `TTF_Text`s anyway, because combobox will need it for sure
It will just be slightly less efficient data wise because we need to copy
the real data text into three ttf texts

- [ ] set version number to 0.6.0

# 0.5.0 The Borderline Update

- [x] add "edit" callback use when radiobutton gets deselected by a group member
- [x] fix bg drawing not changing along window size
- [x] fix menubar width not changing along window size
- [x] turn `CTK_WidgetId` into a size_t for index type consistency
- [x] turn cacheIds into size_t for index type consistency

- [x] fix `CTK_SetWidgetFocusable` not unfocusing a widget if needed
This left focus on unfocusable widgets in the example,
if the focusable checkbox was used via keybind.
And no, these are not regressions from the Id conversion commits -.-
It was bugged before.

- [x] add menubar cascade padding
This removes menubar's fixed height setting.

- [x] remove cascade hover border
Because it seemingly doesn't exist in Tcl, also not in GTK or Qt.

- [x] remove floats from text render target coords in `CTK_RenderText`
This caused fontsizes other than 11 to cause blurry awfulness...
I HATE FLOATS. WHY IS EVERY PIECE OF SDL RENDERING ASKING FOR FLOATS?

- [x] increase default fontsize by one
Because it looks more in line with Tcl.
Maybe that's just a font thing.
Whatever. It'll be fine.

- [x] add menu command padding
This removes command's fixed height setting.

- [x] add menu accelerator padding

- [x] add offset of 1 pixel to menu command drawing
- [x] add offset of 1 pixel to menubar cascade drawing

- [x] add border to focused menu command
- [x] add border to focused menubar cascade

- [x] add ESC key unfocusing menu and menubar
- [x] add arrow key navigation to menu
- [x] add arrow key navigation to menubar
Also add different drawing for focused/hovered cascades,
as these states can be independent here, for the sake of Tcl parity...
kind of. Tcl is actually quite wonky with all that.
I decided to allow an unfocused hover state for menubars, but not for menus,
since a visible menus is always focused over everything else.

- [x] fix some space and tab keys ignoring menu focus
Also add minor code improvement for menubar arrow nav.

- [x] fix menubar menu positions, a regression from offset change
- [x] add enter key triggering focused menu command
- [x] fix menu arrow nav and mouse motion ignoring disabled commands
- [ ] add "right click key" recognition?

- [ ] crash when key down while entry context menu open

- [ ] rework widget spacing with margin, border, padding, content sizes
x, y are now at upper left of the border.
w, h doesn't exist, must me calculated from margin, border, padding, content.

Right now the only widgets with something like a margin are checkbox and radiobutton.
It's hardwired and can't be brought to others with change in the theme.
See <https://productiveshop.com/wp-content/uploads/2024/03/Visual-representation-of-margin-and-padding-in-CSS-Box-Model-1024x401.webp>

It could be:
```
	size_t            content_width;
	size_t            content_height;
	size_t            padding_left;
	size_t            padding_top;
	size_t            padding_right;
	size_t            padding_bottom;
	size_t            border_left;
	size_t            border_top;
	size_t            border_right;
	size_t            border_bottom;
	size_t            margin_left;
	size_t            margin_top;
	size_t            margin_right;
	size_t            margin_bottom;
```

What about checkboxes?
Margin is just an invisble space that works as distance to other widgets.
That wouldn't trigger hover effects.

What is a "content" size in a button?
TTF_Text rendering doesn't care about available space,
and fontsize changes its size, soo... ???

- [ ] add border style system in the widget style sruct with style "none"
- [ ] add border style "solid"
- [ ] add border style "inset"
- [ ] add border style "outset"

- [ ] add button click border style change

- [ ] track issue: delete key crash
`TTF_DeleteTextString` is broken on latest stable release,
which is SDL_TTF v3.2.2.
The following pull:
<https://github.com/libsdl-org/SDL_ttf/pull/600>
was merged after that release and there has been no release since.

- [ ] set version number to 0.5.0

-----

# 0.4.0 The Handy Update

- [x] add a instance texture for the widgets
This in preparation for the menubar, to avoid having to shift the y of widgets,
since drawing under the menubar is verily useless, you can imagine.
I suppose this will also make scrollbars easier once we get there.

- [x] add SDL error texts to instance creation
"Returns valid instance or NULL on failure."
"Call SDL_GetError() for more information."
Now for real.

- [x] add basic menubar with basic drawing
- [x] add menubar offset to mouse input coordinates
- [x] add menubar hover feedback
- [x] add menubar click and menu drawing
- [x] add missing check for max menubar cascades upon adding
- [x] add border to menubar cascade hover
- [x] add menubar cascade focus change upon hover

- [x] change menu data structure to make menus more sovereign
Also move menu drawing to its own function.

- [x] add menu hover feedback
- [x] add motion handling block for widgets when a menu is visible
- [x] add menu click
- [x] fix menu click not unfocusing the menubar

- [x] add menu separator
- [x] add menu "enabled" property for commands

- [x] clearly separate menu from menubar
Menubar data, Menu-style, -values, -code, and -API now have a clear separation.
This also fixes `if (inst->visible_menu != &mb->menu[new_focused_casc] &&`,
because it got touched in the process and then actually caused crashes.

- [x] fix menu draw order
This fixes menu command hover overlaying the border.

- [x] enforce name conformity in instance style struct
Struct members are now sorted primarily by type size (smallest first).

- [x] fix unguarded array access
This caused crashes upon clicks on a widget.

- [x] add bind function for defining keyboard shortcuts
We just copy the Tcl/Tk way,
where menu accelerators and mnemonics need to be manually given a function,
because we don't know how API users might want to hook things up.

- [x] unify function description format

- [x] add data and visual of mnemonics to menubars
This also changes many things so that actually binding mnemonics to focus a
cascade is a lot easier.

- [x] add data and visual of mnemonics to menus
- [x] add function of mnemonics to menus
They trigger on menus without the alt key, as long as they are focused/visible.

- [x] add data and visual of mnemonics to widgets
Aka. add underlines again.

- [x] fix and instate `CTK_RenderText` for all text drawing
The fix in question regards the positioning.
This also removes the offset_x parameter,
because x is now properly used from the given rect.

- [x] add menu accelerators

- [x] fix prematurely matching keybinds even if there are more pressed keys

- [x] replace keybind scancodes with keycodes and keymods
This enables right modifier keys, eliminates worries about keyboard layouts.
Here we also added some key aliases.
Thanks to a bit comparison algorith by Brian Kernighan,
premature shortcut triggering didn't come back,
as a regression of this new system.

- [x] add error message to bind, if shortcut is already used
- [x] fix menu not unfocusing by clicking elsewhere
- [x] fix text input not stopping when a menu is focused

- [x] add right click menu for entries
For cut, copy, and paste.
This also introduces a differentiation between mouse buttons.
The menu opens at RMB down, while getting triggered by any button up.
So you can right click down, hold, go to your command and release to use it.

- [x] add entry text cut via ctrl + x

- [x] fix checkboxes and radiobuttons "trigger" and "edit" callback use
`CTK_ToggleCheckbox` was internally not utilized,
`CTK_ToggleRadiobutton` only ran the "edit" callback,
and `CTK_ToggleCheckbox` didn't run any callbacks,
which caused inconsistent behavior.
This fixes using the top control checkboxes in the example via mnemonics.

- [x] fix entry not running edit callback
- [x] fix progressbar not running edit callback
Again we have a convenient function,
`CTK_SetWidgetValue` that just hasn't been written to go the whole mile.
We change that because there is no reason to be afraid of hardwiring these two
together.

- [x] set version number to 0.4.0

# 0.3.0

- [x] ~~add text drawing to checkbox and radiobutton~~
~~This also works as a hitbox of course.
Many expect the text next to a checkbox or radiobutton to register clicks too.
`text_alignment` will tell which side the text is on.~~
I thought instead add a system to link labels,
but it can be done manually soon, with mnemonics.

- [x] simplify the instance style struct
In the most obvious way even.
Just have the instance style be made up of widget styles.
Why didn't I do this before?
Probably because the widget style struct came later,
and so I didn't connect the dots.
This also allows for per widget-type border color now.

- [x] add bool to theme apply function for widget resize

- [x] add visual scrolling to entries

- [x] fix entry text selection color
Widget style had been granted a text selection color and it is used,
but the data was never moved.
This removes the instance text selection color, and moves the data.

- [x] fix entry text input causing a selection
Regression from text scrolling.

- [x] fix scrolling math, breaking on text input
What it tried to do in some cases is to get the x_pos,
of a character that doesn't exist yet.
If the addressed character doesn't exist,
the x_pos is different than what was expected.
Instead we now get the prior character, take its x_pos and add its width.
Also the checks for when text should scroll are a bit more aggressive.

- [x] simplify `CTK_MeasureTTFText`
This also shifts the cursor at the start of the entry to stay inside. Nice.

- [x] update version number

# 0.2.0 The Visual Cohesiveness Update

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

- [x] add disabled fg color variants

- [x] change scale slider look
Now we just draw two rects with borders.
Also move slider width to style properties.

- [x] fix scale value overflow
There was a missing check, and float can go higher than int.
It was nery noticable when `value_max` was set to `0 - 1` (overflows to max).
`value` and `value_max` are also short now,
because I am afraid of float imprecision in the high int ranges.
Also set default `value_max` based on default width.

- [x] change checkbox to be a bit smaller but with the same hitbox
This is for parity with Tcl/Tk.
Checkbox got a body color variant in style struct.
Here we also converted scale body values,
and thus allows for a configurable slider height too.

- [x] change radiobuttons look
Change from improvised triangle to angled square.
Now the body and fill sizes can be set via the style.
Also replace style ratio `float`s with size `size_t`s.

- [x] adjust scale coloring to be inline with other widgets
When hovered on, the body darkened,
when every other widget lights up in some way.
This is a minor difference from Tcl/Tk, but now the bg lights up a bit,
while the body stays as is.

- [x] update version number

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
