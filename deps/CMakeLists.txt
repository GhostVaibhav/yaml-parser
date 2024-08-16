cmake_minimum_required(VERSION 3.28)

add_subdirectory(SDL)
add_subdirectory(spdlog)

add_library(deps INTERFACE)
target_link_libraries(deps INTERFACE SDL2::SDL2-static spdlog::spdlog)
