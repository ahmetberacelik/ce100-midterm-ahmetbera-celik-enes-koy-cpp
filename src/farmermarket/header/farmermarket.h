/**
 * @file farmermarket.h
 *
 * @brief Provides functions definations.
 */
#ifndef FARMERMARKET_H
#define FARMERMARKET_H
#include <stdio.h>
#define MAX_SIZE 100 /**< Define the constant MAX_SIZE as 100, indicating the maximum size of arrays or matrices. */
#define N 4 /**< Define the constant N as 4, representing the size of arrays or matrices. */
 /**
  * @brief Struct representing a user with username and password fields.
  *
  * This struct stores user information including username and password.
  */
typedef struct {
    char username[50]; /**< Username of the user. */
    char password[50]; /**< Password of the user. */
} User;
/**
 * @brief Struct representing a product with price, name, and season fields.
 *
 * This struct stores information about a product including its price, name, and season.
 */
typedef struct {
    int price; /**< Price of the product. */
    char* name; /**< Name of the product. */
    char* season; /**< Season associated with the product. */
} ProductSeason;
/**
 * @brief Struct representing a min heap of product seasons.
 *
 * This struct implements a min heap data structure to store product seasons.
 */
typedef struct {
    ProductSeason items[MAX_SIZE]; /**< Array of ProductSeason items representing the heap elements. */
    int size; /**< Current size of the heap. */
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