#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;
public:
    TokoElektronik() {
        etalase = {"Televisi", "Laptop", "Handphone"};
    }
    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        } catch (out_of_range &e) {
            throw string("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

void tampilData() {
    ifstream baca("gudang.txt");
    string baris;
    cout << "\n--- DATA BARANG GUDANG ---\n";
    int no = 1;
    bool kosong = true;
    while (getline(baca, baris)) {
        cout << no << ". " << baris << endl;
        no++;
        kosong = false;
    }
    if (kosong) cout << "(belum ada data)\n";
    baca.close();
}

void tambahData() {
    string nama, harga;
    cin.ignore();
    cout << "Nama barang : ";
    getline(cin, nama);
    cout << "Harga       : ";
    getline(cin, harga);
    ofstream tulis("gudang.txt", ios::app);
    tulis << nama << " - Rp" << harga << endl;
    tulis.close();
    cout << "Data berhasil ditambahkan!\n";
}

void updateData() {
    tampilData();
    int pilih;
    cout << "Nomor barang yg diubah : ";
    cin >> pilih;

    string nama, harga, baris;
    cin.ignore();
    cout << "Nama baru  : ";
    getline(cin, nama);
    cout << "Harga baru : ";
    getline(cin, harga);

    ifstream baca("gudang.txt");
    string data[100];
    int n = 0;
    while (getline(baca, baris)) {
        data[n] = baris;
        n++;
    }
    baca.close();

    if (pilih >= 1 && pilih <= n) {
        data[pilih - 1] = nama + " - Rp" + harga;
        ofstream tulis("gudang.txt");
        for (int i = 0; i < n; i++) tulis << data[i] << endl;
        tulis.close();
        cout << "Data berhasil diubah!\n";
    } else {
        cout << "Nomor tidak ada!\n";
    }
}

void hapusData() {
    tampilData();
    int pilih;
    cout << "Nomor barang yg dihapus : ";
    cin >> pilih;

    ifstream baca("gudang.txt");
    string data[100], baris;
    int n = 0;
    while (getline(baca, baris)) {
        data[n] = baris;
        n++;
    }
    baca.close();

    if (pilih >= 1 && pilih <= n) {
        ofstream tulis("gudang.txt");
        for (int i = 0; i < n; i++) {
            if (i != pilih - 1) tulis << data[i] << endl;
        }
        tulis.close();
        cout << "Data berhasil dihapus!\n";
    } else {
        cout << "Nomor tidak ada!\n";
    }
}

void simulasiEtalase() {
    TokoElektronik toko;
    cout << "\n--- SIMULASI ETALASE ---\n";

    // skenario 1 (sukses)
    try {
        cout << "Rak ke-1 : " << toko.ambilProduk(1) << endl;
    } catch (string pesan) {
        cout << pesan << endl;
    }

    // skenario 2 (gagal)
    try {
        cout << "Rak ke-5 : " << toko.ambilProduk(5) << endl;
    } catch (string pesan) {
        cout << pesan << endl;
    }
}

int main() {
    int menu;
    do {
        tampilData();
        cout << "\n=== MENU TOKO GIBRAN JAYA ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Ubah Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Simulasi Etalase\n";
        cout << "0. Keluar\n";
        cout << "Pilih : ";
        cin >> menu;

        switch (menu) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: updateData(); break;
            case 4: hapusData(); break;
            case 5: simulasiEtalase(); break;
            case 0: cout << "Keluar program.\n"; break;
            default: cout << "Menu tidak ada!\n";
        }
    } while (menu != 0);

    return 0;
}