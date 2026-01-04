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
        clearScreen();
        printf("====================================\n");
        printf("          CAR WASH APPLICATION       \n");
        printf("====================================\n");
        printf("Login sebagai: %s\n", username);
        printf("------------------------------------\n");
        printf(" [1] Mulai Car Wash\n");
        printf(" [2] Lihat Riwayat Aktivitas\n");
        printf(" [3] Logout\n");
        printf("------------------------------------\n");
        printf("Pilih menu: ");
        scanf("%d", &menu);

        if (menu == 1) {
            clearScreen();
            printf("====================================\n");
            printf("             CAR WASH PAGE           \n");
            printf("====================================\n");

            printf("Huruf depan plat : ");
            scanf("%s", hurufDepan);
            printf("Angka plat       : ");
            scanf("%d", &angka);
            printf("Huruf belakang   : ");
            scanf("%s", hurufBelakang);

            sprintf(plat, "%s %d %s", hurufDepan, angka, hurufBelakang);
    
    return 0;
}
