cmake_minimum_required(VERSION 3.18)
project(ft_ls C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCE_FILES "srcs/*/*.c" "srcs/*.c")
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*/*.h")

add_subdirectory(libft)
include_directories(include libft/include)
add_executable(ft_ls ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(ft_ls libft.a)
