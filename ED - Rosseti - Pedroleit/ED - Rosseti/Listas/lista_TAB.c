#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
(a) Implemente o tipo abstrato de dados lista simplesmente encadeada genérica, usando void *.
*/
typedef struct ls{
    void *info;
    struct ls *prox;
}TLSE;
/*-----------------------------------------------------------------------------------------*/

typedef struct ab{
    int info;
    struct ab *esq, *dir;
    char *cor;
}TAB;

/*
(Q1) cópia de uma árvore: TAB* copia (TAB *a);
*/
TAB* copia(TAB *a){
    TAB *p = TAB_inicializa();
    p = TAB_cria(a->info, NULL, NULL);
    p->esq = copia(a->esq);
    p->dir = copia(a->dir);
    return p;
}

/*
(Q2) espelho de uma árvore (o que está a esquerda na árvore original, estará a direita no espelho, e
vice-versa): TAB* espelho (TAB *a);
*/
TAB* espelho(TAB *a){
    TAB *p = TAB_inicializa();
    p = TAB_cria(a->info, NULL, NULL);
    p->esq = copia(p->dir);
    p->dir = copia(p->esq);
    return p;
}

/*
(Q3) maior elemento da árvore: TAB* maior(TAB *a);
*/
TAB* maior(TAB *a){
    if(!a) return a;
    TAB *esq = a->esq, *dir = a->dir;


}

/*
(Q4) menor elemento da árvore: TAB* menor(TAB *a);
*/
TAB* menor(TAB *a){
    TAB *p = a;
}

/*
(Q5) uma função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A função
retorna um se elas são iguais e zero, caso contrário. A função deve obedecer ao seguinte protótipo:
int igual (TAB* a1, TAB* a2);
*/
int igual(TAB* a1, TAB* a2){
    TAB *p1 = a1, *p2 = a2;
    if(p1->info != p2->info) return 0;
    if(igual(p1->esq, p2->esq) != 1) return 0;
    if(igual(p1->dir, p2->dir) != 1) return 0;
    return 1;
}

/*
(Q6) uma função em C que, dada uma árvore binária qualquer, retire todos os elementos pares da
árvore original. A função deve ter o seguinte protótipo: TAB* retira_pares (TAB* arv);
*/
TAB* retira_pares(TAB* a){}

/*
(Q7) se esta estrutura TAB tivesse um campo cor (int cor), defina uma função em C que, ao
receber uma árvore binária “sem cor” e totalmente balanceada (isto é, a distância da raiz a qualquer
folha da árvore é sempre a mesma), retorne esta árvore com os nós coloridos somente de vermelho e
preto, sendo que o nó pai NUNCA pode ter a mesma cor de seus filhos. A função deve possuir o
seguinte protótipo: void colore (TAB* arv);
*/
void colore(TAB* a){}

/*
(Q8) descubra a quantidade de nós internos: int ni(TAB *a);
*/
int ni(TAB *a){
    if(!a) return 0;
    TAB *p = a;
    return 1 + ni(p->esq) + ni(p->dir);
}

/*
(Q9) ache a quantidade de nós folha: int nf(TAB *a);
*/
int nf(TAB *a){
    if(!a) return 1;
    TAB *p = a;
    return nf(p->esq) + nf(p->dir);
}
