# LoggerPSAA
add_library(LoggerCon LoggerCon.cpp LoggerCon.h)
message(STATUS "LoggerPSAA CMAKE_CURRENT_SOURCE_DIR: ")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(LoggerCon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/../ILogger
${CMAKE_CURRENT_SOURCE_DIR}/../FifoQueue
)


