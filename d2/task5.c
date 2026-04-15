#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char slowo[100];
    fgets(slowo, sizeof(slowo), stdin);

    char czysteSlowo[100];
    int k = 0;
    for (int i = 0; slowo[i] != '\0'; i++) {
        char c = slowo[i];
        if (isalpha(c)) {
            c = tolower(c);
            czysteSlowo[k] = c; 
            k++;
        }
    }

    int znalezione[17] = {0};
    for (int i = 0; i < k - 2; i++) {
        for (int j = i + 1; j <= k - 3; j++) {

            if (czysteSlowo[i] == czysteSlowo[j] && 
                czysteSlowo[i+1] == czysteSlowo[j+1] && 
                czysteSlowo[i+2] == czysteSlowo[j+2]) {
                    int odleglosc = j - i;

                for (int d = 2; d <= 16; d++) {
                    if (odleglosc % d == 0) {
                        znalezione[d] = 1; 
                    }
                }
            }   
        }
    }

    int pierwszy = 1;
    for (int d = 2; d <= 16; d++) {
        if (znalezione[d] == 1) {
            if (!pierwszy) printf(" ");
            printf("%d", d);
            pierwszy = 0;
        }
    }
    printf("\n");
}
