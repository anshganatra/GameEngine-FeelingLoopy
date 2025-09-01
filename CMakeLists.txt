cmake_minimum_required(VERSION 3.10)
project(FeelingLoopy)

set(CMAKE_CXX_STANDARD 17)

# find_package(SDL3 REQUIRED)
# find_package(SDL3_image REQUIRED)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

add_executable(main
  ./src/main.cpp
  ./src/engine/engine.cpp
  ./src/engine/entity.cpp
  ./src/keyboardInput.cpp
)

target_link_libraries(main PRIVATE SDL3_image::SDL3_image SDL3::SDL3)
