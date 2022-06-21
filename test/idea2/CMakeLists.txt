include_directories(${CMAKE_SOURCE_DIR}/src/idea2)

add_executable(idea2
    ./main.cpp 
    ${CMAKE_SOURCE_DIR}/src/idea2/stateGroupStorage.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/stateStorage.cpp
)

add_test(NAME idea2 COMMAND idea2)