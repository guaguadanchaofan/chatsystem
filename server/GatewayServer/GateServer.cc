#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include "Cserver.h"
int main()
{
    try
    {
        unsigned short port = static_cast<unsigned short>(8080);
        net::io_context ioc{1};
        boost::asio::signal_set signals(ioc , SIGINT,SIGTERM);
        signals.async_wait([&ioc](const boost::system::error_code &error , int signal_number){
            if(error)
            {
                return;
            }
            ioc.stop();
        });
        std::make_shared<Cserver>(ioc, port) -> Start();
        ioc.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
}