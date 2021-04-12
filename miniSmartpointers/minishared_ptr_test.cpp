#include "minishared_ptr.h"
#include <string>
#include <iostream>
using namespace std;
class student
{
public:
    student(string n, int a) : name(n), age(a) { cout << "构造student name" << name << " age:" << age << endl; }
    ~student()
    {
        cout << "析构student name" << name << " age:" << age << endl;
    }
    string getName() const
    {
        return name;
    }
    void older(int n)
    {
        age += n;
    }

private:
    string name;
    int age;
};

int main()
{
    // minishared_ptr<student> autos;
    // miniunique_ptr<student> autos = miniunique_ptr<student>(new student("稳健",88));
    minishared_ptr<student> autos2(new student("大佬", 66));
    // cout<<autos2.use_count()<<endl;
    // minishared_ptr<student> unique1(autos2);
    // cout<<autos2.use_count()<<endl;
    // minishared_ptr<student> ae3;
    // ae3 = autos2;
    // cout<<autos2.use_count()<<endl;
    miniweak_ptr<student> w1(autos2);
    cout<<autos2.use_count()<<endl;
    // unique1 = autos;//禁止左值赋值
    // unique1 = minishared_ptr<student>(new student("右值稳健", 88));
    // auto au3(autos);//禁止左值复制构造
    // auto au3(minishared_ptr<student>(new student("稳健", 88)));
    // cout<<"------------------"<<endl;
    // cout<<autos.get()<<endl;
}