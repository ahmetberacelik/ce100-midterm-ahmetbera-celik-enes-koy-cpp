/**
 * @file farmermarket.cpp
 *
 * @brief The functions are filled in this file.
 */
#include "../header/farmermarket.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <climits>
#define N 4 /**< Define the constant N as 4, representing the size of arrays or matrices. */
#define MAX_SIZE 100 /**< Define the constant MAX_SIZE as 100, indicating the maximum size of arrays or matrices. */
int dp[MAX_SIZE][MAX_SIZE]; /**< Declare a 2D array dp with dimensions MAX_SIZE x MAX_SIZE for dynamic programming purposes. */
bool guestMode = false; /**< Boolean variable to indicate whether the program is in guest mode (false by default). */
int budget; /**< Variable to store the budget value. */
char* vendors[] = { "Ahmet", "Mehmet", "Veli", "Ayse" }; /**< Array of strings representing vendor names. */
/**
 * @brief Array containing information about vendors and the products they offer.
 *
 * This two-dimensional array holds information about vendors and the products they offer.
 * Each row represents a vendor, where the first element is the vendor's name, and the subsequent elements are the names of the products they offer.
 *
 * The information is organized as follows:
 * - Row 0: Vendor "Ahmet" offers products "Banana", "Apple", "Grape", and "Spinach".
 * - Row 1: Vendor "Mehmet" offers products "Raspberry", "Beet", "Turnip", and "Peas".
 * - Row 2: Vendor "Veli" offers products "Cucumber", "Tomato", "Orange", and "Radish".
 * - Row 3: Vendor "Ayse" offers products "Pear", "Nectarine", "Bean", and "Hazelnut".
 *
 * @note Each product name is represented as a string.
 */
char* products[][5] = {
    {"Ahmet", "Banana", "Apple", "Grape", "Spinach"},
    {"Mehmet", "Raspberry", "Beet", "Turnip", "Peas"},
    {"Veli", "Cucumber", "Tomato", "Orange", "Radish"},
    {"Ayse", "Pear", "Nectarine", "Bean", "Hazelnut"},
};
/**
 * @brief Array containing information about various products including their prices, names, and seasons.
 *
 * This array holds structs representing different products, each containing the price, name, and season of the product.
 * The information is organized as follows:
 * - Index 0-3: Products available in Summer.
 * - Index 4-7: Products available in Fall.
 * - Index 8-11: Products available in Winter.
 * - Index 12-15: Products available in Spring.
 *
 * @note Each product is represented by a struct of type ProductSeason.
 */
ProductSeason productSeasons[] = {
    {10,"Banana", "Summer"},
    {10,"Apple", "Fall"},
    {15, "Grape", "Fall"},
    {30,"Spinach", "Spring"},

    {15,"Raspberry", "Summer"},
    {20,"Beet", "Fall"},
    {25, "Turnip", "Winter"},
    {30, "Peas", "Spring"},

    {25, "Cucumber", "Summer"},
    {30,"Tomato", "Summer"},
    {30, "Orange", "Winter"},
    {15,"Radish", "Spring"},

    {35, "Pear", "Fall"},
    {35,"Nectarine", "Summer"},
    {40, "Bean", "Summer"},
    {40, "Hazelnut", "Fall"},
};
/**
 * @brief 2D array representing the prices of products.
 *
 * This 2D array represents the prices of products, where each row corresponds to a product and each column corresponds to a vendor.
 * For example, productPrices[i][j] represents the price of product i sold by vendor j.
 *
 * The information is organized as follows:
 * - Row 0: Prices of products offered by vendor "Ahmet" (from the products array).
 * - Row 1: Prices of products offered by vendor "Mehmet" (from the products array).
 * - Row 2: Prices of products offered by vendor "Veli" (from the products array).
 * - Row 3: Prices of products offered by vendor "Ayse" (from the products array).
 *
 * @note Each element represents the price of a product and is of type integer.
 */
