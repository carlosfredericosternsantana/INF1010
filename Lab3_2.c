#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int chave;
    int fb;
    int altura;
    struct nodo *esq;
    struct nodo *dir;
} Nodo;

typedef struct avl {
    Nodo *raiz;
} AVL;

int getAltura(Nodo* n) {
    if (n == NULL) return -1;
    return n->altura;
}

int max(int i1, int i2) {
    return (i1 > i2) ? i1 : i2;
}

void atualizaNo(Nodo* no) {
    if (no != NULL) {
        no->altura = 1 + max(getAltura(no->esq), getAltura(no->dir));
        no->fb = getAltura(no->esq) - getAltura(no->dir);
    }
}

Nodo* criaNo(int i) {
    Nodo* no = (Nodo*)malloc(sizeof(Nodo));
    no->chave = i;
    no->dir = NULL;
    no->esq = NULL;
    no->fb = 0;
    no->altura = 0;
    return no;
}

Nodo* RightRotation(Nodo* no) {
    printf("Rotação à direita (RD) no nó %d\n", no->chave);
    Nodo* f1 = no->esq;
    no->esq = f1->dir;
    f1->dir = no;
    atualizaNo(no);
    atualizaNo(f1);
    return f1;
}

Nodo* LeftRotation(Nodo* no) {
    printf("Rotação à esquerda (RE) no nó %d\n", no->chave);
    Nodo* f1 = no->dir;
    no->dir = f1->esq;
    f1->esq = no;
    atualizaNo(no);
    atualizaNo(f1);
    return f1;
}

Nodo* DoubleRightR(Nodo* no) {
    printf("Rotação Dupla à Direita (RDD) no nó %d\n", no->chave);
    no->esq = LeftRotation(no->esq);
    return RightRotation(no);
}

Nodo* DoubleLeftR(Nodo* no) {
    printf("Rotação Dupla à Esquerda (RDE) no nó %d\n", no->chave);
    no->dir = RightRotation(no->dir);
    return LeftRotation(no);
}
Nodo* returnNaoNull (Nodo* no1 , Nodo* no2) {
  if(no1!=NULL)
    return no1;
  return no2;
}

Nodo* insereNo(Nodo* no, int i, int *rot) {
    if (no == NULL) return criaNo(i);

    if (i < no->chave)
        no->esq = insereNo(no->esq, i, rot);
    else if (i > no->chave)
        no->dir = insereNo(no->dir, i, rot);
    else
        return no;

    atualizaNo(no);

    if (abs(no->fb) < 2) return no;

    *rot = 1;
    if (no->fb > 1) {
        if (no->esq->fb >= 0) 
          return RightRotation(no);
        else 
          return DoubleRightR(no);
    } 
    else {
        if (no->dir->fb <= 0) 
          return LeftRotation(no);
        else 
          return DoubleLeftR(no);
    }
}
// Função auxiliar para encontrar o nó com o maior valor (predecessor)
Nodo* getMax(Nodo* no) {
    Nodo* atual = no;
    while (atual->dir != NULL)
        atual = atual->dir;
    return atual;
}

Nodo* deletarNo(Nodo* no, int i) {
    if (no == NULL) return NULL;

    if (i < no->chave) 
        no->esq = deletarNo(no->esq, i);
    else if (i > no->chave) 
        no->dir = deletarNo(no->dir, i);
    else {
        
        if (no->esq == NULL || no->dir == NULL) {
            Nodo* temp = no->esq ? no->esq : no->dir;

            if (temp == NULL) { 
                temp = no;
                no = NULL;
            } 
            else  
              *no = *temp; 
            
            free(temp);
        } 
        else {
            Nodo* temp = getMax(no->esq);
            no->chave = temp->chave;
            no->esq = deletarNo(no->esq, temp->chave);
        }
    }

    if (no == NULL) return NULL;
    atualizaNo(no);

    if (no->fb > 1) {
        if (getAltura(no->esq->esq) >= getAltura(no->esq->dir))
            return RightRotation(no);
        else
            return DoubleRightR(no);
    }
    if (no->fb < -1) {
        if (getAltura(no->dir->dir) >= getAltura(no->dir->esq))
            return LeftRotation(no);
        else
            return DoubleLeftR(no);
    }

    return no;
}
int main(void) {
    int listaEntrada[] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 43, 16, 67, 39};
    int n = sizeof(listaEntrada) / sizeof(listaEntrada[0]);
    
    AVL* avl = (AVL*)malloc(sizeof(AVL));
    avl->raiz = criaNo(50);

    for (int i = 0; i < n; i++) {
        int rot = 0;
        printf("Inserir %d -> ", listaEntrada[i]);
        avl->raiz = insereNo(avl->raiz, listaEntrada[i], &rot);
        if (!rot) printf("sem rotação.\n");
    }
    deletarNo(avl->raiz,58);
    deletarNo(avl->raiz,59);
    deletarNo(avl->raiz,56);
    deletarNo(avl->raiz,18);
    
    return 0;
}