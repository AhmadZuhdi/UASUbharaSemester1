#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <tr1/functional>

// declare all needed functions
int setupFile();
int showLogin(bool clearScreen);
int showMainMenu();
bool checkFileExists(char path[255]);
unsigned long generateHash(const char *str);

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

userData users[15]; // TODO: find a better way to dynamically set this struct length
transactionData transactions[1000000]; // TODO: update this, currently only support up to 1M data

using namespace std;

int main() {

    cout << "Aplikasi TBD" << endl;

    setupFile();
    showLogin(true);
};

int showLogin(bool clearScreen) {


    if (clearScreen) {
        //clrscr(); // TODO: enable this later
    }

    char endln[2];
    strcpy(endln, "\n");

    char inputedUsername[50];

    cout << "Username: "; gets(inputedUsername);
    cout << "Password: ";

    string password;
    char inputKey;

    inputKey = _getch();

    while(inputKey != 13) { // looping selama bukan enter yang di pencet
        password.push_back(inputKey);
        cout << "*";
        inputKey = _getch();
    }

    int matchedUser = -1;

    for(int i = 0; i < currentSupportedUsers; i++) {

        char userName[50];
        strcpy(userName, users[i].username);
        int userPassword = users[i].hashPassword;

        cout << inputedUsername << ":" << userName;

        bool isUsernameMatch = (strcmp(inputedUsername, userName) == 0);

        cout << isUsernameMatch << endl;

        if (isUsernameMatch && (userPassword == generateHash(password.c_str()))) {
            matchedUser = i;
            i = currentSupportedUsers;
        }
    }

    if (matchedUser >= 0) { // user found
        showMainMenu();
        return 1;
    } else {
        cout << endln << "Username " << inputedUsername << " not found" << endl;
        return showLogin(false);
    }
}

int showMainMenu() {
    //clrsrc();
    cout << "\t\tWelcome";
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
