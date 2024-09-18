cmake_minimum_required(VERSION 3.22.1)
project(StatusServer)
# 设置 C++ 标准


set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Common)

add_executable(StatusServer
    StatusServer.cc
    AsioIOServicePool.cc
    ConfigMgr.cc
    Cserver.cc
    HttpConnection.cc
    LogicSystem.cc
    message.grpc.pb.cc
    message.pb.cc
    MysqlDao.cc
    MysqlMgr.cc
    RedisMgr.cc
    StatusServiceImpl.cc
    VerifyGrpcClient.cc
    StatusGrpcClient.cc
)



find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
target_link_libraries(StatusServer PUBLIC -lboost_filesystem -ljsoncpp protobuf::libprotobuf gRPC::grpc++ -lhiredis -lmysqlcppconn)




