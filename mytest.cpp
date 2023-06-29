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
//         std::cout << "Error: " << e.what() << std::endl;
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

// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <condition_variable>

// std::mutex mtx;
// std::condition_variable cv;
// bool ready = false;

// void waitingThread()
// {
//     std::unique_lock<std::mutex> lock(mtx);
//     while (!ready) {
//         std::cout << "Waiting thread: Condition is not met!" << std::endl;
//         cv.wait(lock);  // 等待条件变量，同时释放互斥锁
//     }
//     std::cout << "Waiting thread: Condition is met!" << std::endl;
// }

// void notifyingThread()
// {
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     std::unique_lock<std::mutex> lock(mtx);
//     ready = true;
//     cv.notify_one();  // 通知等待的线程条件变量已满足
// }

// int main()
// {
//     std::thread t1(waitingThread);
//     std::thread t2(notifyingThread);

//     t1.join();
//     t2.join();

//     return 0;
// }

// #include <iostream>
// #include <thread>
// #include <mutex>

// std::mutex mtx;
// int shareddata = 0;

// void updateShareddata()
// {
//     std::lock_guard<std::mutex> lock(mtx);  // 上锁互斥锁
//     // 执行临界区域的代码
//     ++shareddata;
//     std::cout << "Updated shared data: " << shareddata << std::endl;
//     // lock 销毁时会自动解锁互斥锁
// }

// int main()
// {
//     std::thread t1(updateShareddata);
//     std::thread t2(updateShareddata);

//     t1.join();
//     t2.join();

//     return 0;
// }

// #include <iostream>
// #include <thread>
// #include <condition_variable>

// std::mutex mtx;
// std::condition_variable cv;
// bool ready = false;

// void worker()
// {
//     std::unique_lock<std::mutex> lock(mtx);
//     std::cout << "Worker: Waiting for signal..." << std::endl;
//     cv.wait(lock, [] { return ready; });  // 等待条件变量满足。唤醒时会对ready进行检查，当ready为false时，继续阻塞，防止虚假唤醒。
//     std::cout << "Worker: Got the signal!" << std::endl;
// }

// void setter()
// {
//     std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟耗时操作
//     {
//         std::lock_guard<std::mutex> lock(mtx);
//         ready = true;  // 设置条件变量为满足状态
//         cv.notify_one();  // 发送信号通知等待的线程
//     }
// }

// int main()
// {
//     std::thread t1(worker);
//     std::thread t2(setter);

//     t1.join();
//     t2.join();

//     return 0;
// }

// #include <mysql/mysql.h>
// #include <iostream>
// #include <string>

// // 3. 查询数据
// void select(MYSQL *conn) {
//     if (mysql_query(conn, "select * from user") != 0) {
//         std::cout << "failed to fetch data: " << mysql_error(conn) << std::endl;
//     } else {
//         MYSQL_RES *result = mysql_store_result(conn);
//         if (result == NULL) {
//             std::cout << "failed to get result set: " << mysql_error(conn) << std::endl;
//         } else {
//             MYSQL_ROW row;
//             std::cout << "name\tpasswd" << std::endl;
//             while ((row = mysql_fetch_row(result)) != NULL) {
//                 std::cout << row[0] << "\t" << row[1] << std::endl;
//             }
//             mysql_free_result(result);
//         }
//     }
// }

// int main() {
//     std::string localhost = "127.0.0.1";
//     std::string username  = "root";
//     std::string password  = "258088";
//     std::string database = "yourdb";

//     // 1. 初始化
//     MYSQL *conn = mysql_init(NULL);
//     if (conn == NULL) {
//         std::cout << "failed to initialize" << std::endl;
//         return 1;
//     }

//     // 2. 连接数据库
//     if (mysql_real_connect(conn, localhost.c_str(), username.c_str(), password.c_str(), database.c_str(), 0, NULL, 0) == NULL) {
//         std::cout << "failed to connect: " << mysql_error(conn) << std::endl;
//         mysql_close(conn);
//         return 1;
//     }

//     // 3. 查询数据
//     select(conn);

//     // 4. 插入数据
//     if (mysql_query(conn, "insert into user (username, passwd) values ('test1', '20')") != 0) {
//         std::cout << "failed to insert data: " << mysql_error(conn) << std::endl;
//     } else {
//         std::cout << "inserted successfully" << std::endl;
//     }

//     select(conn);

//     // 5. 更新数据
//     if (mysql_query(conn, "update user set passwd = '123456' where username = 'test1'") != 0) {
//         std::cout << "failed to update data: " << mysql_error(conn) << std::endl;
//     } else {
//         std::cout << "updated successfully" << std::endl;
//     }

//     select(conn);

//     // 6. 删除数据
//     if (mysql_query(conn, "delete from user where username = 'test1'") != 0) {
//         std::cout << "failed to delete data: " << mysql_error(conn) << std::endl;
//     } else {
//         std::cout << "data deleted successfully" << std::endl;
//     }

//     select(conn);

//     // 7. 关闭连接
//     mysql_close(conn);
//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <map>
// using namespace std;

