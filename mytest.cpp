// #include<iostream>
// #include<thread>
// #include<string>
// #include "./lock/locker.h"

// locker lock;

// void show(std::string s) {
//     lock.lock();
//     std::cout << s << std::endl;
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     lock.unlock();
// }

// int main() {
//     std::thread t1(show, "I am t1");
//     t1.detach();
//     std::thread t2(show, "I am t2");
//     t2.detach();
//     std::this_thread::sleep_for(std::chrono::seconds(5));
// }

// #include<iostream>
// #include<thread>
// #include<string>
// #include<mutex>
// #include "./lock/locker.h"

// locker lock;
// std::mutex mt;


// void show(std::string s) {
//     // lock.lock();
//     std::unique_lock<std::mutex> unique(mt);
//     std::cout << s << std::endl;
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     unique.unlock();
//     // lock.unlock();
// }

// int main() {
//     std::thread t1(show, "I am t1");
//     t1.detach();
//     std::thread t2(show, "I am t2");
//     t2.detach();
//     std::this_thread::sleep_for(std::chrono::seconds(5));
// }


// #include<iostream>
// #include<unistd.h>
// using namespace std;

// int main(int argc, char **argv) {
//     int opt;
//     while((opt=getopt(argc, argv, "a:b:c:d:")) != -1) {
//         switch (opt){
//             case 'a':
//                 cout << "-a " << optarg << endl;
//                 break;
//             case 'b':
//                 cout << "-b " << optarg << endl;
//                 break;
//             case 'c':
//                 cout << "-c " << optarg << endl;
//                 break;
//             case 'd':
//                 cout << "-d " << optarg << endl;
//                 break;
//             default:
//                 break;
//         }
//     }
// }

// #include<iostream>
// #include<string>
// #include<string.h>
// using namespace std;

// int main() {
//     char name[] = "a1', 'a1'), ('a2', 'a2'), ('a3";
//     char password[] = "a3";
//     char *sql_insert = (char *)malloc(sizeof(char) * 200);
//     strcpy(sql_insert, "INSERT INTO user(username, passwd) VALUES(");
//     strcat(sql_insert, "'");
//     strcat(sql_insert, name);
//     strcat(sql_insert, "', '");
//     strcat(sql_insert, password);
//     strcat(sql_insert, "')");

//     cout << sql_insert << endl;

//     // ('a1', 'a1'), ('a2', 'a2'), ('a3', 'a3')

//     // char name[] = "xujie";
//     // name[0] = 'l';
//     // cout << name << endl;
//     // cout << strlen(name);
// }


// #include <iostream>
// #include <exception>

// int main() {
//     try {
//         int a, b;
//         std::cout << "Enter two numbers: ";
//         std::cin >> a >> b;

//         if (b == 0) {
//             throw std::runtime_error("Divide by zero error");
//         }

//         std::cout << "Result: " << a / b << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }

// #include <pthread.h>
// #include <time.h>
// #include <stdio.h>

// pthread_mutex_t mutex;
// pthread_cond_t cond;

// void* thread_func(void* arg)
// {
//     struct timespec ts;
//     clock_gettime(CLOCK_REALTIME, &ts);
//     ts.tv_sec += 5;   // 等待5秒钟

//     pthread_mutex_lock(&mutex);
//     int ret = pthread_cond_timedwait(&cond, &mutex, &ts);
//     if (ret == 0)
//     {
//         printf("Thread %d: condition variable signaled.\n", (int)arg);
//     }
//     else if (ret != 0)
//     {
//         printf("Thread %d: condition variable timed out.\n", (int)arg);
//     }
//     pthread_mutex_unlock(&mutex);

//     return NULL;
// }

// int main()
// {
//     pthread_t threads[2];

//     pthread_mutex_init(&mutex, NULL);
//     pthread_cond_init(&cond, NULL);

//     for (int i = 0; i < 2; i++)
//     {
//         pthread_create(&threads[i], NULL, thread_func, (void*)i);
//     }

//     sleep(6);  // 等待6秒钟

//     pthread_mutex_lock(&mutex);
//     pthread_cond_signal(&cond);
//     pthread_mutex_unlock(&mutex);

//     for (int i = 0; i < 2; i++)
//     {
//         pthread_join(threads[i], NULL);
//     }

//     pthread_cond_destroy(&cond);
//     pthread_mutex_destroy(&mutex);

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include<thread>
// #include<chrono>

// pthread_mutex_t mutex;
// pthread_cond_t cond;
// int ready = 0;

// void* thread_func(void* arg) {
//     pthread_mutex_lock(&mutex);

//     while (!ready) {
//         pthread_cond_wait(&cond, &mutex);
//     }

//     printf("Thread %d: Condition satisfied\n", *(int*)arg);

//     pthread_mutex_unlock(&mutex);

//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thread;
//     int thread_id = 1;

//     pthread_mutex_init(&mutex, NULL);
//     pthread_cond_init(&cond, NULL);

//     pthread_create(&thread, NULL, thread_func, &thread_id);

    
//     std::this_thread::sleep_for(std::chrono::seconds(2)); 
// }

// #include<iostream>
// #include<pthread.h>
// #include<chrono>
// #include<thread>

// pthread_mutex_t mutex;
// pthread_cond_t cond;
// bool flag = false;

// void* threadFunc1(void* arg)
// {
//     pthread_mutex_lock(&mutex);
//     // 等待条件变量满足
//     while (!flag)
//     {
//         pthread_cond_wait(&cond, &mutex);
//     }
//     std::cout << "Thread 1: Condition is met!" << std::endl;
//     pthread_mutex_unlock(&mutex);
//     return NULL;
// }

// void* threadFunc2(void* arg)
// {
//     // 模拟操作
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     pthread_mutex_lock(&mutex);
//     // 设置条件变量为满足状态
//     flag = true;
//     // 唤醒等待条件变量的线程
//     pthread_cond_signal(&cond);
//     pthread_mutex_unlock(&mutex);
//     return NULL;
// }

// int main()
// {
//     pthread_t thread1, thread2;

//     // 初始化互斥锁和条件变量
//     pthread_mutex_init(&mutex, NULL);
//     pthread_cond_init(&cond, NULL);

//     // 创建线程
//     pthread_create(&thread1, NULL, threadFunc1, NULL);
//     pthread_create(&thread2, NULL, threadFunc2, NULL);

//     // 等待线程结束
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     // 销毁互斥锁和条件变量
//     pthread_mutex_destroy(&mutex);
//     pthread_cond_destroy(&cond);

//     return 0;
// }


// #include <iostream>
// #include <thread>
// #include <mutex>

// std::mutex mtx;

// void printMessage(const std::string& message)
// {
//     // 上锁互斥锁
//     std::unique_lock<std::mutex> lock(mtx);  
//     // 执行临界区操作
//     std::cout << message << std::endl;
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     // 在作用域结束时自动解锁互斥锁
// }

// int main()
// {
//     std::thread t1(printMessage, "Thread 1");
//     std::thread t2(printMessage, "Thread 2");
//     t1.join();
//     t2.join();
//     return 0;
// }


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waitingThread()
{
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready) {
        std::cout << "Waiting thread: Condition is not met!" << std::endl;
        cv.wait(lock);  // 等待条件变量，同时释放互斥锁
    }
    std::cout << "Waiting thread: Condition is met!" << std::endl;
}

void notifyingThread()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_one();  // 通知等待的线程条件变量已满足
}

int main()
{
    std::thread t1(waitingThread);
    std::thread t2(notifyingThread);

    t1.join();
    t2.join();

    return 0;
}