int productPrices[4][4] = {
        {10, 10, 15, 30},
        {15, 20, 25, 30},
        {25, 30, 30, 15},
        {35, 35, 40, 40},
};
/**
 * @brief 2D array representing the quantities of products.
 *
 * This 2D array represents the quantities of products available, where each row corresponds to a product and each column corresponds to a vendor.
 * For example, productQuantities[i][j] represents the quantity of product i sold by vendor j.
 *
 * The information is organized as follows:
 * - Row 0: Quantities of products offered by vendor "Ahmet" (from the products array).
 * - Row 1: Quantities of products offered by vendor "Mehmet" (from the products array).
 * - Row 2: Quantities of products offered by vendor "Veli" (from the products array).
 * - Row 3: Quantities of products offered by vendor "Ayse" (from the products array).
 *
 * @note Each element represents the quantity of a product and is of type integer.
 */
int productQuantities[4][4] = {
        {100, 28, 30, 50},
        {75, 27, 46, 18},
        {15, 73, 48, 24},
        {17, 43, 64, 37},
};
int numVendors = sizeof(vendors) / sizeof(vendors[0]); /**< Number of products per vendor equals the number of columns in the products array. */
int numProductsPerVendor = sizeof(products[0]) / sizeof(products[0][0]); /**< Number of products per vendor equals the number of columns in the products array. */
const int numProducts = sizeof(productSeasons) / sizeof(productSeasons[0]);/**< Total number of products in the productSeasons array. */
int dimensions[] = { 4, 4, 4 }; /**< Array representing the dimensions used for matrix multiplication, where each element corresponds to the number of rows or columns in a matrix. */
int n = sizeof(dimensions) / sizeof(dimensions[0]); /**< Number of elements in the dimensions array, which indicates the number of matrices involved in matrix multiplication. */
/**
 * @brief Clears the console screen.
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
/**
 * @brief Displays the main menu options and handles user input.
 *
 * @param authenticationResult Indicates whether the user is authenticated.
 * @return True if the user chooses to exit the program, otherwise false.
 */
bool mainMenu(bool authenticationResult) {
    if (!authenticationResult) {
        return false;
    }
    int choice;
    while (true) {
        clearScreen();
        printf("+-------------------------------------+\n");
        printf("|            MAIN MENU                |\n");
        printf("+-------------------------------------+\n");
        printf("| 1. Listing of Local Vendors         |\n");
        printf("|    and Products                     |\n");
        printf("| 2. Seasonal Produce Guide           |\n");
        printf("| 3. Price Comparison                 |\n");
        printf("| 4. Market Informations              |\n");
        printf("| 5. Exit                             |\n");
        printf("+-------------------------------------+\n");
        printf("Please select an option: ");

        if (scanf("%d", &choice) != 1) {
            getchar();
            printf("Invalid input, please enter a number.\n");
            continue;
        }
        getchar();

        switch (choice) {
        case 1:
            listingOfInfos();
            break;
        case 2:
            seasonalProduceGuide();
            break;
        case 3:
            PurchasingTransactionsAndPriceComparison(guestMode);
            break;
        case 4:
            MarketInformations();
            break;
        case 5:
            printf("Exiting program...Press enter!\n");
            getchar();
            return true;
        default:
            printf("Invalid option, please try again.\n");
            getchar();
        }
    }
}
/**
 * @brief Saves user information to a binary file.
 *
 * @param user Pointer to the User structure containing user information.
 * @param filename Name of the file to save the user information.
 * @return 1 if the user information is successfully saved, otherwise 0.
 */
int saveUser(const User* user, const char* filename) {
    FILE* file = fopen(filename, "ab");
    fwrite(user, sizeof(User), 1, file);
    fclose(file);
    return 1;
}
/**
 * @brief Authenticates a user by checking the provided username and password against stored records.
 *
 * @param username The username entered by the user.
 * @param password The password entered by the user.
 * @param filename Name of the file containing user records.
 * @return 1 if authentication is successful, -1 if the file cannot be opened, otherwise 0.
 */
int authenticateUser(const char* username, const char* password, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return -1;
    }
    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return 1;
        }
    }
}
/**
 * @brief Handles user authentication, login, registration, and guest mode selection.
 *
 * @return True if the user successfully logs in or registers, otherwise false.
 */
