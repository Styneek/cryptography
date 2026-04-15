#include <stdio.h>
#include <stdlib.h>

int main() {
    char WejscieBinarnie[13];
    unsigned int KluczSzyfrujacy = 0b10101010;
    int LiczbaRund = 8;
    
    int TabelaRozszerzenia[8] = {0, 1, 3, 2, 3, 2, 4, 5};
    int SkrzynkaS1[16] = {5, 2, 1, 6, 3, 4, 7, 0, 1, 4, 6, 2, 0, 7, 5, 3};
    int SkrzynkaS2[16] = {4, 0, 6, 5, 7, 1, 3, 2, 5, 3, 0, 7, 6, 2, 1, 4};

    if (scanf("%12s", WejscieBinarnie) != 1) return 0;

    unsigned int BlokDanych = 0;
    for (int i = 0; i < 12; i++) {
        if (WejscieBinarnie[i] == '1') BlokDanych |= (1 << (11 - i));
    }

    unsigned int LewaPolowa = (BlokDanych >> 6) & 0x3F;
    unsigned int PrawaPolowa = BlokDanych & 0x3F;

    for (int i = 0; i < LiczbaRund; i++) {
        unsigned int PoprzedniaLewa = LewaPolowa;
        unsigned int PoprzedniaPrawa = PrawaPolowa;

        unsigned int RozszerzoneR = 0;
        for (int j = 0; j < 8; j++) {
            int PozycjaBitu = 5 - TabelaRozszerzenia[j];
            unsigned int Bit = (PoprzedniaPrawa >> PozycjaBitu) & 1;
            RozszerzoneR = (RozszerzoneR << (7 - j)) | (Bit << (7 - j)); 
        }
        
        unsigned int CzysteRozszerzoneR = 0;
        for (int j = 0; j < 8; j++) {
            int bit = (PoprzedniaPrawa >> (5 - TabelaRozszerzenia[j])) & 1;
            CzysteRozszerzoneR = (CzysteRozszerzoneR << 1) | bit;
        }

        unsigned int PoXorze = CzysteRozszerzoneR ^ KluczSzyfrujacy;

        int IndeksS1 = (PoXorze >> 4) & 0x0F;
        int IndeksS2 = PoXorze & 0x0F;
        
        unsigned int WyjscieF = (SkrzynkaS1[IndeksS1] << 3) | SkrzynkaS2[IndeksS2];

        LewaPolowa = PoprzedniaPrawa;
        PrawaPolowa = PoprzedniaLewa ^ WyjscieF;
    }
    unsigned int WynikKoncowy = (LewaPolowa << 6) | PrawaPolowa;

    for (int i = 11; i >= 0; i--) {
        printf("%d", (WynikKoncowy >> i) & 1);
    }
    printf("\n");

    return 0;
}