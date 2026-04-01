#include "TAB.c"


TAB* retira(TAB *a){
    TAB *resp = a->dir;
    TAB *p = a;
    while (p->dir)
    {
        p = p->dir;
    }
    p->dir = a->esq;
    free(a);
    return resp;

}
TAB *retira_pares(TAB *a){
    if(!a) return NULL;
    a->esq = retira_pares(a->esq);
    a->dir = retira_pares(a->dir);
    if(a->info%2 == 0) return retira(a);
    return a;

}


int main(){
    TAB *teste = TAB_inicializa();
    teste = TAB_cria(5, TAB_cria(1, NULL, TAB_cria(7, NULL, NULL)), TAB_cria(5, TAB_cria(9, NULL, NULL), TAB_cria(-40, NULL, NULL)));
    TAB_imp_ident(teste);
    teste = retira_pares(teste);
    printf("RETIRADOS: ");
    TAB_imp_ident(teste);



    return 0;
}