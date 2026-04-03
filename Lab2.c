#include <stdlib.h>
#include <stdio.h>

//Pilha
// esse trabalho eh de total autoria de Carlos Frederico Stern Sant'ana
typedef struct no No;
struct no {
    int number;
    struct no* anterior ;
};

void add (No** pilha , No* ad) {
    ad->anterior = (*pilha);
    (*pilha) = ad;
}
No* criaNo (int n) {
    No* no  = (No*)malloc(sizeof(No));
    no->number = n;
    no->anterior = NULL;
    return no;
}
void pop (No** pilha) {
    if (*pilha == NULL) {return;}
    No* temp = (*pilha);
    (*pilha) = (*pilha)->anterior;
    free(temp);
}
void printPilha (No* pilha) {
    while (pilha != NULL) {
        printf("%d", pilha->number);
        if (pilha->anterior != NULL) {
            printf(", ");
        }
        pilha = pilha->anterior;
    }
}

int main (void) {
    FILE* file = fopen("entrada_pilha.txt","r");
    if (file==NULL) {
        printf("Erro ao abrir arquivo\n");
        return 0 ;
    }
     No* inicio = NULL;
    char operation; 
    int num;

    while (fscanf(file," %c",&operation) == 1) {
        if (operation=='e') {
            fscanf(file,"%d",&num);
            add(&inicio, criaNo(num));
        }
        else {
            pop(&inicio);
        }
        printf("[");
        printPilha(inicio);
        printf("]\n");
    }

    fclose(file);
    return 0;
}