bool userAuthentication() {
    clearScreen();
    const char* filename = "Users.bin";
    User user1 = { "Ahmet Bera Celik", "qwerty" };
    saveUser(&user1, filename);
    User user2 = { "Enes Koy", "123456" };
    saveUser(&user2, filename);
    User user3 = { "Ugur Coruh", "asdasd" };
    saveUser(&user3, filename);

    int choice;
    int right_to_try = 3;
    char temp_username[50];
    char temp_password[50];


    while (true) {
        clearScreen();
        printf("+---------------------------+\n");
        printf("|  LOGIN AND REGISTER MENU  |\n");
        printf("+---------------------------+\n");
        printf("| 1. Login                  |\n");
        printf("| 2. Register               |\n");
        printf("| 3. Guest Mode             |\n");
        printf("| 4. Exit Program           |\n");
        printf("+---------------------------+\n");
        printf("Please select an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("Please enter your username: ");
            fgets(temp_username, 50, stdin);
            temp_username[strcspn(temp_username, "\n")] = 0;

            printf("Please enter your password: ");
            fgets(temp_password, 50, stdin);
            temp_password[strcspn(temp_password, "\n")] = 0;

            printf("Please enter your budget: ");
            scanf("%d", &budget);

            getchar();

            if (authenticateUser(temp_username, temp_password, filename) == 1) {
                printf("Welcome %s\n", temp_username);

                getchar();

                return true; }
            else {
                printf("You entered wrong username or password. Please try again.\n");
                right_to_try--;
                if (right_to_try == 0) {
                    printf("You have run out of login attempts. See you...\n");
                    getchar();
                    return false;
                }
            }
            getchar();
            break;

        case 2:
            printf("Please enter your username: ");
            fgets(temp_username, 50, stdin);
            temp_username[strcspn(temp_username, "\n")] = 0;

            printf("Please enter your password: ");
            fgets(temp_password, 50, stdin);
            temp_password[strcspn(temp_password, "\n")] = 0;

            User newUser;
            strcpy(newUser.username, temp_username);
            strcpy(newUser.password, temp_password);
            saveUser(&newUser, filename);
            clearScreen();
            printf("User registered successfully.\nWelcome %s\n", temp_username);
            printf("Your budget is 100 tl.");
            budget = 100;
            getchar();
            return true;

        case 3:
            guestMode = true;
            return true;

        case 4:
            printf("Exiting program...Press enter!\n");
            getchar();
            return false;

        default:
            printf("Invalid option, please try again.\n");
            getchar();
        }
    }
}
/**
 * @brief Swaps two pointers to strings.
 *
 * @param a Pointer to the first string pointer.
 * @param b Pointer to the second string pointer.
 * @return True if the swap is successful.
 */
bool swap(char** a, char** b) {
    char* t = *a;
    *a = *b;
    *b = t;
    return true;
}
/**
 * @brief Partitions an array of strings for quicksort.
 *
 * @param arr Array of strings.
 * @param low Starting index of the partition.
 * @param high Ending index of the partition.
 * @return The partition index.
 */
int partition(char* arr[], int low, int high) {
    char* pivot = arr[low + (rand() % (high - low))];
    int i = low - 1, j = high + 1;

    while (1) {
        do {
            i++;
        } while (strcmp(arr[i], pivot) < 0);
        do {
            j--;
        } while (strcmp(arr[j], pivot) > 0);

        if (i >= j) {
            return j;
        }
        swap(&arr[i], &arr[j]);
    }
}
/**
 * @brief Sorts an array of strings using the quicksort algorithm.
 *
 * @param arr Array of strings.
 * @param low Starting index of the array.
 * @param high Ending index of the array.
 * @return True if the sorting is successful.
 */
bool quickSort(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
    return true;
}
/**
 * @brief Performs binary search on an array of strings.
 *
 * @param arr Array of strings.
 * @param l Left index of the search range.
 * @param r Right index of the search range.
 * @param x String to search for.
 * @return The index of the found string, or -1 if not found.
 */
int binarySearch(char* arr[], int l, int r, char* x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;

        int res = strcmp(arr[mid], x);

        if (res == 0) {
            return mid;
        }

        if (res > 0) {
            return binarySearch(arr, l, mid - 1, x);
        }

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}
/**
 * @brief Searches for a string in an array of strings and prints the result.
 *
 * @param arr Array of strings.
 * @param size Size of the array.
 * @param x String to search for.
 * @return True if the string is found, otherwise false.
 */
