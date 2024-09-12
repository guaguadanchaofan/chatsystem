#include "const.h"
#include "AsioIOServicePool.h"

class Cserver : public std::enable_shared_from_this<Cserver> //奇异递归模板
{
public:
    Cserver(net::io_context& ioc ,unsigned short & port);
    void Start();
    ~Cserver(){};
private:
    net::io_context& _ioc; //上下文
    boost::asio::ip::tcp::acceptor _acceptor;//连接器 接收器
    boost::asio::ip::tcp::socket _socket; //
};

