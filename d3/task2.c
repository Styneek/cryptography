#include <stdio.h>
#include <string.h>

int main() {
    char wiadomoscPierwsza[1024];
    char wiadomoscDruga[1024];

    fgets(wiadomoscPierwsza, sizeof(wiadomoscPierwsza), stdin);
    fgets(wiadomoscDruga, sizeof(wiadomoscDruga), stdin); 

    wiadomoscPierwsza[strcspn(wiadomoscPierwsza, "\n")] = '\0';
    wiadomoscDruga[strcspn(wiadomoscDruga, "\n")] = '\0';

    int dlugoscPierwsza = strlen(wiadomoscPierwsza);
    int dlugoscDruga = strlen(wiadomoscDruga);

    int minimalnaDlugosc = (dlugoscPierwsza < dlugoscDruga) ? dlugoscPierwsza : dlugoscDruga;
    for (int i = 0; i < minimalnaDlugosc; i++) {
        unsigned char wynikXor = (unsigned char)wiadomoscPierwsza[i] ^ (unsigned char)wiadomoscDruga[i];

        
        if (wynikXor == '\t') {
            printf("\\t");
        } else if (wynikXor == '\n') {
            printf("\\n");
        } else if (wynikXor == '\r') {
            printf("\\r");
        } else if (wynikXor == '\\') {
            printf("\\\\"); 
        } 
       
        else if (wynikXor >= 32 && wynikXor <= 126) {
            printf("%c", wynikXor);
        } 
        else {
            printf("\\x%02x", wynikXor);
        }
    }
    printf("\n");

    return 0;
}