#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#define MAX_USERS 4
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define DATA_FILE "users.dat"

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    float saldo; // Tambahkan saldo ke struktur Pengguna
} Pengguna;

void getPassword(char *password);
void daftarPengguna(Pengguna pengguna[], int* jumlah);
int loginPengguna(Pengguna pengguna[], int jumlah, char namaUser[USERNAME_LENGTH]);
void muatPengguna(Pengguna pengguna[], int* jumlah);
void simpanPengguna(Pengguna pengguna[], int jumlah);
void lihatPengguna(Pengguna pengguna[], int jumlah);
void tambahSaldo(Pengguna pengguna[], int jumlah, const char namaUser[USERNAME_LENGTH], float jumlahSaldo);
void tampilkanSaldo(const char namaUser[USERNAME_LENGTH], Pengguna pengguna[], int jumlah);
void transferSaldo(Pengguna pengguna[], int jumlah, const char namaUser[USERNAME_LENGTH]);
void beli(Pengguna pengguna[], int jumlah, const char namaUser[USERNAME_LENGTH]);


void getPassword(char *password) {
    int i = 0;
    char ch;
    while ((ch = _getch()) != '\r') {  // \r is carriage return (Enter key)
        if (ch == '\b' && i > 0) {  // handle backspace
            printf("\b \b");
            i--;
        } else if (ch != '\b' && i < PASSWORD_LENGTH - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}

void daftarPengguna(Pengguna pengguna[], int* jumlah) {
    if (*jumlah >= MAX_USERS) {
    	system("cls");
    	printf("=====================REGISTER====================\n\n");
    	printf("-------------------------------------------------\n");
        printf("Batas pengguna tercapai. Tidak dapat mendaftar.\n");
        printf("-------------------------------------------------\n");
        sleep(2);
        return;
    }

    Pengguna penggunaBaru;
    char konfirmasiPassword[PASSWORD_LENGTH];

    printf("=====================REGISTER====================\n\n");
    printf("Masukkan username: ");
    fgets(penggunaBaru.username, USERNAME_LENGTH, stdin);
    penggunaBaru.username[strcspn(penggunaBaru.username, "\n")] = '\0';  // Membersihkan karakter baris baru
    
    system("cls");
    int i;
    for (i = 0; i < *jumlah; i++) {
        if (strcmp(pengguna[i].username, penggunaBaru.username) == 0) {
        	printf("=====================REGISTER====================\n\n");
        	printf("-------------------------------------------------\n");
            printf("Username sudah ada. Pilih username yang berbeda.\n");
            printf("-------------------------------------------------\n");
            sleep(2);
            system("cls");
            return;
        }
    }

    int passwordMatch;
    do {
    	printf("=====================REGISTER====================\n\n");
    	printf("Hello %s\n\n", penggunaBaru.username);
        // Meminta password pertama
        printf("Masukkan kata sandi: ");
        getPassword(penggunaBaru.password);
        printf("\n");

        // Meminta konfirmasi password
        printf("Konfirmasi kata sandi: ");
        getPassword(konfirmasiPassword);
        printf("\n");
        system("cls");

        // Memeriksa apakah kedua password cocok
        if (strcmp(penggunaBaru.password, konfirmasiPassword) != 0) {
        	printf("=====================REGISTER====================\n\n");
    		printf("Hello %s\n\n", penggunaBaru.username);
    		printf("-------------------------------------------------\n");
            printf("   Kata sandi tidak cocok. Silakan coba lagi.\n");
            printf("-------------------------------------------------\n");
            sleep(2);
            system("cls");
            passwordMatch = 0;
        } else {
            passwordMatch = 1;
        }
    } while (!passwordMatch);

    

    penggunaBaru.saldo = 0.0;  // Set saldo awal Rp.0
    pengguna[*jumlah] = penggunaBaru;
    (*jumlah)++;
    simpanPengguna(pengguna, *jumlah);
    system("cls");
    printf("=====================REGISTER====================\n\n");
    printf("YEY! Berhasil mendaftar, sekarang kamu bisa login: \n\n");
    printf("Username: %s\n", penggunaBaru.username);
    printf("Kata Sandi: %s\n\n", penggunaBaru.password);
    system("pause");
}

int loginPengguna(Pengguna pengguna[], int jumlah, char namaUser[USERNAME_LENGTH]) {
    char nama[USERNAME_LENGTH];
    char kataSandi[PASSWORD_LENGTH];
	
	system("cls");
	printf("======================LOGIN======================\n\n");
    printf("Masukkan username: ");
    fgets(nama, USERNAME_LENGTH, stdin);
    nama[strcspn(nama, "\n")] = '\0';  // Membersihkan karakter baris baru

    printf("Masukkan kata sandi: ");
    getPassword(kataSandi);
    printf("\n");
    int i;
    for (i = 0; i < jumlah; i++) {
        if (strcmp(pengguna[i].username, nama) == 0 && strcmp(pengguna[i].password, kataSandi) == 0) {
            strcpy(namaUser, nama);
            return 1;
        }
    }
    return 0;
}

void muatPengguna(Pengguna pengguna[], int* jumlah) {
    FILE *file = fopen(DATA_FILE, "rb");
    if (!file) {
        *jumlah = 0;
        return;
    }
    *jumlah = 0;
    while (fread(&pengguna[*jumlah], sizeof(Pengguna), 1, file)) {
        (*jumlah)++;
    }
    fclose(file);
}

void simpanPengguna(Pengguna pengguna[], int jumlah) {
    FILE *file = fopen(DATA_FILE, "wb");
    if (!file) {
    	system("cls");
    	printf("=====================REGISTER====================\n\n");
    	printf("-------------------------------------------------\n");
        printf("\n\n\nGagal menyimpan pengguna.\n");
        printf("-------------------------------------------------\n");
        return;
    }
    fwrite(pengguna, sizeof(Pengguna), jumlah, file);
    fclose(file);
}

void lihatPengguna(Pengguna pengguna[], int jumlah) {
    printf("==============Pengguna BRB Terdaftar==============\n\n");
    printf("--------------------------------------------------\n");
    int i;
    for (i = 0; i < jumlah; i++) {
        printf("%d. %s\n", i + 1, pengguna[i].username);
    }
    printf("--------------------------------------------------\n");
}

void tambahSaldo(Pengguna pengguna[], int jumlah, const char namaUser[USERNAME_LENGTH], float jumlahSaldo) {
    int i;
	for (i = 0; i < jumlah; i++) {
        if (strcmp(pengguna[i].username, namaUser) == 0) {
            pengguna[i].saldo += jumlahSaldo;
            printf("\n--------------------------------------------------\n");
            printf("Saldo berhasil ditambah. \nSaldo saat ini: Rp%.2f\n", pengguna[i].saldo);
            simpanPengguna(pengguna, jumlah);
            break;
        }
    }
}

void tampilkanSaldo(const char namaUser[USERNAME_LENGTH], Pengguna pengguna[], int jumlah) {
    int i;
	for (i = 0; i < jumlah; i++) {
        if (strcmp(pengguna[i].username, namaUser) == 0) {
            printf("nama: %s\n", pengguna[i].username);
            printf("Saldo saat ini: Rp.%.2f\n", pengguna[i].saldo);
            break;
        }
    }
}

void transferSaldo(Pengguna pengguna[], int jumlah, const char namaUser[USERNAME_LENGTH]) {
    char penerima[USERNAME_LENGTH];
    float jumlahTransfer;

	printf("==================BRB TRANSFER==================\n\n");
    printf("Masukkan username penerima: ");
    fgets(penerima, USERNAME_LENGTH, stdin);
    penerima[strcspn(penerima, "\n")] = '\0';// Membersihkan karakter baris baru
    
    printf("Masukkan jumlah yang ingin ditransfer: ");
    scanf("%f", &jumlahTransfer);
    getchar();  // Membersihkan karakter baris baru dari buffer
    printf("\n------------------------------------------------\n");
    
    int foundSender = -1, foundReceiver = -1;

    int i;
	for (i = 0; i < jumlah; i++) {
        if (strcmp(pengguna[i].username, namaUser) == 0) {
            foundSender = i;
        }
        if (strcmp(pengguna[i].username, penerima) == 0) {
            foundReceiver = i;
        }
    }

    if (foundSender == -1) {
        printf("Pengirim tidak ditemukan.\n");
    } else if (foundReceiver == -1) {
        printf("Penerima tidak ditemukan.\n");
    } else if (pengguna[foundSender].saldo < jumlahTransfer) {
        printf("Saldo tidak mencukupi untuk transfer.\n");
    } else {
        pengguna[foundSender].saldo -= jumlahTransfer;
        pengguna[foundReceiver].saldo += jumlahTransfer;
        printf("Transfer berhasil.\nSaldo saat ini: Rp%.2f\n", pengguna[foundSender].saldo);
        simpanPengguna(pengguna, jumlah);
    }
}

void beli(Pengguna pengguna[], int jumlah, const char namaUser[USERNAME_LENGTH]) {
    float jumlahPembelian;
    float cashback = 0.0;
	printf("====================BRB BELI====================\n\n");
    printf("Masukkan jumlah pembelian: ");
    scanf("%f", &jumlahPembelian);
    getchar();  // Membersihkan karakter baris baru dari buffer
    printf("\n------------------------------------------------\n");
    
	int i;
    for (i = 0; i < jumlah; i++) {
        if (strcmp(pengguna[i].username, namaUser) == 0) {
            if (pengguna[i].saldo < jumlahPembelian) {
                printf("Saldo tidak mencukupi untuk pembelian.\n");
                return;
            }
            pengguna[i].saldo -= jumlahPembelian;

            if (jumlahPembelian > 500000) {
                cashback = 10000;
            } else if (jumlahPembelian > 100000) {
                cashback = 5000;
            }

            pengguna[i].saldo += cashback;
            printf("Pembelian berhasil.\n");
            if (cashback > 0) {
                printf("Anda mendapatkan cashback sebesar Rp%.2f.\n", cashback);
            }
            printf("------------------------------------------------\n\n");
            printf("Saldo saat ini: Rp%.2f\n", pengguna[i].saldo);
            simpanPengguna(pengguna, jumlah);
            return;
        }
    }
}


int main() {
    char opsi[2];
    int mode;
    char namaUser[USERNAME_LENGTH] = "";
    Pengguna pengguna[MAX_USERS];
    int jumlah = 0;
    muatPengguna(pengguna, &jumlah);

menu:
    while (1) {
        int pilihan;
        system("cls");
        printf("\033[1;36m");
        printf("=======================BRB========================\n");
        printf("    Selamat Datang di BRB (Bank Rakyat Blater)\n");
        printf("--------------------------------------------------\n\n");
        printf("1. Daftar\n");
        printf("2. Login\n");
        printf("3. Keluar\n\n");
        printf("--------------------------------------------------\n");
        printf("Pilih [1...3] >> ");
        scanf("%d", &pilihan);
        getchar();  // Membersihkan karakter baris baru dari buffer

        switch (pilihan) {
            case 1:
                system("cls");
                daftarPengguna(pengguna, &jumlah);
                break;
            case 2:
                if (loginPengguna(pengguna, jumlah, namaUser)) {
                    system("cls");
                    printf("======================LOGIN======================\n\n");
                    printf("-------------------------------------------------\n");
                    printf("Berhasil Masuk! Selamat datang, %s.\n", namaUser);
                    printf("-------------------------------------------------\n");
                    sleep(2);
                    goto masuk;  // Pergi ke bagian utama program
                } else {
                	system("cls");
                	printf("======================LOGIN======================\n\n");
                    printf("-------------------------------------------------\n");
                    printf("        Username atau kata sandi salah.\n");
                    printf("-------------------------------------------------\n");
                    sleep(2);
                }
                break;
            case 3:
            	system("cls");
            	printf("\n\n\n Transaksi Mudah, Cepat dan Aman hanya di BRB\n\n\n");
                exit (0);
            default:
            	system("cls");
            	printf("=======================BRB========================\n");
        		printf("    Selamat Datang di BRB (Bank Rakyat Blater)\n");
       		 	printf("--------------------------------------------------\n\n");
                printf(" Pilihan tidak sesuai! Pilih angka diantara 1-3!\n\n");
                printf("--------------------------------------------------\n");
        }
    }

masuk:
    do {
        system("cls");
        printf("=====================MENU-BRB=====================\n\n");
        tampilkanSaldo(namaUser, pengguna, jumlah);
        printf("\n--------------------------------------------------\n\n");
        printf("1. Top Up\n");
        printf("2. Beli\n");
        printf("3. Transfer antar akun\n\n");
        printf("4. Lihat Semua Pengguna Terdaftar\n");
        printf("5. Reset(akan menghapus semua akun yang terdaftar)\n");
        printf("6. Log Out\n\n");
        printf("--------------------------------------------------\n");
        printf("\nPilih [1...6] >> ");
        scanf("%d", &mode);
        getchar();  // Membersihkan karakter baris baru dari buffer
        
        switch (mode) {
            case 1: {
                float jumlahSaldo;
                system("cls");
                printf("====================BRB TOP-UP====================\n\n");
                printf("Masukkan jumlah saldo yang ingin di-top up: ");
                scanf("%f", &jumlahSaldo);
                tambahSaldo(pengguna, jumlah, namaUser, jumlahSaldo);
                break;
            }
            case 2:
                system("cls");
                beli(pengguna, jumlah, namaUser);
                break;
            case 3:
                system("cls");
                transferSaldo(pengguna, jumlah, namaUser);
                break;
            case 4:
                system("cls");
                lihatPengguna(pengguna, jumlah);
                break;
            case 5:
                system("cls");
                printf("===============HAPUS SEMUA AKUN BRB===============\n\n");
                printf("\n--------------------------------------------------\n");
                printf("Semua akun telah terhapus!\n");
                printf("Silahkan daftar ulang akun\n");
                printf("--------------------------------------------------\n");
                remove(DATA_FILE);
                main();
                return 0;
            case 6:
                system("cls");
                goto menu;
                break;
            default:
                system("cls");
                printf("=====================MENU-BRB=====================\n\n");
                printf("\n--------------------------------------------------\n");
                printf("Pilihan tidak sesuai!\nPilih angka diantara 1-6!\n");
                printf("--------------------------------------------------\n");
                sleep(3);
                goto masuk;
                break;
        }
        sleep(1);
        printf("\n\n\n--------------------------------------------------\n");
        printf("Menu/Log Out [a/b] >> ");
        scanf("%s", opsi);
    } while (opsi[0] == 'a');
    goto menu;
}

