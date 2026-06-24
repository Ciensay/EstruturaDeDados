#include "include/TARVBM.h"
#include "include/TLSEINT.h"
#include <limits.h>

    void aux(TARVBM *a, int elem, TLSEINT **lista){
    if(!a) return;
    int i = 0;

    if((i==0) && a->chave[i]>elem){
    printf("We got this!aaa");
    aux(a->filho[i], elem, lista);
    *lista = TLSEINT_insere(*lista, INT_MIN, a->chave[i]);
    return;
}

    for(i = 0; i<a->nchaves-1; i++){
        

        if(a->chave[i]<=elem && a->chave[i+1]>=elem){
            printf("WE GOT THIS\n");
            aux(a->filho[i+1], elem, lista);
            *lista = TLSEINT_insere(*lista,a->chave[i], a->chave[i+1]);
            return;
        }
    }
    aux(a->filho[i+1], elem, lista);
    *lista = TLSEINT_insere(*lista, a->chave[i], INT_MAX);
}

TLSEINT *misc(TARVBM *a, int elem){
    if(!a) return NULL;
    TLSEINT *lista = TLSEINT_inicializa();
    aux(a,elem,&lista);
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

    TLSEINT *l = misc(a, 6);

    //printf("\nMenores que 100:\n");
    TLSEINT_imprime(l);

    return 0;
}
