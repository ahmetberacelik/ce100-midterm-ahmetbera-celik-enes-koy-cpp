/**
 * @file farmermarket.h
 * 
 * @brief Provides functions
 */
#ifndef FARMERMARKET_H
#define FARMERMARKET_H
#include <stdio.h>
typedef struct {
    char username[50];
    char password[50];
} User;

bool mainMenu(FILE* in, FILE* out);

int saveUser(const User* user, const char* filename);

int authenticateUser(const char* username, const char* password, const char* filename);

bool userAuthentication(FILE* in, FILE* out);

bool swap(char** a, char** b);

int partition(char* arr[], int low, int high);

bool quickSort(char* arr[], int low, int high);

int binarySearch(char* arr[], int l, int r, char* x);

bool searchAndPrintResult(char* arr[], int size, char* x);

bool listingOfInfos(FILE* in, FILE* out);
#endif // FARMERMARKET_H