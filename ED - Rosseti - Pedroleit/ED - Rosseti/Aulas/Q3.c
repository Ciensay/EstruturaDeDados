#include <stdio.h>
#include <stdlib.h>

typedef struct arvbinbusca{
    int info;
    struct arvbinbusca *esq, *dir;
}TABB;

typedef struct lse{
    int info;
    struct lse *prox;
} TLSE;

TLSE* TLSE_insere(TLSE *l, int elem){
  TLSE *novo = (TLSE *) malloc(sizeof(TLSE));
  novo->prox = l;
  novo->info = elem;
  return novo;
}

void TLSE_libera(TLSE *l){
  TLSE *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}

void TABB_libera(TABB* t){
  if(t){
    TABB_libera(t->esq);
    TABB_libera(t->dir);
    free(t);
  }
}

void imp_aux(TABB *a, int andar){
  int j;
  if(a){
    imp_aux(a->dir, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->info);
    imp_aux(a->esq, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TABB_imprime(TABB* a){
  imp_aux(a, 1);
}

TABB* TABB_cria(int x, TABB* e, TABB* d){
  TABB* a = (TABB*) malloc(sizeof(TABB));
  a->info = x;
  a->esq = e;
  a->dir = d;
  return a;
}

TABB* TABB_insere(int e, TABB* t){
  if(!t) t = TABB_cria(e, NULL, NULL);
  else if(e < t->info) t->esq = TABB_insere(e, t->esq);
  else if(e > t->info) t->dir = TABB_insere(e, t->dir);
  return t;
}

//-------------------------
TLSE* TLSE_ins_fim(TLSE* l, int info) {
    TLSE* novo = (TLSE*) malloc(sizeof(TLSE));
    novo->info = info;
    novo->prox = NULL;
    if(!l) return novo;
    TLSE* p = l;
    while(p->prox) {
        p = p->prox;
    }
    p->prox = novo;
    return l;
}

int maximo(int x, int y){
    if(x>y) return x;
    return y;
}

int altura(TABB *a){
    if(!a) return 0;
    return 1+maximo(altura(a->esq), altura(a->dir));
}

void aux(TABB *a, TLSE** vet, int nivel){
    if(!a) return;
    aux(a->esq, vet, nivel+1);
    if(nivel%2==0) vet[nivel] = TLSE_ins_fim(vet[nivel], a->info);
    else vet[nivel] = TLSE_insere(vet[nivel], a->info);
    aux(a->dir, vet, nivel+1);
}

void imp_zz(TABB *a){
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

int main(void){
  int n, m;
  TABB *a = NULL;
  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_insere(n, a);
  }
  TABB_imprime(a);
  
  imp_zz(a);
  TABB_libera(a);
  return 0;
}

//40 30 50 25 35 45 55 -1