#include<iostream>
#include<thread>

using namespace std;

int i = 0; //共享变量数据

void test(int num){
    // int num = 10000;
    for(int n=0;n < num; n++){
        i=i+1;
    }
}

int main(){
    thread t1(test,1000000);
    thread t2(test,1000000);
    t1.join();
    t2.join();

    cout<<"All thread joined"<<endl;
    cout<<"i = "<<i<<endl;
    // 由于没有对变量i做保护 所以i很可能不等于单线程跑出来的结果
    return 0;
}