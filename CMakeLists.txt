cmake_minimum_required(VERSION 3.20)
project(FeelingLoopy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(SDL3 REQUIRED)
# find_package(SDL3_image REQUIRED)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

add_executable(main
  ./src/main.cpp
  ./src/engine/engine.cpp
  ./src/engine/entity.cpp
  ./src/engine/collision.cpp
  ./src/keyboardInput.cpp
  ./src/engine/physics.cpp
  ./src/input.cpp
  ./src/input_handler.cpp
)

target_link_libraries(main PRIVATE SDL3_image::SDL3_image SDL3::SDL3)
