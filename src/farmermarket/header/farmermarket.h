/**
 * @file farmermarket.h
 * 
 * @brief Provides functions
 */
#ifndef FARMERMARKET_H
#define FARMERMARKET_H
#include <stdio.h>
#define MAX_SIZE 100
typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    int id;
    char* name;
    char* season;
} ProductSeason;

typedef struct {
    ProductSeason items[MAX_SIZE];
    int size;
} MinHeap;

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

void initMinHeap(MinHeap* heap);

void insertMinHeap(MinHeap* heap, ProductSeason item);

ProductSeason removeMin(MinHeap* heap);

int saveProductSeason(const ProductSeason* productSeason, int numProducts, const char* filename);

int loadProductSeasonsAndPrint(FILE* in, FILE* out, const char* filename, const char* selectedSeason);

bool seasonalProduceGuide(FILE* in, FILE* out);
#endif // FARMERMARKET_H