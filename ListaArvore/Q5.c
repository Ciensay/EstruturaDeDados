#include "TAB.c"

int igual(TAB *a1, TAB*a2, int resp){
    if((!a1) && (!a2)) return 1;
    if(a1->info != a2->info) return 0;
    int verificador = igual(a1->dir, a2->dir, 1);
    if(!verificador) return 0;
    return igual(a1->esq, a2->esq, 1);

}



int main(){
    TAB *arvore = TAB_inicializa();
    TAB *arvore2 = TAB_inicializa();
    arvore = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(2,TAB_cria(99, NULL, NULL),NULL));
    arvore2 = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(30,NULL,NULL));

    printf("%d ", igual(arvore, arvore2, 1));
    //TAB *arvorecopiada = copia(arvore);
    //TAB_imp_pre(arvore);
    //TAB_imp_pre(arvorecopiada);

    return 0;
}