cmake_minimum_required(VERSION 3.11)
project(MyBigNumLib)

# Установка стандарта языка C
set(CMAKE_C_STANDARD 11)

add_subdirectory(BigNumLib)
add_executable(bignum tests/maintest.c)

target_compile_options(bignum PRIVATE -Wall -g)
target_link_libraries(bignum BigNumLib -Wall -g)
