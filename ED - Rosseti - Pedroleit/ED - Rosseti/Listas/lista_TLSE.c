#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct lista{
    int info;
    struct lista *prox;
}TLSE;

TLSE *TLSE_cria(void){
    return NULL;
}

int TLSE_tamanho(TLSE *l){
    if(!l) return 0;
    TLSE *p = l;
    int cont = 0;
    while(p){
        p = p->prox;
        cont++;
    }
    return cont;
}

/*
Q1) Escreva uma função em C que, dada uma lista l qualquer, inverta os elementos de l. O
protótipo da função de inversão é o seguinte: void inverte (TLSE* l).
*/
void inverte(TLSE* l){
    if((!l)||(!l->prox)) return;
    TLSE *ant = NULL;
    TLSE *atual = l;
    TLSE *prox = l->prox;

    while(atual){
        atual->prox = ant;
        ant = atual;
        atual = prox;
        prox = prox->prox;
    }
}

/*
Q2) Refaça a Q1, escrevendo uma função em C que, dada uma lista l qualquer, inverta os
elementos de l em uma outra lista de saída. Portanto, a lista de entrada não pode ser
alterada. O protótipo da função de inversão é o seguinte: TLSE* inverte (TLSE* l).
*/
TLSE* inverte_2(TLSE* l){
    if((!l)||(!l->prox)) return l;
    TLSE *p  = NULL;
    //ja fiz nos exercicios abaixo
}

/*
Q3) Escreva uma função em C que, dada uma lista l qualquer, desloque uma vez os
elementos de l, de acordo com n. Se n é ímpar, o elemento que está na última posição
passa a ser o primeiro quando a lista é deslocada. Senão, o elemento que está na
primeira posição passa a ser o último. O protótipo desta função é o seguinte: TLSE*
desloca (TLSE* l, int n).
*/
TLSE* desloca(TLSE* l, int n){
    if(!l) return NULL;
    TLSE *ini = l, *fim = l, *penul;
    if (n % 2 == 0){
        while(fim){
            fim = fim->prox;
        }
        ini->prox = NULL;
        fim->prox = ini;
        return l;
    }
    if (n % 2 == 1){
        while(fim){
            if (fim->prox->prox == NULL){
                TLSE *penul = fim;
            }
            fim = fim->prox;
        }
        penul->prox = NULL;
        fim->prox = ini;
        return l;
    }
}

/*
Q4) Implemente uma função que copie uma lista. A lista original deve permanecer
inalterada. O protótipo da função é o seguinte: TLSE *copia(TLSE *l).
*/
TLSE *copia(TLSE *l){
    TLSE *p;
    p->info = l->info;
    p->prox = copia(l->prox);
    return p;
}

/*
Q5) Crie uma função em C que remova todas as ocorrências de um elemento numa lista.
O protótipo desta função é o seguinte: TLSE* rto(TLSE* l, int elem).
*/
TLSE* rto(TLSE* l, int elem){
    TLSE *p = l, *ant = NULL;
    while(p){
        if(p->info == elem){
            ant->prox = p->prox;
            p->prox = NULL;
        }
        ant = p;
        p = p->prox;
    }
    return l;
}

/*
Q6) Defina uma função em C que, dada uma lista l qualquer, retorne, numa lista de saída,
os elementos ímpares e os elementos pares da lista l, na ordem em que os elementos
aparecem em l. Ao final da execução desta função, a lista resultante terá todos os
elementos da lista l (primeiro os ímpares, depois os pares, na ordem em que eles
aparecem em l), e a lista l continuará contendo os seus elementos. O protótipo da função
é o seguinte: TLSE* i_p(TLSE *l).
*/
TLSE* i_p(TLSE *l){
    if(!l) return NULL;
    TLSE *p = l;
    int n = TLSE_tamanho(p), v[n], i = 0;
    while(p){
        if(p->info % 2 == 1){
            v[i] = p->info;
            i++;
        }
    }
    p = l;
    while(p){
        if(p->info % 2 == 0){
            v[i] = p->info;
            i++;
        }
    }
    TLSE *nova = NULL;
    for (i = n - 1; i >= 0; i--) {
        TLSE *no = TLSE_cria();
        no->info = v[i];
        no->prox = nova;
        nova = no;
    }
    return nova;
}

