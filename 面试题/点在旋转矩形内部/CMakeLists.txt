cmake_minimum_required(VERSION 3.10)
project(is_point_in_rot_rectangle)
add_compile_options(-std=c++14)
set(CMAKE_BUILD_TYPE "Debug")

find_package(Eigen3 REQUIRED)
find_package(PCL 1.8 REQUIRED)
find_package(OpenCV REQUIRED)

set(PCL_INCLUDE_DIR /usr/include/pcl-1.8)  #指定pcl1.8路径

include_directories(${EIGEN3_INCLUDE_DIR} 
                    ${PCL_INCLUDE_DIR} 
                    ${OpenCV_INCLUDE_DIRS}
                    include)
message("PCL_INCLUDE_DIR: " ${PCL_INCLUDE_DIR})

# add_executable(is_point_in_triangle is_point_in_triangle.cc)
add_executable(${PROJECT_NAME} is_point_in_rot_rectangle.cc)
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${OpenCV_LIBS})