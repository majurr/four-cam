# CMakeList.txt : CMake project for QualidadeCortePrototype, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CiMMov")

# Add source to this project's executable.
find_package( OpenCV REQUIRED )

IF(NOT APPLE AND NOT MSVC)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF()

IF(NOT APPLE AND NOT MSVC)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ltbb")
ENDIF()

add_executable ( OPENCVPROJECT "includes/CameraStreamer.hpp" "./CameraStreamer.cpp" "./MultiCamera.cpp")
message(STATUS "foo include dir: ${OpenCV_LIBS}")
target_link_libraries( OPENCVPROJECT ${OpenCV_LIBS} )


# TODO: Add tests and install targets if needed.