/*
Q7) Refaça Q6, alterando a lista passada como parâmetro. O protótipo desta função é o
seguinte: void i_p_2(TLSE *l).
*/
void i_p_2(TLSE *l){
    if(!l) return NULL;
    TLSE *p = l;
    int n = TLSE_tamanho(p), v[n], i = 0;
    while(p){
        if(p->info % 2 == 1){
            v[i] = p->info;
            i++;
        }
    }
    p = l;
    while(p){
        if(p->info % 2 == 0){
            v[i] = p->info;
            i++;
        }
    }
    p = l;
    while(p){
        p->info = v[i];
        p = p->prox;
    }
    return l;
}

/*
Q8) Escreva uma função em C que, dadas duas listas l1 e l2 encadeadas, verifique se l1
e l2 são iguais. As listas l1 e l2 devem permanecer inalteradas. Esta função retorna 1 se
as listas são iguais e 0, caso contrário. O protótipo desta função é o seguinte: int igual(TLSE *l1, TLSE *l2).
*/
int igual(TLSE *l1, TLSE *l2){
    if(TLSE_tamanho(l1) != TLSE_tamanho(l2)) return 0;
    TLSE *p1 = l1, *p2 = l2;
    while(p1 && p2){
        if(p1->info != p2->info) return 0;
        p1 = p1->prox;
        p2 = p2->prox;
    }
    return 1;
}

/*
Q9) Implemente uma função em C que, dadas duas listas, faça a concatenação das
mesmas ao final de l1. O protótipo da função é o seguinte: TLSE* junta_listas(TLSE* l1, TLSE* l2).
*/
TLSE* junta_listas(TLSE* l1, TLSE* l2){
    TLSE *p1 = l1, *p2 = l2;
    while(p1){
        p1 = p1->prox;
    }
    p1->prox = p2;
    return l1;
}

/*
Q10) Escreva uma função em C que, dadas duas listas l1 e l2 encadeadas, verifique se l1
é a inversão de l2. As listas l1 e l2 devem permanecer inalteradas. Esta função retorna 1
se as listas estão invertidas e 0, caso contrário. O protótipo desta função é o seguinte: int
Contrario (TLSE *l1, TLSE *l2).
*/
int contrario(TLSE *l1, TLSE *l2){
    if((!l1)||(!l2)) return 0;
    inverte(l2);
    TLSE *p1 = l1, *p2 = l2;
    int n1 = TLSE_tamanho(p1), n2 = TLSE_tamanho(p2);
    if(n1 == n2){
        while(p1 && p2){
            if(p1->info != p2->info) return 0;
        }
        return 1;
    }
    return 0;
}

/*
Q11) Defina uma função em C que, dada uma lista l qualquer, ordene os elementos de l
em uma outra lista de saída. Portanto, a lista de entrada não pode ser alterada. O
protótipo da função desta função é o seguinte: TLSE *ordena(TLSE* l).
*/
void ordenacao(const void *a, const void *b){
    int *pa = a, *pb = b;
    if(*pa > *pb) return -1;
    if(*pa < *pb) return 1;
    return 0;
}

TLSE *ordena(TLSE* l){
    if(!l) return;
    TLSE *p = l;
    int n = TLSE_tamanho(p), i = 0, v[n];
    while (p){
        v[i] = p->info;
        i++;
        p = p->prox;
    }
    qsort(v, n, sizeof(int), ordenacao);
    TLSE *nova = NULL;
    for (i = n - 1; i >= 0; i--) {
        TLSE *no = TLSE_cria();
        no->info = v[i];
        no->prox = nova;
        nova = no;
    }
    return nova;
}

/*
Q12) Refaça Q11, alterando a lista passada como parâmetro. O protótipo desta função é
o seguinte: void ordena(TLSE *l).
*/
void ordena_2(TLSE *l){
    if(!l) return;
    TLSE *p = l;
    int n = TLSE_tamanho(p), i = 0, v[n];
    while (p){
        v[i] = p->info;
        i++;
        p = p->prox;
    }
    qsort(v, n, sizeof(int), ordenacao);
    p = l;
    i = 0;
    while(p){
        p->info = v[i];
        p = p->prox;
        i++;
    }
    return l;
}
