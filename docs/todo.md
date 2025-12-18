- [ ] add more themes, especially a dark one
- [ ] use `SDL_GetSystemTheme`

- [ ] add a way to grid widgets
- [ ] add mnemonics

- [ ] add proper borders
- [ ] add button click border change

# basic

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

- [ ] add `value_step` variable for widgets
Thus also update input handling of scale.

- [ ] use value for radiobuttons and checkboxes
This eliminates the hacky use of text.

- [ ] much needed clean up (too many indents)

- [ ] add instance cache for visible widgets
This eliminates the if in `CTK_DrawInstance` for each widget.
- [ ] add instance cache for active widgets
This eliminates the if in `CTK_TickInstance` for each widget.

- [ ] add bg for each widget in style
- [ ] add a content fitting resize (just initially?)

- [ ] add proper drag for scale
This might result in a whole rework of mouse input handling bringing proper click as well.
Right now a click is just button release event on a widget, which might confuse.

- [ ] add a way to bind keypresses to functions
- [ ] set version to 0.1.0
