cmake_minimum_required(VERSION 3.4)
project(SimpleSudoku)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(SimpleSudoku_VERSION_MAJOR 0)
set(SimpleSudoku_VERSION_MINOR 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
configure_file(
	"${PROJECT_SOURCE_DIR}/SimpleSudoku.h.in"
	"${PROJECT_SOURCE_DIR}/include/SimpleSudoku.h"
)
include_directories("${PROJECT_SOURCE_DIR}/include")
#stack
add_executable(sudoku src/sudoku.cc)