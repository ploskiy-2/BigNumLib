add_library(BigNumLib STATIC bignum.c bignum.h)

target_compile_options(BigNumLib PRIVATE -Wall -g)
target_include_directories(BigNumLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
