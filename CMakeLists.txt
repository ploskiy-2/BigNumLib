cmake_minimum_required(VERSION 3.0)
project(MyBigNumLib)

# Установка стандарта языка C
set(CMAKE_C_STANDARD 11)

set(SOURCES tests/maintest.c)
set(EXENAME bignum)

add_subdirectory(BigNumLib)
add_executable(${EXENAME} ${SOURCES})

target_compile_options(${EXENAME} PRIVATE -Wall -g)
target_link_libraries(${EXENAME} PUBLIC BigNumLib -Wall -g)
