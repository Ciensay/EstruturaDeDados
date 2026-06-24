#include <stdio.h>

/*
Árvores B:
    *Suposição: qualquer info adicional a uma chave
    está armazenada no nó onde a chave se encontra.

    *Uma árvore B possui:
        1) Todo nó x tem os campos:
            - nchaves
            - nchaves ordenadas:
                ch1 < ch2 < ... < ch(nchaves)
            - folha (1 ou zero)

        2) Cada nó tem nchaves + 1 ponteiros
        p/ filhos. Se nó é folha, os ponteiros
        são NULL.

        3) Cada folha tem a profundidade h = log(t)n

        4) Existem limites inferiores e superiores 
        sobre o n de chaves do nó expressos em 
        relação a um inteiro fixo, t>=2, chamado 
        grau mínimo da árvore B:

               4A) Todo nó, DISTINTO DA RAIZ, devem ter, 
               pelo menos t-1 chaves. Só a raiz pode ter 1 chave.

               4B) Todo nó pode conter, no máximo,
               2t-1 chaves.
*/

typedef struct arvb{
    int nchaves;
    int *chave;
    int folha;
    struct arvb **filho;
}TARVB;

TARVB *TARVB_cria(int t){
    TARVB *a = (TARVB *)malloc(sizeof(TARVB));
    a->chave = (int *)malloc(sizeof(int) * 2*t-1);
    a->nchaves = 0;
    a->folha = 1;
    a->filho = (TARVB *)malloc(sizeof(TARVB)*2*t);
    for(int i = 0;i<2*t;i++){
        a->filho[i] = NULL;
    }
    return a;
}

TARVB *TARVB_busca(TARVB *a, int x){
    if(!a) return a;
    int i = 0;
    while((i<a->nchaves)&&(a->chave[i] < x)) i++;
    if((i<a->nchaves)&&(a->chave[i] == x)) return a;
    return TARVB_busca(a->filho[i], x);
}

TARVB *divisao(TARVB *x, int i, TARVB *y, int t){
    TARVB *z = TARVB_cria(t);
    z->nchaves = t-1;
    z->folha = y->folha;
    int j;
    for(j = 0;j<t-1;j++) z->chave[j] = y->chave[j+t];
    if(!y->folha){
        for(j = 0;j<t;j++){
            z->filho[j] = y->filho[j+t];
            y->filho[j+t] = NULL;
        }
    }
    y->nchaves = t-1;
    for(j=x->nchaves;j>=i;j--) x->filho[j+1] = x->filho[j];
    x->filho[i] = z;
    for(j=x->nchaves;j>=i;j--) x->chave[j] = x->chave[j-1];
    x->chave[i-1] = y->chave[t-1];
    x->nchaves++;
    return x;
}

TARVB *insere_nao_completo(TARVB *x, int k, int t){
    int i = x->nchaves-1;
    if(x->folha){
        while((i>=0)&&(k<x->chave[i])){
            x->chave[i+1] = x->chave[i];
            i--;
        }
        x->chave[i+1] = k;
        x->nchaves++;
        return x;
    }
    while((i>=0)&&(k<x->chave[i])) i--;
    i++;
    if(x->filho[i]->nchaves == ((2*t)-1)){
        x = divisao(x, (i+1), x->filho[i], t);
        if(k>x->chave[i]) i++;
    }
    //x->filho[i] = insere_nao_completo();
    return x;
}

TARVB *TARVB_insere(TARVB *a, int k, int t){
    if(!TARVB_busca(a, k)) return a;
    if(!a){
        a = TARVB_cria(t);
        a->chave[0] = k;
        a->nchaves = 1;
        return a;
    } 
    if(a->nchaves == (2*t)-1){
        TARVB *s = TARVB_cria(t);
        s->nchaves = 0;
        s->folha = 0;
        s->filho[0] = a;
        s = divisao(s, 1, a, t);
        s = insere_nao_completo(s, k, t);
    }


}

/*
Eliminar uma chave na árvore B:
    * Análoga a inserção.
    * Mais complicada: chave eliminada do nó interno.
    * Eliminação de um nó interno:
        - Filhos reorganizados para não violar limite anterior.
        -  Só a raiz pode ter [1] chave. Demais, [t-1] chaves.
    * Algoritmo recursivo em O(log_t(n)): (PREEMPTIVO)
        c1 - Se a chave k está no nó x, e x é folha, elimine k de x.
        c2 - Se k está em x, e x é nó interno:
            c2a - Se o filho y que precede k no nó x tem,
                ao menos, t chaves, então ache o predecessor
                k' de k em y. Elimine k' de y, e troque k' 
                por k em x.
            c2b - Se o filho Z que SUCEDE k no nó x tem,
                ao menos, t chaves, então ache o SUCESSOR
                k' de k em Z. Elimine k' de Z, e troque k' 
                por k em x.
            c2c - Caso contrário, se y e z tem [t-1] chaves,
                  faça a intercalação de k com todas as chaves
                  de z em y. Neste momento y terá [2t-1] chaves.
                  Em seguida, libere, recursivamente, k de y.
        c3 - Se k não está em x, ache qual filho f que k
             deve estar. Se f tem t-1 chaves, use ou c3a
             ou c3b, ação necessária para garantir descida
             em nós com [t] chaves. Em seguida, termine a 
             recursão a partir de f:
            c3a - Se f tem [t-1] chaves, mas tem um [irmão imediato] 
                  i com [t] chaves, de uma chave de i para seu pai 
                  e passe uma chave do pai para f.
            c3b - Se f tem [t-1]  chaves e seu(s) irmão(s) imediato(s)
                  tem [t-1] chaves, faça a intercalação de f com [um] 
                  de seus irmãos, junto com [uma] chave ao pai.
*/