bool searchAndPrintResult(char* arr[], int size, char* x) {
    int result = binarySearch(arr, 0, size - 1, x);
    if (result == -1) {
        return false; }
    else {
        return true;
    }
}
/**
 * @brief Searches for a vendor in the vendors array and prints the result.
 *
 * @return True if the vendor is found, otherwise false.
 */
bool browseVendor() {
    char vendor_query[50];
    printf("Please enter vendor name: ");
    fgets(vendor_query, 50, stdin);
    vendor_query[strcspn(vendor_query, "\n")] = 0;

    quickSort(vendors, 0, numVendors - 1);

    clearScreen();
    if (searchAndPrintResult(vendors, numVendors, vendor_query)) {
        printf("Vendor found: %s\n", vendor_query);
    }
    else {
        printf("Vendor not found.\n");
        return false;
    }
    return true;
}
/**
 * @brief Searches for a product in the products array and prints the result.
 *
 * @return True if the product is found, otherwise false.
 */
bool searchProduct() {
    char product_query[50];
    printf("Please enter product name: ");
    fgets(product_query, 50, stdin);
    product_query[strcspn(product_query, "\n")] = 0;

    for (int i = 0; i < numVendors; i++) {
        quickSort(products[i] + 1, 0, numProductsPerVendor - 2);
        clearScreen();
        int result = binarySearch(products[i] + 1, 0, numProductsPerVendor - 2, product_query);
        if (result != -1) {
            printf("Product %s found at vendor %s\n", product_query, products[i][0]);
            return true;
        }
    }
    printf("Product not found.\n");
    return false;
}
/**
 * @brief Displays the listing of information options and handles user input.
 *
 * @return True if the user chooses to exit, otherwise false.
 */
bool listingOfInfos() {
    clearScreen();

    int choice;
    while (true) {
        clearScreen();
        printf("+----------------------------+\n");
        printf("|   LISTING OF INFORMATIONS  |\n");
        printf("+----------------------------+\n");
        printf("| 1. Browse Vendors          |\n");
        printf("| 2. Search Product          |\n");
        printf("| 3. Exit                    |\n");
        printf("+----------------------------+\n");
        printf("Please select an option: ");
        if (scanf("%d", &choice) != 1) {
            getchar();
            printf("Invalid input, please enter a number.\n");
            getchar();
            continue;
        }
        getchar();

        switch (choice) {
        case 1:
            browseVendor();
            getchar();
            break;
        case 2:
            searchProduct();
            getchar();
            break;
        case 3:
            return true;
        default:
            printf("Invalid option, please try again.\n");
            getchar();
        }
    }
}
/**
 * @brief Initializes a min heap.
 *
 * @param heap Pointer to the min heap.
 */
void initMinHeap(MinHeap* heap) {
    heap->size = 0;
}
/**
 * @brief Inserts a product season into the min heap.
 *
 * @param heap Pointer to the min heap.
 * @param item Product season to insert.
 */
void insertMinHeap(MinHeap* heap, ProductSeason item) {
    if (heap->size == MAX_SIZE) {
        return;
    }
    int i = heap->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->items[parent].price <= item.price) break;
        heap->items[i] = heap->items[parent];
        i = parent;
    }
    heap->items[i] = item;
}
/**
 * @brief Removes and returns the minimum element from the min heap.
 *
 * @param heap Pointer to the min heap.
 * @return The minimum element in the heap.
 */
ProductSeason removeMin(MinHeap* heap) {
    ProductSeason result = heap->items[0];
    ProductSeason lastItem = heap->items[--heap->size];
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int left = i * 2 + 1, right = i * 2 + 2;
        int smallest = left;
        if (right < heap->size && heap->items[right].price < heap->items[left].price) smallest = right;
        if (lastItem.price <= heap->items[smallest].price) break;
        heap->items[i] = heap->items[smallest];
        i = smallest;
    }
    heap->items[i] = lastItem;
    return result;
}
/**
 * @brief Saves an array of product seasons to a binary file.
 *
 * @param productSeason Pointer to the array of product seasons.
 * @param numProducts Number of product seasons.
 * @param filename Name of the file to save to.
 * @return 1 if successful, otherwise 0.
 */
