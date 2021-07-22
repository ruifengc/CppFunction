// 我们提供了一个类：

// public class Foo {
//   public void first() { print("first"); }
//   public void second() { print("second"); }
//   public void third() { print("third"); }
// }
// 三个不同的线程 A、B、C 将会共用一个 Foo 实例。

// 一个将会调用 first() 方法
// 一个将会调用 second() 方法
// 还有一个将会调用 third() 方法
// 请设计修改程序，以确保 second() 方法在 first() 方法之后被执行，third() 方法在 second() 方法之后被执行。
#include<iostream>
#include<functional>
#include<string>
using namespace std;


// 一、mutex 互斥量

// 互斥锁是用来防止多个线程同时访问共享资源对象的机制，在同一时间只有一个线程可以拥有一个特定的锁对象，其他线程如果尝试获取锁会阻塞直到锁资源被释放或直接返回失败。

// 针对这道题我们可以用两个互斥锁来阻塞 second 和 third 函数，分别在 first 和 second 执行结束后解锁。
// 这段代码能够 ac，但实际上这种使用 mutex 的方法是错误的，因为根据 c++ 标准，在一个线程尝试对一个 mutex 对象进行 unlock 操作时，mutex 对象的所有权必须在这个线程上；也就是说，应该由同一个线程来对一个 mutex 对象进行 lock 和 unlock 操作，否则会产生未定义行为。

#include<mutex>

class Foo {

public:
    Foo() {
        mt1.lock();
        mt2.lock();
    }

    void first(function<void()> printFirst) {
        cout<<"first"<<endl;
        mt1.unlock();
    }

    void second(function<void()> printSecond) {
        mt1.lock();
        cout<<"second"<<endl;
        mt1.unlock();
        mt2.unlock();
    }

    void third(function<void()> printThird) {
        mt2.lock();
        cout<<"third"<<endl;
        mt2.unlock();
    }
private:
    mutex mt1,mt2;
};
// 略微升级到unique_lock
class Foo1 {

public:
    Foo1():lock1(mt1,try_to_lock),lock2(mt2,try_to_lock){}

    void first(function<void()> printFirst) {
        cout<<"first"<<endl;
        lock1.unlock();
    }

    void second(function<void()> printSecond) {
        lock_guard<mutex> guard(mt1);
        cout<<"second"<<endl;
        lock2.unlock();
    }

    void third(function<void()> printThird) {
        lock_guard<mutex> guard(mt2);
        cout<<"third"<<endl;
    }
private:
    mutex mt1,mt2;
    unique_lock<mutex> lock1,lock2;
};

// 二、条件变量 condition_variable
// 条件变量一般和互斥锁搭配使用，互斥锁用于上锁，条件变量用于在多线程环境中等待特定事件发生。
// std::condition_variable::wait 函数会执行三个操作：先将当前线程加入到等待唤醒队列，然后 unlock mutex 对象，最后阻塞当前线程；它有两种重载形式，第一种只接收一个 std::mutex 对象，此时线程一旦接受到唤醒信号（通过 std::condition_variable::notify_one 或 std::condition_variable::notify_all 进行唤醒），则无条件立即被唤醒，并重新 lock mutex；第二种重载形式还会接收一个条件（一般是 variable 或者 std::function），即只有当满足这个条件时，当前线程才能被唤醒，

// 针对这道题我们可以分别在 first 和 second 执行完之后修改特定变量的值（例如修改成员变量 k 为特定值），然后通知条件变量，唤醒下一个函数继续执行。

#include<condition_variable>
class Foo2 {
private:
    mutex mt;
    condition_variable cv;
    int k=0;
public:

    void first(function<void()> printFirst) {
        cout<<"first"<<endl;
        k=1;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(mt);
        // wait会解锁lock，并且把自己加入到等待队列
        cv.wait(lock,[this](){return k==1;});
        cout<<"second"<<endl;
        k=2;
        cv.notify_one();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(mt);
        cv.wait(lock,[this](){return k==2;});
        cout<<"third"<<endl;
    }

};

// 三、信号量 semaphore.h
// 
#include<semaphore.h>
class Foo3 {
private:
    sem_t sem1,sem2;
public:
    Foo3(){
        // 第一个参数是是否支持进程间使用，0是只支持线程间
        // 第二个参数是初始值大小
        sem_init(&sem1,0,0);
        sem_init(&sem2,0,0);
    }
    void first(function<void()> printFirst) {
        cout<<"first"<<endl;
        sem_post(&sem1);
    }

    void second(function<void()> printSecond) {
        sem_wait(&sem1);
        cout<<"second"<<endl;
        sem_post(&sem2);

    }

    void third(function<void()> printThird) {
        sem_wait(&sem2);
        cout<<"third"<<endl;
    }

};

// 四、原子操作 atomic
#include<atomic>
#include<thread>
#include<chrono>
class Foo4 {
private:
    atomic<bool> a{false};
    atomic<bool> b{false};
public:
    Foo4(){

    }
    void first(function<void()> printFirst) {
        cout<<"first"<<endl;
        a = true;
    }

    void second(function<void()> printSecond) {
        while(!a){
            this_thread::sleep_for(chrono::seconds(1));
        }
        cout<<"second"<<endl;
        b = true;
    }

    void third(function<void()> printThird) {
        while(!b){
            this_thread::sleep_for(chrono::seconds(1));
        }
        cout<<"third"<<endl;
    }

};