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
    PRCFailed = 1002,   //RPC请求错误
    VarifyExpired = 1003,  //验证码过期
    VarifyCodeErr = 1004, //验证码错误
    UserExist = 1005, //用户已经存在
    PasswdErr = 1006, //密码错误
    EmailNotMatch = 1007, //邮箱不匹配
    PasswdUpFailed = 1008, //更新密码失败
    PasswdInvalid = 1009, //密码更新失败
};

#define CODEPREFIX "code_"
