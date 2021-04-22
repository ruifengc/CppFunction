// C++11规定了local static在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。
class Singleton{
private:
    Singleton(){};
    Singleton(const Singleton&){};
    Singleton& operator=(const Singleton&){};
public:
    static Singleton& getInstance(){
        static Singleton instance;
        return instance;
    }
};