#include "../header/farmermarket.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
bool guessMode = false;
char active_user[50];
bool mainMenu(FILE* in, FILE* out) {
    if (!userAuthentication(in, out)) {
        return false;
    }
    int choice;
    while (true) {
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
            fprintf(out, "Seasonal Produce Guide\n");
            break;
        case 3:
            fprintf(out, "Price Comparison\n");
            break;
        case 4:
            fprintf(out, "Market Hours and Locations\n");
            break;
        case 5:
            fprintf(out, "Exiting program...\n");
            return true;
        default:
            fprintf(out, "Invalid option, please try again.\n");
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
                fprintf(out, "Welcome %s\n", temp_username);
                strcpy(active_user, temp_username);
                return true; }
            else {
                fprintf(out, "You entered wrong username or password. Please try again.\n");
                right_to_try--;
                if (right_to_try == 0) {
                    fprintf(out, "You have run out of login attempts. See you...\n");
                    return false;
                }
            }
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
            return true;

        case 3:
            guessMode = true;
            return true;

        case 4:
            fprintf(out, "Exiting program...\n");
            return false;

        default:
            fprintf(out, "Invalid option, please try again.\n");
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
        return false; }
    else {
        return true;
    }
}

bool listingOfInfos(FILE* in, FILE* out) {
    char* vendors[] = { "Ahmet", "Mehmet", "Veli", "Ayse", "Nuriye" };
    char* products[][6] = {
        {"Ahmet", "Banana", "Apple", "Cherry", "Date", "Grape"},
        {"Mehmet", "Raspberry", "Eggplant", "Mushroom", "Beet", "Turnip"},
        {"Veli", "Cucumber", "Melon", "Lemon", "Tomato", "Orange"},
        {"Ayse", "Pear", "Nectarine", "Carrot", "Bean", "Beet"},
        {"Nuriye", "Hazelnut", "Chestnut", "Fig", "Coconut", "Broccoli"}
    };
    int numVendors = sizeof(vendors) / sizeof(vendors[0]);
    int numProductsPerVendor = sizeof(products[0]) / sizeof(products[0][0]);
    char vendor_query[50];
    char product_query[50];
    bool found = false;
    int choice;
    while (true) {
        fprintf(out, "1. Browse Vendors\n");
        fprintf(out, "2. Search Product\n");
        fprintf(out, "3. Exit\n");
        fprintf(out, "Please select an option: ");
        if (fscanf(in, "%d", &choice) != 1) {
            while (fgetc(in) != '\n' && !feof(in));
            fprintf(out, "Invalid input, please enter a number.\n");
            continue;
        }
        while (fgetc(in) != '\n' && !feof(in));

        switch (choice) {
        case 1:
            fprintf(out, "Please enter vendor name: ");
            fgets(vendor_query, 50, in);
            vendor_query[strcspn(vendor_query, "\n")] = 0;
            quickSort(vendors, 0, numVendors - 1);
            if (searchAndPrintResult(vendors, numVendors, vendor_query)) {
                fprintf(out, "Vendor found: %s\n", vendor_query);
                }
            else {
                fprintf(out, "Vendor not found.\n");
            }
            break;
        case 2:
            fprintf(out, "Please enter product name: ");
            fgets(product_query, 50, in);
            product_query[strcspn(product_query, "\n")] = 0;
            for (int i = 0; i < numVendors; i++) {
                quickSort(products[i] + 1, 0, numProductsPerVendor - 2);
                if (binarySearch(products[i] + 1, 0, numProductsPerVendor - 2, product_query) != -1) {
                    fprintf(out, "Product %s found at vendor %s\n", product_query, products[i][0]);
                    found = true;
                    break; }
                else {
                    found = false;
                }
            }
            if (!found) {
                fprintf(out, "Product not found.\n");
            }
            break;
        case 3:
            fprintf(out, "Exiting Listing Of Infos...\n");
            return true;
        default:
            fprintf(out, "Invalid option, please try again.\n");
        }
    }
}
