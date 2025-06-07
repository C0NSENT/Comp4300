//
// Created by consent_ on 07/06/25.
//

#include <vector>
#include <iostream>
#include <memory>

class Base {
};

class DerivedA : public Base {
public:
    int num;

    DerivedA(int num) : num(num) {}
    int getA() const { return num; }
};

class DerivedB : Base {
public:
    int num;

    DerivedB(int num) : num(num) {}
    int getA() const { return num; }
};

class DerivedC : Base {
public:
    int num;

    DerivedC(int num) : num(num) {}
    int getA() const { return num; }
};

int main() {
    /*std::vector<Base*> vec;
    Base* ptr;
    DerivedA derivedObj(1);

    ptr = new DerivedA(1);
    vec.push_back(new DerivedA(1));
    vec.push_back(ptr);

    std::cout << static_cast<DerivedA*>(ptr)->getA();*/

    std::vector<std::unique_ptr<Base>> vec;
    vec.push_back(std::make_unique<DerivedA>(1));
    std::cout << std::dynamic_pointer_cast<DerivedA>>vec[0]->getA() << std::endl;
}