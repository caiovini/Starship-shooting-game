cmake_minimum_required(VERSION 3.7)

project(SpacePixel)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

find_package(SDL2 REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})

file (GLOB source_files "${source_dir}/*.cpp")

add_executable(SpacePixel ${source_files})
target_link_libraries(SpacePixel ${SDL2_LIBRARIES} ${SDL2_Image} ${SDL2_ttf})