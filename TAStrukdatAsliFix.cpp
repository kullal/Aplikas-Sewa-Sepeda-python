#include <iostream>
#include <vector>
#include <map>
#include <set> //set buat elemen yang ditentukan 
#include <climits> //tentukan batasa nilai dengan INT_MAX dan INT_MN
#include <algorithm> //algoritma sort,dan find

using namespace std;

struct Sepeda {
    string nama;
    int hargaSewa;
    bool disewa;
    string cabang;
    Sepeda* next;

    Sepeda(string n, int h, bool d, string c) : nama(n), hargaSewa(h), disewa(d), cabang(c),  next(nullptr) {}
};

struct Penyewa {
    string idPenyewa;
    string namaPenyewa;
    int umur;
    Penyewa* next;

    Penyewa(string id, string nama, int umur) : idPenyewa(id), namaPenyewa(nama), umur(umur), next(nullptr) {}
};

struct SepedaList {
    Sepeda* front = nullptr;
    Sepeda* rear = nullptr;

    void append(Sepeda* newSepeda) {
        if (!rear) {
            front = rear = newSepeda;
        } else {
            rear->next = newSepeda;
            rear = newSepeda;
        }
    }

    void display() {
        vector<Sepeda*> bicycles;
        for (Sepeda* temp = front; temp != nullptr; temp = temp->next) {
            bicycles.push_back(temp);
        }

        sort(bicycles.begin(), bicycles.end(), [](Sepeda* a, Sepeda* b) {
            return a->hargaSewa < b->hargaSewa;
        });

        cout << "Daftar Sepeda:\n";
        for (auto& bike : bicycles) {
            cout << "Nama: " << bike->nama << ", Harga Sewa: " << bike->hargaSewa << ", Cabang: " << bike->cabang;
            if (bike->disewa) cout << " (Sedang disewa)";
            cout << endl;
        }
        cout << "\n";
    }

    void displayByCabang(string cabang) {
        Sepeda* temp = front;
        cout << "Sepeda di Cabang " << cabang << ":\n";
        while (temp) {
            if (temp->cabang == cabang) {
                cout << "Nama: " << temp->nama << ", Harga Sewa: " << temp->hargaSewa;
                if (temp->disewa) {
                    cout << " (Sedang disewa)";
                }
                cout << endl;
            }
            temp = temp->next;
        }
        cout << "\n";
    }

