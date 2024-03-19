set(SOURCES bignum.c)
set(HEADERS bignum.h)

add_library(BigNumLib STATIC ${SOURCES} ${HEADERS})

target_compile_options(BigNumLib PRIVATE -Wall -g)
target_include_directories(BigNumLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
