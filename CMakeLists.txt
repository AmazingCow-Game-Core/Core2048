cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fmax-errors=5 ")

##----------------------------------------------------------------------------##
## Project Settings.                                                          ##
##----------------------------------------------------------------------------##
set(PROJECT_NAME Core2048)
project(${PROJECT_NAME})


##----------------------------------------------------------------------------##
## Sources                                                                    ##
##----------------------------------------------------------------------------##
set(SOURCES
    Core2048/src/GameCore.cpp
    Core2048/src/PresetValuesGenerator.cpp
)


##----------------------------------------------------------------------------##
## Executable / Libary                                                        ##
##----------------------------------------------------------------------------##
set(CORE2048_STANDALONE ON)
if(CORE2048_STANDALONE)
    message("Building Standalone version")

    add_subdirectory(libs/acow_c_goodies    )
    add_subdirectory(libs/acow_cpp_goodies  )
    add_subdirectory(libs/acow_math_goodies )
    add_subdirectory(libs/acow_posix_goodies)
    add_subdirectory(libs/CoreAssert        )
    add_subdirectory(libs/CoreGame          )
    add_subdirectory(libs/CoreRandom        )
    add_subdirectory(libs/libtermcolor      )

    add_executable(${PROJECT_NAME} ${SOURCES} ./test_game/main.cpp)

    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC acow_posix_goodies)
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC libtermcolor      )


else()
    message("Building Library version")
    add_library(${PROJECT_NAME} ${SOURCES})
endif(CORE2048_STANDALONE)



##----------------------------------------------------------------------------##
## Include directories                                                        ##
##----------------------------------------------------------------------------##
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


##----------------------------------------------------------------------------##
## Dependencies                                                               ##
##----------------------------------------------------------------------------##
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC acow_c_goodies   )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC acow_cpp_goodies )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC acow_math_goodies)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC CoreAssert       )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC CoreGame         )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC CoreRandom       )
