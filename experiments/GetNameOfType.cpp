//
// Created by consent_ on 07/06/25.
//

#include <iostream>
#include <vector>

class Foo{};
class Bar{};

int main() {
    Foo foo;
    if (typeid(Foo) == typeid(foo)) {
        std::cout << typeid(Foo).name() << std::endl;
        std::cout << typeid(Bar).name() << std::endl;
        std::cout << typeid(foo).name() << std::endl;
        std::cout << typeid(std::cout).name() << std::endl;
        std::cout << typeid(std::vector<Foo>).name() << std::endl;
        std::cout << typeid(std::vector<int>).name() << std::endl;
    }
}