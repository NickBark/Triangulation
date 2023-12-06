cmake_minimum_required(VERSION 3.10)
project(Test_Task)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(CGAL REQUIRED COMPONENTS Core)

set(CMAKE_BUILD_TYPE "Release")

add_executable(my_app main.cpp triang.cpp)

target_include_directories(my_app PRIVATE ${CGAL_INCLUDE_DIRS})
target_link_libraries(my_app PRIVATE ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

target_include_directories(my_app PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(my_app PRIVATE ${Boost_LIBRARIES} Boost::program_options)
