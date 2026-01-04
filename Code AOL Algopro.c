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

    return 0;
}
