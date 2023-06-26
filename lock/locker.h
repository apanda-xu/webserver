#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

// 封装信号量的操作
class sem
{
public:
    // 默认构造函数：初始化信号量为0
    sem()
    {
        if (sem_init(&m_sem, 0, 0) != 0)
        {
            throw std::exception();
        }
    }
    // 有参构造函数：初始化信号量为num
    sem(int num)
    {
        if (sem_init(&m_sem, 0, num) != 0)
        {
            throw std::exception();
        }
    }
    // 析构函数：销毁信号量
    ~sem()
    {
        sem_destroy(&m_sem);
    }
    // 成员函数：减少信号量的值。如果信号量的值大于0，则将其减一，表示资源已被占用，函数返回true；如果信号量值为0，则阻塞等待，直到有其他线程调用post函数，增加信号量的值。
    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    }
    // 成员函数：增加信号量的值。表示资源已经释放，其他等待的线程可以继续执行，函数返回true。
    bool post()
    {
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};


class locker
{
public:
    // 构造函数：初始化互斥锁，如果失败，抛出异常
    locker()
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::exception();
        }
    }
    // 析构函数：销毁互斥锁
    ~locker()
    {
        pthread_mutex_destroy(&m_mutex);
    }
    // 获取锁
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    // 释放锁
    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
    // 获取互斥锁指针的函数，返回一个指向互斥锁的指针
    pthread_mutex_t *get()
    {
        return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};


class cond
{
public:
    cond()
    {
        if (pthread_cond_init(&m_cond, NULL) != 0)
        {
            //pthread_mutex_destroy(&m_mutex);
            throw std::exception();
        }
    }
    ~cond()
    {
        pthread_cond_destroy(&m_cond);
    }
    bool wait(pthread_mutex_t *m_mutex)
    {
        int ret = 0;
        //pthread_mutex_lock(&m_mutex);
        ret = pthread_cond_wait(&m_cond, m_mutex);
        //pthread_mutex_unlock(&m_mutex);
        return ret == 0;
    }
    bool timewait(pthread_mutex_t *m_mutex, struct timespec t)
    {
        int ret = 0;
        //pthread_mutex_lock(&m_mutex);
        ret = pthread_cond_timedwait(&m_cond, m_mutex, &t);
        //pthread_mutex_unlock(&m_mutex);
        return ret == 0;
    }
    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }
    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }

private:
    //static pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};
#endif
