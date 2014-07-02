include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../fltk
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  )

add_executable(gui fltk-test.cxx)
target_link_libraries(gui ${FLTK_LIBRARIES} ${X11_LIBRARIES} ${X11_Xfixes_LIB} ${PNG_LIBRARY} ${DL_LIBRARY})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
