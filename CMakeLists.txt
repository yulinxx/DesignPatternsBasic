cmake_minimum_required(VERSION 3.0.0)

project(DesignPatterns VERSION 0.1.0)


message(STATUS "-----BEGIN------")


set(DESIGNPATTERNS    
    CreationalDesignPatterns    # 创建型模式
    StructuralDesignPatterns    # 结构型模式
    BehavioralDesignPatterns    # 行为型模式
)


message(STATUS "__CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "__PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})

foreach(SUB_DIR ${DESIGNPATTERNS})
    message(STATUS "---${SUB_DIR}")

    file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/${SUB_DIR}/*.cpp")
    message(STATUS "---all cpp: ${SRC}")
    foreach(CPP ${SRC})
        message(STATUS "---Create Exe: ${CPP}")

        MESSAGE(${CPP})
        STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${CPP})
        MESSAGE(" --- FILE_NAME"  ${FILE_NAME})

        add_executable(${SUB_DIR}_${FILE_NAME} ${CPP})

    endforeach(CPP)    

endforeach(SUB_DIR)


message(STATUS "-----END------")
