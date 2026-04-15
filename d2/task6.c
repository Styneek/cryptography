#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char tekst[1000];
    char czystyTekst[1000];
    
    double angielski[26] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193, 
    0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015, 
    0.0197, 0.0007
    };

    fgets(tekst, sizeof(tekst), stdin);
    int k = 0;
    for (int i = 0; tekst[i] != '\0'; i++) {
        char c = tekst[i];

        if (isalpha(c)) {
            c = tolower(c);
            czystyTekst[k] = c;
            int indeks = c - 'a';
            k++;
        }
    }

    for (int L = 1; L <= 10; L++) {
        char potencjalnyKlucz[11] = {0};

        for (int i = 0; i < L; i++) {
            double chi = 1e18;
            int najlepszySkok = 0;

            for (int s = 0; s < 26; s++) {
                int licznik[26] = {0};
                int nKolumny = 0;

                for (int j = i; j < k; j += L) {
                    int odszyfrowany = (czystyTekst[j] - 'a' - s + 26) % 26;
                    licznik[odszyfrowany]++;
                    nKolumny++;
                }
                double aktualneChi = 0;

                for (int x = 0; x < 26; x++) {
                    double oczekiwane = nKolumny * angielski[x];
                    if (oczekiwane > 0) {
                        double roznica = licznik[x] - oczekiwane;
                        aktualneChi += (roznica * roznica) / oczekiwane;
                    }
                }
                if (aktualneChi < chi) {
                    chi = aktualneChi;
                    najlepszySkok = s;
                }
            }
            potencjalnyKlucz[i] = najlepszySkok + 'a';
        }
        potencjalnyKlucz[L] = '\0';
        
        double sumaIc = 0;
        int iloscIc[26] = {0};

        for (int p = 0; p < k; p++) {
            int zmiana = potencjalnyKlucz[p % L] - 'a';
            int odszyfrowana = (czystyTekst[p] - 'a' - zmiana + 26) % 26;
            iloscIc[odszyfrowana]++;
        }
        
        for (int p = 0; p< 26; p++) {
            sumaIc += (double)iloscIc[p] * (iloscIc[p] - 1);
        }
        double ostatnieIc = (k > 1) ? (sumaIc / ((double)k * (k - 1))) : 0;

        if (ostatnieIc > 0.07) {
            int literaIdx = 0;

            for (int p = 0; tekst[p] != '\0'; p++) {
                if (isalpha(tekst[p])) {
                    int zmiana = potencjalnyKlucz[literaIdx % L] - 'a';
                    char baza = isupper(tekst[p]) ? 'A' : 'a';
                    printf("%c", (tekst[p] - baza - zmiana + 26) % 26 + baza);
                    literaIdx++;
                } else if (tekst[p] != '\n' && tekst[p] != '\r') {
                    printf("%c", tekst[p]);
                }
            }
            printf(" %s\n", potencjalnyKlucz);
            return 0;
        }
    }   
}