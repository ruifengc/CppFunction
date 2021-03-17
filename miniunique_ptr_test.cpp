#include "miniunique_ptr.h"
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
    miniunique_ptr<student> autos;
    // miniunique_ptr<student> autos = miniunique_ptr<student>(new student("稳健",88));
    miniunique_ptr<student> autos2(new student("大佬", 66));
    miniunique_ptr<student> unique1;
    // unique1 = autos;//禁止左值赋值
    unique1 = miniunique_ptr<student>(new student("右值稳健", 88));
    // auto au3(autos);//禁止左值复制构造
    auto au3(miniunique_ptr<student>(new student("稳健", 88)));
    // cout<<"------------------"<<endl;
    // cout<<autos.get()<<endl;
}