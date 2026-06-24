// Percorrer a arvore B e retornar uma lista ordenada com numeros divisiveis de N e M

#include "include/TARVB.h"
#include "include/TLSE.h"


void aux(TARVB *a, int m, int n, TLSE **lista, int *tam){
    if(!a) return;
    
    int i = a->nchaves;
    aux(a->filho[i], m, n, lista, tam);
    for(i = i-1; i>=0; i--){

        if(a->chave[i]%m == 0 && a->chave[i]%n == 0){
            (*tam)++;
            *lista = TLSE_insere(*lista, a->chave[i]);
        }
        aux(a->filho[i], m, n, lista, tam);

    }
}

int *vetMeN(TARVB *a, int m, int n, int *tam){
    if(!a) return NULL;

    (*tam) = 0;
    TLSE *l = NULL;
    aux(a, m, n, &l, tam);
    if(*tam == 0){
        TLSE_libera(l);
        printf("Nada encontrado\n");
        return NULL;
    }
    int *vet = (int *)malloc(sizeof(int)*(*tam));

    TLSE * p = l; int i = 0;

    while((p)&&i<(*tam)){
        vet[i] = p->info;
        printf(" %d ", vet[i]);
        i++;
        p = p->prox;
    }
    TLSE_libera(l);


    return vet;


}

