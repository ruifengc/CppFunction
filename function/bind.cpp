#include<functional>
#include<iostream>
#include<vector>

using namespace std;
// function虽然能解决函数指针类型不好表示的问题，但是对于类成员方法还是不方便提取
// bind 可以对函数进行重新封装，是一个通用的函数适配器，他接受一个可调用对象，生成一个新的可调用对象

int add(int a, int b){return a+b;} 

struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1 <<" " << n2 << '\n';
    }
    int data = 10;
};

// 这里的placeholders的位置是等待填入参数的位置，所以要从1开始填写
int main(){
    // 将某个参数进行了绑定
    function<int(int)> func = bind(add,placeholders::_1,2);
    cout<<func(12)<<endl;

    // 绑定成员函数
    // 1.bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
    // 2.必须显示的指定&Foo::print_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Foo::print_sum前添加&；
    // 3.使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &foo；

    Foo foo;
    auto f = bind(&Foo::print_sum, &foo, 95, placeholders::_1);
    f(5); 
    
}