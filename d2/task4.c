#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int alfabet[26] = {0};
    char slowo[100];
    int N = 0;
    fgets(slowo, sizeof(slowo), stdin);

    for (int i = 0; slowo[i] != '\0'; i++) {
        char c = slowo[i];
        if (isalpha(c)) {
            c = tolower(c);
            int indeks = c - 'a';
            alfabet[indeks]++;
            N++;
        }
    }

    long suma = 0;
    for (int i = 0; i < 26; i++) {
        int n = alfabet[i];
        if (n > 1) {
            suma += n * (n - 1);
        }
    }

    double ic = 0.0;
    if (N > 1) {
        ic = (double)suma / (N * (N - 1));
    }
    printf("%.4f", ic);
}