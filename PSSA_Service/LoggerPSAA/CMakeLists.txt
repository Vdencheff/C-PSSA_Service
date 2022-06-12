# LoggerPSAA
add_library(LoggerPSAA Logger.cpp Logger.h)
message(STATUS "LoggerPSAA CMAKE_CURRENT_SOURCE_DIR: ")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(LoggerPSAA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/../ILogger
)


