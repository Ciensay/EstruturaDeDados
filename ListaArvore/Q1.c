#include <stdio.h>
#include "TAB.c"
#include <stdlib.h>

TAB* copia (TAB *a){
    if(!a) return NULL;
    TAB *novo = (TAB *)malloc(sizeof(TAB));
    novo->info = a->info;
    novo->dir = copia(a->dir);
    novo->esq = copia(a->esq);
    return novo;
}


int main(){
    TAB *arvore = TAB_inicializa();
    arvore = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(30,NULL,NULL));
    TAB *arvorecopiada = copia(arvore);
    TAB_imp_pre(arvore);
    TAB_imp_pre(arvorecopiada);

    return 0;
}