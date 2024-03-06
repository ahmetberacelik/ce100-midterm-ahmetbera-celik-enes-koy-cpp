#include "../header/farmermarket.h"
#include <iostream>
using namespace std;

bool guessMode = false;
char active_user[50];
bool mainMenu(std::istream& in, std::ostream& out) {
    int choice; 
    while (true) {
        out << "1. Listing of Local Vendors and Products\n";
        out << "2. Seasonal Produce Guide\n";
        out << "3. Price Comparison\n";
        out << "4. Market Hours and Locations\n";
        out << "5. Exit\n";
        out << "Please select an option: ";
        if (!(in >> choice)) {
            in.clear();
            in.ignore(1000, '\n');
            out << "Invalid input, please enter a number.\n";
            continue;
        }
        in.ignore(1000, '\n');
        switch (choice) {
        case 1:
            out << "User Authentication";
            break;
        case 2:
            out << "User Authentication";
            break;
        case 3:
            out << "User Authentication";
            break;
        case 4:
            out << "User Authentication";
            break;
        case 5:
            out << "Exiting program...\n";
            return true;
        default:
            out << "Invalid option, please try again.\n";
        }
    }
}

int saveUser(const User* user, const char* filename) {
    FILE* file = fopen(filename, "ab");
    fwrite(user, sizeof(User), 1, file);
    fclose(file);
    return 0;
}

int authenticateUser(const char* username, const char* password, const char* filename) {
    FILE* file = fopen(filename, "rb");
    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

bool userAuthentication(std::istream& in, std::ostream& out) {
    const char* filename = "Users.bin";
    int choice;
    int right_to_try = 3;
    while (true) {
        out << "1. Login\n";
        out << "2. Register\n";
        out << "3. Guest Mode\n";
        out << "4. Exit Program\n";
        out << "Please select an option: ";
        if (!(in >> choice)) {
            in.clear();
            in.ignore(1000, '\n');
            out << "Invalid input, please enter a number.\n";
            continue;
        }
        in.ignore(1000, '\n');
        switch (choice) {
        case 1: {
            out << "Please enter your username: ";
            char temp_username[50];
            in.getline(temp_username, 50);
            out << "Please enter your password: ";
            char temp_password[50];
            in.getline(temp_password, 50);
            if (authenticateUser(temp_username, temp_password, filename)) {
                out << "Welcome " << temp_username << "\n";
                strcpy(active_user, temp_username);
                return true;
            }
            else {
                out << "You entered wrong username or password. Please try again.\n";
                right_to_try--;
                if (right_to_try == 0) {
                    out << "You have run out of login attempts. See you...\n";
                    return false;
                }
            }
            break;
        }
        case 2: {
            out << "Please enter your username: ";
            char new_username[50];
            in.getline(new_username, 50);
            out << "Please enter your password: ";
            char new_password[50];
            in.getline(new_password, 50);
            User newUser;
            strcpy(newUser.username, new_username);
            strcpy(newUser.password, new_password);
            saveUser(&newUser, filename);
            out << "User registered successfully.\n";
            out << "Welcome " << new_username << "\n";
            strcpy(active_user, new_username);
            return true;
            break;
        }
        case 3:
            guessMode = true;
            return true;
            break;
        case 4:
            out << "Exiting program...\n";
            return false;
        default:
            out << "Invalid option, please try again.\n";
        }
    }
}