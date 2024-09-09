#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifyGrpcClient.h"
bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> conn)
{
    if(_get_handlers.find(path) == _get_handlers.end())
    return false;

    _get_handlers[path](conn);
    return true;
}
bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> conn)
{
    if(_post_handlers.find(path) == _post_handlers.end())
    return false;

    _post_handlers[path](conn);
    return true;
}
void LogicSystem::RegGet(std::string url, HttpHandler handler)
{
    _get_handlers.insert(make_pair(url, handler));
}
void LogicSystem::RegPost(std::string url, HttpHandler handler)
{
    _post_handlers.insert(make_pair(url, handler));
}

LogicSystem::LogicSystem()
{
    RegGet("/get_test" ,[](std::shared_ptr<HttpConnection> conn){
        beast::ostream(conn -> _response.body()) << "receive get_test req";
        int i = 0;
        for(auto &elem : conn -> _get_params)
        {
            i++;
            beast::ostream(conn -> _response.body()) << "param" << i << "key is" << elem.first;
            beast::ostream(conn -> _response.body()) << "param" << i << "key is" << elem.second << std::endl;
        }
    });
    RegPost("/get_varifycode",[](std::shared_ptr<HttpConnection> conn){
        auto body_str = boost::beast::buffers_to_string(conn -> _request.body().data());
        std::cout << "receive body is" << body_str << std::endl;
        conn -> _response.set(http::field::content_type,"text/json");
        Json::Value root;
        Json::Reader reader;
        Json::Value src_root;
        bool parse_success = reader.parse(body_str , src_root);
        if(!parse_success)
        {
            std::cout << "Faileed to parse Json data!" <<std::endl;
            root["error"] == ErrorCodes::Error_Json;
            std::string jsonstr = root.toStyledString();
            beast::ostream(conn -> _response.body()) << jsonstr;
            return true;
        }
        if(!src_root.isMember("email"))
        {
            std::cout << "Faileed to parse Json data!" <<std::endl;
            root["error"] == ErrorCodes::Error_Json;
            std::string jsonstr = root.toStyledString();
            beast::ostream(conn -> _response.body()) << jsonstr;
            return true;
        }
        else
        {
            auto email = src_root["email"].asString();
            auto rsp = VerifyGrpcClient::GetInstance() -> GetVarifyCode(email);
            std::cout << "email is " << email <<std::endl;
            root["error"] = rsp.error();
            root["error"] = src_root["email"];
            std::string jsonstr = root.toStyledString();
            beast::ostream(conn -> _response.body()) << jsonstr;
            return true;
        }
    });
}
