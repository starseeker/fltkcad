# Minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

# Set CMake project name
PROJECT(BCAD)

# Identify CMake directory
if(0)
set(BCAD_CMAKE_DIR "${BCAD_SOURCE_DIR}/CMake")
if(BCAD_IS_SUBBUILD)
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${BCAD_CMAKE_DIR}")
else(BCAD_IS_SUBBUILD)
  set(CMAKE_MODULE_PATH "${BCAD_CMAKE_DIR};${CMAKE_MODULE_PATH}")
endif(BCAD_IS_SUBBUILD)
endif(0)

find_package(OpenGL)
find_package(FLTK 1.3)

add_subdirectory(src)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
