#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void formatRupiah(int num, char *buffer) {
    char temp[50]; rev[50];
    int i, j = 0, len, pos = 0;

    sprintf(temp, "%d", num);
    len = strlen(temp);

    for (i = len - 1; i >= 0; i--) {
        rev[pos++] = temp[i];
        if ((len - i) % 3 == 0 && i != 0) {
            rev[pos++] = '.';
        }
    }
    rev[pos] = '\0';

    len = strlen(rev);
    for (i = len - 1; i >= 0; i--) 
        buffer[j++] = rev[i];
    
    buffer[j] = '\0';
}

int userExists(const char *username) {
    FILE *fp = fopen("users.txt", "r");
    char u[30], p[30];
    if (!fp) return 0;

    while (fscanf(fp, "%s %s", u, p) != EOF) {
        if (strcmp(u, username) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void saveUser(const char *username, const char *password) {
    FILE *fp = fopen("users.txt", "a");
    if (!fp) return;
    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
}

int checkLogin(const char *username, const char *password) {
    FILE *fp = fopen("users.txt", "r");
    char u[30], p[30];
    if (!fp) return 0;

    while (fscanf(fp, "%s %s", u, p) != EOF) {
        if (strcmp(u, username) == 0 && strcmp(p, password) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void saveHistory(const char *username, const char *plat,
                 const char *jenis, const char *tambahan, int total) {
    FILE *fp = fopen("history.txt", "a");
    if (!fp) return;
    fprintf(fp, "%s|%s|%s|%s|%d\n",
            username, plat, jenis, tambahan, total);
    fclose(fp);
}

void showHistory(const char *username) {
    FILE *fp = fopen("history.txt", "r");
    char line[200];
    int found = 0;
clearScreen();
    printf("====================================\n");
    printf("        RIWAYAT AKTIVITAS AKUN        \n");
    printf("====================================\n");

    if (!fp) {
        printf("Belum ada riwayat transaksi.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        char u[30], plat[30], jenis[30], tambahan[30];
        int total;

        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%d",
               u, plat, jenis, tambahan, &total);

        if (strcmp(u, username) == 0) {
            char totalFormat[50];
            formatRupiah(total, totalFormat);

            printf("Plat Mobil  : %s\n", plat);
            printf("Jenis Cuci  : %s\n", jenis);
            printf("Tambahan    : %s\n", tambahan);
            printf("Total Bayar : Rp %s\n", totalFormat);
            printf("------------------------------------\n");
            found = 1;
        }
    }
    fclose(fp);

    if (!found)
        printf("Belum ada transaksi untuk akun ini.\n");

    printf("\nTekan ENTER untuk kembali ke menu...");
    getchar(); getchar();
}

   
int main() {
    char username[30], password[30];
    char hurufDepan[5], hurufBelakang[10];
    char plat[30];
    int angka;
    int pilihan, tambahan, total;
    char jenis[20], tambahanText[20], totalFormat[50];
    int menu;
    char daftar;

    while (1) {
        clearScreen();
        printf("====================================\n");
        printf("              LOGIN AKUN             \n");
        printf("====================================\n");

        printf("Username : ");
        scanf("%s", username);
        printf("Password : ");
        scanf("%s", password);

        if (checkLogin(username, password)) {
            break;
        }

        if (!userExists(username)) {
            printf("\nAkun tidak ditemukan.\n");
            printf("Buat akun baru? (y/n): ");
            scanf(" %c", &daftar);

            if (daftar == 'y' || daftar == 'Y') {
                saveUser(username, password);
                printf("Akun berhasil dibuat.\n");
                printf("Tekan ENTER untuk login...");
                getchar(); getchar();
            }
        } else {
            printf("\nPassword salah.\n");
            printf("Tekan ENTER untuk coba lagi...");
            getchar(); getchar();
        }
    }

    do {
        total = 0;
        system("cls");

        printf("====================================\n");
        printf("          CAR WASH SYSTEM \n");
        printf("====================================\n");
        printf("Pilih jenis cuci mobil:\n");
        printf("1. Cuci Ekonomi     - Rp 50.000\n");
        printf("2. Cuci Reguler     - Rp 250.000\n");
        printf("3. Cuci Premium     - Rp 350.000\n");
        printf("------------------------------------\n");
        printf("Masukkan pilihan Anda (1-3): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: total = 50000; break;
            case 2: total = 250000; break;
            case 3: total = 350000; break;
            default: 
                printf("Pilihan tidak valid!\n");
                continue;
        }

        printf("\nApakah ingin tambahan layanan?\n");
        printf("1. Waxing (+ Rp 20.000)\n");
        printf("2. Vacuum Interior (+ Rp 15.000)\n");
        printf("3. Tidak ada tambahan\n");
        printf("Pilih (1-3): ");
        scanf("%d", &tambahan);

        if (tambahan == 1) {
            total += 20000;
        } else if (tambahan == 2) {
            total += 15000;
        }

        formatRupiah(total, totalFormat);

        printf("\n========= STRUK PEMBAYARAN =========\n");
        printf("Nama User   : %s\n", loginUser);
        printf("Plat Mobil  : %s\n", plat);
        printf("Jenis Cuci  : ");
        if (pilihan == 1) printf("Cuci Ekonomi\n");
        else if (pilihan == 2) printf("Cuci Reguler\n");
        else if (pilihan == 3) printf("Cuci Premium\n");

        printf("Tambahan    : ");
        if (tambahan == 1) printf("Waxing\n");
        else if (tambahan == 2) printf("Vacuum Interior\n");
        else printf("Tidak ada\n");

        printf("------------------------------------\n");
        printf("TOTAL BAYAR : Rp %s\n", totalFormat);
        printf("====================================\n");

        printf("\nApakah ingin input lagi? (y/n): ");
        scanf(" %c", &ulang);

    } while (ulang == 'y' || ulang == 'Y');

    printf("\nTerima kasih telah menggunakan Car Wash System!\n");
    
    return 0;
}
