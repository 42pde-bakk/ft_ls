cmake_minimum_required(VERSION 3.18)
project(ft_ls C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

file(GLOB_RECURSE SOURCE_FILES "srcs/*/*.c" "srcs/*.c")
file(GLOB HEADER_FILES "include/*.h" "include/*/*.h")

add_executable(ft_ls ${SOURCE_FILES} ${HEADER_FILES} srcs/print.c)
include_directories(include libft/include)
