#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buforLinii[1000];

    fgets(buforLinii, sizeof(buforLinii), stdin);
    int dlugoscKlucza = atoi(buforLinii);

    char znanyPrefiks[1000];
    fgets(znanyPrefiks, sizeof(znanyPrefiks), stdin);
    znanyPrefiks[strcspn(znanyPrefiks, "\n")] = '\0';

    fgets(buforLinii, sizeof(buforLinii), stdin);
    int liczbaSzyfrogramow = atoi(buforLinii);

    unsigned char wyliczonyKlucz[1000];
    unsigned char zdekodowanySzyfrogram[1000];
    int dlugoscSzyfrogramu;

    for (int numerSzyfrogramu = 0; numerSzyfrogramu < liczbaSzyfrogramow; numerSzyfrogramu++) {
        if (fgets(buforLinii, sizeof(buforLinii), stdin) == NULL) break;

        dlugoscSzyfrogramu = 0;
        int j = 0;
        while (buforLinii[j] != '\0' && buforLinii[j] != '\n' && buforLinii[j] != '\r') {
            if (buforLinii[j] == '\\') {
                if (buforLinii[j+1] == 't') { zdekodowanySzyfrogram[dlugoscSzyfrogramu++] = '\t'; j += 2; }
                else if (buforLinii[j+1] == 'n') { zdekodowanySzyfrogram[dlugoscSzyfrogramu++] = '\n'; j += 2; }
                else if (buforLinii[j+1] == 'r') { zdekodowanySzyfrogram[dlugoscSzyfrogramu++] = '\r'; j += 2; }
                else if (buforLinii[j+1] == '\\') { zdekodowanySzyfrogram[dlugoscSzyfrogramu++] = '\\'; j += 2; }
                else if (buforLinii[j+1] == 'x') {
                    int wartoscHex;
                    sscanf(&buforLinii[j+2], "%02x", &wartoscHex);
                    zdekodowanySzyfrogram[dlugoscSzyfrogramu++] = (unsigned char)wartoscHex;
                    j += 4;
                } else {
                    zdekodowanySzyfrogram[dlugoscSzyfrogramu++] = buforLinii[j++];
                }
            } else {
                zdekodowanySzyfrogram[dlugoscSzyfrogramu++] = buforLinii[j++];
            }
        }

        if (numerSzyfrogramu == 0) {
            for (int i = 0; i < dlugoscKlucza; i++) {
                // K = C1 XOR P1
                wyliczonyKlucz[i] = zdekodowanySzyfrogram[i] ^ (unsigned char)znanyPrefiks[i];
            }
        }

        for (int i = 0; i < dlugoscSzyfrogramu; i++) {
            // P_x = C_x XOR K
            printf("%c", zdekodowanySzyfrogram[i] ^ wyliczonyKlucz[i % dlugoscKlucza]);
        }
        printf("\n");
    }

    return 0;
}