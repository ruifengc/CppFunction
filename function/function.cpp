#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// 普通函数
int add(int a, int b) { return a + b; }

// lambda表达式
auto mod = [](int a, int b)
{ return a % b; };

// 函数对象类
struct divide
{
    int operator()(int denominator, int divisor)
    {
        return denominator / divisor;
    }
    int dosomething(int a, int b)
    {
        return a - b;
    }
    static int dosomestatic(int a, int b)
    {
        return a - b;
    }
};

int main()
{
    vector<function<int(int, int)>> funcvec;
    funcvec.emplace_back(add);
    funcvec.emplace_back(mod);
    funcvec.emplace_back(divide());
    // funcvec.emplace_back(divide::dosomething); //报错
    funcvec.emplace_back(divide::dosomestatic); //static并不需要this指针，所以可以直接放进去

    for (auto func : funcvec)
    {
        cout << func(1, 2) << endl;
    }
}