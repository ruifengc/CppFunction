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
        if(instance==nullptr){
            mt.lock();
            if(instance==nullptr){
                instance = new Singleton();
            }
            mt.unlock();
        }
        return instance;
    }
};
Singleton* Singleton::instance=nullptr;