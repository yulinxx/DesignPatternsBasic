cmake_minimum_required(VERSION 3.0.0)
project(DesignPatterns VERSION 0.1.0)


file(GLOB CPP_FILE ./DesignPatterns/*.cpp)
list(APPEND CPP_NAME ${CPP_FILE})

#message(STATUS "-----------")
#message(STATUS ${CPP_FILE})
#message(STATUS "-----------")
#message(STATUS ${CPP_NAME})









file(GLOB_RECURSE CPP_SRC_LIST *.cpp)
foreach(v ${CPP_SRC_LIST})
    string(REGEX MATCH "tests/.*" relative_path ${v})
    #string(REGEX REPLACE "tests/" "" target_name ${relative_path})
    #string(REGEX REPLACE ".cpp" "" target_name ${target_name})

    #STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${file_name}) 
    #add_executable(my_test_${target_name} ${v})


    #set(file_name "D:\\no.cpp")
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${v})
    set(name ${FILE_NAME})
    message(${FILE_NAME})
    message(${v})
    message("--------")
    #add_executable(test_${FILE_NAME} ${v})
endforeach()

#add_executable(DesignPatterns ./DesignPatterns/备忘录模式MementoPattern.cpp)
add_executable(DesignPatterns2 ./DesignPatterns/策略模式StrategyPattern.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
