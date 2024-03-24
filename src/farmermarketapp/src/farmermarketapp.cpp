/**
 * @file farmermarketapp.cpp
 * @brief A simple program to demonstrate the usage of the farmermarket model class.
 *
 * This program calls userAuthentication and mainMenu functions.
 *
 */
#include <stdio.h>
#include "../../farmermarket/header/farmermarket.h"
 /**
  * @brief The main function of the program.
  *
  * This function initiates the user authentication process and displays the main menu based on the authentication result.
  *
  * @return 0 indicating successful execution of the program.
  */
int main() {
    bool authenticationResult = userAuthentication();
    mainMenu(authenticationResult);
    return 0;
}
