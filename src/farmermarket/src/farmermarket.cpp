#include "../header/farmermarket.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
using namespace std;

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
            fprintf(out, "Listing of Local Vendors and Products\n");
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

