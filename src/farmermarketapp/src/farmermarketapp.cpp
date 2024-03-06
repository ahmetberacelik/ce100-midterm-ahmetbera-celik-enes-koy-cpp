/**
 * @file farmermarketapp.cpp
 * @brief A simple program to demonstrate the usage of the farmermarket model class.
 *
 * This program process infix notations and calculate operations
 *
 */
 // Standard Libraries
#include <iostream>
#include "../../farmermarket/header/farmermarket.h"

int main() {
    const char* filename = "Users.bin";
    User user1 = { "Ahmet Bera Celik", "qwerty" };   
    saveUser(&user1, filename);
    User user2 = { "Enes Koy", "123456" };
    saveUser(&user2, filename);
    User user3 = { "Ugur Coruh", "asdasd" };
    saveUser(&user3, filename);
    if (userAuthentication(std::cin, std::cout))
    {
        mainMenu(std::cin, std::cout);
    }
    else
    {
        return 0;
    } 
}
