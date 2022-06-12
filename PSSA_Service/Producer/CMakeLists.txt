# LoggerPSAA
add_library(Producer Producer.cpp Producer.h)
message(STATUS "Producer CMAKE_CURRENT_SOURCE_DIR: ")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Producer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/../ILogger
${CMAKE_CURRENT_SOURCE_DIR}/../LoggerPSAA
${CMAKE_CURRENT_SOURCE_DIR}/../FifoQueue
)


