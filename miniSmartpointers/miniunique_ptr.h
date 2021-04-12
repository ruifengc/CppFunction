template <typename T>
class miniunique_ptr
{
public:
    // 构造函数
    explicit miniunique_ptr(T *p = nullptr) : pointer(p) {}

    // 禁用左值构造
    template <typename U>
    miniunique_ptr(miniunique_ptr<U> &) = delete;
    // 允许右值构造
    template <typename U>
    miniunique_ptr(miniunique_ptr<U> &&p) : pointer(p.release()) {}
    // 析构函数
    ~miniunique_ptr()
    {
        delete pointer;
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
    // 放弃智能指针管理，并没有销毁对象
    T *release()
    {
        T *old_ptr = pointer;
        pointer = nullptr;
        return old_ptr;
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
    // 禁止左值赋值
    template <typename U>
    miniunique_ptr<T> &operator=(miniunique_ptr<U> &rp) = delete;
    // 允许右值赋值
    // 重写赋值操作符，这里是于unique_ptr不同的地方,额外再加入一个U是为了增加弹性
    // 等于操作符会释放右操作数到左操作数
    template <typename U>
    miniunique_ptr<T> &operator=(miniunique_ptr<U> &&rp)
    {
        if (this->pointer != rp.pointer)
        {
            reset(rp.release());
        }
        return *this;
    }

private:
    T *pointer;


};