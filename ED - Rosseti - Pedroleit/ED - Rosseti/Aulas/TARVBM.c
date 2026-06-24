#include <stdio.h>

/*
* Semelhante a B, exceto por:
    1 - Armazenar somente as infos nas folhas(nós internos servem de ponteiros)
    2 - As folhas são encadeadas
* B+ mais eficiente e mais usada, na prática, que a B
*/

typedef struct arvbmais{
    int nchaves;
    int *chave;
    int folha;
    struct arvbmais **filho, *prox;
}TARVBM;

/*
OPERAÇÕES IDÊNTICAS:
    IMPRESSÃO 
    LIBERAÇÃO 
    INICIALIZAÇÃO
*/

/*
OPERAÇÕES DISTINTAS:
    CRIAÇÃO DE UM NÓ  \
    BUSCA DE INFO     / CÓDIGO

    INSERÇÃO          \
    RETIRADA          / DESENHO
*/

TARVBM *TARVBM_cria(int t){
    TARVBM *a = (TARVBM*)malloc(sizeof(TARVBM));
    a->folha = 1;
    a->nchaves = 0;
    a->chave = (int*)malloc(sizeof(int) * (2*t-1));
    a->prox = NULL;
    a->filho = (TARVBM**)malloc(sizeof(TARVBM*)*2*t);
    int i;
    for(i=0;i<2*t;i++){
        a->filho[i] = NULL;
    }
    return a;
}

TARVBM *TARVBM_busca(TARVBM *a, int x){
    if(!a) return a;
    int i = 0;
    while((i<a->nchaves)&&(a->chave[i]<x))i++;
    if((a->folha)&&(i<a->nchaves)&&(a->chave[i]==x)) return a;
    if((i<a->nchaves)&&(a->chave[i]==x))i++;
    return TARVBM_busca(a->filho[i], x);
}

/*
* Inserção na folha 
* Divisão:
    - Se nó é interno: igual a B
    - Se nó é folha: info mediana sobe p/ o pai e fica na folha

* Retirada de B+: 3 casos
    caso 1 - k está em x e x é folha
    caso 3 - k não está em x. achar filho f onde k pode estar.
    se f tem [t-1] chaves, aplicar 3a ou 3b.
        3a - irmão imediato i tem t chaves.
        3b - cada irmão imediato tem t-1 chaves.
*/