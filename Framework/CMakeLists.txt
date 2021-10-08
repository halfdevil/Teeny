cmake_minimum_required(VERSION 3.12)

project(Framework CXX C)

include_directories(Include)

file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c??)

add_library(Framework ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Framework PUBLIC glad glfw assimp meshoptimizer)

set_property(TARGET Framework PROPERTY CXX_STANDARD 20)
set_property(TARGET Framework PROPERTY CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(Framework PRIVATE DEBUG_BUILD=1)
endif()
