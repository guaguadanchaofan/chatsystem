#include "AsioIOServicePool.h"



AsioIOServicePool::AsioIOServicePool(std::size_t size):
_ioServices(size),
_works(size),
_nextIOService(0)
{
    for(std::size_t i = 0 ; i < size ; i++)
    {
        //将io_context 封装到unique_ptr 给到vector管理
        _works[i] = std::unique_ptr<Work>(new Work(_ioServices[i]));
    }
    //遍历ioservice，创建多个线程，每个线程启动一个ioservice
    for(std::size_t i = 0 ; i < _ioServices.size() ; i++)
    {
        _threads.emplace_back([this , i](){
            _ioServices[i].run();
        });
    }

}
boost::asio::io_context &AsioIOServicePool::GetIOService()
{
    // TODO: 在此处插入 return 语句
    auto& service = _ioServices[_nextIOService++];
    if(_nextIOService == _ioServices.size())
    {
        _nextIOService = 0;
    }
    return service;
}

void AsioIOServicePool::Stop()
{
    //因为仅仅执行work。reset并不能让iocontext从run的状态中推出
    //当iocontext已经绑定了读或写的监听事件后，还需要手动stop该服务
    for(auto& work : _works)
    {
        //把服务停止
        work -> get_io_context().stop();
        work.reset();
    }
    for(auto& t : _threads)
    {
        //回收线程
        t.join();
    }
}


AsioIOServicePool::~AsioIOServicePool()
{
    Stop();
    std::cout<<"AsioIOServicePool destruct" <<std::endl;
}