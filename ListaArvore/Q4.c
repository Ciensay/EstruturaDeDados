#include "TAB.c"


TAB *menosmenos(TAB *a){
    if(!a) return NULL;
    TAB *menoral = a;
    TAB *b = menosmenos(a->esq);
    TAB *c = menosmenos(a->dir);
    if(b&&(b->info < menoral->info)) menoral = b;
    if(c&&(c->info< menoral->info)) menoral = c;
    return menoral;
}
int main(){
    TAB *teste = TAB_inicializa();
    teste = TAB_cria(-4, TAB_cria(-40, NULL, TAB_cria(7, NULL, NULL)), TAB_cria(5, TAB_cria(1, NULL, NULL), TAB_cria(-40, NULL, NULL)));
    printf("\n %d \n", menosmenos(teste)->info);


    return 0;
}