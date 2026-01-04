#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatRupiah(int num, char *buffer) {
    char temp[50];
    int i, j = 0, len, pos = 0;

    sprintf(temp, "%d", num);
    len = strlen(temp);
    char rev[50];

    for (i = len - 1; i >= 0; i--) {
        rev[pos++] = temp[i];
        if ((len - i) % 3 == 0 && i != 0) {
            rev[pos++] = '.';
        }
    }
    rev[pos] = '\0';

    len = strlen(rev);
    for (i = len - 1; i >= 0; i--) {
        buffer[j++] = rev[i];
    }
    buffer[j] = '\0';
}

int main() {
char username[30], password[30];
    char loginUser[30], loginPass[30];
    char hurufDepan[5], hurufBelakang[10];
    char plat[20];
    int angka;
    int pilihan, tambahan, total;
    char ulang;
    char totalFormat[50];
    
    printf("====================================\n");
    printf("       REGISTRASI CAR WASH APP\n");
    printf("====================================\n");
    printf("Buat Username : ");
    scanf("%s", username);
    printf("Buat Password : ");
    scanf("%s", password);

    system("cls");

    printf("====================================\n");
    printf("            LOGIN AKUN\n");
    printf("====================================\n");

    while (1) {
        printf("Masukkan Username : ");
        scanf("%s", loginUser);
        printf("Masukkan Password : ");
        scanf("%s", loginPass);

        if (strcmp(loginUser, username) == 0 && strcmp(loginPass, password) == 0) {
            printf("\nLogin berhasil! Selamat datang, %s\n\n", loginUser);
            break;
        } else {
            printf("\nUsername atau Password salah! Silakan coba lagi.\n\n");
        }
    }

    printf("Masukkan huruf depan plat : ");
    scanf("%s", hurufDepan);
    printf("Masukkan angka plat       : ");
    scanf("%d", &angka);
    printf("Masukkan huruf belakang   : ");
    scanf("%s", hurufBelakang);

    sprintf(plat, "%s %d %s", hurufDepan, angka, hurufBelakang);

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
        
    return 0;
}
