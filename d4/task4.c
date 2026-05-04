#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int wartosciSbox1[16] = {5, 2, 1, 6, 3, 4, 7, 0, 1, 4, 6, 2, 0, 7, 5, 3};
const int wartosciSbox2[16] = {4, 0, 6, 5, 7, 1, 3, 2, 5, 3, 0, 7, 6, 2, 1, 4};

int main() {
    char *daneWejsciowe = malloc(100000 * sizeof(char));
    char kluczWejsciowy[9];
    char permutacjaWejsciowa[9];
    int permutacjaRozszerzajaca[8];
    int kluczGlowny[8];

    if (scanf("%99999s", daneWejsciowe) != 1) {
        free(daneWejsciowe);
        return 1;
    }
    
    if (scanf("%8s", kluczWejsciowy) != 1) {
        free(daneWejsciowe);
        return 1;
    }
    
    if (scanf("%8s", permutacjaWejsciowa) != 1) {
        free(daneWejsciowe);
        return 1;
    }
    
    for (int i = 0; i < 8; i++) {
        kluczGlowny[i] = kluczWejsciowy[i] - '0';
        permutacjaRozszerzajaca[i] = permutacjaWejsciowa[i] - '0';
    }

    int dlugosc = strlen(daneWejsciowe);
    int liczbaUzytecznychBitow = dlugosc - (dlugosc % 12);
    int liczbaRund = 7;

    for (int blok = 0; blok < liczbaUzytecznychBitow; blok += 12) {
        int lewaStrona[6], prawaStrona[6];
        
        for (int i = 0; i < 6; i++) {
            lewaStrona[i] = daneWejsciowe[blok + i] - '0';
            prawaStrona[i] = daneWejsciowe[blok + 6 + i] - '0';
        }

        for (int runda = 1; runda <= liczbaRund; runda++) {
            int rozszerzonaPrawaStrona[8];
            for (int i = 0; i < 8; i++) {
                rozszerzonaPrawaStrona[i] = prawaStrona[permutacjaRozszerzajaca[i]];
            }
            
            int kluczRundy[8];
            int poczatekKlucza = (liczbaRund - runda + 1) % 8;
            for (int i = 0; i < 8; i++) {
                kluczRundy[i] = kluczGlowny[(poczatekKlucza + i) % 8];
            }
            
            int wynikXor[8];
            for (int i = 0; i < 8; i++) {
                wynikXor[i] = rozszerzonaPrawaStrona[i] ^ kluczRundy[i];
            }
            
            int indeksSbox1 = wynikXor[0]*8 + wynikXor[1]*4 + wynikXor[2]*2 + wynikXor[3]*1;
            int indeksSbox2 = wynikXor[4]*8 + wynikXor[5]*4 + wynikXor[6]*2 + wynikXor[7]*1;
            
            int wartoscZarowSbox1 = wartosciSbox1[indeksSbox1];
            int wartoscZarowSbox2 = wartosciSbox2[indeksSbox2];
            
            int wynikFunkcji[6];
            wynikFunkcji[0] = (wartoscZarowSbox1 >> 2) & 1;
            wynikFunkcji[1] = (wartoscZarowSbox1 >> 1) & 1;
            wynikFunkcji[2] = wartoscZarowSbox1 & 1;
            
            wynikFunkcji[3] = (wartoscZarowSbox2 >> 2) & 1;
            wynikFunkcji[4] = (wartoscZarowSbox2 >> 1) & 1;
            wynikFunkcji[5] = wartoscZarowSbox2 & 1;
            
            int nowaPrawaStrona[6];
            int nowaLewaStrona[6];
            
            for (int i = 0; i < 6; i++) {
                nowaPrawaStrona[i] = lewaStrona[i] ^ wynikFunkcji[i];
                nowaLewaStrona[i] = prawaStrona[i];
            }
            
            for (int i = 0; i < 6; i++) {
                lewaStrona[i] = nowaLewaStrona[i];
                prawaStrona[i] = nowaPrawaStrona[i];
            }
        }
        
        for (int i = 0; i < 6; i++) {
            printf("%d", prawaStrona[i]);
        }
        for (int i = 0; i < 6; i++) {
            printf("%d", lewaStrona[i]);
        }
    }
    
    printf("\n");
    free(daneWejsciowe);
    
    return 0;
}