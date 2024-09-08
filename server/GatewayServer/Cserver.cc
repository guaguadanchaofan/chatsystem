#include "Cserver.h"
#include "HttpConnection.h"
Cserver::Cserver(boost::asio::io_context &ioc, unsigned short &port):
_ioc(ioc),
_acceprot(ioc , tcp::endpoint(tcp::v4(), port)),
_socket(ioc)
{}

void Cserver::Start()
{
    auto self = shared_from_this();
    _acceprot.async_accept(_socket,[self](beast::error_code ec){
        try
        {
            //出错放弃这链接，继续监听其他链接
            if(ec)
            {
                self->Start();
                return;
            }
            //创建新连接，并且创建HttpConnection类管理这个链接
            std::make_shared<HttpConnection>(std::move(self -> _socket)) -> Start();
            
            //继续监听
            self -> Start();
        }
        catch(const std::exception& exp)
        {
            std::cout << "exception is " << exp.what() << std::endl;
            self->Start();
        }
        
    });
}
