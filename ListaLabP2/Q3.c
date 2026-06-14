#include <stdio.h>
#include "TARVBM.h"
#include "TLSE.h"

void aux(TARVBM *a, int n, TLSE **lista){
    if(!a) return;

    int i = 0;
    for(i = 0; i<a->nchaves; i++){
        aux(a->filho[i], n, lista);
        if(a->chave[i]<n && a->folha){
            *lista = TLSE_insere(*lista, a->chave[i]);
            
        }
    }
    aux(a->filho[i],n, lista);


}

TLSE *mN(TARVBM *a, int n){
    if(!a) return NULL;
    TLSE *lista = TLSE_inicializa();
    aux(a,n,&lista);
    return lista;

}


int main(){

    TARVBM *a = TARVBM_Inicializa();

    int t = 2;

    int v[] = {10,20,5,6,12,30,7,17};

    for(int i=0;i<8;i++)
        a = TARVBM_insere(a, v[i], t);

    printf("Arvore:\n");

    TARVBM_imprime(a);

    TLSE *l = mN(a, 100);

    printf("\nMenores que 100:\n");
    TLSE_imprime(l);

    return 0;
}