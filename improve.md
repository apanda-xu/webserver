# webserver改进
    1. 服务连接着，但是换了网络环境，会出现bug
    2. 用户验证时，用户数据全部读取出来，效率低
    3. 线程池改进，不使用detach，使用模板类，使用c++标准库
    4. 分布式、负载均衡
    5. 非异步超时检测问题
    6. LT模式如果没读到数据会返回false，连接会在dealwithread中被关闭
    7. addfd(m_epollfd, sockfd, true, m_TRIGMode);中m_TRIGMode没有初始化就使用了，初始化语句被放到了下面m_TRIGMode = TRIGMode;
    8. 在dealwithread的proactor中，是不是得先修改定时器在加入队列，虽然源代码加入之后立马修改时间，但是这种写法感觉不好。或许是作者觉得主线程已经完成了耗时的读操作，下面的process很快，不需要修改？