#pragma once
#include "const.h"
#include"CSession.h"



class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;
class LogicSystem : public Singleton<LogicSystem>
{
   friend class Singleton<LogicSystem>;
   void PostMsgToQue(std::shared_ptr<LogicNode> msg);

public:
   ~LogicSystem() {};
   void DealMsg();
   bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
   bool HandlePost(std::string, std::shared_ptr<HttpConnection>);
   void RegGet(std::string, HttpHandler handler);
   void RegPost(std::string, HttpHandler handler);
private:
   LogicSystem();
   std::map<std::string, HttpHandler> _post_handlers;
   std::map<std::string, HttpHandler> _get_handlers;
   std::thread _worker_thread;
   std::queue<std::shared_ptr<LogicNode>> _msg_que;
   std::mutex _mutex;
   std::condition_variable _consume;
   bool _b_stop;
   std::map<short, FunCallBack> _fun_callbacks;
};
