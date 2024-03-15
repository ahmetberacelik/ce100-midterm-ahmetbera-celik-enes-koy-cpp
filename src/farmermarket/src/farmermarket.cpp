#include "../header/farmermarket.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
bool guessMode = false;
char active_user[50];
char* vendors[] = { "Ahmet", "Mehmet", "Veli", "Ayse", "Nuriye" };
char* products[][6] = {
    {"Ahmet", "Banana", "Apple", "Cherry", "Date", "Grape"},
    {"Mehmet", "Raspberry", "Eggplant", "Mushroom", "Beet", "Turnip"},
    {"Veli", "Cucumber", "Melon", "Lemon", "Tomato", "Orange"},
    {"Ayse", "Pear", "Nectarine", "Carrot", "Bean", "Beet"},
    {"Nuriye", "Hazelnut", "Chestnut", "Fig", "Coconut", "Broccoli"}
};

ProductSeason productSeasons[] = {
    {10,"Banana", "Summer"},
    {10,"Apple", "Fall"},
    {10,"Cherry", "Summer"},
    {15,"Date", "Fall"},
    {15, "Grape", "Fall"},
    {15,"Raspberry", "Summer"},
    {20,"Eggplant", "Summer"},
    {20,"Mushroom", "Fall"},
    {20,"Beet", "Fall"},
    {25, "Turnip", "Winter"},
    {25, "Cucumber", "Summer"},
    {25, "Melon", "Summer"},
    {30, "Lemon", "Winter"},
    {30,"Tomato", "Summer"},
    {30, "Orange", "Winter"},
    {35, "Pear", "Fall"},
    {35,"Nectarine", "Summer"},
    {35, "Carrot", "Fall"},
    {40, "Bean", "Summer"},
    {40, "Hazelnut", "Fall"},
    {40, "Chestnut", "Fall"},
    {45, "Fig", "Summer"},
    {45, "Coconut", "Summer"},
    {45,"Broccoli", "Fall"},
    {15, "Asparagus", "Spring"},
    {15,"Radish", "Spring"},
};
int numProducts = sizeof(productSeasons) / sizeof(productSeasons[0]);
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
bool mainMenu(FILE* in, FILE* out) {
    if (!userAuthentication(in, out)) {
        return false;
    }
    int choice;
    while (true) {
        clearScreen();
        fprintf(out, "1. Listing of Local Vendors and Products\n");
        fprintf(out, "2. Seasonal Produce Guide\n");
        fprintf(out, "3. Price Comparison\n");
        fprintf(out, "4. Market Hours and Locations\n");
        fprintf(out, "5. Exit\n");
        fprintf(out, "Please select an option: ");
        if (fscanf(in, "%d", &choice) != 1) {
            while (fgetc(in) != '\n' && !feof(in));
            fprintf(out, "Invalid input, please enter a number.\n");
            continue;
        }
        while (fgetc(in) != '\n' && !feof(in));

        switch (choice) {
        case 1:
            listingOfInfos(in, out);
            break;
        case 2:
            seasonalProduceGuide(in, out);
            break;
        case 3:
            PurchasingTransactionsAndPriceComparison(in, out);
            break;
        case 4:
            fprintf(out, "Market Hours and Locations\n");
            break;
        case 5:
            fprintf(out, "Exiting program...Press enter!\n");
            while (fgetc(in) != '\n' && !feof(in));
            return true;
        default:
            fprintf(out, "Invalid option, please try again.\n");
            while (fgetc(in) != '\n' && !feof(in));
        }
    }
    return true;
}

int saveUser(const User* user, const char* filename) {
    FILE* file = fopen(filename, "ab");
    fwrite(user, sizeof(User), 1, file);
    fclose(file);
    return 1;
}

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

