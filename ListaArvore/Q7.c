#include "TAB.c"


void aux(TAB * a, int corpai){
    if(!a) return;
    if(corpai){
        a->info = 0;
        aux(a->esq, a->info);
        aux(a->dir, a->info);

    }else{
        a->info = 1;
        aux(a->esq, a->info);
        aux(a->dir, a->info);
    }

}
void colore(TAB* a){
    if(!a) return;
    a->info = 0;
    aux(a->esq, a->info);
    aux(a->dir, a->info);


}

int main(){
    TAB *arvore_balanceada = TAB_inicializa();
    arvore_balanceada = TAB_cria(4, 
                                TAB_cria(2, 
                                    TAB_cria(1, TAB_inicializa(), TAB_inicializa()), 
                                    TAB_cria(3, TAB_inicializa(), TAB_inicializa())
                                ), 
                                TAB_cria(6, 
                                    TAB_cria(5, TAB_inicializa(), TAB_inicializa()), 
                                    TAB_cria(7, TAB_inicializa(), TAB_inicializa())
                                )
                             );
                             TAB_imp_ident(arvore_balanceada);
                             colore(arvore_balanceada);
                             printf("COLORODO:   \n \n");
                             TAB_imp_ident(arvore_balanceada);





    return 0;
}