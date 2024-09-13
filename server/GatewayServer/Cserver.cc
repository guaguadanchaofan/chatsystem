#include "Cserver.h"
#include "HttpConnection.h"

Cserver::Cserver(net::io_context& ioc, unsigned short &port):
_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
}

void Cserver::Start()
{
    auto self = shared_from_this();
    auto &io_context = AsioIOService::GetInstance()->GetIOService();
    std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);
    _acceptor.async_accept(new_con->GetSocket(), [self , new_con](beast::error_code ec)
    {
           try
            {
            // 出错放弃这链接，继续监听其他链接
                if (ec)
                {
                    self->Start();
                    return;
                }
                // 创建新连接，并且创建HttpConnection类管理这个链接
                new_con -> Start();
                // 继续监听
                self->Start();
            }
            catch (const std::exception &exp)
            {
                std::cout << "exception is " << exp.what() << std::endl;
                self->Start();
            }
    });
}
