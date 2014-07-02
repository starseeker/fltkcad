# Minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

# Set CMake project name
PROJECT(FLTKCAD)

find_package(PNG)
find_package(X11)
find_package(OpenGL)
add_subdirectory(fltk)

set(FLTK_LIBRARIES fltk fltk_images fltk_gl fltk_forms)

include(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(dl dlopen "" HAVE_DL_LIBRARY)
if(HAVE_DL_LIBRARY)
  set(DL_LIBRARY "dl")
endif(HAVE_DL_LIBRARY)

add_subdirectory(src)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
