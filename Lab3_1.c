#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int chave;
    int altura;
    struct nodo *esq;
    struct nodo *dir;
} Nodo;

typedef struct abb {
    Nodo *raiz;
} ABB;

int getAltura(Nodo* n) {
    if (n == NULL) return -1; 
    return n->altura;
}

int max(int i1, int i2) {
    return (i1 > i2) ? i1 : i2;
}

Nodo* criaNodo(int i) {
    Nodo* no = (Nodo*) malloc(sizeof(Nodo));
    no->altura = 0;
    no->chave = i;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

void inserirNo(Nodo* no, int i) {
    if (i < no->chave) {
        if (no->esq != NULL) 
            inserirNo(no->esq, i);
        else 
            no->esq = criaNodo(i);
    } 
    else if (i > no->chave) {
        if (no->dir != NULL) 
            inserirNo(no->dir, i);
        else 
            no->dir = criaNodo(i);
    } else {
        return;
    }

    
    no->altura = 1 + max(getAltura(no->esq), getAltura(no->dir));
}

void inserirNaABB(ABB* ar, int i) {
    if (ar->raiz != NULL) 
        inserirNo(ar->raiz, i);
    else 
        ar->raiz = criaNodo(i);
}

int* readArchive(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return NULL;
    }
    
    int* v = (int*)malloc(20 * sizeof(int));
    int counter = 0;
    while (counter < 20 && fscanf(file, "%d", &v[counter]) == 1) {
        counter++;
    }
    
    fclose(file);
    return v;
}
void PreorderPrintNo(Nodo* no) {
  if (no==NULL) 
    return;
  printf("%d(%d)\n",no->chave,no->altura);
  PreorderPrintNo(no->esq);
  PreorderPrintNo(no->dir);
}
void PosorderPrintNo(Nodo* no) {
  if (no==NULL) 
    return;
  PosorderPrintNo(no->esq);
  PosorderPrintNo(no->dir);
  printf("%d(%d)\n",no->chave,no->altura);
}
void SimetricorderPrintNo(Nodo* no) {
  if (no==NULL) 
    return;
  SimetricorderPrintNo(no->esq);
  printf("%d(%d)\n",no->chave,no->altura);
  SimetricorderPrintNo(no->dir);
}

void SimetricOrder (ABB* abb) {
  printf("Ordem simetrica!\n");
  SimetricorderPrintNo(abb->raiz);
  printf("\n");
}
void PosOrder (ABB* abb) {
  printf("Pos Ordem!\n");
  PosorderPrintNo(abb->raiz);
  printf("\n");
}
void PreOrder (ABB* abb) {
  printf("Pre Ordem!\n");
  PreorderPrintNo(abb->raiz);
  printf("\n");
}

void PrintNivelNo (Nodo* no,int i) {
  if (no==NULL)
    return;
  if (i!=0) {
    PrintNivelNo(no->esq,i-1);
    PrintNivelNo(no->dir,i-1);
    return;
  }
  printf("%d(%d)\n",no->chave,no->altura);
  
}
void PrintNivel (ABB* abb) {
  printf("Print por nivel !\n");
  for (int i = 0 ; i <= abb->raiz->altura;i++) {
    PrintNivelNo(abb->raiz,i);
  }
}
int main() {
    int* v = readArchive("arq1.txt");
    if (v == NULL) return 1;

    ABB* arvore = (ABB*)malloc(sizeof(ABB));
    arvore->raiz = NULL; 
    
    for (int i = 0; i < 20; i++) {
        inserirNaABB(arvore, v[i]);
    }
  SimetricOrder(arvore);
  PosOrder(arvore);
  PreOrder(arvore);
  PrintNivel(arvore);
  
    return 0;
}