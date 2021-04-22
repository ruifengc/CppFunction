// 加锁，多线程安全
#include<mutex>
using namespace std;
mutex mt;
class Singleton
{
private:
    Singleton(){};
    Singleton(const Singleton&){};
    Singleton& operator=(const Singleton&){};
    static Singleton *instance;
public:
    static Singleton* getInstance(){
        mt.lock();
        if(instance==nullptr){
            instance = new Singleton();
        }
        mt.unlock();
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;