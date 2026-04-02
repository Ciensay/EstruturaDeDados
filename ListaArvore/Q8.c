#include "TAB.c"

int ni(TAB *a){
    if(!a) return 0;
    return 1+ni(a->esq)+ni(a->dir);

}

int main(){
    TAB *arvore = TAB_inicializa();
    TAB *arvore2 = TAB_inicializa();
    arvore = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(2,TAB_cria(99, NULL, NULL),NULL));
    arvore2 = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(30,NULL,NULL));


    printf("%d ", ni(arvore2));
    //TAB *arvorecopiada = copia(arvore);
    //TAB_imp_pre(arvore);
    //TAB_imp_pre(arvorecopiada);

    return 0;
}
