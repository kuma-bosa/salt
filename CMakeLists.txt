cmake_minimum_required (VERSION 3.5.11)
project (salt)
add_compile_options(-std=c++14 -rdynamic -O2)
add_compile_options(-march=armv8.2-a+sve -msve-vector-bits=512)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
set(CMAKE_C_COMPILE /usr/local/bin/gcc)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(EXECUTABLE_OUTPUT_PATH ./output/bin)
set(LIBRARY_OUTPUT_PATH ./output/lib)


#add_subdirectory (src)
FILE(GLOB_RECURSE SALT_SRC src/*.cpp)
FILE(GLOB_RECURSE SALT_TEST_SRC test/*.cpp)

add_library (salt SHARED ${SALT_SRC})
add_executable (salt_test ${SALT_TEST_SRC})

target_link_libraries (salt pthread)

target_include_directories(salt_test PUBLIC
	./include/)
target_link_libraries (salt_test salt) 


