#include <iostream>

using namespace std;

struct Widget{
    int x;
    int y;
};

struct Gibbet{
    /*
     * In the case fields are not set,
     * objects are initialized through default constructor,
     * primitives are not initialized (junk at their memory).
     */
    Widget w;
    int x;

    Gibbet() {}
};

struct Character {
    bool evil;
    int age;
    //int age{7} is the same as putting age(7) in the default constructor member initializer list
    //Note member-initializer-list takes precedence over class body initializations

    /*
     * Member initialization list.
     * Instead of an instance of Character
     * setting evil and age to default values and then resetting
     * those values in the constructor, the fields are directly
     * initialized.
     *
     * NOTE: the initializer lists executes in the order set by the
     * order of fields in the class
     *
     * References & consts should be initialized here.
     */
    Character(bool evil, int age) : evil(evil), age(age){};
};

int main() {
    /*
     * Default initialization
     */
    Widget w;
    cout << w.x; //junk


    /*
     * Uniform Initialization/Brace initialization
     */
    int pi{3};

    /*
     * Direct initialization
     */
    Character sam(false, 10);
    //braces prevent type conversion
    Character samantha{false, 10};

    /*
     * Copy initialization
     */
    Character sammy = sam;

    /*
     * Copy-list initialization
     */
    //same as Character sage{false, 10} except no EXPLICIT constructor
    Character sage = {false, 10};

    /*
     * Aggregate initialization
     */
    //if no constructors explicitly defined, can use {...} to define fields in order
    Widget myWidget{1, 3};

    /*
     * EXTRA NOTES
     */

    /*
     * MOST VEXING PARSE
     * Not allowed to call default constructor
     * because interpreted as function declaration
     * like int stuff();
     */
    //Widget w();
}

