/**
 * @file farmermarket.h
 *
 * @brief Provides functions definations.
 */
#ifndef FARMERMARKET_H
#define FARMERMARKET_H
#include <stdio.h>
#define MAX_SIZE 100
#define N 4
typedef struct {
    char username[50];
    char password[50];
} User;
typedef struct {
    int price;
    char* name;
    char* season;
} ProductSeason;

typedef struct {
    ProductSeason items[MAX_SIZE];
    int size;
} MinHeap;

void clearScreen();

bool mainMenu(bool authenticationResult);

int saveUser(const User* user, const char* filename);

int authenticateUser(const char* username, const char* password, const char* filename);

bool userAuthentication();

bool swap(char** a, char** b);

int partition(char* arr[], int low, int high);

bool quickSort(char* arr[], int low, int high);

int binarySearch(char* arr[], int l, int r, char* x);

bool searchAndPrintResult(char* arr[], int size, char* x);

bool browseVendor();

bool searchProduct();

bool listingOfInfos();

void initMinHeap(MinHeap* heap);

void insertMinHeap(MinHeap* heap, ProductSeason item);

ProductSeason removeMin(MinHeap* heap);

int saveProductSeason(const ProductSeason* productSeason, int numProducts, const char* filename);

int loadProductSeasonsAndPrint(const char* filename, const char* selectedSeason);

bool seasonalProduceGuide();

int lcs(char* X, char* Y, int m, int n);

bool compareAndPrintLCS(char* season1, char* season2, char* name1, char* name2, int price);

int max(int a, int b);

int knapsack(int W, int wt[], int val[], int n, int* selectedItems);

bool suggestPurchases(int budget);

bool CompareProducts();

bool BuyProducts(int local_budget);

bool PurchasingTransactionsAndPriceComparison(bool localGuestMode);

void recursiveMatrixMultiply(int A[N][N], int B[N][N], int C[N][N], int rowA, int colA, int rowB, int colB, int size);

void initializeDP();

int MCM_MemorizedRecursive(int dimensions[], int i, int j);

int MCM_DynamicProgramming(int dimensions[], int n);

bool MarketInformations();
#endif // FARMERMARKET_H