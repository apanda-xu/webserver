#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "../lock/locker.h"
#include "../CGImysql/sql_connection_pool.h"

template <typename T>
class threadpool
{
public:
    /*thread_number是线程池中线程的数量，max_requests是请求队列中最多允许的、等待处理的请求的数量*/
    threadpool(int actor_model, connection_pool *connPool, int thread_number = 8, int max_request = 10000);
    ~threadpool();
    bool append(T *request, int state);
    bool append_p(T *request);

private:
    /*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
    static void *worker(void *arg);
    void run();

private:
    int m_thread_number;        //线程池中的线程数
    int m_max_requests;         //请求队列中允许的最大请求数
    pthread_t *m_threads;       //描述线程池的数组，其大小为m_thread_number
    std::list<T *> m_workqueue; //请求队列
    locker m_queuelocker;       //保护请求队列的互斥锁
    sem m_queuestat;            //是否有任务需要处理
    connection_pool *m_connPool;  //数据库
    int m_actor_model;          //模型切换
};

// 构造函数
template <typename T>
threadpool<T>::threadpool( int actor_model, connection_pool *connPool, int thread_number, int max_requests) : m_actor_model(actor_model),m_thread_number(thread_number), m_max_requests(max_requests), m_threads(NULL),m_connPool(connPool)
{
    // 如果线程的数量或最大请求数量小于等于0，则抛出异常
    if (thread_number <= 0 || max_requests <= 0)
        throw std::exception();
    // 描述线程的数组
    m_threads = new pthread_t[m_thread_number];
    if (!m_threads)
        throw std::exception();
    // 创建线程
    for (int i = 0; i < thread_number; ++i)
    {   
        // 创建线程并检查是否成功
        if (pthread_create(m_threads + i, NULL, worker, this) != 0)
        {
            delete[] m_threads;
            throw std::exception();
        }
        // 分离线程并检查是否成功
        if (pthread_detach(m_threads[i]))
        {
            delete[] m_threads;
            throw std::exception();
        }
    }
}

// 析构函数，释放线程池
template <typename T>
threadpool<T>::~threadpool()
{
    delete[] m_threads;
}

// 成员函数：添加请求
template <typename T>
bool threadpool<T>::append(T *request, int state)
{   
    m_queuelocker.lock();           // 获取锁
    if (m_workqueue.size() >= m_max_requests)
    {   
        m_queuelocker.unlock();
        return false;               // 如果达到最大请求数量，释放锁，返回false
    }
    request->m_state = state;
    m_workqueue.push_back(request); // 添加请求
    m_queuelocker.unlock();         // 释放锁
    m_queuestat.post();             // 增加信号量的值，表示资源已经释放，其他等待的线程可以继续执行
    return true;
}

// 成员函数：添加请求
template <typename T>
bool threadpool<T>::append_p(T *request)
{
    m_queuelocker.lock();
    if (m_workqueue.size() >= m_max_requests)
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();
    return true;
}

// 成员函数：工作线程
template <typename T>
void *threadpool<T>::worker(void *arg)
{
    threadpool *pool = (threadpool *)arg;   // 参数是线程池，需要强制类型转换
    pool->run();
    return pool;
}

// 成员函数：
template <typename T>
void threadpool<T>::run()
{
    while (true)
    {
        m_queuestat.wait();      // 请求数减一，如果没有请求，线程会被阻塞在这里
        m_queuelocker.lock();    // 操作请求队列前加锁
        if (m_workqueue.empty()) // 若请求队列为空，释放锁
        {
            m_queuelocker.unlock();
            continue;
        }
        // 从请求队列中取出一个请求，然后释放锁
        T *request = m_workqueue.front();
        m_workqueue.pop_front();         
        m_queuelocker.unlock();
        // 判断请求是否为空
        if (!request)
            continue;
        // Reactor模型
        if (m_actor_model == 1)
        {
            // 执行读操作
            if (request->m_state == 0)
            {   
                if (request->read_once())   // 读取请求成功
                {
                    request->improv = 1;
                    connectionRAII mysqlcon(&request->mysql, m_connPool);   // 创建一个connectionRAII对象连接数据库
                    request->process();     // 处理请求
                }   
                // 读取请求失败
                else
                {
                    request->improv = 1;
                    request->timer_flag = 1;
                }
            }
            // 执行写操作
            else
            {
                if (request->write())   // 写入成功
                {
                    request->improv = 1;
                }
                else
                {
                    request->improv = 1;
                    request->timer_flag = 1;
                }
            }
        }
        // Proactor模型：主线程中已经完成了读操作，所以这里只需要处理数据，相当于模拟了一个快速的异步读操作    
        else
        {
            connectionRAII mysqlcon(&request->mysql, m_connPool);
            request->process();
        }
    }
}
#endif
