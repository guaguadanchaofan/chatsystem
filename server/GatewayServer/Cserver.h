#include "const.h"
class Cserver : public std::enable_shared_from_this<Cserver> //奇异递归模板
{
public:
    Cserver(boost::asio::io_context& ioc ,unsigned short & port);
    void Start();
    ~Cserver(){};
private:
    tcp::acceptor _acceprot;//连接器 接收器
    net::io_context& _ioc; //上下文
    boost::asio::ip::tcp::socket _socket; //
};

