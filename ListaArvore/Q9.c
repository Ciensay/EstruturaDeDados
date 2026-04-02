#include "TAB.c"

int nf(TAB *a){
    if(!a) return 0;
        if (a->esq || a->dir) return nf(a->esq)+nf(a->dir);
    return 1;
}

int main(){
    TAB *arvore = TAB_inicializa();
    TAB *arvore2 = TAB_inicializa();
    arvore = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(2,TAB_cria(99, NULL, NULL),NULL));
    arvore2 = TAB_cria(2, TAB_cria(4,TAB_cria(3, NULL, NULL),NULL), TAB_cria(30,NULL,NULL));
    /* 10
     /  \
    5    15
   / \   / \
  2   7 12  20
*/
TAB *cheia = TAB_cria(10,
                TAB_cria(5, TAB_cria(2, NULL, NULL), TAB_cria(7, NULL, NULL)),
                TAB_cria(15, TAB_cria(12, NULL, NULL), TAB_cria(20, NULL, NULL))
             );

             // Estrutura: 10 -> 8 -> 5 -> 2
TAB *esq = TAB_cria(10, 
                TAB_cria(8, 
                    TAB_cria(5, 
                        TAB_cria(2, NULL, NULL), 
                    NULL), 
                NULL), 
            NULL);

    printf("%d \n \n", nf(esq));
    //TAB *arvorecopiada = copia(arvore);
    //TAB_imp_ident(arvore);
    //TAB_imp_pre(arvorecopiada);

    return 0;
}
