#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buforXor[1024];
    char buforPozycji[64];
    char tekstCrib[1024];

    fgets(buforXor, sizeof(buforXor), stdin);
    fgets(buforPozycji, sizeof(buforPozycji), stdin); 
    fgets(tekstCrib, sizeof(tekstCrib), stdin); 

    tekstCrib[strcspn(tekstCrib, "\n")] = '\0';
    int dlugoscCrib = strlen(tekstCrib);

    int pozycja = atoi(buforPozycji);

    unsigned char zdekodowanyXor[1024];
    int dlugoscXor = 0;
    int k = 0;

    while (buforXor[k] != '\0' && buforXor[k] != '\n' && buforXor[k] != '\r') {
        if (buforXor[k] == '\\') {
            if (buforXor[k+1] == 't') { zdekodowanyXor[dlugoscXor++] = '\t'; k += 2; }
            else if (buforXor[k+1] == 'n') { zdekodowanyXor[dlugoscXor++] = '\n'; k += 2; }
            else if (buforXor[k+1] == 'r') { zdekodowanyXor[dlugoscXor++] = '\r'; k += 2; }
            else if (buforXor[k+1] == '\\') { zdekodowanyXor[dlugoscXor++] = '\\'; k += 2; }
            else if (buforXor[k+1] == 'x') {
                int wartoscHex;
                sscanf(&buforXor[k+2], "%02x", &wartoscHex);
                zdekodowanyXor[dlugoscXor++] = (unsigned char)wartoscHex;
                k += 4;
            } else {
                zdekodowanyXor[dlugoscXor++] = buforXor[k++];
            }
        } else {
            zdekodowanyXor[dlugoscXor++] = buforXor[k++];
        }
    }

    if (pozycja < 0 || pozycja >= dlugoscXor) {
        printf("Błąd: pozycja poza zakresem.\n");
        return 1;
    }
    
    if (pozycja + dlugoscCrib > dlugoscXor) {
        dlugoscCrib = dlugoscXor - pozycja;
    }

    for (int i = 0; i < dlugoscCrib; i++) {
        unsigned char bajtP2 = zdekodowanyXor[pozycja + i] ^ (unsigned char)tekstCrib[i];
        printf("%c", bajtP2);
    }
    
    printf("\n");

    return 0;
}