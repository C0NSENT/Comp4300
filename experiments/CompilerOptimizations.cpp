//
// Created by consent_ on 15/05/25.
//

#include <iostream>

 class Aboba
 {
 public:
 	Aboba() {std::cout << "Default" << std::endl; }
 	Aboba(const Aboba &other) {std::cout << "Copy" << std::endl; }
 };

Aboba createObj() {return Aboba{};}

int main()
{
	Aboba obj = createObj();
}