int saveProductSeason(const ProductSeason* productSeason, int numProducts, const char* filename) {
    FILE* file = fopen(filename, "wb");
    fwrite(&numProducts, sizeof(int), 1, file);
    fwrite(productSeason, sizeof(ProductSeason), numProducts, file);
    fclose(file);
    return 1;
}
/**
 * @brief Loads product seasons from a binary file based on the selected season and prints them.
 *
 * @param filename Name of the file to load from.
 * @param selectedSeason The selected season.
 * @return Number of product seasons found for the selected season.
 */
int loadProductSeasonsAndPrint(const char* filename, const char* selectedSeason) {
    FILE* file = fopen(filename, "rb");
    int numProducts;
    fread(&numProducts, sizeof(int), 1, file);

    MinHeap heap;
    initMinHeap(&heap);

    ProductSeason productSeason;
    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        fread(&productSeason, sizeof(ProductSeason), 1, file);
        if (strcmp(productSeason.season, selectedSeason) == 0) {
            insertMinHeap(&heap, productSeason);
            found++;
        }
    }
    fclose(file);
    while (heap.size > 0) {
        ProductSeason ps = removeMin(&heap);
        printf("|- Price: %d, Name: %s\n", ps.price, ps.name);
    }
    printf("+------------------------------------+");

    return found;
}
/**
 * @brief Displays the seasonal produce guide menu and allows the user to view available produce for different seasons.
 *
 * @return True if the function executes successfully, otherwise false.
 */
bool seasonalProduceGuide() {
    clearScreen();
    const char* filename = "ProductSeasons.bin";

    saveProductSeason(productSeasons, numProducts, filename);
    while (true) {
        clearScreen();
        printf("+------------------------------------------+\n");
        printf("|      SEASONAL PRODUCE GUIDE              |\n");
        printf("+------------------------------------------+\n");
        printf("| Select a season to see available produce:|\n");
        printf("+------------------------------------------+\n");
        printf("| 1. Spring                                |\n");
        printf("| 2. Summer                                |\n");
        printf("| 3. Fall                                  |\n");
        printf("| 4. Winter                                |\n");
        printf("| 5. Return to Main Menu                   |\n");
        printf("+------------------------------------------+\n");
        printf("Please select an option: ");

        int choice;
        scanf("%d", &choice);
        getchar();

        if (choice == 5) {
            break;
        }

        char* selectedSeason = NULL;
        switch (choice) {
        case 1: selectedSeason = "Spring"; break;
        case 2: selectedSeason = "Summer"; break;
        case 3: selectedSeason = "Fall"; break;
        case 4: selectedSeason = "Winter"; break;
        default:
            printf("Invalid option, please try again.\n");
            continue;
        }
        clearScreen();
        printf("+------------------------------------+\n");
        printf("|Available produce for %s season:\n", selectedSeason);
        printf("+------------------------------------+\n");
        loadProductSeasonsAndPrint(filename, selectedSeason);
        getchar();
    }
    return true;
}
/**
 * @brief Finds the length of the longest common subsequence (LCS) between two strings.
 *
 * @param X First string.
 * @param Y Second string.
 * @param m Length of the first string.
 * @param n Length of the second string.
 * @return Length of the LCS.
 */
