#include <iostream>

using namespace std;

/*
 * this is a pointer to the object which the method is called on
 */
struct Enemy {
    string name;
    int level;

    void Attack(Enemy& enemy) {
        enemy.TakeDamage(*this);
    }

    void TakeDamage(Enemy& attacker) {
        cout << attacker.name << " attacked me!!" << endl;
    }

    Enemy& setName(string _name) {
        name = _name;
    }

    Enemy& setLevel(int _level) {
        level = _level;
    }

    void getPointerAddress() {
        cout << this << endl;
    }

    Enemy& getRef() {
        return *this;
    }

    Enemy* getPointer() {
        return this;
    }

    Enemy copy() {
        return *this;
    }

    Enemy& operator*=(int multiplier) {
        level *= multiplier;
        return *this;
    }
};

int main(){
    Enemy e{"Bob", 10};
    Enemy o{"Bill", 1};
    cout << &e << endl;
    e.getPointerAddress(); //same as above

    /*
     * USES
     * 1. Identifying the caller
     * 2. Chaining
     * 3. Overloading operators
     */

    //1
    e.Attack(o); //Bob has attacked me!

    //2
    e.setName("Sam")
     .setLevel(1000);

    //3
    e *= 10;
}