    Sepeda* searchByNama(string nama) {
        Sepeda* temp = front;
        while (temp) {
            if (temp->nama == nama && !temp->disewa) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void remove(string nama, string cabang) {
        Sepeda* temp = front;
        Sepeda* prev = nullptr;
        while (temp) {
            if (temp->nama == nama && temp->cabang == cabang) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    front = temp->next;
                }
                if (temp == rear) {
                    rear = prev;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }
};

struct PenyewaList {
    Penyewa* front = nullptr;
    Penyewa* rear = nullptr;

    void add(Penyewa* newPenyewa) {
        if (!rear) {
            front = rear = newPenyewa;
        } else {
            rear->next = newPenyewa;
            rear = newPenyewa;
        }
    }

    Penyewa* search(string idOrName) {
        Penyewa* temp = front;
        while (temp) {
            if (temp->idPenyewa == idOrName || temp->namaPenyewa == idOrName) {
                return temp;
            }               

            temp = temp->next;
        }
        return nullptr;
    }

    void displaySortedByID(map<string, string>& rentedBikes) {
        if (!front) {
            cout << "Tidak ada penyewa untuk ditampilkan.\n";
            return;
        }

        vector<Penyewa*> penyewaList;
        for (Penyewa* temp = front; temp != nullptr; temp = temp->next) {
            penyewaList.push_back(temp);
        }

        sort(penyewaList.begin(), penyewaList.end(), [](Penyewa* a, Penyewa* b) {
            return a->idPenyewa < b->idPenyewa;
        });

        cout << "Daftar Penyewa (diurutkan berdasarkan ID):\n";
        for (auto& p : penyewaList) {
            cout << "ID Penyewa: " << p->idPenyewa << ", Nama Penyewa: " << p->namaPenyewa << ", Umur Penyewa: ";
            if (rentedBikes.find(p->idPenyewa) != rentedBikes.end()) {
                cout << ", Sepeda yang disewa: " << rentedBikes[p->idPenyewa];
            }
            cout << endl;
        }
        cout << "\n";
    }
};

#define N 6

map<int, string> cityMap = {
    {0, "Jakarta"},
    {1, "Bandung"},
    {2, "Surabaya"},
    {3, "Medan"},
    {4, "Makassar"},
    {5, "Denpasar"}
};

int Edge[N][N] = {
    {0, 4, 0, 3, 0, 5},
    {0, 0, 3, 4, 4, 0},
    {0, 0, 0, 2, 0, 0},
    {0, 0, 0, 0, 3, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
};

struct GraphTB {
    map<int, string> V;
    int E[N][N];
};

void Jalur(GraphTB G) {
    int i, j; // Deklarasi variabel i dan j sebagai indeks perulangan
    printf("Daftar Garis (Edge) : \n"); // Mencetak judul daftar garis (edge)
    // Loop pertama untuk mengakses setiap simpul (vertex) dalam graf
    for (i = 0; i < N; i++) {
        // Loop kedua untuk mengakses simpul berikutnya setelah i
        for (j = i + 1; j < N; j++) {
            // Mengecek apakah ada edge (garis) antara simpul i dan j
            if (G.E[i][j] > 0) {
                // Jika ada, cetak pasangan simpul (vertex) dan bobotnya
                printf("(%s, %s) = %d\n", G.V[i].c_str(), G.V[j].c_str(), G.E[i][j]);
            }
        }
    }
}

void DataGraph(GraphTB* G) {
    for (int i = 0; i < N; i++)
        G->V[i] = cityMap[i];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            G->E[i][j] = Edge[i][j];
}

vector<int> dijkstra(GraphTB G, int src) {
    vector<int> dist(N, INT_MAX);
    dist[src] = 0;
    set<pair<int, int>> pq;
    pq.insert({0, src});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

    
        for (int v = 0; v < N; v++) { // Loop melalui semua node
            if (G.E[u][v] > 0 && dist[u] + G.E[u][v] < dist[v]) { // Jika ada edge antara node u dan v, dan jarak baru lebih kecil dari jarak saat ini
        pq.erase({dist[v], v}); // Hapus jarak saat ini dari priority queue
        dist[v] = dist[u] + G.E[u][v]; // Perbarui jarak ke node v
        pq.insert({dist[v], v}); // Masukkan jarak baru ke priority queue
            }
        }
    }
    return dist;
}

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

bool loginAdmin() {
    string username, password;
    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    return (username == "Udang" && password == "Galah");
}

int main() {
    SepedaList sepedaList;
    sepedaList.append(new Sepeda("BMX", 10000, false, "Jakarta"));
    sepedaList.append(new Sepeda("Downhill", 12000, false, "Bandung"));
    sepedaList.append(new Sepeda("Listrik", 15000, false, "Surabaya"));
    sepedaList.append(new Sepeda("RodaTiga", 13000, false, "Medan"));
    sepedaList.append(new Sepeda("BMX", 10000, false, "Makassar"));
    sepedaList.append(new Sepeda("Downhill", 12000, false, "Surabaya"));
    sepedaList.append(new Sepeda("Downhill", 12000, false, "Makassar"));
    sepedaList.append(new Sepeda("Downhill", 12000, false, "Denpasar"));
    sepedaList.append(new Sepeda("Downhill", 12000, false, "Denpasar"));
    sepedaList.append(new Sepeda("BMX", 10000, false, "Bandung"));

    PenyewaList penyewaList;
    GraphTB G;
    DataGraph(&G);
    int choice;
    map<string, string> rentedBikes; // Mapping penyewa ID to bike name

    do {
    clearScreen();
    cout << "Aplikasi Rental Sepeda\n";
    cout << "================================\n";
    cout << "1. Login Admin\n";
    cout << "2. Tampilkan Sepeda\n";
    cout << "3. Sewa Sepeda\n";
    cout << "4. Cabang Terdekat\n";
    cout << "5. Keluar\n";
    cout << "================================\n";
    cout << "Pilih opsi: ";
    cin >> choice;
    cout << "\n";

    switch (choice) {
        case 1: {
            if (loginAdmin()) {
                bool isAdmin = true;
                do {
                    clearScreen();
                    cout << "\nMenu Admin\n";
                    cout << "================================\n";
                    cout << "1. Tambah Sepeda\n";
                    cout << "2. Hapus Sepeda Rusak\n";
                    cout << "3. Cari Penyewa\n";
                    cout << "4. Tampilkan Penyewa\n";
                    cout << "5. Tampilkan Sepeda\n";
                    cout << "6. Logout\n";
                    cout << "================================\n";
                    cout << "Pilih opsi: ";
                    cin >> choice;
                    cout << "\n";

                    switch (choice) {
                        case 1: {
                            Sepeda* newSepeda = new Sepeda("", 0, false, "");
                            cout << "Masukkan nama sepeda: ";
                            cin >> newSepeda->nama;
                            cout << "Masukkan harga sewa: ";
                            cin >> newSepeda->hargaSewa;
                            cout << "Masukkan nama cabang (Jakarta, Bandung, Surabaya, Medan, Makassar, Denpasar): ";
                            cin >> newSepeda->cabang;
                            sepedaList.append(newSepeda);
                            cout << "\nSepeda baru berhasil ditambahkan!\n\n";
                            break;
                        }
                        case 2: {
                            // Menampilkan semua cabang dan sepeda di dalamnya
                            for (auto& city : cityMap) {
                                sepedaList.displayByCabang(city.second);
                            }

                            string branch;
                            cout << "Pilih cabang untuk menghapus sepeda (Jakarta, Bandung, Surabaya, Medan, Makassar, Denpasar): ";
                            cin >> branch;

                            auto it = find_if(cityMap.begin(), cityMap.end(), [&](const pair<int, string>& p){ return p.second == branch; });
                            if (it == cityMap.end()) {
                                cout << "Cabang tidak valid.\n";
                            } else {
                                string nama;
                                cout << "Masukkan nama sepeda yang rusak: ";
                                cin >> nama;

                                Sepeda* bicycleToRemove = sepedaList.searchByNama(nama);
                                if (bicycleToRemove) {
                                    sepedaList.remove(nama, branch);
                                    cout << "\nSepeda " << nama << " dari cabang " << branch << " berhasil dihapus!\n\n";
                                } else {
                                    cout << "\nSepeda tidak ditemukan di cabang ini.\n\n";
                                }
                            }
                            break;
                        }
                        case 3: {
                            string searchTerm;
                            cout << "Masukkan Nama Penyewa: ";
                            cin.ignore();
                            getline(cin, searchTerm);

                            // Mengubah searchTerm menjadi huruf kecil
                            transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

                            bool found = false;
                            for (const auto& entry : rentedBikes) {
                                string nama = entry.first;
                                string bike = entry.second;

                                // Mengubah nama menjadi huruf kecil
                                transform(nama.begin(), nama.end(), nama.begin(), ::tolower);

                                // Mencari berdasarkan Nama  (case-insensitive)
                                if (nama == searchTerm || bike.find(searchTerm) != string::npos) { 
                                    cout << "Penyewa ditemukan:\n";
                                    cout << "Nama: " << nama << endl;
                                    cout << "Sepeda yang disewa: " << bike << endl;
                                    cout << "Umur: " << umur << endl;
                                    cout << endl;
                                    found = true;
                                }
                            }

                            if (!found) {
                                cout << "Penyewa tidak ditemukan.\n\n";
                            }
                            break;
                        }
                        case 4: {
                            penyewaList.displaySortedByID(rentedBikes);
                            break;
                        }
                        case 5: {
                        sepedaList.display();
                        break;
                        }
                        case 6: {
                            isAdmin = false;
                            break;
                        }
                        default: {
                            cout << "Opsi tidak valid. Silakan coba lagi.\n";
                            break;
                        }
                    }
                    cout << "Tekan enter untuk melanjutkan...";
                    cin.ignore();
                    cin.get();
                } while (isAdmin);
            } else {
                cout << "Login gagal!\n";
            }
            break;
        }
        case 2: {
            sepedaList.display();
            break;
        }
        case 3: { // Sewa Sepeda
            string lokasi;
            cout << "Masukkan nama cabang Anda saat ini (Jakarta, Bandung, Surabaya, Medan, Makassar, Denpasar): ";
            cin >> lokasi;

            auto it = find_if(cityMap.begin(), cityMap.end(), [&](const pair<int, string>& p){ return p.second == lokasi; });
            if (it == cityMap.end()) {
                cout << "Cabang tidak valid.\n";
            } else {
                int locationIndex = distance(cityMap.begin(), it);

                // Menampilkan semua cabang dan sepeda di dalamnya
                for (auto& city : cityMap) {
                    sepedaList.displayByCabang(city.second);
                }

                string namaSepeda;
                cout << "\nMasukkan nama sepeda yang ingin disewa: ";
                cin >> namaSepeda;

                // Memasukkan data penyewa
                string idPenyewa, namaPenyewa;
                cout << "Masukkan ID Penyewa: ";
                cin >> idPenyewa;
                cout << "Masukkan Nama Penyewa: ";
                cin >> namaPenyewa;

                Penyewa penyewa(idPenyewa, namaPenyewa);

                // Tambahkan penyewa ke dalam daftar
                penyewaList.add(new Penyewa(penyewa.idPenyewa, penyewa.namaPenyewa));

                // Mencari cabang terdekat dengan sepeda yang diinginkan
                vector<int> dist = dijkstra(G, locationIndex); // Menjalankan algoritma Dijkstra untuk mencari jarak terpendek dari lokasi saat ini ke semua cabang dalam graf G.
                int minDist = INT_MAX; // Inisialisasi jarak minimum dengan nilai maksimum integer.
                int nearestBranch = -1; // Inisialisasi indeks cabang terdekat dengan -1.
                Sepeda* nearestBicycle = NULL; // Inisialisasi pointer untuk sepeda terdekat dengan NULL.

                for (Sepeda* s = sepedaList.front; s != NULL; s = s->next) { // Iterasi melalui semua sepeda dalam daftar sepeda.
                    // Cari indeks cabang dari sepeda s dengan mencari dalam peta kota (cityMap).
                    auto it = find_if(cityMap.begin(), cityMap.end(), [&](const pair<int, string>& p){ return p.second == s->cabang; });
                    int branchIndex = distance(cityMap.begin(), it); // Menghitung jarak (index) dari awal cityMap ke cabang yang ditemukan.
                    
                    // Memeriksa apakah sepeda memiliki nama yang sesuai, tidak disewa, dan jarak ke cabang lebih kecil dari jarak minimum saat ini.
                    if (s->nama == namaSepeda && !s->disewa && dist[branchIndex] < minDist) {
                        minDist = dist[branchIndex]; // Memperbarui jarak minimum dengan jarak ke cabang saat ini.
                        nearestBranch = branchIndex; // Memperbarui indeks cabang terdekat dengan indeks cabang saat ini.
                        nearestBicycle = s; // Menyimpan pointer ke sepeda terdekat.
                    }
                }

                if (nearestBranch == -1) {
                    cout << "\nSepeda tidak ditemukan atau sudah disewa.\n\n";
                } else {
                    // Menampilkan informasi jarak dan cabang terdekat
                    cout << "\nSepeda ini tersedia di cabang " << cityMap[nearestBranch] << ".\n";
                    cout << "Jarak dari cabang Anda ke cabang sepeda ini adalah " << minDist << " km.\n";

                    // Meminta persetujuan
                    char agree;
                    cout << "Apakah Anda setuju untuk menyewa sepeda ini? (y/n): ";
                    cin >> agree;

                    if (agree == 'y' || agree == 'Y') {
                        nearestBicycle->disewa = true;
                        rentedBikes[idPenyewa] = namaSepeda; // Menyimpan data penyewa
                        cout << "\nSepeda " << namaSepeda << " berhasil disewa oleh ";
                        cout << penyewa.namaPenyewa << " (ID: " << penyewa.idPenyewa << ")!\n\n";
                    } else {
                        cout << "\nPeminjaman dibatalkan.\n\n";
                    }
                }
            }
            break;
        }
        case 4: {
            string lokasi;
            cout << "Masukkan nama cabang Anda saat ini (Jakarta, Bandung, Surabaya, Medan, Makassar, Denpasar): ";
            cin >> lokasi;

            auto it = find_if(cityMap.begin(), cityMap.end(), [&](const pair<int, string>& p){ return p.second == lokasi; });
            if (it == cityMap.end()) {
                cout << "Cabang tidak valid.\n";
            } else {
                int locationIndex = distance(cityMap.begin(), it);
                vector<int> dist = dijkstra(G, locationIndex);
                int minDist = INT_MAX;
                int nearest = -1;

                for (int i = 0; i < N; ++i) {
                    if (i != locationIndex && dist[i] < minDist) {
                        minDist = dist[i];
                        nearest = i;
                    }
                }

                if (nearest != -1) {
                    cout << "Cabang terdekat adalah cabang " << cityMap[nearest] << " dengan jarak " << minDist << " km.\n";
                } else {
                    cout << "Tidak ada cabang lain yang ditemukan.\n";
                }
            }
            break;
        }
        case 5: {
            exit(0);
            break;
        }
        default: {
            cout << "Opsi tidak valid. Silakan coba lagi.\n";
            break;
        }
    }

    cout << "Tekan enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
} while (true);

    return 0;
}
