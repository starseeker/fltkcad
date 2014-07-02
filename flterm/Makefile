CC = $(shell fltk-config --cxx)
MYLIB = .
CFLAGS = -I. -Wall -Os 
CXXFLAGS = -Wall -Os -I. $(shell fltk-config --cxxflags)

LIB = -L/usr/X11R6/lib -lX11
LINKFLTK = $(shell fltk-config --ldflags)

OBJS = term_sh.o Fl_Term.o gterm.o actions.o utils.o states.o vt52_states.o flkeys.o pseudo.o

# flkeys.o

all: fl_term text_box


text_box: text_box.cxx
	fltk-config --compile $<

fl_term: $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS)  $(LINKFLTK) -o $@
	fltk-config --post $@


clean:
	rm -f *.o fl_term text_box

%.o: %.cpp Makefile *.hpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cxx Makefile *.h
	$(CC) $(CXXFLAGS) -c $< -o $@

## end ##
