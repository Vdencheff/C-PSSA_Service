# AppManager
add_library(AppManager appmanager.cpp)
message(STATUS "AppManager CMAKE_CURRENT_SOURCE_DIR: ")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(AppManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/../LoggerPSAA
${CMAKE_CURRENT_SOURCE_DIR}/../ILogger
${CMAKE_CURRENT_SOURCE_DIR}/../LoggerCon
${CMAKE_CURRENT_SOURCE_DIR}/../FifoQueue
${CMAKE_CURRENT_SOURCE_DIR}/../Producer
)


