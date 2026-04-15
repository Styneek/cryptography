#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int L;
    char slowo[100];

    scanf("%d", &L);
    getchar();
    fgets(slowo, sizeof(slowo), stdin);

    char czysteSlowo[100];
    int k = 0;
    for (int i = 0; slowo[i] != '\0'; i++) {
        char c = slowo[i];
        if (isalpha(c)) {
            czysteSlowo[k] = c;
            k++;
        }
    }
    czysteSlowo[k] = '\0';

    for (int i = 0; i < L; i++) {
        for (int j = i; j < k; j+= L) {
            printf("%c", czysteSlowo[j]);
        }
        printf("\n");
    }
}