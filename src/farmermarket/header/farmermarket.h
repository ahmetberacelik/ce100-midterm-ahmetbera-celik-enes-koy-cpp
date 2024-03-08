/**
 * @file farmermarket.h
 * 
 * @brief Provides functions
 */
#ifndef FARMERMARKET_H
#define FARMERMARKET_H

typedef struct {
    char username[50];
    char password[50];
} User;

bool mainMenu();

int saveUser(const User* user, const char* filename);

int authenticateUser(const char* username, const char* password, const char* filename);

bool userAuthentication();
#endif // FARMERMARKET_H