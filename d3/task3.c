#include <stdio.h>
#include <string.h>

int main() {
    char tekstJawnyBuf[1024];
    char szyfrogramPierwszyBuf[1024];
    char szyfrogramDrugiBuf[1024];


    fgets(tekstJawnyBuf, sizeof(tekstJawnyBuf), stdin);
    fgets(szyfrogramPierwszyBuf, sizeof(szyfrogramPierwszyBuf), stdin);
    fgets(szyfrogramDrugiBuf, sizeof(szyfrogramDrugiBuf), stdin);

    tekstJawnyBuf[strcspn(tekstJawnyBuf, "\n")] = '\0';
    int dlugoscJawnego = strlen(tekstJawnyBuf);

    unsigned char szyfrogramPierwszy[1024];
    unsigned char szyfrogramDrugi[1024];

    int dlugoscPierwszego = 0;
    int k = 0;
    while (szyfrogramPierwszyBuf[k] != '\0' && szyfrogramPierwszyBuf[k] != '\n' && szyfrogramPierwszyBuf[k] != '\r') {
        if (szyfrogramPierwszyBuf[k] == '\\') {
            if (szyfrogramPierwszyBuf[k+1] == 't') { szyfrogramPierwszy[dlugoscPierwszego++] = '\t'; k += 2; }
            else if (szyfrogramPierwszyBuf[k+1] == 'n') { szyfrogramPierwszy[dlugoscPierwszego++] = '\n'; k += 2; }
            else if (szyfrogramPierwszyBuf[k+1] == 'r') { szyfrogramPierwszy[dlugoscPierwszego++] = '\r'; k += 2; }
            else if (szyfrogramPierwszyBuf[k+1] == '\\') { szyfrogramPierwszy[dlugoscPierwszego++] = '\\'; k += 2; }
            else if (szyfrogramPierwszyBuf[k+1] == 'x') {
                int wartoscHex;
                sscanf(&szyfrogramPierwszyBuf[k+2], "%02x", &wartoscHex);
                szyfrogramPierwszy[dlugoscPierwszego++] = (unsigned char)wartoscHex;
                k += 4;
            } else {
                szyfrogramPierwszy[dlugoscPierwszego++] = szyfrogramPierwszyBuf[k++];
            }
        } else {
            szyfrogramPierwszy[dlugoscPierwszego++] = szyfrogramPierwszyBuf[k++];
        }
    }

    int dlugoscDrugiego = 0;
    int j = 0;
    while (szyfrogramDrugiBuf[j] != '\0' && szyfrogramDrugiBuf[j] != '\n' && szyfrogramDrugiBuf[j] != '\r') {
        if (szyfrogramDrugiBuf[j] == '\\') {
            if (szyfrogramDrugiBuf[j+1] == 't') { szyfrogramDrugi[dlugoscDrugiego++] = '\t'; j += 2; }
            else if (szyfrogramDrugiBuf[j+1] == 'n') { szyfrogramDrugi[dlugoscDrugiego++] = '\n'; j += 2; }
            else if (szyfrogramDrugiBuf[j+1] == 'r') { szyfrogramDrugi[dlugoscDrugiego++] = '\r'; j += 2; }
            else if (szyfrogramDrugiBuf[j+1] == '\\') { szyfrogramDrugi[dlugoscDrugiego++] = '\\'; j += 2; }
            else if (szyfrogramDrugiBuf[j+1] == 'x') {
                int wartoscHex;
                sscanf(&szyfrogramDrugiBuf[j+2], "%02x", &wartoscHex);
                szyfrogramDrugi[dlugoscDrugiego++] = (unsigned char)wartoscHex;
                j += 4;
            } else {
                szyfrogramDrugi[dlugoscDrugiego++] = szyfrogramDrugiBuf[j++];
            }
        } else {
            szyfrogramDrugi[dlugoscDrugiego++] = szyfrogramDrugiBuf[j++];
        }
    }

    int minimalnaDlugosc = dlugoscJawnego;
    if (dlugoscPierwszego < minimalnaDlugosc) minimalnaDlugosc = dlugoscPierwszego;
    if (dlugoscDrugiego < minimalnaDlugosc) minimalnaDlugosc = dlugoscDrugiego;

    for (int i = 0; i < minimalnaDlugosc; i++) {
        unsigned char kluczBajt = (unsigned char)tekstJawnyBuf[i] ^ szyfrogramPierwszy[i];
        unsigned char jawnyDrugiBajt = szyfrogramDrugi[i] ^ kluczBajt;
        printf("%c", jawnyDrugiBajt);
    }
    
    printf("\n");

    return 0;
}