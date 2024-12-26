#include "transport.h"

int main() {
    transportNetwork cityTransport;
    initNetwork(cityTransport);

    int pilihan;
    string startID, destID, blockedID;
    int roadLength, safetyScore;

    do {
        cout << "==============================================";
        cout << "\n   Selamat Datang di Aplikasi Transportasi  " << endl;
        cout << "==============================================" << endl;
        cout << "1. Tambah Persimpangan" << endl;
        cout << "2. Tambah Jalan" << endl;
        cout << "3. Tampilkan Jaringan Transportasi" << endl;
        cout << "4. Cari Rute Terpendek" << endl;
        cout << "5. Cari Rute Teraman" << endl;
        cout << "6. Cari Rute Darurat" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            cout << "Masukkan Nama Persimpangan: ";
            getline(cin, startID);
            addIntersection(cityTransport, startID);
            break;
        case 2:
            cout << "Masukkan Persimpangan Asal: ";
            getline(cin, startID);
            cout << "Masukkan Persimpangan Tujuan: ";
            getline(cin, destID);
            cout << "Masukkan Panjang Jalan (km): ";
            cin >> roadLength;
            cout << "Masukkan Skor Keamanan Jalan (1-10): ";
            cin >> safetyScore;
            cin.ignore();
            addRoad(cityTransport, startID, destID, roadLength, safetyScore);
            break;
        case 3:
            cout << "\n========= Jaringan Transportasi Kota =========" << endl;
            printNetwork(cityTransport);
            break;
        case 4:
            cout << "Masukkan Persimpangan Asal: ";
            getline(cin, startID);
            cout << "Masukkan Persimpangan Tujuan: ";
            getline(cin, destID);
            searchByShortestPath(cityTransport, startID, destID);
            break;
        case 5:
            cout << "Masukkan Persimpangan Asal: ";
            getline(cin, startID);
            cout << "Masukkan Persimpangan Tujuan: ";
            getline(cin, destID);
            searchBySafestPath(cityTransport, startID, destID);
            break;
        case 6:
            cout << "Masukkan Persimpangan Asal: ";
            getline(cin, startID);
            cout << "Masukkan Persimpangan Tujuan: ";
            getline(cin, destID);
            cout << "Masukkan Persimpangan yang Harus Dihindari (contoh: A): ";
            getline(cin, blockedID);
            findEmergencyRoute(cityTransport, startID, destID, blockedID);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan aplikasi kami dan sampai jumpa!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
