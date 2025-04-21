

#include<future>
#include<string>
#include<iostream>
std::once_flag flag;

void may_throw() {
    throw std::runtime_error("Error during initialization");
}

void thread_func() {
    try {
        std::call_once(flag, may_throw);
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

int main() {
    std::thread t1(thread_func);
    std::thread t2(thread_func);

    t1.join();
    t2.join();

    return 0;
}