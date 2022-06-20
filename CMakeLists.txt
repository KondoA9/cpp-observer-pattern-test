cmake_minimum_required (VERSION 3.1)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
	set(CMAKE_CXX_FLAGS "/W4 /EHsc")
else()
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unknown-pragmas")
endif()

project(observer-pattern-test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ../bin)

add_executable(observer-test "src/main.cpp")
add_executable(mock "src/mock.cpp")
add_executable(state "src/state.cpp")