# CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project("CodeCraft-2021")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 

file(GLOB_RECURSE DIR_SRCS "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h*")

# include路径
include_directories(${PROJECT_SOURCE_DIR}/src)

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 生成debug版本
# SET(CMAKE_BUILD_TYPE "release")
SET(CMAKE_BUILD_TYPE "Debug")
if (CMAKE_BUILD_TYPE STREQUAL debug)
    add_definitions(-D_DEBUG)
endif ()
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11")


# 指定生成目标
add_executable(CodeCraft-2022 ${DIR_SRCS})
