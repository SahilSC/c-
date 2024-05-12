#include <iostream>

using namespace std;

struct Widget {
    int x;
    int y;
};

struct Gibbet {
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
    //Note member-initializer-list takes precedence over class body initializations (when they are
    //initialized in the same line of declaration)


    /*
     * MEMBER INITIALIZATION LIST.
     * Instead of an instance of Character
     * setting evil and age to default values and then resetting
     * those values in the constructor, the fields are directly
     * initialized.
     *
     * NOTE:
     * 1) the initializer lists executes in the order set by the
     * order of fields in the class
     * 2) References & consts should be initialized here.
     */
    Character(bool evil, int age) : evil(evil), age(age) {};

    /*
     * DELEGATING CONSTRUCTOR
     * Calls another constructor in the same class
     * NOTE:
     * 1) cannot add other items to member initializer list after
     */
    Character(bool evil) : Character(evil, 9999) {};

};

int main() {
    /*
     * DEFAULT INITIALIZATION
     */
    Widget w;
    cout << w.x; //junk

    /*
     * UNIFORM INITIALIZATION/BRACE INITIALIZATION
     */
    int pi{3};

    /*
     * DIRECT INITIALIZATION
     */
    Character sam(false, 10);
    //braces prevent type conversion
    Character samantha{false, 10};

    /*
     * COPY INITIALIZATION
     */
    Character sammy = sam;

    /*
     * COPY-LIST INITIALIZATION
     */
    //same as Character sage{false, 10} except no EXPLICIT constructor
    Character sage = {false, 10};

    /*
     * AGGREGATE INITIALIZATION
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

