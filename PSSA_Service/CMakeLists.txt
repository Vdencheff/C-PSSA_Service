# Main
cmake_minimum_required(VERSION 3.10)

# set the project name
project(Main VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(AppManager)
add_subdirectory(LoggerPSAA)
add_subdirectory(LoggerCon)
add_subdirectory(FifoQueue)
add_subdirectory(Producer)
add_executable(Main Main.cpp)

target_link_libraries(Main PRIVATE AppManager
                                   LoggerPSAA
                                   LoggerCon
                                   Producer
)

target_include_directories(Main PUBLIC ${PROJECT_BINARY_DIR}
                                       ${CMAKE_CURRENT_SOURCE_DIR}/LoggerPSAA
                                       ${CMAKE_CURRENT_SOURCE_DIR}/AppManager
                                       ${CMAKE_CURRENT_SOURCE_DIR}/ILogger
)

target_link_directories(Main PRIVATE ${PROJECT_BINARY_DIR})