bool userAuthentication(FILE* in, FILE* out) {
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
        fprintf(out, "1. Login\n");
        fprintf(out, "2. Register\n");
        fprintf(out, "3. Guest Mode\n");
        fprintf(out, "4. Exit Program\n");
        fprintf(out, "Please select an option: ");
        fscanf(in, "%d", &choice);
        while (fgetc(in) != '\n' && !feof(in));

        switch (choice) {
        case 1:
            fprintf(out, "Please enter your username: ");
            fgets(temp_username, 50, in);
            temp_username[strcspn(temp_username, "\n")] = 0;
            fprintf(out, "Please enter your password: ");
            fgets(temp_password, 50, in);
            temp_password[strcspn(temp_password, "\n")] = 0;

            if (authenticateUser(temp_username, temp_password, filename) == 1) {
                clearScreen();
                fprintf(out, "Welcome %s\n", temp_username);
                strcpy(active_user, temp_username);
                while (fgetc(in) != '\n' && !feof(in));
                return true;
            }
            else {
                fprintf(out, "You entered wrong username or password. Please try again.\n");
                right_to_try--;
                if (right_to_try == 0) {
                    fprintf(out, "You have run out of login attempts. See you...\n");
                    while (fgetc(in) != '\n' && !feof(in));
                    return false;
                }
            }
            while (fgetc(in) != '\n' && !feof(in));
            break;

        case 2:
            fprintf(out, "Please enter your username: ");
            fgets(temp_username, 50, in);
            temp_username[strcspn(temp_username, "\n")] = 0;
            fprintf(out, "Please enter your password: ");
            fgets(temp_password, 50, in);
            temp_password[strcspn(temp_password, "\n")] = 0;

            User newUser;
            strcpy(newUser.username, temp_username);
            strcpy(newUser.password, temp_password);
            saveUser(&newUser, filename);
            fprintf(out, "User registered successfully.\nWelcome %s\n", temp_username);
            strcpy(active_user, temp_username);
            while (fgetc(in) != '\n' && !feof(in));
            return true;

        case 3:
            guessMode = true;
            return true;

        case 4:
            fprintf(out, "Exiting program...Press enter!\n");
            while (fgetc(in) != '\n' && !feof(in));
            return false;

        default:
            fprintf(out, "Invalid option, please try again.\n");
            while (fgetc(in) != '\n' && !feof(in));
        }
    }
}

bool swap(char** a, char** b) {
    char* t = *a;
    *a = *b;
    *b = t;
    return true;
}

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

bool quickSort(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
    return true;
}

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
bool searchAndPrintResult(char* arr[], int size, char* x) {
    int result = binarySearch(arr, 0, size - 1, x);
    if (result == -1) {
        return false;
    }
    else {
        return true;
    }
}

bool listingOfInfos(FILE* in, FILE* out) {
    clearScreen();

    int numVendors = sizeof(vendors) / sizeof(vendors[0]);
    int numProductsPerVendor = sizeof(products[0]) / sizeof(products[0][0]);
    char vendor_query[50];
    char product_query[50];
    bool found = false;
    int choice;
    while (true) {
        clearScreen();
        fprintf(out, "1. Browse Vendors\n");
        fprintf(out, "2. Search Product\n");
        fprintf(out, "3. Exit\n");
        fprintf(out, "Please select an option: ");
        if (fscanf(in, "%d", &choice) != 1) {
            while (fgetc(in) != '\n' && !feof(in));
            fprintf(out, "Invalid input, please enter a number.\n");
            while (fgetc(in) != '\n' && !feof(in));
            continue;
        }
        while (fgetc(in) != '\n' && !feof(in));

        switch (choice) {
        case 1:
            fprintf(out, "Please enter vendor name: ");
            fgets(vendor_query, 50, in);
            vendor_query[strcspn(vendor_query, "\n")] = 0;
            quickSort(vendors, 0, numVendors - 1);
            clearScreen();
            if (searchAndPrintResult(vendors, numVendors, vendor_query)) {
                fprintf(out, "Vendor found: %s\n", vendor_query);
            }
            else {
                fprintf(out, "Vendor not found.\n");
            }
            while (fgetc(in) != '\n' && !feof(in));
            break;
        case 2:
            fprintf(out, "Please enter product name: ");
            fgets(product_query, 50, in);
            product_query[strcspn(product_query, "\n")] = 0;
            for (int i = 0; i < numVendors; i++) {
                quickSort(products[i] + 1, 0, numProductsPerVendor - 2);
                clearScreen();
                if (binarySearch(products[i] + 1, 0, numProductsPerVendor - 2, product_query) != -1) {
                    fprintf(out, "Product %s found at vendor %s\n", product_query, products[i][0]);
                    found = true;
                    break;
                }
                else {
                    found = false;
                }
            }
            if (!found) {
                fprintf(out, "Product not found.\n");
            }
            while (fgetc(in) != '\n' && !feof(in));
            break;
        case 3:
            fprintf(out, "Exiting Listing Of Infos...Press enter!\n");
            while (fgetc(in) != '\n' && !feof(in));
            return true;
        default:
            fprintf(out, "Invalid option, please try again.\n");
            while (fgetc(in) != '\n' && !feof(in));
        }
    }
}

void initMinHeap(MinHeap* heap) {
    heap->size = 0;
}

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