// // {3,0,1,0}
// // 1
// vector<int> topKFrequent(vector<int> &nums, int k) {
//     map<int, int> mp;
//     vector<int> res;
//     for (int i = 0; i < nums.size(); i++)
//     {
//         mp[nums[i]]++;
//     }
//     // {3:1
//     // 0:2
//     // 1:1}
//     for (int i = 0; i < k; i++)
//     {
//         int key = 0, value = 0;
//         for (auto it : mp)
//         {
//             cout << "it.first" << it.first << " it.second" << it.second << endl;
//             if (it.second >= value)
//             {
//                 key = it.first;
//                 value = it.second;
//             }
//             cout << "key=" << key << " value=" << value << endl;
//         }
//         res.push_back(key);
//         mp[key] = -1;
//     }
//     return res;
// }

// int main() {
//     vector<int> nums = {3,0,1,0};
//     int k = 1;
//     vector<int> res = topKFrequent(nums, k);
//     cout << res[0] << endl;
// }

// #include<iostream>
// #include<exception>

// int main() {
//     int a = 1;
//     if(a == 1) {
//         throw std::exception();
//     }
// }

// #include <pthread.h>
// #include <iostream>

// // 线程函数
// void *thread_func(void *arg) {
//     int thread_id = *(int *)arg;
//     std::cout << "hello from thread " << thread_id << std::endl;
//     return NULL;
// }

// int main() {
//     pthread_t thread_id;
//     int thread_arg = 1;
    
//     // 创建线程
//     int result = pthread_create(&thread_id, NULL, thread_func, &thread_arg);
//     if (result != 0) {
//         std::cout << "failed to create thread" << std::endl;
//         return 1;
//     }

//     // 等待线程结束
//     result = pthread_join(thread_id, NULL);
//     if (result != 0) {
//         std::cout << "failed to join thread" << std::endl; 
//         return 1;
//     }
//     std::cout << "thread joined" << std::endl; 
//     return 0;
// }

// #include <iostream>
// #include <pthread.h>

// // 线程函数，打印消息
// void* printMessage(void* arg) {
//     std::string message = static_cast<char*>(arg);
//     std::cout << "Thread ID: " << pthread_self() << " Message: " << message << std::endl;
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thread1, thread2;
//     const char* message1 = "Hello from Thread 1";
//     const char* message2 = "Hello from Thread 2";

//     // 创建线程1，并执行线程函数printMessage
//     if (pthread_create(&thread1, NULL, printMessage, (void*)message1) != 0) {
//         std::cerr << "Failed to create thread 1" << std::endl;
//         return 1;
//     }

//     // 创建线程2，并执行线程函数printMessage
//     if (pthread_create(&thread2, NULL, printMessage, (void*)message2) != 0) {
//         std::cerr << "Failed to create thread 2" << std::endl;
//         return 1;
//     }

//     // 等待线程1和线程2执行完成
//     if (pthread_join(thread1, NULL) != 0) {
//         std::cerr << "Failed to join thread 1" << std::endl;
//         return 1;
//     }

//     if (pthread_join(thread2, NULL) != 0) {
//         std::cerr << "Failed to join thread 2" << std::endl;
//         return 1;
//     }

//     return 0;
// }

// #include<iostream>
// using namespace std;

// class Test
// {
// public:
//     Test(){}
//     // virtual ~Test() {
//     //     cout << "调用析构函数"  << endl;
//     // }
//     virtual ~Test() = 0;
// };

// // Test::~Test() {
// //     cout << "调用析构函数" << endl;
// // }


// int main() {
//     Test *test = new Test();
//     delete test; 
// }

// #include <iostream>
// #include <pthread.h>

// // 线程函数，打印消息
// void printMessage(void* arg) {
//     std::string message = static_cast<char*>(arg);
//     std::cout << "Thread ID: " << pthread_self() << " Message: " << message << std::endl;
//     pthread_exit(NULL);
// }

// void (*fun)(void* arg) = printMessage;
// int main() {
//     pthread_t thread1, thread2;
//     const char* message1 = "Hello from Thread 1";
//     const char* message2 = "Hello from Thread 2";

//     // 创建线程1，并执行线程函数printMessage
//     if (pthread_create(&thread1, NULL, fun, (void*)message1) != 0) {
//         std::cerr << "Failed to create thread 1" << std::endl;
//         return 1;
//     }
//     pthread_join(thread1, NULL);
// }

// #include<iostream>

// class Singleton {
// private:
//     static Singleton instance;
//     // 私有构造函数
//     Singleton() {}

// public:
//     // 全局访问点，用于获取单例对象
//     static Singleton* getInstance() {
//         return &instance;
//     }
// };

// // 静态成员初始化
// Singleton Singleton::instance;

// int main() {
//     Singleton *instance1 = Singleton::getInstance();
//     Singleton *instance2 = Singleton::getInstance();
//     if(instance1 == instance2) {
//         std::cout << "same" << std::endl;
//     }
// }

#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>

bool flag = false;
std::condition_variable cv;
std::mutex mtx;

void fun() {
    std::unique_lock<std::mutex> lock(mtx);
    // while(!flag) {
    //     cv.wait(lock);
    // }
    cv.wait(lock, [](){return flag;});
    std::cout << "hello" << std::endl;
}

int main() {
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // flag = true;
    std::thread t1(fun);
    t1.join();
}