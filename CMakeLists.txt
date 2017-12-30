cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Release)

# Set the project name and version
project(JOYROOT)

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

ROOT_GENERATE_DICTIONARY(G__joyroot
 Plot1.hh Utils1.hh OPTIONS -inlineInputHeader LINKDEF ${CMAKE_SOURCE_DIR}/include/LinkDef.hh )

file(GLOB SOURCES src/*.cc)
file(GLOB INCLUDES include/Plot1.hh include/ROOTinclude.hh include/Utils1.hh include/def.hh)

add_library(JOYROOT SHARED ${SOURCES} G__joyroot.cxx)
target_link_libraries(JOYROOT ${ROOT_LIBRARIES})

# Install the library for edep-sim
install(TARGETS JOYROOT LIBRARY DESTINATION lib)

# Install the header files.
install(FILES ${INCLUDES} DESTINATION include)

install(FILES ${CMAKE_SOURCE_DIR}/setup.sh DESTINATION .)

if(${ROOT_VERSION} VERSION_GREATER 6)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libjoyroot.rootmap
    DESTINATION lib)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libjoyroot_rdict.pcm
    DESTINATION lib)
endif(${ROOT_VERSION} VERSION_GREATER 6)
