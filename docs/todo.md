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
- [ ] add widget focus system
- [ ] finalize canonical entry
- [ ] add canonical checkbox
- [ ] add canonical radiobutton
- [ ] add canonical progressbar
- [ ] add canonical scale

- [ ] add a content fitting resize (just initially?)

- [ ] add a way to bind keypresses to functions
- [ ] set version to 0.1.0
