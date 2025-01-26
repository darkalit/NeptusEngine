cmake_minimum_required(VERSION 3.8)
project("NeptusEngine" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

unset(NEPTUS_USE_SDL CACHE)
unset(NEPTUS_BUILD_RENDERSYSTEM_GL CACHE)
unset(NEPTUS_SHARED CACHE)
option(NEPTUS_USE_SDL "Use and build an SDL as window backend" TRUE)
option(NEPTUS_BUILD_RENDERSYSTEM_GL "Build OpenGL 3+ RenderSystem" TRUE)
option(NEPTUS_SHARED "Build engine as shared library" TRUE)

if(NEPTUS_SHARED)
    add_compile_definitions(NEPTUS_SHARED)
endif()

if (NEPTUS_BUILD_RENDERSYSTEM_GL)
    add_compile_definitions(NEPTUS_BUILD_RENDERSYSTEM_GL)
endif()

set(RUNTIME_BUILD_DIR ${CMAKE_BINARY_DIR}/Runtime)
set(EDITOR_BUILD_DIR ${CMAKE_BINARY_DIR}/Editor)

add_subdirectory("Neptus")
add_subdirectory("Runtime")
add_subdirectory("Editor")
