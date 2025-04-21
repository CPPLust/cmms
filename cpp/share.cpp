//#include <iostream>
//#include <memory>
//
//class Event;
//class EventLoop {
//public:
//    void EnableEventWriting(std::shared_ptr<Event>& event, bool enable) {
//        if (enable) {
//            std::cout << "Event writing enabled." << std::endl;
//        }
//        else {
//            std::cout << "Event writing disabled." << std::endl;
//        }
//
//        // ��ӡ���ü����Ͷ����ַ
//        std::cout << "Reference count: " << event.use_count() << std::endl;
//        std::cout << "Event object address: " << event.get() << std::endl;
//    }
//};
//
//class Event : public std::enable_shared_from_this<Event> {
//private:
//    EventLoop* m_loop;
//
//public:
//    Event(EventLoop* loop) : m_loop(loop) {}
//
//    void EnableWriting(bool enable) {
//        // ʹ�� shared_from_this() ��ȡ��ǰ����� shared_ptr
//        auto self = shared_from_this(); // ��ȡ shared_ptr
//        std::cout << "Inside EnableWriting:" << std::endl;
//        std::cout << "  Reference count: " << self.use_count() << std::endl;
//        std::cout << "  Event object address: " << this << std::endl;
//
//        m_loop->EnableEventWriting(self, enable);
//    }
//};
//
//int main() {
//    EventLoop loop;
//
//    {
//
//    }
//    // ����һ�� Event ���󣬲��� shared_ptr ����
//    auto event = std::make_shared<Event>(&loop);
//
//    std::cout << "Initial state:" << std::endl;
//    std::cout << "  Reference count: " << event.use_count() << std::endl;
//    std::cout << "  Event object address: " << event.get() << std::endl;
//
//    // �����¼�д��
//    event->EnableWriting(true);
//
//
//    std::cout << "after EnableWriting:" << std::endl;
//    std::cout << "  Reference count: " << event.use_count() << std::endl;
//    std::cout << "  Event object address: " << event.get() << std::endl;
//    getchar();
//
//    return 0;
//}