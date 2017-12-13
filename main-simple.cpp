#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

using namespace std;

// deklarasi fungsi fungsi custom
// biasanya ada di bawah #include, di atas main()
void setupData();
void setupUsers();
void setupTopping();
void setupBases();

int showLogin();
int showMainMenu();
int showAddTransaction();
int showAllTransactions();
int showSetting();
string showInputPassword();
void clearScr();

// deklarasi struct
struct userData {
    int id;
    char username[50];
    char password[50];
    char role[50];
};

struct base {
    char name[255];
    float price;
};

struct topping {
    int id;
    char name[255];
    float price;
};

// TODO: update this struct
struct transactionData {
    int userId;
    int baseId;
    int toppingsId[5]; // up to 5 toppings
    float totalPrice;
    float totalPayment;
};

int currentSupportedUsers = 10;
int maxToppings = 5;
int latestTransactionIndex = 0;

int loginUserIndex = -1;
userData loggedUser;

userData users[10]; // TODO: find a better way to dynamically set this struct length
topping toppings[50]; // TODO: find a better way to dynamically set this struct length
base bases[50]; // TODO: find a better way to dynamically set this struct length
transactionData transactions[1000000]; // TODO: update this, currently only support up to 1M data


int main() {

    setupData();
    showLogin();
};

