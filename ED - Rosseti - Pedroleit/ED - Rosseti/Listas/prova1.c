#include <stdio.h>
#include "TLSE.h"

typedef struct lse{
    int info;
    struct lse *prox;
} TLSE;

typedef struct viz{ //VIZINHOS (horizontal) arestas
    int id_viz;
    struct viz *prox_viz;
}TVIZ;

typedef struct grafo{ // GRAFO (vertical) nós
    int id_no, visitado, cor_no;
    TVIZ *prim_viz;
    struct grafo *prox_no;
}TG;

typedef struct arvbin{
    int info; //void *info; int tipo;
    struct arvbin *esq, *dir;
}TAB;


//--------------------------------------------//
TLSE *TLSE_ins_fim(TLSE* t, int x){
    TLSE *p = t, *novo;
    while(p) p = p->prox;
    p->prox = novo;
    novo->info = x;
    novo->prox = NULL;
    return t;
}

int maximo(int x, int y){
    if(x>y) return x;
    return y;
}

int altura(TAB *a){
    if(!a) return 0;
    return 1+maximo(altura(a->esq), altura(a->dir));
}

void aux(TAB *a, TLSE** vet, int nivel){
    if(!a) return;
    aux(a->esq, vet, nivel+1);
    if(nivel%2==0) vet[nivel] = TLSE_insere(vet[nivel], a->info);
    else vet[nivel] = TLSE_ins_fim(vet[nivel], a->info);
    aux(a->dir, vet, nivel+1);
}

void imp_zz(TAB *a){
    if(!a) return;
    int alt = altura(a);
    TLSE **vet = (TLSE**)malloc(sizeof(TLSE*)*alt);
    for(int i=0;i<alt;i++){
        vet[i] = NULL;
    }
    aux(a, vet, 0);
    for(int i=0;i<alt;i++){
        TLSE *p = vet[i];
        while(p){
            printf("%d ", p->info);
            p = p->prox;
        }
    }
    for(int i=0;i<alt;i++) TLSE_libera(vet[i]);
    free(vet);
}
//--------------------------------------------//

int index(int v[], int tam, int k){
    int i;
    for(i=0;i<tam;i++){
        if(v[i]==k) return i;
    }
    return -1;
}

int tripartido_k_arestas(TG *g, int k){
    if(!g) return 0;
    TG *p = g;
    int cores[3] = {-1, -1, -1};
    while(p){
        for(int i=0;i<3;i++){
            if(p->cor_no==cores[2]) break;
            if((cores[i]!=-1)) continue;
            if(cores[i]==p->cor_no) continue;
            cores[i] = p->cor_no;
        }
        p = p->prox_no;
    }
    p = g;
    int cont[3] = {0, 0, 0};
    while(p){
        TVIZ *v = p->prim_viz;
        while(v){
            TG *u = TG_busca_no(g, v->id_viz);
            if(p->cor_no == u->cor_no) return 0;
            cont[index(cores, 3, p->cor_no)]++;
            cont[index(cores, 3, u->cor_no)]++;
            v = v->prox_viz;
        }
        p = p->prox_no;
    }
    int i;
    for(i=0;i<3;i++) if(cont[i]!=(k/2)) return 0;
    return 1;
}

//--------------------------------------------//
