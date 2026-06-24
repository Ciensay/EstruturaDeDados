#include "TAB.c"


void aux(TAB *a, int n, TAB **resp){
    if(!a) return;

    if(a->info > n){  
        if(*resp == NULL || a->info-n < (*resp)->info-n){  
            *resp = a;  
        }
    }

    aux(a->esq, n, resp);
    aux(a->dir, n, resp);
}

TAB *sucessor(TAB *a, int n){
    TAB *resp = NULL;  // Inicializa sem candidato
    aux(a, n, &resp);
    return resp;  // Retorna NULL se não houver sucessor
}


int main(){
    TAB *teste = TAB_inicializa();
    teste = TAB_cria(3, TAB_cria(4, NULL, TAB_cria(7, NULL, NULL)), TAB_cria(5, TAB_cria(1, NULL, NULL), TAB_cria(12, NULL, NULL)));
    TAB_imp_ident(teste);
    printf("\n %d \n", sucessor(teste, 3)->info);


    return 0;
}