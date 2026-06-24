#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin{
    int info; //void *info; int tipo;
    struct arvbin *esq, *dir;
}TAB;

/*
1) Faça uma função que soma todos os elementos de nível ímpar em uma árvore binária simples e subtraia todos os de nível par - void misc1(TAB *a, int *soma, int *sub).
*/
int misc1(TAB *a){
    if(!a) return 0;
    int x = 0;
    if(nivel(a) % 2 == 0){
        x -= a->info;
    }
    else if(nivel(a) % 2 == 1){
        x += a->info;
    }
    return x + misc1(a->esq) + misc1(a->dir);
}

/*
2) Faça uma função que encontra a média simples de elementos em cada nível de uma árvore binária simples - int *media(TAB *a, int *tam_vet).
*/
int *media(TAB *a, int *tam_vet){
    if(!a) return;
    int v[] = (int *)malloc(sizeof(int) * *tam_vet);
    int v2[] = (int *)malloc(sizeof(int) * *tam_vet);
    for(int i = 0;i<*tam_vet;i++){
        v[i] = 0;
        v2[i] = 0;
    }
    int nivel_atual = nivel(a);
    aux(a, v, v2, nivel_atual);

    for(int i = 0;i<*tam_vet;i++){
        v[i] = v[i] / v2[i];
    }
    free(v2);
    return v;
}

void aux(TAB *a, int *v, int *v2, int nivel){
    if(!a) return;
    v[nivel] += a->info;
    v2[nivel]++;
    aux(a->esq, v, v2, nivel+1);
    aux(a->dir, v, v2, nivel+1);
}

/*
3) Faça uma função que encontra todos os elementos maiores que N e retorne num vetor ordenado, não utilize nenhum algoritmo de ordenação - int *maioresN(TAB *a, int N, int *tam_vet).
*/
int *maioresN(TAB *a, int N, int *tam_vet){
    if(!a) return;
    TAB *p = TABB_busca(a, N);
    aux32(p->dir, tam_vet);
    int v[] = (int *)malloc(sizeof(int) * *tam_vet);
    int *tam = 0;
    aux31(p->dir, v, tam);
    return v;
}

void aux32(TAB *a, int *tam_vet){
    if(!a) return 0;
    (*tam_vet)++;
    aux32(a->esq, tam_vet);
    aux32(a->dir, tam_vet);
}

int *aux31(TAB *a, int *v, int *tam){
    if(!a) return;
    v[(*tam)++] = aux_3(a->esq, v, tam);
    v[(*tam)++] = a->info;
    v[(*tam)++] = aux_3(a->dir, v, tam);
    return v;
}

/*
4) Faça uma função que encontra todos os elementos menores que N e retorne num vetor ordenado, não utilize nenhum algoritmo de ordenação - int *menoresN(TAB *a, int N, int *tam_vet).
*/
int *menoresN(TAB *a, int N, int *tam_vet){
    if(!a) return;
    TAB *p = TABB_busca(a, N);
    aux42(p->esq, tam_vet);
    int v[] = (int *)malloc(sizeof(int) * *tam_vet);
    int *tam = 0;
    aux41(p->esq, v, tam);
    return v;
}

void aux42(TAB *a, int *tam_vet){
    if(!a) return 0;
    (*tam_vet)++;
    aux32(a->esq, tam_vet);
    aux32(a->dir, tam_vet);
}

int *aux41(TAB *a, int *v, int *tam){
    if(!a) return;
    v[(*tam)++] = aux_3(a->esq, v, tam);
    v[(*tam)++] = a->info;
    v[(*tam)++] = aux_3(a->dir, v, tam);
    return v;
}

/*
5) Retorne o nó de maior nível que é ancestral tanto de N quanto de M - TAB* maior_nivel(TAB *a, int N, int M).
*/


/*
6) Retorne a quantidade de caminhos que somam N em uma árvore binária simples - int quant_caminhos(TAB *a, int N).
*/

/*---------------------------------------------------------------------------------------------------------------*/
typedef struct viz{ //VIZINHOS (horizontal) arestas
    int id_viz;
    struct viz *prox_viz;
}TVIZ;

typedef struct grafo{ // GRAFO (vertical) nós
    int id_no, visitado;
    TVIZ *prim_viz;
    struct grafo *prox_no;
}TG;

/*
7) Faça uma função que descubra se um grafo não direcionado é cíclico - int dir_ciclico(TG *g).
*/
int dir_ciclico(TG *g){
    TG *p = g, *c = g;
    p->visitado = 1;
    while(p){
        TVIZ *v = p->prim_viz;
        
    }
}

/*
8) Faça uma função que descubra se um grafo não direcionado é conectado - int dir_conect(TG *g).
*/
int dir_conect(TG *g){

}
