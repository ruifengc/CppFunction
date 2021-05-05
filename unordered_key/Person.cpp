#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
using namespace std;

class Person{
public:
    string name;
    int age;

    Person(string n, int a){
        name = n;
        age = a;
    }
    // 类内实现operatror==
    bool operator==(const Person & p) const 
    {
        return name == p.name && age == p.age;
    }
};
namespace std{
    // 在std空间内补充hash<Person>的实现
    template<>
    class hash<Person>{
    public:
        size_t operator()(const Person & p) const{
            return hash<string>()(p.name) ^ hash<int>()(p.age);
        }
    };    
}



int main(int argc, char* argv[]){
	unordered_map<Person, int> ids;
	ids[Person("Mark", 17)] = 40561;
    ids[Person("Andrew",16)] = 40562;
    for ( auto ii = ids.begin() ; ii != ids.end() ; ii++ )
        cout << ii->first.name 
        << " " << ii->first.age
        << " : " << ii->second
        << endl;
    return 0;
}
