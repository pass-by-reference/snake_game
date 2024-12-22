cmake_minimum_required(VERSION 3.22)
project(snake)

# All module for fetch content
include(FetchContent)

FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.4.zip # v3.4
)

FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip # v1.0.1
)

FetchContent_Declare(
  stb_image
  DOWNLOAD_NO_EXTRACT TRUE
  URL https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(stb_image)

# ========================================
# Build library

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER clang++)

# Add automatically to source code
set(DEPENDENCY_SOURCES
  src/glad/glad.c
  src/image/stb_image.cpp
)

# Set header dir
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${HEADERS_DIR})


set(DEPENDENCY_SOURCES
  src/glad/glad.c
  src/image/stb_image.cpp
)

set(SNAKE_SOURCES
  src/main.cpp
  src/engine/engine.cpp
  src/engine/char_3d.cpp
  src/snake_scene.cpp
  src/main_menu_scene.cpp
  src/game_end_scene.cpp
)

add_executable(snake ${SNAKE_SOURCES} ${DEPENDENCY_SOURCES})
target_link_libraries(snake PRIVATE glfw)
target_link_libraries(snake PRIVATE glm)
