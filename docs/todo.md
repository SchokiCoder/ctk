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
- [ ] add text alignment
- [ ] add tabfocus change upon mouse click
- [ ] add drawn tabfocus ring

- [ ] add canonical checkbox
- [ ] add canonical radiobutton
- [ ] add canonical progressbar
- [ ] add canonical scale

- [ ] add a content fitting resize (just initially?)

- [ ] add a way to bind keypresses to functions
- [ ] set version to 0.1.0
