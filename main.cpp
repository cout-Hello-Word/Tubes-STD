#include "transport.h"

int main() {
    transportNetwork cityTransport;
    initNetwork(cityTransport);

    int pilihan;
    char startID[50], destID[50], blockedID[50];
    int roadLength, safetyScore;

    do {
        cout << "==============================================" << endl;
        cout << "             Aplikasi Transportasi            " << endl;
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
            cin.getline(startID, 50);
            addIntersection(cityTransport, startID);
            cout << "Persimpangan \"" << startID << "\" berhasil ditambahkan!" << endl;
            break;
        case 2:
            cout << "Masukkan Persimpangan Asal: ";
            cin.getline(startID, 50);
            cout << "Masukkan Persimpangan Tujuan: ";
            cin.getline(destID, 50);
            cout << "Masukkan Panjang Jalan (km): ";
            cin >> roadLength;
            cout << "Masukkan Skor Keamanan Jalan (1-10): ";
            cin >> safetyScore;
            cin.ignore();
            addRoad(cityTransport, startID, destID, roadLength, safetyScore);
            cout << "Jalan dari \"" << startID << "\" ke \"" << destID << "\" berhasil ditambahkan!" << endl;
            break;
        case 3:
            cout << "\n========= Jaringan Transportasi Kota =========" << endl;
            printNetwork(cityTransport);
            cout << "==============================================" << endl;
            break;
        case 4:
            cout << "Masukkan Persimpangan Asal: ";
            cin.getline(startID, 50);
            cout << "Masukkan Persimpangan Tujuan: ";
            cin.getline(destID, 50);
            searchByShortestPath(cityTransport, startID, destID);
            break;
        case 5:
            cout << "Masukkan Persimpangan Asal: ";
            cin.getline(startID, 50);
            cout << "Masukkan Persimpangan Tujuan: ";
            cin.getline(destID, 50);
            searchBySafestPath(cityTransport, startID, destID);
            break;
        case 6:
            cout << "Masukkan Persimpangan Asal: ";
            cin.getline(startID, 50);
            cout << "Masukkan Persimpangan Tujuan: ";
            cin.getline(destID, 50);
            cout << "Masukkan Persimpangan yang Harus Dihindari (contoh: Simpang Dago): ";
            cin.getline(blockedID, 50);
            searchByEmergencyRoute(cityTransport, startID, destID, blockedID);

            break;
        case 0:
            cout << "Terima kasih telah menggunakan aplikasi kami. Sampai jumpa!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
