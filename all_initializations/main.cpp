#include <iostream>

using namespace std;

struct Character {
    bool evil;
    int age;

    /*
     * Member initialization list.
     * Instead of an instance of Character
     * setting evil and age to default values and then resetting
     * those values in the constructor, the fields are directly
     * initialized.
     */
    Character(bool evil, int age) : evil(evil), age(age){};
};

int main() {
    Character a{true, 19};
}