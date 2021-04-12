#include "miniauto_ptr.h"
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
    miniauto_ptr<student> autos = miniauto_ptr<student>(new student("稳健", 88));
    miniauto_ptr<student> autos2(new student("大佬", 66));
    auto au3{autos};
    cout << "------------------" << endl;
    cout << autos.get() << endl;
}