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

foreach(DES ${DESIGNPATTERNS})
    message(STATUS "---Dir: ${DES}")

    file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/${DES}/*.cpp")
    message(STATUS "---cpp: ${SRC}")

    foreach(CPP ${SRC})
        message(STATUS "---Create Exe: ${CPP}")

        MESSAGE(${CPP})
        STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${CPP})
        MESSAGE(${FILE_NAME})

        add_executable(${DES}_${FILE_NAME} ${CPP})

    endforeach(CPP)    

endforeach(DES)





# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)



message(STATUS "-----END------")


# set(创建型模式
#     # 1.CreationalDesignPatterns
#     1.1.SingletonPattern
#     1.2.SimpleFactoryPattern
#     1.3.FactoryMethodPattern
#     1.4.AbstractFactory
#     1.5.BuilderPattern
#     1.6.PrototypePattern
# )


# set(结构型模式
#     # 2.StructuralDesignPatterns
#     2.1.ProxyPattern
# )

# set(行为型模式
#     # 3.BehavioralDesignPatterns
#     3.1.MementoPattern
# )

