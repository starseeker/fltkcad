include_directories(
	${FLTK_INCLUDE_DIR}
	)

set(FLTK_LIBRARIES ${FLTK_GL_LIBRARY} ${FLTK_IMAGES_LIBRARY}
	${FLTK_BASE_LIBRARY} ${FLTK_MATH_LIBRARY})

add_executable(gui fltk-test.cxx)
target_link_libraries(gui ${FLTK_LIBRARIES})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
