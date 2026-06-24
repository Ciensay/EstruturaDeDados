#include <stdio.h>
#include <stdlib.h>

typedef struct avl{
    int info;
    int alt;
    struct avl *esq, *dir;
}TAVL;

/*
Para ser AVL: |altura(a->esq) - altura(a->dir)| <= 1
*/
int maximo(int x, int y){
    if(x>=y) return x;
    return y;
}

int *alt(TAVL *a){
    if(!a) return -1;
    return 1 + maximo(alt(a->esq), alt(a->dir));
}

// ESTUDAR ROTAÇÕES VAI ESTAR NA PROVA
TAVL *RSD(TAVL* a){
    TAVL *p = a->esq;
    a->esq = p->dir;
    p->dir = a;
    a->alt = alt(a);
    p->alt = alt(p);
    return p;
}

TAVL *RSE(TAVL *a){
    TAVL *p = a->dir;
    a->dir = p->esq;
    p->esq = a;
    a->alt = alt(a);
    p->alt = alt(p);
    return p;
}

TAVL *RED(TAVL *a){
    a->esq = RSE(a->esq);
    return RSD(a);
}

TAVL *RDE(TAVL *a){
    a->dir = RSD(a->dir);
    return RSE(a);
}

TAVL *TAVL_insere(TAVL *a, int x){
    if(!a) return TAVL_cria(x, NULL, NULL);
    if(x > a->info){
        a->dir = TAVL_insere(a->dir, x);
        if(FB(a) == 2){
            if(FB(a->esq) >= 0) a = RSD(a);
            else a = RED(a);
        }
    }
    else if(x < a->info){
        a->esq = TAVL_insere(a->esq, x);
        if(FB(a) == -2){
            if(FB(a->dir) <= 0) a = RSE(a);
            else a = RDE(a);
        }
    }
    return a;
}
