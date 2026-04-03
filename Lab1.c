#include <stdio.h>
#include <stdlib.h>
// Trabalho feito por : 
// Pedro mucelin e Carlos Frederico Stern
void bubblesort (int v[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (v[j] > v[j+1]) {
                int first = v[j];
                int second = v[j+1];
                v[j] = second;
                v[j+1] = first;
            }
        }
    }
}

int main() {
    int v[10];

    printf("ANTES DO SORT _____\n");
    for (int i = 0; i < 10; i++) {
        v[i] = rand() % 100;
        printf("O item de indice %d tem valor %d\n", i, v[i]);
    }

    bubblesort(v, 10);

    printf("DEPOIS DO SORT _____\n");
    for (int i = 0; i < 10; i++) {
        printf("O item de indice %d tem valor %d\n", i, v[i]);
    }

    return 0;
}