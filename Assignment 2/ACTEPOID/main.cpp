//
// Created by consent_ on 20/05/25.
//

#include "Vector2.tpp"
#include "Logger.hpp"
#include <unistd.h>

#include <iostream>
#include "Components.hpp"
#include "Entity.hpp"

#include "SFML/System/Vector2.hpp"

#include <array>
#include <unordered_map>
#include <iostream>
#include <vector>

int main()
{
    /*std::unordered_map<int, int> um;

    for (auto i = 0; i < 2000; i++) {
        std::cout << um.size() << " " << um.bucket_count() << "\n";
        um.insert({i , i});
    }*/

    /*std::vector<lrh::Component*>  TiPutin;
    TiPutin.push_back(new lrh::CCollision(2));


    std::cout << static_cast<lrh::CCollision*>(TiPutin.at(0))->radius;*/

    lrh::Entity gay(32);
    gay.addComponent<lrh::CCollision>(lrh::CCollision{2});

    std::cout << gay.hasComponent<lrh::CCollision>() << std::endl;
    std::cout << gay.hasComponent<lrh::CTransform>() << std::endl;

    std::cout << typeid(gay.getComponent<lrh::CTransform>()).name() << std::endl;

    std::cout << gay.getComponent<lrh::CLifespan>()->remaining;

}

