#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ab{
int info;
struct ab *esq, *dir;
}TABB;

int TABB_tam(TABB *a);

/*
(Q1) maior elemento da árvore: TABB* maior(TAB *a);
*/
TABB *maior(TABB *a){
    if(!a) return;
    TABB *m = maior(a->dir);
    return m;
}

/*
(Q2) menor elemento da árvore: TABB* menor(TAB *a);
*/
TABB *menor(TABB *a){
    if(!a) return;
    TABB *m = menor(a->esq);
    return m;
}

/*
(Q3) uma função em C que, dada uma árvore binária de busca qualquer, retire todos os elementos
ímpares da árvore original. A função deve ter o seguinte protótipo: TABB* retira_impares(TABB* a);
*/


/*
(Q4) uma função em C que, dada uma árvore binária de busca qualquer, retorne, num vetor, todos
os elementos menores que N. A função deve ter o seguinte protótipo: int* mN(TABB*a, int N);
*/
int *mN(TABB *a, int n){
    if(!a) return NULL;
    int v[] = malloc(sizeof(int) * TABB_tam(a));
    int tam = 0;

}

int *mn_aux(TABB *a, int n, int v[], int tam){
    if(!a) return;
    if(a->info < n){
        v[tam] = a->info;
        tam++;
    } 

    return mn_aux(a->esq, n, v, tam);

}

/*
(Q5) Reescreva as operações básicas da ABB para poder armazenar as figuras geométricas
quadrado, triângulo, retângulo e trapézio. A área da figura será usada para definir os elementos
pertencentes a sub-árvore esquerda e a sub-árvore direita. A impressão será em ordem simétrica e,
além da área, devem ser informadas as dimensões da figura.
*/