# C/Tk

...is a simple to use, lightweight, open library for GUI.  
Open obviously means FLOSS,
but also that it doesn't hide data away,
and only exposes a few bits here and there.
This means you can touch all\* the data and mess things up.
With great power comes great responsibility.

It is based on the SDL, and made so that SDL is the background player,
but can also be directly used, when special needs arise.
<https://libsdl.org/>

# Quick facts

- written in C, specifically C99
- architectured as header-only-library
- utilizing the header only aspect, we avoid allocations as much as possible
- SDL alike ergonomics, since it's the main dependency
- with Linux code format but camel case naming for functions
- max. 20000 SLOC for the lib itself
- max. 500 SLOC for build system
- compatibility with Linux, FreeBSD, OpenBSD, and MS Windows
- Apple's macOS will be a best effort, since they don't give me an ISO for a VM
  _almost as if they don't care about developing for their platform_ :)

# Have a look at it

Install dependencies:
```
sudo apt install libsdl3-{dev,ttf-dev}
```

Run my example:
```
git clone https://github.com/schokicoder/ctk.git
cd ctk
make run
```
and have fun.

# Heritage

C/Tk looks like Tcl/Tk, because that's where it is spiritually derived from.
It is not a fork. C/Tk aims to be lighter and better integrated into C,
which uh yeah... we only have C here. That's how well it should be integrated.
I have worked with Tk for quite a while and really really like it,
but in certain cases it feels lacking,
especially when you want to use it from C as much as possible.
So this here hopefully gives you more control and power.
If you don't like this library for some reason but the general idea,
definitely go check out Tcl/Tk.

# Additional disclaimers? `¯\(ツ)/¯`

\* maybe there are some rare cases where you can't :)
