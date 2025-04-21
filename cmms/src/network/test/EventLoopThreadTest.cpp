//
//#include "network/net/EventLoopThread.h"
//#include "network/net/EventLoopThreadPool.h"
//#include "network/net/PipeWinEvent.h"
//#include <iostream>
//#include <thread>
//#include "base/TTime.h"
//#include <stdint.h>
//using namespace cmms;
//
//
//
//void TestEventLoopThread()
//{
//	EventLoopThread eventloop_thread(1);
//	eventloop_thread.Run();
//	EventLoop* loop = eventloop_thread.Loop();
//	if (loop)
//	{
//		std::cout << "loop:" << loop << std::endl;
//
//		PipeWinEventPtr pipe= std::make_shared<PipeWinEvent>(loop,1);
//		loop->AddEvent(pipe);
//		int64_t msg = 1234;
//		pipe->Write((const char *)&msg, sizeof(msg));
//
//
//		std::thread th = std::thread([&pipe]() {
//
//			while (true)
//			{
//				int64_t msg = TTime::NowMS();
//				pipe->Write((const char*)&msg, sizeof(msg));
//				
//				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//			}
//
//			}
//		);
//
//		while (true)
//		{
//			std::this_thread::sleep_for(std::chrono::milliseconds(50));
//		}
//		
//	}
//
//}
//
//void TestEventLoopThreadPool()
//{
//	EventLoopThreadPool pool(2,0,2);
//	pool.Start();
//
//#if  0
//	std::vector<EventLoop*> list = pool.GetLoops();
//	for (auto& l : list)
//	{
//		std::cout << "loop:" << l << std::endl;
//	}
//	EventLoop* l = pool.GetNextLoop();
//	std::cout << "event loop:" << l << std::endl;
//
//	l = pool.GetNextLoop();
//	std::cout << "event loop:" << l << std::endl;
//#endif
//
//
//	/*std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
//	std::vector<EventLoop*> list = pool.GetLoops();
//	for (auto& l : list)
//	{
//		l->RunInLoop([&l]()
//			{
//				std::cout << "event loop:" << l <<", thread id:" << std::this_thread::get_id() << std::endl;
//			});
//		std::cout << "loop:" << l << std::endl;
//	}*/
//	EventLoop* l = pool.GetNextLoop();
//	std::cout << "event loop:" << l << std::endl;
//	l->RunAfter(1, []() {
//		std::cout << "run after 1s now:" << TTime::Now()<< std::endl;
//		});
//	l->RunAfter(5, []() {
//		std::cout << "run after 5s now:" << TTime::Now() << std::endl;
//		});
//
//	l->RunEvery(1, []() {
//		std::cout << "run every 1s now:" << TTime::Now() << std::endl;
//		});
//	l->RunEvery(5, []() {
//		std::cout << "run every 5s now:" << TTime::Now() << std::endl;
//		});
//
//	while (true)
//	{
//		std::this_thread::sleep_for(std::chrono::seconds(1));
//	}
//
//}
//
//
//int main(int argc, char* argv[])
//{
//
//	TestEventLoopThreadPool();
//
//
//
//	getchar();
//	return 0;
//}
