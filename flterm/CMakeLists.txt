include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../fltk
	)

set(flterm_srcs
	Fl_Term.cxx
	actions.cpp
	flkeys.cxx
	gterm.cpp
	pseudo.cpp
	states.cpp
	term_sh.cxx
	#text_box.cxx
	utils.cpp
	vt52_states.cpp
	)

add_executable(fl_term ${flterm_srcs})
target_link_libraries(fl_term fltk)
