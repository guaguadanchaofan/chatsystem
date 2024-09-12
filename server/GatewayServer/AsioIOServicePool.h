#pragma once
#include <vector>
#include <boost/asio.hpp>
#include "const.h"

class AsioIOService : public Singleton<AsioIOService>
{
    friend Singleton<AsioIOService>;
public:
    using IOservice = boost::asio::io_context;
    using Work = boost::asio::io_context::work;
    using WorkPtr = std::unique_ptr<Work>;
    ~AsioIOService();
    AsioIOService(const AsioIOService&) = delete;
    AsioIOService& operator= (const AsioIOService&&) = delete;
    //使用 round—robin 的方式返回一个 io_service
    boost::asio::io_context& GetIOService();
    void Stop();
private:
    AsioIOService(std::size_t size = 2 /*std::thread::hardware_concurrency*/);
    std::vector<IOservice> _ioServices;
    std::vector<WorkPtr> _works;
    std::vector<std::thread> _threads;
    std::size_t _nextIOService;
};