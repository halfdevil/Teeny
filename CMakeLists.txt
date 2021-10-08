cmake_minimum_required(VERSION 3.12)

project(OpenGLSamples CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

set(ASSIMP_NO_EXPORT ON CACHE BOOL "")
set(ASSIMP_BUILD_DRACO OFF CACHE BOOL "")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "")
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "")
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "")
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "")

set(MESHOPT_BUILD_DEMO OFF CACHE BOOL "")
set(MESHOPT_BUILD_TOOLS OFF CACHE BOOL "")
set(MESHOPT_BUILD_SHARED_LIBS OFF CACHE BOOL "")

add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/cmake/glad)
add_subdirectory(ThirdParty/assimp)
add_subdirectory(ThirdParty/meshoptimizer)

set_property(TARGET glfw PROPERTY FOLDER "ThirdParty")
set_property(TARGET glad PROPERTY FOLDER "ThirdParty")
set_property(TARGET assimp PROPERTY FOLDER "ThirdParty")
set_property(TARGET meshoptimizer PROPERTY FOLDER "ThirdParty")

include_directories(ThirdParty/glfw/include)
include_directories(ThirdParty/glm/include)
include_directories(ThirdParty/glad/include)
include_directories(ThirdParty/assimp/include)
include_directories(ThirdParty/stb)
include_directories(ThirdParty/glm)

add_subdirectory(Framework)
add_subdirectory(Samples)