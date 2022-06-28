include_directories(${CMAKE_SOURCE_DIR}/src/idea2)

set(SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/idea2/factory/stateFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/factory/stateGroupFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/state/stateInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/stateGroup/stateGroupInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/storage/stateGroupStorage.cpp
    ${CMAKE_SOURCE_DIR}/src/idea2/storage/stateStorage.cpp
)

macro(test name)
    add_executable(${name} ./${name}.cpp ${SOURCE_FILES})
    add_test(NAME ${name} COMMAND ${name})
endmacro()

test(main)
test(comparison_operator)
test(binding)
test(onChange)