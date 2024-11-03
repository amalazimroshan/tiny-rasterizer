cmake_minimum_required(VERSION 3.20)
project(tiny-rasterizer)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE RASTERIZER_HEADERS "include/*.hpp")
file(GLOB_RECURSE RASTERIZER_SOURCES "source/*.cpp")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg -O0")

add_executable(tiny-rasterizer
    ${RASTERIZER_HEADERS}
    ${RASTERIZER_SOURCES}
)

target_include_directories(tiny-rasterizer PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${SDL2_INCLUDE_DIRS}"
)

target_link_libraries(tiny-rasterizer PUBLIC
    ${SDL2_LIBRARIES}
)