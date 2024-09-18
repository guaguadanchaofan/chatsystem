cmake_minimum_required(VERSION 3.22.1)
project(GateServer)
# 设置 C++ 标准


set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")

# 添加可执行文件
add_executable(GateServer
    AsioIOServicePool.cc
    ConfigMgr.cc
    Cserver.cc
    GateServer.cc
    HttpConnection.cc
    LogicSystem.cc
    message.grpc.pb.cc
    message.pb.cc
    MysqlDao.cc
    MysqlMgr.cc
    RedisMgr.cc
    VerifyGrpcClient.cc
    StatusGrpcClient.cc
)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
target_link_libraries(GateServer PUBLIC -lboost_filesystem -ljsoncpp protobuf::libprotobuf gRPC::grpc++ -lhiredis -lmysqlcppconn)