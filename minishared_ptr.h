#include<iostream>
using namespace std;
class counter{
public:
    counter():shared_count(0),weak_count(0){}
    int shared_count;
    int weak_count;
};
template <typename T> class miniweak_ptr;

template <typename T>
class minishared_ptr
{
public:
    friend class miniweak_ptr<T>;
    // 构造函数
    explicit minishared_ptr(T *p = nullptr) : pointer(p) {
        count_ptr = new counter();
        if(p){
            count_ptr->shared_count = 1;
        }
    }

    template <typename U>
    minishared_ptr(minishared_ptr<U> &p) : pointer(p.pointer),count_ptr(p.count_ptr) {
        count_ptr->shared_count++;
    }

    
    template <typename U>
    minishared_ptr(miniweak_ptr<U> &p) : pointer(p.pointer),count_ptr(p.count_ptr) {
        count_ptr->shared_count++;
    }

    // 析构函数
    ~minishared_ptr()
    {
        _release();
    }
    // 模拟-> * 符号
    T *operator->() const
    {
        return pointer;
    }
    T &operator*() const
    {
        return *pointer;
    }
    // 危险操作 返回原始指针
    T *get() const
    {
        return pointer;
    }
    // 控制另一个对象，销毁之前保存的对象 注意可能会出现自己重新控制自己的问题
    void reset(T *p = nullptr)
    {
        if (p != pointer)
        {
            delete pointer;
            pointer = p;
        }
    }

    // 允许右值赋值
    // 重写赋值操作符，这里是于unique_ptr不同的地方,额外再加入一个U是为了增加弹性
    // 等于操作符会释放右操作数到左操作数
    template <typename U>
    minishared_ptr<T> &operator=(minishared_ptr<U> &rp)
    {
        if (this->pointer != rp.pointer)
        {
            _release();
            pointer = rp.pointer;
            count_ptr = rp.count_ptr;
            count_ptr->shared_count++;
        }
        return *this;
    }
    int use_count(){
        return count_ptr->shared_count;
    }
    bool unique(){
        return use_count() == 1;
    }


private:
    T *pointer;
    counter *count_ptr;
    void _release(){

        count_ptr->shared_count--;
        cout<<"minishared_ptr尝试析构 s,w:"<<count_ptr->shared_count<<" "<<count_ptr->weak_count<<endl;
        if(count_ptr->shared_count<1){
            delete pointer;
            if(count_ptr->weak_count<1){
                delete count_ptr;
                count_ptr = nullptr;
            }
        }    
    }
};

template <typename T> 
class miniweak_ptr{
    public:
    friend class minishared_ptr<T>;
    // 构造函数
    explicit miniweak_ptr() : pointer(nullptr),count_ptr(nullptr) {}

    template <typename U>
    miniweak_ptr(miniweak_ptr<U> &p) : pointer(p.pointer),count_ptr(p.count_ptr) {
        count_ptr->weak_count++;
    }

    
    template <typename U>
    miniweak_ptr(minishared_ptr<U> &p) : pointer(p.pointer),count_ptr(p.count_ptr) {
        count_ptr->weak_count++;
    }

    // 析构函数
    ~miniweak_ptr()
    {
        _release();
    }
    // 模拟-> * 符号
    T *operator->() const
    {
        return pointer;
    }
    T &operator*() const
    {
        return *pointer;
    }
    // 危险操作 返回原始指针
    T *get() const
    {
        return pointer;
    }
    // 控制另一个对象，销毁之前保存的对象 注意可能会出现自己重新控制自己的问题
    void reset(T *p = nullptr)
    {
        if (p != pointer)
        {
            delete pointer;
            pointer = p;
        }
    }

    // 重写赋值操作符，这里是于unique_ptr不同的地方,额外再加入一个U是为了增加弹性
    // 等于操作符会释放右操作数到左操作数
    template <typename U>
    miniweak_ptr<T> &operator=(miniweak_ptr<U> &rp)
    {
        if (this->pointer != rp.pointer)
        {
            _release();
            pointer = rp.pointer;
            count_ptr = rp.count_ptr;
            count_ptr->weak_count++;
        }
        return *this;
    }

    template <typename U>
    miniweak_ptr<T> &operator=(minishared_ptr<U> &rp)
    {
        if (this->pointer != rp.pointer)
        {
            _release();
            pointer = rp.pointer;
            count_ptr = rp.count_ptr;
            count_ptr->weak_count++;
        }
        return *this;
    }
    minishared_ptr<T> lock(){
        return minishared_ptr<T>(*this);
    }
    int use_count(){
        return count_ptr->shared_count;
    }
    bool unique(){
        return use_count() == 1;
    }
    bool expired(){
        return use_count()==0;
    }


private:
    T *pointer;
    counter *count_ptr;
    void _release(){
        cout<<"miniweak_ptr尝试析构"<<endl;
        if(count_ptr){
            count_ptr->weak_count--;
            cout<<"miniweak_ptr尝试析构 s,w:"<<count_ptr->shared_count<<" "<<count_ptr->weak_count<<endl;
            if(count_ptr->weak_count<1&&count_ptr->shared_count<1){
                delete count_ptr;
                count_ptr = nullptr;
            }
        }    
    }
};