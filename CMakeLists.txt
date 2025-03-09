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
    utils/SHACalc.cpp
)

find_package(OpenSSL)

add_executable(LibraryManagementSystem ${SOURCES})
if(OpenSSL_FOUND)
    message(STATUS "OpenSSL found: ${OpenSSL_VERSION}")
    add_definitions(-DOPENSSL_FOUND)
    target_link_libraries(LibraryManagementSystem PRIVATE OpenSSL::SSL OpenSSL::Crypto)
else()
    message(WARNING "OpenSSL not found. Some features may be disabled.")
endif()
