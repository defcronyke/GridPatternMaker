project (gridpatternmaker-project C CXX)

cmake_minimum_required (VERSION 2.8.10)
set (CMAKE_VERBOSE_MAKEFILE ON)
#set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_BUILD_TYPE Release)
list (APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")	# This project uses C++11.
file (TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/src" src_dir)	# Path to project source code.
file (TO_NATIVE_PATH "${src_dir}/cmake_modules" CMAKE_MODULE_PATH)	# Path to custom cmake modules.

set (wxWidgets_CONFIGURATION mswud)

# --- Find dependencies ---
find_package (Threads REQUIRED)
find_package (SDL2 2.0 REQUIRED)
find_package (SDL2_image 2.0 REQUIRED)
find_package (wxWidgets REQUIRED net gl core base)
# ------

include(${wxWidgets_USE_FILE})

add_library (gridpatternmaker-frontend STATIC ${src_dir}/Frontend.cpp)
set_property (TARGET gridpatternmaker-frontend PROPERTY INCLUDE_DIRECTORIES ${SDL_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR})
target_link_libraries (gridpatternmaker-frontend ${SDL_LIBRARY} ${SDL2IMAGE_LIBRARY})

add_executable (gridpatternmaker ${src_dir}/wxCtrlsApp.cpp)
set_property (TARGET gridpatternmaker PROPERTY INCLUDE_DIRECTORIES ${wxWidgets_INCLUDE_DIRS} ${SDL_INCLUDE_DIR})
target_link_libraries (gridpatternmaker ${wxWidgets_LIBRARIES} ${SDL_LIBRARY} ${SDL2IMAGE_LIBRARY} gridpatternmaker-frontend)
