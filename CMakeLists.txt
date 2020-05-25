cmake_minimum_required( VERSION 3.15 )
project( jamspot VERSION 0.1 LANGUAGES C CXX )

# Dependencies
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
include( gfxspot )

# Options
add_library( project-options INTERFACE )
target_compile_features( project-options INTERFACE cxx_std_17 )

add_subdirectory( src )
