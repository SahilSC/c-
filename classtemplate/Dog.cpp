#include "Dog.h"
#include <iostream>

int Dog::counter = 0;

/**
 * Default constructor; C++ adds default by default if no user-defined constructor. (deleted
 * if using unique_pointers)
 */
Dog::Dog() : name("Unnamed"), age(-1), weight(-1), generation_ptr(new int(0)) {
    std::cout << "Constructor for called." << std::endl;
}

/**
 * Destructor.
 * Provided by default by compiler if no user-defined destructor
 * It calls the destructor for each member field (eg. a char arr[] field would be automatically
 * destructed). The issue is with pointers (e.g. int*), as the ptr, not *ptr, is destructed,
 * causing memory leak.
 */
Dog::~Dog() {
    std::cout << "Destructor called." << std::endl;
}

/**
 * Copy constructor.
 * Provided: by default by compiler and automatically shallow copies each field.
 * Not provided:
 *  - if no user-defined move constructor/assignment
 *  - if any field has a deleted copy ctor (e.g. unique_ptr)
 *
 * Issue will arise if you need a deep copy (e.g. you want to copy a pointer's pointed-to data).
 * Parameter is reference, otherwise infinite loop is caused when copying into parameter.
 * @param other the parameter to copy
 */
Dog::Dog(const Dog &other) {
    std::cout << "Copy constructor for called." << std::endl;
    age = other.age;
    weight = other.weight;
    name = other.name;
    generation_ptr = new int(*other.generation_ptr);
}

/**
 * Copy assignment operator.
 * Provided by default by compiler if no user-defined move constructor/assignment
 * and automatically shallow copies each field (deletes if unique pointer is used)
 * Copy assignment, copy constructor, destructor = rule of 3.
 * @param other the object to copy.
 * @return the current object
 */
Dog& Dog::operator=(const Dog &other) {
    /*
     * This is important if, for example, you have a class that creates an array of integers
     * int* a = new int[10].
     * If you delete the current array in the copy constructor, self assignment fails.
     */
    if (&other == this) {
        std::cout << "Copy assignment called on same object." << std::endl;
        return *this;
    }
    std::cout << "Copy assignment called." << std::endl;
    age = other.age;
    weight = other.weight;
    name = other.name;
    generation_ptr = new int(*other.generation_ptr);
    return *this;
}

/**
 * Move constructor.
 * Provided by default by compiler if no user-defined copy constructor, copy assignment, destructor,
 * and move constructor is valid.
 * Copies the resources from other.
 * @param other the Dog object to pillage resources from
 */
Dog::Dog(Dog&& other) {
    std::cout << "Move constructor called." << std::endl;
    age = other.age;
    weight = other.weight;
    name = other.name;
    generation_ptr = other.generation_ptr;
    other.generation_ptr = nullptr;
}

/**
 * Move assignment.
 * Provided by default by compiler if no user-defined copy constructor, copy assignment, destructor,
 * and move constructor is valid.
 * Rule of 5 = previous 5 things (copy assignment, copy constructor, destructor, move assignment,
 * move constructor).
 * Prevents copies by noticing if the object is an R-value, in which case this operator is matched
 * and resources are pillaged.
 * @param other the Dog object that is an R value.
 * @return reference to this Dog object.
 */
Dog& Dog::operator=(Dog&& other) {
    std::cout << "Move assignment called." << std::endl;
    age = other.age;
    weight = other.weight;
    name = other.name;
    generation_ptr = other.generation_ptr;
    other.generation_ptr = nullptr;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Dog& other) {
    os << other.name << " is " << other.age << " years old. He weighs " << other.weight <<
    " pounds and his generation is " << *other.generation_ptr << ".";
    return os;
}