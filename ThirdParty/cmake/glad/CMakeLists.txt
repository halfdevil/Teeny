cmake_minimum_required(VERSION 3.0)

project(glad)

include_directories(../../glad/include)
add_library(glad ../../glad/src/glad.c)

set_property(TARGET glad PROPERTY FOLDER "ThirdParty")