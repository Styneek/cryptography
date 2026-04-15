#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char tryb[10];
    char tekst[100];
    char klucz[100];

    scanf("%s", tryb);
    getchar();
    fgets(tekst, sizeof(tekst), stdin);
    tekst[strcspn(tekst, "\n")] = 0;

    fgets(klucz, sizeof(klucz), stdin);
    klucz[strcspn(klucz, "\n")] = 0;

    int dlugoscTekstu = strlen(tekst);
    int dlugoscKlucza = strlen(klucz);

    int j = 0;
    
    for (int i = 0; i < dlugoscTekstu; i++) {
        char c = tekst[i];
        if (isalpha(c)) {
            int przesuniecie = tolower(klucz[j]) - 'a';
            char baza = isupper(c) ? 'A' : 'a';

            if (strcmp(tryb, "ENC") == 0) {
                c = (c - baza + przesuniecie) % 26 + baza;
            } else {
                c = (c - baza - przesuniecie + 26) % 26 + baza;
            }
            j = (j + 1) % dlugoscKlucza;
        }
        printf("%c", c);
    }
    return 0;
}