cmake_minimum_required(VERSION 2.6)

project(xrtcserver)

set( TOP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../.. )
set( SRC_PATH ${TOP_PATH}/src)


message(${TOP_PATH})
message(${SRC_PATH})

include_directories( ${SRC_PATH}/ 
					 ${SRC_PATH}/base/
					 )

message(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_EXE_LINKER_FLAGS " -no-pie")

add_definitions("-g -pipe -W -Wall -fPIC -std=c++14 -DOS_LINUX  -DWEBRTC_POSIX -DWEBRTC_LINUX")


file(GLOB all_src
        "${SRC_PATH}/base/*.cpp"
        "${SRC_PATH}/*.cpp"
)


link_directories()


add_executable(cmms ${all_src})


target_link_libraries(cmms -lpthread -ldl)


