#include "Dog.h"
#include <iostream>

int Dog::counter = 0;

/**
 * Default constructor; C++ adds default by default if no user-specified constructor.
 */
Dog::Dog() : name("Unnamed"), age(-1), weight(-1), generation_ptr(new int(0)) {
    std::cout << "Constructor for called." << std::endl;
}

/**
 * Destructor.
 * C++ creates one by default. It calls the destructor for each member field (eg. a char arr[]
 * field would be automatically destructed). The issue is with pointers (e.g. int*), as the ptr,
 * not *ptr, is destructed, causing memory leak.
 */
Dog::~Dog() {
    std::cout << "Destructor called." << std::endl;
}

/**
 * Copy constructor.
 * Provided by default by compiler and automatically shallow copies each field.
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
 * Copy assignment, copy constructor, destructor = rule of 3.
 * @param other the object to copy.
 * @return the current object
 */
Dog& Dog::operator=(const Dog &other) {
    std::cout << "Copy assignment called." << std::endl;
    age = other.age;
    weight = other.weight;
    name = other.name;
    generation_ptr = new int(*other.generation_ptr);
    return *this;
}

/**
 * Move constructor.
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