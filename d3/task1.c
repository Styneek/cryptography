#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char klucz[100];
    char slowo[100];

    fgets(klucz, sizeof(klucz), stdin);
    fgets(slowo, sizeof(slowo), stdin);

    klucz[strcspn(klucz, "\n")] = '\0';
    slowo[strcspn(slowo, "\n")] = '\0';

    int dlugoscKlucza = strlen(klucz);
    int dlugoscSlowa = strlen(slowo);

    for (int i = 0; i < dlugoscSlowa; i++) {
     unsigned char wynik = (unsigned char)slowo[i] ^ (unsigned char)klucz[i % dlugoscKlucza];
        if (wynik == '\t') {
            printf("\\t");
        } else if (wynik == '\n') {
            printf("\\n");
        } else if (wynik == '\r') {
            printf("\\r");
        } else if (wynik == '\\') {
            printf("\\\\"); 
        } 
        else if (wynik >= 32 && wynik <= 126) {
            printf("%c", wynik);
        } 
        else {
            printf("\\x%02x", wynik);
        }
    }
    printf("\n");

    return 0;
}