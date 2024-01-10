#include <iostream>
using namespace std;

struct Character {
    /*
     * VIRTUAL = enables runtime polymorphism by enabling dynamic binding
     * Also makes all functions that override it implicitly virtual
     *
     * Static (early) vs. Dynamic Binding (late)
     * "Binding" describes the function that will be executed on an object/pointer
     * 1. Static binding used by default
     * 2. Static binding faster
     * 3. Static binding = compile time, dynamic binding = runtime
     * 4. When the compiler sees SomeType->Method(), static binding will look at only the
     * pointer type and bind to that. Dynamic binding asks the compiler to go a step further
     * and bind to the function that would be called by the pointed to object.
     *
     */
    virtual void Attack(Character* player) {
        cout << "Character Attack" << endl;
    }
};

struct Goblin : public Character {
    /*
     * OVERRIDE = optional
     * Tells compiler that the function must override a virtual method & more clear intent
     */
    void Attack(Character* player) override {
        cout << "Goblin Attack" << endl;
    }
};

struct Hoblin : public Character {
    void Attack(Character* player) {
        cout << "Hoblin Attack" << endl;
    }
};

struct GoblinWarrior : public Goblin {
    /*
     * FINAL: prevents subclasses from overriding this function
     */
    void Attack(Character* player) final override {
        cout << "GoblinWarrior Attack" << endl;
    }
};


void Battle(Character* c1, Character* c2) {
    c1->Attack(c2);
}

struct Animal {
    Animal() {
        cout << "Animal constructor" << endl;
    }

    virtual void Sound() {
        cout << "Animal sound" << endl;
    }
};
struct Dog : public Animal{
    string breed;
    Dog() {
        cout << "Dog constructor" << endl;
    }
    void Sound() {
        cout << "Dog Sound" << endl;
    }
};

void makeSound(Animal a) {
    a.Sound();
}
/*
 * 3 main parts of runtime polymorphism
 * 1. Inheritance
 * 2. References and pointers (will slice object otherwise, preventing polymorphism)
 * 3. Virtual functions
 */
int main(){
    Character c;
    Goblin g;
    Hoblin h;

    //Without virtual, all of these are Character Attack
    Battle(&c, &g); //Character Attack
    Battle(&h, &c); //Hoblin Attack
    Battle(&g, &h); //Goblin Attack

    Animal a;
    Dog d;

    makeSound(a); //Animal Sound
    /*
     * SLICING: If not passed by pointer/reference, an object is sliced, meaning it will quite
     * literally become the object parameter and discard method/attributes
     */
    makeSound(d); //Animal Sound
}