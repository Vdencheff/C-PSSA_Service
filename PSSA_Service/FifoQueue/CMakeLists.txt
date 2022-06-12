# LoggerPSAA
add_library(FifoQueue FifoQueue.cpp FifoQueue.h)
message(STATUS "FifoQueue CMAKE_CURRENT_SOURCE_DIR: ")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(FifoQueue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/../ILogger
)


