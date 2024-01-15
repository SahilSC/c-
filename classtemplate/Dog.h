#pragma once
#include <string>
#include <memory>
struct Bone{
    int hunger{20};
};
class Dog {
private:
    std::string name;
    int age;
    double weight;
    int* generation_ptr;
public:
    static int counter;
    Dog();
    ~Dog();
    Dog(const Dog& other);
    Dog(Dog&& other);

    Dog& operator=(const Dog& other);
    Dog& operator=(Dog&& other);
    friend std::ostream& operator<<(std::ostream& os, const Dog& other);

};


