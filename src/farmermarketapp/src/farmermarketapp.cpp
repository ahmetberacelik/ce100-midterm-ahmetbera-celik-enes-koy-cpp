/**
 * @file farmermarketapp.cpp
 * @brief A simple program to demonstrate the usage of the farmermarket model class.
 *
 * This program process infix notations and calculate operations
 *
 */
 // Standard Libraries
#include <stdio.h>
#include "../../farmermarket/header/farmermarket.h"

int main() {
    bool authenticationResult = userAuthentication();
    mainMenu(authenticationResult);
    return 0;
}
