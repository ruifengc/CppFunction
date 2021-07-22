// TAS 是一种自旋锁 也叫忙等锁

struct MyLock
{
    bool flag = false;
};

bool TestAndSet(bool *old_ptr, bool new_val)
{
    int old = *old_ptr;
    *old_ptr = new_val;
    return old;
}

void lock(MyLock *lock)
{
    while (TestAndSet(&(lock->flag), 1) == 1)
        ;
}

void unlock(MyLock *lock)
{
    lock->flag = false;
}

// compare-and-swap

// prt指的是共有的资源的地址，old_val是这个线程获取资源时拿到的值，new_val是想要修改成的值；cas要判断这个线程是不是基于最新的值所做的修改
// 但是存在ABA问题，ABA问题可以简单的转换为，线程或者进程两次读取相同的值以后是否关注在两次读取之前变量的值是否发送改变，如果中间的改变会影响计算结果，就会出现ABA问题，如果只关注值本身，那么即使出现了ABA也不会影响程序执行结果。
// 这里就要考虑到prt指向的可能也是一根指针，也就是他本身的状态不变也不能判定old_val==*prt就一定等价于是对最新的进行修改，最简单的解决办法是加入版本号限制
// x86的实现叫 CMPXCHG
int CAS(int *ptr, int old_val, int new_val)
{
    // 原子
    int old_reg_val = *ptr;
    if (old_reg_val == old_val)
        *ptr = new_val;
    // 原子结束

    return old_reg_val;
}

// 也有的根据old_val是不是等于ptr里保存的去直接返回这次交换是否成功，但是这个操作也可以延迟到调用者那里判断