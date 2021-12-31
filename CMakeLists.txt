cmake_minimum_required(VERSION 3.5)

project(pyxx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror -std=c++17")
set(src_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB src_files "${src_dir}/*.cpp")

add_executable(pyxx ${src_files})
