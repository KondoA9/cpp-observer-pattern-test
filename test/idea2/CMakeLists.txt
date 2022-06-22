include_directories(${CMAKE_SOURCE_DIR}/src/idea2)

add_executable(idea2
    ./main.cpp 
    ${CMAKE_SOURCE_DIR}/src/idea2/state/stateInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/stateGroup/stateGroupInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/storage/stateGroupStorage.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/storage/stateStorage.cpp
)

add_test(NAME idea2 COMMAND idea2)