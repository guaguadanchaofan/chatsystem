#pragma once

#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <iostream>
#include "Singleton.h"
#include <functional>
#include <map>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <unordered_map>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <hiredis/hiredis.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;


enum ErrorCodes
{
    Success = 0,
    Error_Json = 1001,  //json解析失败
    RPCFailed = 1002,   //RPC请求错误
    VarifyExpired = 1003,  //验证码过期
    VarifyCodeErr = 1004, //验证码错误
    UserExist = 1005, //用户已经存在
    PasswdErr = 1006, //密码错误
    EmailNotMatch = 1007, //邮箱不匹配
    PasswdUpFailed = 1008, //更新密码失败
    PasswdInvalid = 1009, //密码更新失败
};




//Defer类
class Defer
{
public:
    //接受一个lamada表达式
    Defer(std::function<void()> func):func_(func){}
    //析构函数执行传入的函数
    ~Defer()
    {
        func_();
    }
private:
    std::function<void()> func_;
};


#define MAX_LENGTH  1024*2
//头部总长度
#define HEAD_TOTAL_LEN 4
//头部id长度
#define HEAD_ID_LEN 2
//头部数据长度
#define HEAD_DATA_LEN 2
#define MAX_RECVQUE  10000
#define MAX_SENDQUE 1000


#define CODEPREFIX "code_"
