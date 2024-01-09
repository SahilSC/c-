#include <iostream>
using namespace std;

/*
 * Public, protected, private inheritance
 * Public = same restricts as inherited
 * Protected = public/protected members -> protected
 * Private = public/protected -> private
 * Private variables always private
 */
struct Animal {
    int age;
    string name;
    Animal(int age, string name) : age(age), name(name) {
        cout << "Animal multiple args constructor called" << endl;
    }

    Animal() {
        cout << "Animal default constructor called" << endl;
    };

};

struct Dog : public Animal {
    string breed;
    /*
     * NOTE: Only way to call specific constructor of parent is through
     * member initializer list
     */
    Dog() : Animal{20, "Bentley"}, breed("Dalmatian"){
        cout << "Dog default constructor called" << endl;
    }

    /*
     * NOTE: Parent no-arg constructor (has to have one) automatically called if
     * not explicitly called.
     */
    Dog(string breed) {

    }

};

/*
 * FINAL: used to prevent a class from extending another one
 */
class Cat final : public Animal {};
class Cash final {};

/*
 * SHADOWED VARIABLES
 */
struct Enemy {
    int health{100};
    int getHealth() {
        return health;
    }

    void Attack() {
        cout << "Enemy attack!" << endl;
    }

    void Heal() {
        cout << "Regenerating 10 HP" << endl;
    }
};

struct Goblin : public Enemy {
    int health{150};

    void Attack() {
        cout << "Goblin attack!" << endl;
    }

    void Heal() {
        Enemy::Heal();
        cout << "Goblin scream" << endl;
    }
};

int main(){

    //Animal multiple args constructor called
    //Dog default constructor called
    Dog d;
    cout << d.name << endl; //Bentley

    Goblin g;
    cout << g.getHealth() << endl; //returns 100 since health is defined in Enemy scope
    cout << g.health << endl; //returns 150

    /*
     * NOTE: Shadowing functions can happen as well. By default,
     * calling a method shared by a class and its parent simply
     * does the method in the child class.
     *
     * NOTE: To extend functionality by using the parent's method, use ::
     */
    g.Attack(); //Goblin attack!

    //Regenerating 10 HP
    //Goblin scream
    g.Heal();
}
