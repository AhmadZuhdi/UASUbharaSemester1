#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <tr1/functional>

// declare all needed functions
int showLogin();
int setupFile();
bool checkFileExists(char path[255]);

// declare all struct
struct userData {
    char username[50];
    int hashPassword;
    char role[50];
};

using namespace std;

int main() {
    setupFile();
    showLogin();
};

int showLogin() {
    clrscr();
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
        // kalo engga, bikin file baru users.txt yang bentuk nya csv = username, password, role

        ofstream userFile;
        userFile.open(usersFileName);

        // generate hash password buat admin
        int adminPassword = tr1::hash<string>()("admin");

        // tulis baris pertama buat user admin
        userFile << "admin,";
        userFile << adminPassword;
        userFile << ",admin";

        // bikin file users.txt
        userFile.close();
    }

    if (!isTransactionsFileExists) {

        // sama kaya yang di atas, cuma kita ga isi, karna bakal di isi nanti di menu transaksi
        ofstream transactionFile;
        transactionFile.open(transactionsFileName);

        transactionFile.close();
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
