project(creazy)

cmake_minimum_required(VERSION 2.6)

file(GLOB SRCS src/*.cc include/*.h include/*.hpp)

include_directories(include)

add_executable(${PROJECT_NAME} ${SRCS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

find_package(OpenCV REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