int lcs(char* X, char* Y, int m, int n)
{
    int** L;
    L = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        L[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    int i, j;

    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    int result = L[m][n];

    for (int i = 0; i <= m; i++) {
        free(L[i]);
    }
    free(L);

    return result;
}
/**
 * @brief Compares two product names and prints their details if they have a common subsequence and belong to the same season.
 *
 * @param season1 Season of the first product.
 * @param season2 Season of the second product.
 * @param name1 Name of the first product.
 * @param name2 Name of the second product.
 * @param price Price of the products.
 * @return True if the comparison and printing are successful, otherwise false.
 */
bool compareAndPrintLCS(char* season1, char* season2, char* name1, char* name2, int price)
{
    int m = strlen(name1);
    int n = strlen(name2);

    int lcsLength = lcs(name1, name2, m, n);

    if (lcsLength > 0 && strcmp(season1, season2) == 0) {
        printf("|- Name 1: %s, Name 2: %s, Price: %d\n", name1, name2, price);
    }
    return true;
}
/**
 * @brief Returns the maximum of two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return The maximum of the two integers.
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}
/**
 * @brief Solves the 0/1 knapsack problem to maximize the value of items selected within a given weight constraint.
 *
 * @param W The maximum weight that can be carried.
 * @param wt[] An array containing the weights of the items.
 * @param val[] An array containing the values of the items.
 * @param n The number of items.
 * @param selectedItems An array to store which items are selected (1 for selected, 0 for not selected).
 * @return The maximum value that can be achieved.
 */
int knapsack(int W, int wt[], int val[], int n, int* selectedItems) {
    int i, w;
    int** K = (int**)malloc((n + 1) * sizeof(int*));
    for (i = 0; i <= n; i++) {
        K[i] = (int*)malloc((W + 1) * sizeof(int));
    }

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int res = K[n][W];

    w = W;
    for (i = n; i > 0 && res > 0; i--) {
        if (res == K[i - 1][w])
            continue;
        else {
            selectedItems[i - 1] = 1;
            res = res - val[i - 1];
            w = w - wt[i - 1];
        }
    }

    for (i = 0; i <= n; i++) {
        free(K[i]);
    }
    free(K);

    return res;
}
/**
 * @brief Solves the 0/1 knapsack problem to suggest purchases maximizing value within a given budget.
 *
 * @param budget The available budget.
 * @return True if suggestions are successfully printed, otherwise false.
 */
bool suggestPurchases(int budget) {
    int wt[numProducts];
    int val[numProducts];
    for (int i = 0; i < numProducts; i++) {
        wt[i] = productSeasons[i].price;
        val[i] = 1;
    }

    int* selectedItems = (int*)calloc(numProducts, sizeof(int));

    int maxValue = knapsack(budget, wt, val, numProducts, selectedItems);
    printf("+----------------------------------------------------+\n");
    printf("|Your budget: %d|\n", budget);
    printf("+----------------------------------------------------+\n");
    printf("|Suggested purchases to maximize value within budget:|\n");
    printf("+----------------------------------------------------+\n");
    bool anySelected = false;
    for (int i = 0; i < numProducts; i++) {
        if (selectedItems[i] == 1) {
            printf("|- %s for %d\n", productSeasons[i].name, productSeasons[i].price);
            anySelected = true;
        }
    }
    if (!anySelected) {
        printf("+----------------------------------------------------+\n");
        printf("No products suggested. Increase your budget or check back later for different options.\n");
        free(selectedItems);
        return false;
    }
    printf("+----------------------------------------------------+\n");
    free(selectedItems);
    return true;
}
/**
 * @brief Compares products in the same price range within a selected season and prints their details.
 *
 * @return True if the comparison and printing are successful, otherwise false.
 */
bool CompareProducts() {
    bool validSeason = false;
    bool found = false;
    printf("Enter a season: ");
    char selectedSeason[50];
    fgets(selectedSeason, sizeof(selectedSeason), stdin);
    selectedSeason[strcspn(selectedSeason, "\n")] = '\0';

    for (int i = 0; i < sizeof(productSeasons) / sizeof(productSeasons[0]); i++) {
        if (strcmp(productSeasons[i].season, selectedSeason) == 0) {
            validSeason = true;
        }
    }
    if (!validSeason) {
        printf("Invalid season. Please enter a valid season.\n");
        getchar();
        return false;
    }
    printf("+-----------------------------------------------------+\n");
    printf("|Products at the same price as %s season products:\n", selectedSeason);
    printf("+-----------------------------------------------------+\n");
    for (int i = 0; i < sizeof(productSeasons) / sizeof(productSeasons[0]); i++)
    {
        if (strcmp(productSeasons[i].season, selectedSeason) == 0)
        {
            for (int j = i + 1; j < sizeof(productSeasons) / sizeof(productSeasons[0]); j++)
            {
                if (productSeasons[i].price == productSeasons[j].price)
                {
                    compareAndPrintLCS(selectedSeason, productSeasons[i].season, productSeasons[i].name, productSeasons[j].name, productSeasons[i].price);

                    found = true;
                }
            }
        }
    }
    printf("+-----------------------------------------------------+\n");
    return true;
}
/**
 * @brief Simulates a purchasing transaction by allowing the user to buy products within a specified budget.
 *
 * @param localBudget The current budget of the user.
 * @return True if the purchase is successful, otherwise false.
 */
bool BuyProducts(int localBudget) {
    bool productFound = false;
    int productPrice = 0;
    char* vendorName = NULL;
    char productQuery[50];
    printf("Please enter the product name you wish to buy: ");
    fgets(productQuery, 50, stdin);
    productQuery[strcspn(productQuery, "\n")] = 0;

    for (int i = 0; i < numProducts; i++) {
        if (strcmp(productSeasons[i].name, productQuery) == 0) {
            productFound = true;
            productPrice = productSeasons[i].price;

            for (int j = 0; j < sizeof(products) / sizeof(products[0]); j++) {
                for (int k = 1; k < sizeof(products[j]) / sizeof(products[j][0]); k++) {
                    if (strcmp(products[j][k], productQuery) == 0) {
                        vendorName = products[j][0];
                        break; } }
                if (vendorName != NULL) break; }
            break;
        }
    }

    if (!productFound) {
        printf("Product not found. Please ensure the product name is spelled correctly.\n");
        return false; }
    else if (localBudget < productPrice) {
        printf("Insufficient budget to buy %s from %s. Your current budget is %d.\n", productQuery, vendorName, localBudget);
        return false; }
    else {
        localBudget -= productPrice;
        budget = localBudget;
        printf("You have successfully purchased %s for %d from %s. Remaining budget: %d.\n", productQuery, productPrice, vendorName, localBudget);
    }
    return true;
}
/**
 * @brief Displays a menu for purchasing transactions and price comparison, allowing users to perform various actions.
 *
 * @param localGuestMode Indicates if the user is in guest mode or not.
 * @return True if the function executes successfully, otherwise false.
 */
bool PurchasingTransactionsAndPriceComparison(bool localGuestMode) {
    clearScreen();
    int choice;
    while (true) {
        clearScreen();
        printf("+----------------------------------+\n");
        printf("|  PURCHASING AND PRICE COMPARISON |\n");
        printf("+----------------------------------+\n");
        printf("| 1. Shopping Suggestion           |\n");
        printf("| 2. Compare Products              |\n");
        printf("| 3. Buy Products                  |\n");
        printf("| 4. Exit                          |\n");
        printf("+----------------------------------+\n");
        printf("Please select an option: ");
        if (scanf("%d", &choice) != 1) {
            getchar();
            printf("Invalid input, please enter a number.\n");
            continue;
        }
        getchar();
        switch (choice) {
        case 1:
            clearScreen();
            if (localGuestMode)
            {
                printf("You can not take suggestion in guest mode.\n");
                getchar();
                break; }
            else {
                suggestPurchases(budget);
            }
            getchar();
            break;
        case 2:
            clearScreen();
            CompareProducts();
            getchar();
            break;
        case 3:
            clearScreen();
            if (localGuestMode)
            {
                printf("You can not buy product in guest mode.\n");
                getchar();
                break; }
            else
            {
                BuyProducts(budget);
            }
            getchar();
            break;
        case 4:
            return true;
        default:
            printf("Invalid option, please try again.\n");
            getchar();
        }
    }
}
/**
 * @brief Recursively multiplies two matrices A and B to produce matrix C.
 *
 * This function recursively multiplies two matrices A and B to produce matrix C using the
 * Strassen's algorithm for matrix multiplication.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 * @param C The resulting matrix.
 * @param rowA The starting row index of matrix A.
 * @param colA The starting column index of matrix A.
 * @param rowB The starting row index of matrix B.
 * @param colB The starting column index of matrix B.
 * @param size The size of the matrices.
 */
void recursiveMatrixMultiply(int A[N][N], int B[N][N], int C[N][N], int rowA, int colA, int rowB, int colB, int size) {
    if (size == 1) {
        C[rowA][colB] += A[rowA][colA] * B[rowB][colB];
    }
    else {
        int newSize = size / 2;
        // Top-left
        recursiveMatrixMultiply(A, B, C, rowA, colA, rowB, colB, newSize);
        recursiveMatrixMultiply(A, B, C, rowA, colA + newSize, rowB + newSize, colB, newSize);

        // Top-right
        recursiveMatrixMultiply(A, B, C, rowA, colA, rowB, colB + newSize, newSize);
        recursiveMatrixMultiply(A, B, C, rowA, colA + newSize, rowB + newSize, colB + newSize, newSize);

        // Bottom-left
        recursiveMatrixMultiply(A, B, C, rowA + newSize, colA, rowB, colB, newSize);
        recursiveMatrixMultiply(A, B, C, rowA + newSize, colA + newSize, rowB + newSize, colB, newSize);

        // Bottom-right
        recursiveMatrixMultiply(A, B, C, rowA + newSize, colA, rowB, colB + newSize, newSize);
        recursiveMatrixMultiply(A, B, C, rowA + newSize, colA + newSize, rowB + newSize, colB + newSize, newSize);
    }
}
/**
 * @brief Initializes the dynamic programming table used for memorization in matrix chain multiplication.
 *
 * This function initializes the dynamic programming table used for memorization in matrix chain multiplication.
 */
void initializeDP() {
    memset(dp, -1, sizeof(dp));
}
/**
 * @brief Finds the minimum cost of matrix chain multiplication using memorization.
 *
 * This function finds the minimum cost of matrix chain multiplication using memorization technique.
 *
 * @param dimensions An array containing the dimensions of the matrices.
 * @param i The starting index of the matrix chain.
 * @param j The ending index of the matrix chain.
 * @return The minimum cost of matrix chain multiplication.
 */
int MCM_MemorizedRecursive(int dimensions[], int i, int j) {
    if (i == j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    dp[i][j] = INT_MAX;
    for (int k = i; k < j; k++) {
        int count = MCM_MemorizedRecursive(dimensions, i, k) + MCM_MemorizedRecursive(dimensions, k + 1, j) + dimensions[i - 1] * dimensions[k] * dimensions[j];
        if (count < dp[i][j]) {
            dp[i][j] = count;
        }
    }
    return dp[i][j];
}
/**
 * @brief Finds the minimum cost of matrix chain multiplication using dynamic programming.
 *
 * This function finds the minimum cost of matrix chain multiplication using dynamic programming.
 *
 * @param dimensions An array containing the dimensions of the matrices.
 * @param n The number of matrices.
 * @return The minimum cost of matrix chain multiplication.
 */
int MCM_DynamicProgramming(int dimensions[], int n) {
    int** dp = new int* [n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[n];
    }

    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    for (int chainLength = 2; chainLength < n; chainLength++) {
        for (int i = 1; i < n - chainLength + 1; i++) {
            int j = i + chainLength - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int count = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (count < dp[i][j])
                    dp[i][j] = count;
            }
        }
    }
    int result = dp[1][n - 1];

    for (int i = 0; i < n; ++i) {
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}
/**
 * @brief Provides market information such as total income and minimum multiplication cost.
 *
 * This function provides market information such as total income and the minimum multiplication cost
 * of matrix chain multiplication used in calculating total income.
 *
 * @return True if the operation is successful, false otherwise.
 */
bool MarketInformations() {
    clearScreen();
    int choice;

    while (true) {
        clearScreen();
        printf("+------------------------------------------------+\n");
        printf("|             MARKET INFORMATIONS                |\n");
        printf("+------------------------------------------------+\n");
        printf("| 1. Market's Total Income Information           |\n");
        printf("| 2. The Minimum Multiplication Cost Information |\n");
        printf("| 3. Exit                                        |\n");
        printf("+------------------------------------------------+\n");
        printf("Please select an option: ");
        if (scanf("%d", &choice) != 1) {
            getchar();
            printf("Invalid input, please enter a number.\n");
            continue;
        }
        getchar();
        int totalIncome = 0;
        int C[N][N] = { 0 };
        initializeDP();
        int minMultiplicationCostMemorizedRecursive = MCM_MemorizedRecursive(dimensions, 1, n - 1);
        int minMultiplicationCostDynamicProgramming = MCM_DynamicProgramming(dimensions, n);
        switch (choice) {
        case 1:
            recursiveMatrixMultiply(productPrices, productQuantities, C, 0, 0, 0, 0, N);

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    totalIncome += C[i][j];
                }
            }

            printf("Market's Total Product Price: %d\n", totalIncome);
            getchar();
            break;
        case 2:
            printf("The minimum multiplication cost of matrix multiplication used when calculating total income information: \n");
            printf("With Memorized Recursive: %d\n", minMultiplicationCostMemorizedRecursive);
            printf("With Dynamic Programming: %d\n", minMultiplicationCostDynamicProgramming);
            getchar();
            break;
        case 3:
            return true;
        default:
            printf("Invalid option, please try again.\n");
            getchar();
            break;
        }
    }
}