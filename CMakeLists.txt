cmake_minimum_required(VERSION 3.10)

project(Mahjong)

# 添加后缀 编译为调试模式 优化模式 输出警告模式
if(CMAKE_HOST_UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall -fexec-charset=UTF-8")
elseif(CMAKE_HOST_WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall -fexec-charset=UTF-8")
endif()


include_directories(${CMAKE_SOURCE_DIR}/include)
## add_library

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/player.cpp 
    src/game_class.cpp 
    src/card_example.cpp
)

