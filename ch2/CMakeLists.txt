# Add CmakeList version
cmake_minimum_required(VERSION 2.8)
# Name of project 
project(helloSLAM)
# Add executable
add_executable(helloSLAM helloSLAM.cpp)

##---- Library ---
# Add library 
add_library(hello libHelloSLAM.cpp)

# Add Share library 
add_library(hello_shared SHARED libHelloSLAM.cpp)

# Add excutable using lib
add_executable(useHello useHello.cpp)
target_link_libraries(useHello hello_shared)