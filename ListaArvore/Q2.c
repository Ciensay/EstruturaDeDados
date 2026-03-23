#include "TAB.c"

TAB *espelho(TAB *a){
    if(!a) return NULL;
    TAB *novo = (TAB *)malloc(sizeof(TAB));
    novo->info = a->info;

    novo->dir = espelho(a->esq);
    novo->esq = espelho(a->dir);
    return novo;

}




int main(){
    TAB *arvore = TAB_inicializa();
    arvore = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(30,NULL,NULL));
    TAB *arvorecopiada = espelho(arvore);
    TAB_imp_sim(arvore);
    printf("\n");
    TAB_imp_sim(arvorecopiada);

    return 0;
}