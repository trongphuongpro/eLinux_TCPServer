cmake_minimum_required(VERSION 3.0)

#-----------------------------------------------------------------------------#
find_package(Threads REQUIRED)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_COMPILER arm-linux-g++)
set(CMAKE_C_COMPILER arm-linux-gcc)
#-----------------------------------------------------------------------------#

set(TARGET testbench)

add_executable(${TARGET} test.cpp ../src/tcpserver.cpp 
								../src/connectionhandler.cpp)
target_link_libraries(${TARGET} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${TARGET} PUBLIC ../include)

#-----------------------------------------------------------------------------#
target_compile_options(${TARGET} PUBLIC -std=gnu++11
										-Wall
										-Werror
										-O2
)
#-----------------------------------------------------------------------------#
install(TARGETS ${TARGET} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)