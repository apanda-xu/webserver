#include<iostream>
#include<thread>
#include<string>
#include "./lock/locker.h"

locker lock;

void show(std::string s) {
    lock.lock();
    std::cout << s << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    lock.unlock();
}

int main() {
    std::thread t1(show, "I am t1");
    t1.detach();
    std::thread t2(show, "I am t2");
    t2.detach();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}