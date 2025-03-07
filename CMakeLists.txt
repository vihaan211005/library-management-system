cmake_minimum_required(VERSION 3.10)

project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(include)

set(SOURCES
    src/Account.cpp
    src/Book.cpp
    src/Library.cpp
    src/main.cpp
    src/User.cpp
    utils/DateUtils.cpp
    utils/TerminalPrint.cpp
)

add_executable(LibraryManagementSystem ${SOURCES})
