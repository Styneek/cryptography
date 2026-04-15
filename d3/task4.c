#include <stdio.h>
#include <string.h>

int main() {
    char tekstWejsciowy[1024];

    fgets(tekstWejsciowy, sizeof(tekstWejsciowy), stdin);

    tekstWejsciowy[strcspn(tekstWejsciowy, "\n")] = '\0';

    int dlugoscTekstu = strlen(tekstWejsciowy);
    unsigned char sumaKontrolna = 0;

    for (int i = 0; i < dlugoscTekstu; i++) {
        sumaKontrolna ^= (unsigned char)tekstWejsciowy[i];
    }

    if (sumaKontrolna == '\t') {
        printf("\\t");
    } else if (sumaKontrolna == '\n') {
        printf("\\n");
    } else if (sumaKontrolna == '\r') {
        printf("\\r");
    } else if (sumaKontrolna == '\\') {
        printf("\\\\"); 
    } 
    else if (sumaKontrolna >= 32 && sumaKontrolna <= 126) {
        printf("%c", sumaKontrolna);
    } 
    else {
        printf("\\x%02x", sumaKontrolna);
    }
    printf("\n");

    return 0;
}