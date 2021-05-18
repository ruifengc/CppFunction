#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 先定义obs，这样才能在被观察者里面用
class Observer;

class Subject{
public:
    virtual void attach(Observer *obs) = 0;
    virtual void detach(Observer *obs) = 0;
    virtual void notify() = 0;
};

class Observer{
public:
    virtual void update(Subject *sub) = 0;
};


class Earth:public Subject{
private:
    string weather;
    vector<Observer *> obs;
public:
    void attach(Observer *obs){
        this->obs.emplace_back(obs);
    }
    void notify(){
        for(auto ob:obs){
            ob->update(this);
        }
    }
    void setWeather(string str){
        this->weather = str;
        notify();
    }
    string getWeather(){
        return this->weather;
    }
    
};

class Satellite:public Observer{
private:
    string name;
public:
    Satellite(string str="666"):name(str){};
    string getName(){
        return name;
    }
    void update(Subject *sub){
        cout<< this->getName() + " " + sub->getWeather()<<endl;
    }
};

int main()
{
    Earth e;
    Satellite *s1 = new Satellite("风云一号");
    Satellite *s2 = new Satellite("风云二号");
    Satellite *s3 = new Satellite("风云三号");
    Satellite *s4 = new Satellite("风云四号");
    e.attach(s1);
    e.attach(s2);
    e.attach(s3);
    e.attach(s4);
    e.setWeather("fine");

    delete s1;
    delete s2;
    delete s3;
    delete s4;

    // while(1) {}
    return 0;
}