void clearScr(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void setupData() {
    setupUsers();
    setupTopping();
    setupBases();
}

void setupUsers() {
    // set admin user
    // kita pake function strcpy buat set value ke array users di index 0
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin");
    strcpy(users[0].role, "admin");
    //users[0].id = 1;

    // set kasir user
    strcpy(users[1].username, "kasir1");
    strcpy(users[1].password, "123123");
    strcpy(users[1].role, "kasir");
    //users[1].id = 2;
}

void setupBases() {
    bases[0].price = 1500;
    strcpy(bases[0].name, "Pancong Segita");

    bases[1].price = 2000;
    strcpy(bases[1].name, "Pancong Persegi");

    bases[2].price = 2500;
    strcpy(bases[2].name, "Pancong Persegi Panjang");
}

void setupTopping() {
    // coklat
    toppings[5].price = 1000;
    strcpy(toppings[5].name, "Coklat");

    // susu
    toppings[1].price = 500;
    strcpy(toppings[1].name, "Susu");

    // keju kotak
    toppings[2].price = 2000;
    strcpy(toppings[2].name, "Keju Kotak");

    // keju serut
    toppings[3].price = 1500;
    strcpy(toppings[3].name, "Keju Serut");

    // meises coklat
    toppings[4].price = 500;
    strcpy(toppings[4].name, "Meises Coklat");
}

int showLogin() {

    clearScr();

    char inputedUsername[50];

    cout << "\tAplikasi Kasir Pancong" << endl << endl;
    cout << "Username: "; gets(inputedUsername);
    cout << "Password: ";

    string password = showInputPassword();

    for(int i = 0; i < currentSupportedUsers; i++) {

        bool isUsernameMatch = (strcmp(inputedUsername, users[i].username) == 0);
        bool isPasswordMatch = (strcmp(password.c_str(), users[i].password) == 0);

        if (isUsernameMatch && isPasswordMatch) {
            loginUserIndex = i;
            loggedUser = users[i];
            i = currentSupportedUsers;
        }
    }

    if (loginUserIndex >= 0) { // user found
        showMainMenu();
        return 1;
    } else {
        cout << endl << "Username " << inputedUsername << " tidak di temukan, atau password salah" << endl;
        getch();
        return showLogin();
    }
}

int showMainMenu() {

    clearScr();

    cout << endl << "\tSelamat Datang " << loggedUser.username << endl;
    cout << endl << "===============================";
    cout << endl << "1. Tambah Transaksi";
    cout << endl << "2. Semua Transaksi";
    //cout << endl << "3. Setting"; // TODO: temp disable setting menu
    cout << endl << "===============================";
    cout << endl << "0. Keluar";

    int selectedMenu = 0;

    cout << endl;
    cout << endl << "Masukkan nomer menu [0-2]: "; cin >> selectedMenu;

    if (selectedMenu > 3) {
        cout << endl << "Nomer menu salah!";
        getch();
        showMainMenu();
        return 0;
    }

    switch(selectedMenu) {
        case 1:
            return showAddTransaction();
        case 2:
            return showAllTransactions();
        case 3:
            return showSetting();
        default:
            return 0;
    }
}

int showAddTransaction() {
    clearScr();

    cout << endl << "\tTambah Transaksi";
    cout << endl << "===============================";

    int totalBases = sizeof(bases) / sizeof(bases[0]);
    int totalToppings = sizeof(toppings) / sizeof(toppings[0]);

    int totalSelectableBases=0, totalSelectableToppings=0;

    cout << endl << "Pilihan Pancong: " << endl;

    // kita cuma ambil base yang harga nya di atas 0 aja
    for (int i = 0; i < totalBases; i++) {
        if (bases[i].price > 0) {
            totalSelectableBases++;
            cout << (i+1) << ". " << bases[i].name << " (Rp. " << bases[i].price << ")" << endl;
        }
    }

    int selectedBaseKey=0;
    int userToppings = 0;
    int selectedUserToppings[5];
    float totalHarga = 0;
    transactionData trx;

    cout << endl << "Masukkan kode pancong [1-" << (totalSelectableBases) << "] : ";
    cin >> selectedBaseKey;
    selectedBaseKey--;

    totalHarga = totalHarga + bases[selectedBaseKey].price;

    cout << endl;
    cout << endl << "Jumlah Topping yang di inginkan (max 5): ";
    cin >> userToppings;

    if (userToppings < 1) {
        userToppings = 1;
    }

    if (userToppings > 5) {
        userToppings = 5;
    }

    cout << endl << "Pilihan Topping: " << endl;

    for (int a = 0; a < totalToppings; a++) {
        topping selectedTopping = toppings[a];
        if (selectedTopping.price > 0) {
            totalSelectableToppings++;
            cout << (a) << ". " << selectedTopping.name << " (Rp. " << selectedTopping.price << ")" << endl;
        }
    }

    cout << endl;

    for(int b = 0; b < userToppings; b++) {
        int selectedTopping = 0;
        cout << "Masukkan kode topping [1-" << totalSelectableToppings << "]: ";
        cin >> selectedTopping;

        totalHarga = totalHarga + toppings[selectedTopping].price;
        trx.toppingsId[b] = selectedTopping;
    }

    float totalBayar;

    totalHarga = totalHarga + (totalHarga * 0.1);

    cout << endl << "Total Harga (Termasuk PPN 10%) : Rp." << totalHarga;

    trx.baseId = selectedBaseKey;
    //trx.toppingsId = selectedUserToppings;
    trx.totalPrice = totalHarga;
    trx.userId = loginUserIndex;

    cout << endl << "Total Bayar : ";
    cin >> trx.totalPayment;

    transactions[latestTransactionIndex] = trx;
    latestTransactionIndex++;

    cout << endl << "Transaksi berhasil di buat!"; getch();
    showMainMenu();
}

int showAllTransactions() {
    clearScr();

    cout << "\t\tTransaksi Sesi ini";
    cout << endl << "================================================";
    cout << endl << endl;

    printf("%-4s%-10s%-25s%-15s%-15s", "#", "Kasir", "Tipe Pancong", "Topping", "Total Harga");

    for(int i = 0; i < latestTransactionIndex; i++) {
        transactionData trx = transactions[i];
        topping firstTopping = toppings[trx.toppingsId[0]];

        cout << endl;
        printf("%-4d%-10s%-25s%-15s", (i+1), users[trx.userId].username, bases[trx.baseId].name, firstTopping.name);
        int totalTopping = 1;
        for(int a = 1; a < maxToppings-1; a++) {
            topping selectedTopping = toppings[trx.toppingsId[a]];

            if (trx.toppingsId[a] > 0) {
                totalTopping++;
                cout << endl;
                printf("%-4s%-10s%-25s%-15s", "", "", "", selectedTopping.name);
            }
        }

        topping lastTopping = toppings[trx.toppingsId[totalTopping]];

        cout << endl;
        printf("%-4s%-10s%-25s%-15s%-15.0f", "", "", "", lastTopping.name, trx.totalPrice);
        cout << endl;
    }

    cout << "Tekan tombol apapun untuk kembali ke menu utama"; getch();
    showMainMenu();
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
            return 0;
        default:
            return showMainMenu();
    }
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
