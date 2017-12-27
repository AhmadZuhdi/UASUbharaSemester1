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
void setupBuku();

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

struct buku {
    char nama[255];
    char pengarang[255];
    char penerbit[255];
    int tahunTerbit;
    float harga;
};

// TODO: update this struct
struct transactionData {
    int userId;
    int kodeBuku;
};

int currentSupportedUsers = 10;
int latestTransactionIndex = 0;

int loginUserIndex = -1;
userData loggedUser;

userData users[10];
buku bukuBuku[50];
transactionData transactions[1000000];


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
    setupBuku();
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

void setupBuku() {
    bukuBuku[0].harga = 75000;
    bukuBuku[0].tahunTerbit = 2017;
    strcpy(bukuBuku[0].nama, "Perempuan Perempuan Pengukir Sejarah");
    strcpy(bukuBuku[0].pengarang, "Mulyono Atmosiswartoputra");
    strcpy(bukuBuku[0].penerbit, "Bhuana Ilmu Populer");


    bukuBuku[1].harga = 135000;
    bukuBuku[1].tahunTerbit = 2017;
    strcpy(bukuBuku[1].nama, "Collapse");
    strcpy(bukuBuku[1].pengarang, "Jared Diamond");
    strcpy(bukuBuku[1].penerbit, "Kepustakaan Populer Gramedia");

    bukuBuku[2].harga = 65000;
    bukuBuku[2].tahunTerbit = 2017;
    strcpy(bukuBuku[2].nama, "Koran Kami, With Lucy In The Sky");
    strcpy(bukuBuku[2].pengarang, "Bre Redana");
    strcpy(bukuBuku[2].penerbit, "Kepustakaan Populer Gramedia");

    bukuBuku[3].harga = 99800;
    bukuBuku[3].tahunTerbit = 2017;
    strcpy(bukuBuku[3].nama, "Gladiator: Bertarung untuk Hidup, Kemuliaan, dan Kebebasan");
    strcpy(bukuBuku[3].pengarang, "Ben Hubbard");
    strcpy(bukuBuku[3].penerbit, "Elex Media Komputindo");

    bukuBuku[4].harga = 360000;
    bukuBuku[4].tahunTerbit = 2017;
    strcpy(bukuBuku[4].nama, "Kronik '65");
    strcpy(bukuBuku[4].pengarang, "Kuncoro Hadi, dkk");
    strcpy(bukuBuku[4].penerbit, "Media Pressindo");

    bukuBuku[5].harga = 110000;
    bukuBuku[5].tahunTerbit = 2017;
    strcpy(bukuBuku[5].nama, "Kitab Epos Mahabarata");
    strcpy(bukuBuku[5].pengarang, "YUDHI MURTANTO");
    strcpy(bukuBuku[5].penerbit, "Laksana");

    bukuBuku[6].harga = 200000;
    bukuBuku[6].tahunTerbit = 2017;
    strcpy(bukuBuku[6].nama, "Perubahan Sosial dalam Masyarakat Agraris Madura");
    strcpy(bukuBuku[6].pengarang, "Prof. Dr. Kuntowijoyo");
    strcpy(bukuBuku[6].penerbit, "Diva Press");

    bukuBuku[7].harga = 49500;
    bukuBuku[7].tahunTerbit = 2017;
    strcpy(bukuBuku[7].nama, "Sejarah Penaklukan Jawa");
    strcpy(bukuBuku[7].pengarang, "Ahmad Wahyu Sudrajad");
    strcpy(bukuBuku[7].penerbit, "Penerbit Anak Hebat");
}

int showLogin() {

    clearScr();

    char inputedUsername[50];

    cout << "\tSelamat Databg di Aplikasi Toko Buku" << endl << endl;
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
        default:
            return 0;
    }
}

int showAddTransaction() {
    clearScr();

    cout << endl << "\tTambah Transaksi";
    cout << endl << "===============================";

    // jumlah buku yang ada datanya di struct
    int jumlahBukuTersedia = sizeof(bukuBuku) / sizeof(bukuBuku[0]);
    int totalBuku=0;

    cout << endl << "Pilihan Buku: " << endl;

    // ambil semua buku yang harga nya lebih dari 0
    for (int i = 0; i < jumlahBukuTersedia; i++) {
        if (bukuBuku[i].harga > 0) {
            totalBuku++;
            cout << (i+1) << ". " << bukuBuku[i].nama << " (Rp. " << bukuBuku[i].harga << ")" << endl;
        }
    }

    int jumlahBukuYangDiBeli;

    cout << endl;
    cout << endl << "Jumlah Buku yang di dibeli : ";
    cin >> jumlahBukuYangDiBeli;

    for (int a = 0; a < jumlahBukuYangDiBeli; a++) {
        transactionData trx;
        int kodeBuku;

        cout << "Masukkan Kode Buku [1-" << totalBuku << "]: ";
        cin >> kodeBuku;

        trx.userId = loginUserIndex;
        trx.kodeBuku = --kodeBuku;

        transactions[latestTransactionIndex] = trx;
        latestTransactionIndex++;
    }

    cout << endl << "Transaksi berhasil di buat!"; getch();
    showMainMenu();
}

int showAllTransactions() {
    clearScr();

    cout << "\t\tTransaksi Sesi ini";
    cout << endl << "================================================";
    cout << endl << endl;

    printf("%-4s%-10s%-10s%-35s%-15s", "#", "Kasir", "Kode Buku", "Judul Buku", "Harga");

    float totalTransaksi = 0;

    cout << endl;

    for(int i = 0; i < latestTransactionIndex; i++) {
        transactionData trx = transactions[i];
        buku dataBuku = bukuBuku[trx.kodeBuku];

        char namaPendek[30];
        strncpy(namaPendek, dataBuku.nama, 30);

        printf("%-4d%-10s%-10d%-35s%-15.0f", (i+1), users[trx.userId].username, (trx.kodeBuku+1), namaPendek, dataBuku.harga);

        totalTransaksi = totalTransaksi + dataBuku.harga;

        cout << endl;

    }

    cout << endl << "Total Transaksi : Rp. "; printf("%0.f", totalTransaksi);

    cout << endl << "Tekan tombol apapun untuk kembali ke menu utama"; getch();
    showMainMenu();
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
