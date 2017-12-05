#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

// declare all needed functions
int setupFile();

int showLogin(bool clearScreen);
int showMainMenu(bool clearScreen);
int showAddTransaction();

int showSetting();
int showSettingFormUpdatePassword();

bool checkFileExists(char path[255]);
unsigned long generateHash(const char *str);

string showInputPassword();

void clearScr();

void clearScr(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

// declare all struct
struct userData {
    char username[50];
    unsigned long hashPassword;
    char role[50];
};

// TODO: update this struct
struct transactionData {
};

int currentSupportedUsers = 15;
int loginUserIndex = -1;
userData loggedUser;

userData users[15]; // TODO: find a better way to dynamically set this struct length
transactionData transactions[1000000]; // TODO: update this, currently only support up to 1M data

int main() {

    cout << "Aplikasi TBD" << endl;

    setupFile();
    showLogin(false);
};

int showLogin(bool clearScreen) {

    if (clearScreen) {
        clearScr(); // TODO: enable this later
    }

    char endln[2];
    strcpy(endln, "\n");

    char inputedUsername[50];

    cout << "Username: "; gets(inputedUsername);
    cout << "Password: ";

    string password = showInputPassword();


    for(int i = 0; i < currentSupportedUsers; i++) {

        char userName[50];
        strcpy(userName, users[i].username);
        int userPassword = users[i].hashPassword;

        bool isUsernameMatch = (strcmp(inputedUsername, userName) == 0);

        if (isUsernameMatch && (userPassword == generateHash(password.c_str()))) {
            loginUserIndex = i;
            loggedUser = users[i];
            i = currentSupportedUsers;
        }
    }

    if (loginUserIndex >= 0) { // user found
        showMainMenu(true);
        return 1;
    } else {
        cout << endln << "Username " << inputedUsername << " not found" << endl;
        return showLogin(false);
    }
}

int showMainMenu(bool clearScreen) {

    if (clearScreen) {
        clearScr(); // TODO: enable this later
    }

    cout << endl << "\tWelcome " << loggedUser.username;
    cout << endl << "===============================";
    cout << endl << "1. Add Transaction";
    cout << endl << "2. All Transactions";
    cout << endl << "3. Setting";
    cout << endl << "===============================";
    cout << endl << "0. Exit";

    int selectedMenu = 0;

    cout << endl;
    cout << endl << "Input menu number [0-3]: "; cin >> selectedMenu;

    if (selectedMenu > 3) {
        showMainMenu(false);
        return 0;
    }

    switch(selectedMenu) {
        case 3:
            return showSetting();
        default:
            return 0;
    }
}

int showAddTransaction() {

}

int showSetting() {
    clearScr();

    cout << endl << "\tSetting";
    cout << endl << "===============================";
    cout << endl << "1. Update Password";
    cout << endl << "===============================";
    cout << endl << "0. Main Menu";

    int selectedMenu = 0;

    cout << endl;
    cout << endl << "Input menu number [0-1]: "; cin >> selectedMenu;

    if (selectedMenu > 3) {
        showSetting();
        return 0;
    }

    switch(selectedMenu) {
        case 1:
            return showSettingFormUpdatePassword();
        default:
            return showMainMenu(true);
    }
}

int showSettingFormUpdatePassword() {
    clearScr();
    string oldPassword;
    string newPassword;

    cout << endl << "\tUpdate Password";
    cout << endl << "===============================";
    cout << endl;
    cout << "Old Password: ";
    oldPassword = showInputPassword();
    cout << endl;

    cout << "New Password: ";
    newPassword = showInputPassword();

    bool isOldPasswordSame = (loggedUser.hashPassword == generateHash(oldPassword.c_str()));

    if (!isOldPasswordSame) {
        cout << endl << "Old password is not same";
        getch();
        showSettingFormUpdatePassword();
        return 0;
    }

    users[loginUserIndex].hashPassword = generateHash(newPassword.c_str());

    ofstream userFile;
    userFile.open("users.txt");

    for(int i = 0; i < currentSupportedUsers; i++) {
        if (sizeof users[i].username > 0) {
            userFile << users[i].username << " ";
            userFile << users[i].hashPassword << " ";
            userFile << users[i].role;
            userFile << "\r\n";
        }
    }

    userFile.close();
}

// setup initial needed file
int setupFile() {
    char usersFileName[255], transactionsFileName[255];

    strcpy(usersFileName, "users.txt");
    strcpy(transactionsFileName, "transactions.txt");

    bool isUsersFileExists = checkFileExists(usersFileName);
    bool isTransactionsFileExists = checkFileExists(transactionsFileName);

    if (!isUsersFileExists) {

        // check file users.txt udah ada atau belum
        // kalo engga, bikin file baru users.txt yang bentuk nya ssv (space separated value) = username password role

        ofstream userFile;
        userFile.open(usersFileName);

        // tulis baris pertama buat user admin
        userFile << "admin ";
        userFile << generateHash("admin");
        userFile << " admin";

        // bikin file users.txt
        userFile.close();
    } else {
        // kalo file nya udah ada, kita looping, masukin ke struct users;

        ifstream input(usersFileName);
        string line;
        int i=0;

        while(getline(input, line)) {
            sscanf(line.c_str(), "%s %i %s", users[i].username, &users[i].hashPassword, users[i].role);
            i++;
        }
    }

    if (!isTransactionsFileExists) {

        // sama kaya yang di atas, cuma kita ga isi, karna bakal di isi nanti di menu transaksi
        ofstream transactionFile;
        transactionFile.open(transactionsFileName);

        transactionFile.close();
    } else {
        ifstream input(transactionsFileName);
        string line;
        int i = 0;

        while(getline(input, line)) {
            //sscanf(line.c_str(), "%s %i %s", users[i].username, &users[i].hashPassword, users[i].role);
            i++;
        }
    }

    return 1;
}

bool checkFileExists(char path[255]) {
    if (FILE *file = fopen(path, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

unsigned long generateHash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

string showInputPassword() {
    string password;
    char inputKey;

    inputKey = _getch();

    while(inputKey != 13) { // looping selama bukan enter yang di pencet

        if (inputKey == 8 && password.size() > 0) {
            //cout << password.end();
            password.erase(password.size()-1);
        } else {
            password.push_back(inputKey);
        }

        //cout << "*";
        inputKey = _getch();
    }

    return password;
}
