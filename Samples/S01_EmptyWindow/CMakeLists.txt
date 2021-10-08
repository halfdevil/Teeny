cmake_minimum_required(VERSION 3.12)

project(S01_EmptyWindow CXX C)

include_directories(Include)
include_directories(../../Framework/Include)

file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c??)

add_executable(S01_EmptyWindow ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(S01_EmptyWindow PRIVATE Framework)

set_property(TARGET S01_EmptyWindow PROPERTY CXX_STANDARD 20)
set_property(TARGET S01_EmptyWindow PROPERTY CXX_STANDARD_REQUIRED ON)

if (MSVC)
  target_compile_definitions(S01_EmptyWindow PRIVATE -D_CONSOLE)
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(S01_EmptyWindow PRIVATE DEBUG_BUILD=1)
endif()