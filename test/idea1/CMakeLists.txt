include_directories(${CMAKE_SOURCE_DIR}/src/idea1)

add_executable(idea1 "./main.cpp")
add_test(NAME idea1 COMMAND idea1)