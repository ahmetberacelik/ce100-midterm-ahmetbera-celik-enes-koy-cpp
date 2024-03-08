#include "../header/farmermarket.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
using namespace std;

bool guessMode = false;
char active_user[50];
bool mainMenu() {
    if (!userAuthentication()) {
        return false;
    }
    int choice;
    while (true) {
        printf("1. Listing of Local Vendors and Products\n");
        printf("2. Seasonal Produce Guide\n");
        printf("3. Price Comparison\n");
        printf("4. Market Hours and Locations\n");
        printf("5. Exit\n");
        printf("Please select an option: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input, please enter a number.\n");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("Listing of Local Vendors and Products\n");
            break;
        case 2:
            printf("Seasonal Produce Guide\n");
            break;
        case 3:
            printf("Price Comparison\n");
            break;
        case 4:
            printf("Market Hours and Locations\n");
            break;
        case 5:
            printf("Exiting program...\n");
            return true;
        default:
            printf("Invalid option, please try again.\n");
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

bool userAuthentication() {
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
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Guest Mode\n");
        printf("4. Exit Program\n");
        printf("Please select an option: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("Please enter your username: ");
            fgets(temp_username, 50, stdin);
            temp_username[strcspn(temp_username, "\n")] = 0;
            printf("Please enter your password: ");
            fgets(temp_password, 50, stdin);
            temp_password[strcspn(temp_password, "\n")] = 0;

            if (authenticateUser(temp_username, temp_password, filename) == 1) {
                printf("Welcome %s\n", temp_username);
                strcpy(active_user, temp_username);
                return true;
            }
            else {
                printf("You entered wrong username or password. Please try again.\n");
                right_to_try--;
                if (right_to_try == 0) {
                    printf("You have run out of login attempts. See you...\n");
                    return false;
                }
            }
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
            printf("User registered successfully.\nWelcome %s\n", temp_username);
            strcpy(active_user, temp_username);
            return true;

        case 3:
            guessMode = true;
            return true;

        case 4:
            printf("Exiting program...\n");
            return false;

        default:
            printf("Invalid option, please try again.\n");
        }
    }
}