/**
 * @file farmermarket.h
 * 
 * @brief Provides functions
 */
#ifndef FARMERMARKET_H
#define FARMERMARKET_H
#include <iostream>

typedef struct {
    char username[50];
    char password[50];
} User;

bool mainMenu(std::istream& in, std::ostream& out);

int saveUser(const User* user, const char* filename);

int authenticateUser(const char* username, const char* password, const char* filename);

bool userAuthentication(std::istream& in, std::ostream& out);
#endif // FARMERMARKET_H