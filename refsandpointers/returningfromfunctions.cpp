#include <iostream>
using namespace std;

struct Enemy {
    int age;
    ~Enemy() {
        cout << "Destructor!" << endl;
    }
};

Enemy* getRef() {
    Enemy e;
    return &e;
}

int main(){
    //danging pointer
    Enemy enemy = *getRef();
    cout << enemy.age << endl;
}