ProductSeason removeMin(MinHeap* heap) {
    ProductSeason result = heap->items[0];
    ProductSeason lastItem = heap->items[--heap->size];
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int left = i * 2 + 1, right = i * 2 + 2;
        int smallest = left;
        if (right < heap->size && heap->items[right].price < heap->items[left].price) {
            smallest = right;
        }
        if (lastItem.price <= heap->items[smallest].price) break;
        heap->items[i] = heap->items[smallest];
        i = smallest;
    }
    heap->items[i] = lastItem;
    return result;
}

int saveProductSeason(const ProductSeason* productSeason, int numProducts, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(&numProducts, sizeof(int), 1, file);
    fwrite(productSeason, sizeof(ProductSeason), numProducts, file);
    fclose(file);
    return 1;
}

int loadProductSeasonsAndPrint(FILE* in, FILE* out, const char* filename, const char* selectedSeason) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(out, "File didn't open.\n");
        return 0;
    }

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
        fprintf(out, "- Price: %d, Name: %s\n", ps.price, ps.name);
    }
    while (fgetc(in) != '\n' && !feof(in));

    return found;
}

bool seasonalProduceGuide(FILE* in, FILE* out) {
    clearScreen();
    const char* filename = "ProductSeasons.bin";

    saveProductSeason(productSeasons, numProducts, filename);
    while (true) {
        clearScreen();
        fprintf(out, "Select a season to see available produce:\n");
        fprintf(out, "1. Spring\n2. Summer\n3. Fall\n4. Winter\n5. Return to Main Menu\n");
        fprintf(out, "Please select an option: ");

        int choice;
        fscanf(in, "%d", &choice);
        while (fgetc(in) != '\n');

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
            fprintf(out, "Invalid option, please try again.\n");
            continue;
        }
        clearScreen();
        fprintf(out, "Available produce for %s season:\n", selectedSeason);
        if (!loadProductSeasonsAndPrint(in, out, filename, selectedSeason)) {
            fprintf(out, "No produce found for this season.\n");
        }
    }
    return true;
}

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

void compareAndPrintLCS(char* season1, char* season2, char* name1, char* name2, int price, FILE* out)
{
    int m = strlen(name1);
    int n = strlen(name2);

    int lcsLength = lcs(name1, name2, m, n);

    if (lcsLength > 0 && strcmp(season1, season2) == 0) {
        fprintf(out, "- Name 1: %s, Name 2: %s, Price: %d\n", name1, name2, price);
    }
}

bool PurchasingTransactionsAndPriceComparison(FILE* in, FILE* out) {
    clearScreen();
    int choice;
    while (true) {
        clearScreen();
        fprintf(out, "1. Buy Products\n");
        fprintf(out, "2. Compare Products\n");
        fprintf(out, "3. Exit\n");
        fprintf(out, "Please select an option: ");
        if (fscanf(in, "%d", &choice) != 1) {
            while (fgetc(in) != '\n' && !feof(in));
            fprintf(out, "Invalid input, please enter a number.\n");
            continue;
        }
        while (fgetc(in) != '\n' && !feof(in));
        bool found = false;
        bool validSeason = false;
        switch (choice) {
        case 1:
            if (guessMode)
            {
                fprintf(out, "You can not buy product in guess mode.\n");
                break;
            }

            break;
        case 2:
            clearScreen();
            fprintf(out, "Enter a season: ");
            char selectedSeason[50];
            fgets(selectedSeason, sizeof(selectedSeason), in);
            selectedSeason[strcspn(selectedSeason, "\n")] = '\0';
            
            for (int i = 0; i < sizeof(productSeasons) / sizeof(productSeasons[0]); i++) {
                if (strcmp(productSeasons[i].season, selectedSeason) == 0) {
                    validSeason = true;
                    break;
                }
            }
            if (!validSeason) {
                fprintf(out, "Invalid season. Please enter a valid season.\n");
                while (fgetc(in) != '\n' && !feof(in));
                break;
            }
            fprintf(out, "Products at the same price as %s season products:\n", selectedSeason);
            for (int i = 0; i < sizeof(productSeasons) / sizeof(productSeasons[0]); i++)
            {
                if (strcmp(productSeasons[i].season, selectedSeason) == 0)
                {
                    for (int j = i + 1; j < sizeof(productSeasons) / sizeof(productSeasons[0]); j++)
                    {
                        if (productSeasons[i].price == productSeasons[j].price)
                        {
                            compareAndPrintLCS(selectedSeason, productSeasons[i].season, productSeasons[i].name, productSeasons[j].name, productSeasons[i].price, out);

                            found = true;
                        }
                    }
                }
            }
            while (fgetc(in) != '\n' && !feof(in));
            break;
        case 3:
            return false;
        default:
            fprintf(out, "Invalid option, please try again.\n");
            while (fgetc(in) != '\n' && !feof(in));
        }
    }
    return true;
}