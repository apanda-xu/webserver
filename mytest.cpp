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

#include<iostream>
#include<string>
#include<string.h>
using namespace std;

int main() {
    char name[] = "a1', 'a1'), ('a2', 'a2'), ('a3";
    char password[] = "a3";
    char *sql_insert = (char *)malloc(sizeof(char) * 200);
    strcpy(sql_insert, "INSERT INTO user(username, passwd) VALUES(");
    strcat(sql_insert, "'");
    strcat(sql_insert, name);
    strcat(sql_insert, "', '");
    strcat(sql_insert, password);
    strcat(sql_insert, "')");

    cout << sql_insert << endl;

    // ('a1', 'a1'), ('a2', 'a2'), ('a3', 'a3')

    // char name[] = "xujie";
    // name[0] = 'l';
    // cout << name << endl;
    // cout << strlen(name);
}