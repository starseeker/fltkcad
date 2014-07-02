Fl_Term:

This code arose as a conjunction of two factors:

- There was some discussion on the fltk mailing list about provision of
  a "terminal" capability in fltk.

- My wife is a musician, and works a lot of weekends at this (December)
  time of year...

So, one Saturday, I decide to take a look at hacking together some sort
of "terminal" that would work with fltk.

This widget (such as it is) is the result... In principle, it should be
possible to attach it to any r/w file descriptor, be it a serial port or
a file or a pty, and it ought to do the Right Thing. Possibly. A simple
pty based "terminal shell" example is provided for testing purposes.

Background:

As it happens, I had the source for Timothy Miller's GTerm terminal
emulator to hand - this is a handy piece of C++ code that makes a pretty
good stab at emulating the guts of a "traditional" DEC VT100 (and to
some extent also can emulate a VT52.) 
GTerm does not, however, provide any "interface" component, just the
comms and i/o. So, a natural place for fltk to step in...

The GTerm code itself seems to be more or less orphaned now - there
doesn't seem to have been anything done on it since about 1999 or so,
and the dialect of C++ it was written in is not acceptable to many
modern compilers. However, the tweaks to get it to compile under gcc-4
are straightforward.

The GTerm code is distributed with a "worked example" of building it
into an X-windows XTerm application, with support for attaching to linux
pseudo-terminals. That code, too, has been a victim of creeping change,
so I have modified it to work with the "new style" linux pts (rather
than the older pty) interface, and whilst I was at it, I added support
for OSX (and possibly other BSD) pty's.


What all the files are:

The tarball contains the following files:

Makefile     - the Makefile... uses fltk-config and should be portable

gterm.cpp    - these files are the core of the GTerm emulator
gterm.hpp
actions.cpp
utils.cpp
states.cpp
vt52_states.cpp

Fl_Term.cxx  - the fltk widget the wraps the GTerm core
Fl_Term.cxx

term_sh.cxx  - a simple demo using Fl_Term as a console terminal
flkeys.cxx   - provides a mapping between fltk and VT100 key codes
pseudo.cpp   - provides [pts|pty] support for term_sh.cxx on [linux|OSX]

notes/       - this directory holds an un-molested copy of the GTerm
source


What Works?

This code has been built on an extensive test set of two (2) platforms
(one linux FC5, one OSX 10.4.8) and works on both. It may or may not
work on other platforms - I'd hope that it does work, but YMMV.

Once built into the demo application on each platform, the following
"extensive test suite" was run in the resulting shell:

  ls --color (ls -G on OSX) (shows colouration works, etc.)

  man (various pages)       (shows bold, pagination etc.)

  top                       (inverse, pagination, cursor control etc.)

  vi                        (whatever...)

Not exactly comprehensive, but it is a start!


What Does Not Work?

Lots of things... Here's a few basics for starters:

- The translation between fltk key-codes and VT100 key codes is a mess,
I just threw together something that works, but it is far from optimal
(or even correct!) In particular...

- META and ALT keys are not handled, so (for example) emacs isn't likely
to work. If someone who actually understands the fltk key handling
mechanism could fix that up...

- The font face, size, colours are all hard coded. There ought to be a
way of setting them under user control.

- I'm not convinced the "terminal" identifies itself correctly to the
host under all situations, so linux doesn't seems to know it is a
"VT100" sometimes...

- The Fl_Term widget really wants to be derived from both a fltk parent
(I used Fl_Box) and from GTerm. However, it does not really lend itself
to multiple inheritance. So I just bodged it for now. Really, this wants
cleaned up so the user only has to see the Fl_Term widget, and does not
need to see the encapsulated GTerm object at all...

- The API is a not well planned. It wasn't planned at all, I just
started typing...

- You can't cut/paste text in the terminal window.

- Window resizing is not supported (although there are hooks in for it,
I never actually made it work...)

- The text buffering is somewhat redundant - things are buffered in
several places. It is just wasteful.

- There ought to be some means for "logging" all the text on the display
to a file.

- There should be support for local echo (some terminals need that).
GTerm supports that but my code does not support that functionality.

- "Real" VT100's could do a few things that are hard to do under fltk
(notably flashing text.) This is mapped to "italic" for now?

- DEC Graphics set support? Is that even needed now?

- Character set support is probably a bit suspect anyway - fonts,
mappings, etc... Also UTF-8 support? (Not that a real VT100 would know
UTF-8 but these days it matters!)


Conclusion

It sort of works, most of the time. It needs a lot more testing, and a
lot of things need fixing.

I might work on it some more.
Or I might not.
