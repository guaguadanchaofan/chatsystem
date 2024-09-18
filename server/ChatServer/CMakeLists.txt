cmake_minimum_required(VERSION 3.22.1)
project(ChatServer)
# 设置 C++ 标准


set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")






find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
target_link_libraries(GateServer PUBLIC -lboost_filesystem -ljsoncpp protobuf::libprotobuf gRPC::grpc++ -lhiredis -lmysqlcppconn)
target_link_libraries(StatusServer PUBLIC -lboost_filesystem -ljsoncpp protobuf::libprotobuf gRPC::grpc++ -lhiredis -lmysqlcppconn)




include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third/include)