// 懒汉式 会有多线程问题
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
            instance = new Singleton();
        }
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;
