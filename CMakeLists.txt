cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Release)

# Set the project name and version
project(JOYROOT)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("-- JoyRoot -- ${VERSION}")

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})
# necesary for ROOT_GENERATE_DICTIONARY
include_directories(${CMAKE_SOURCE_DIR}/include/joyroot)

#ROOT_GENERATE_DICTIONARY(G__joyroot
# Plot1.hh Utils1.hh OPTIONS -inlineInputHeader LINKDEF ${CMAKE_SOURCE_DIR}/include/LinkDef.hh )
ROOT_GENERATE_DICTIONARY(G__joyroot
 Plot1.hh Utils1.hh OPTIONS -inlineInputHeader LINKDEF include/LinkDef.hh )

file(GLOB SOURCES src/*.cc)
file(GLOB INCLUDES include/joyroot/Plot1.hh include/joyroot/ROOTinclude.hh include/joyroot/Utils1.hh include/joyroot/def.hh)

add_library(JOYROOT SHARED ${SOURCES} G__joyroot.cxx)
target_link_libraries(JOYROOT ${ROOT_LIBRARIES})
target_include_directories(JOYROOT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Install the library for edep-sim
install(TARGETS JOYROOT LIBRARY DESTINATION lib)

# Install the header files.
install(FILES ${INCLUDES} DESTINATION include/joyroot)

install(FILES ${CMAKE_SOURCE_DIR}/setup.sh DESTINATION .)

if(${ROOT_VERSION} VERSION_GREATER 6)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libjoyroot.rootmap
    DESTINATION lib)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libjoyroot_rdict.pcm
    DESTINATION lib)
endif(${ROOT_VERSION} VERSION_GREATER 6)
