#include "TAB.c"


TAB *maismais(TAB *a){
    if(!a) return NULL;
    TAB *maioral = a;
    TAB *b = maismais(a->esq);
    TAB *c = maismais(a->dir);
    if(b&&(b->info > maioral->info)) maioral = b;
    if(c&&(c->info>maioral->info)) maioral = c;
    return maioral;
}
int main(){
    TAB *teste = TAB_inicializa();
    teste = TAB_cria(3, TAB_cria(4, NULL, TAB_cria(7, NULL, NULL)), TAB_cria(5, TAB_cria(1, NULL, NULL), TAB_cria(12, NULL, NULL)));
    printf("\n %d \n", maismais(teste)->info);


    return 0;
}