#include <stdio.h>

typedef struct lseint{
  int lim_inf, lim_sup;
  struct lseint *prox;
} TLSEINT;

typedef struct lista{
    int info;
    struct lista *prox;
}TLSE;

typedef struct arvb{
    int nchaves;
    int *chave;
    int folha;
    struct arvb **filho;
}TARVB;

/*
(Q1) Uma função em C que, dada uma árvore B qualquer, retorne, numa lista, todos os elementos menores que N.
A função deve ter o seguinte protótipo: TLSE* mN(TARVB*a, int N);
*/
TLSE* mN(TARVB* a, int N){
    if(!a) return NULL;
    
    TLSE *resp = NULL;
    int i;
    
    // Percorre as chaves do nó atual
    for(i = 0; i < a->nchaves; i++){
        
        // CASO 1: Encontrámos uma chave MAIOR ou IGUAL a N
        if(a->chave[i] >= N){
            if(!a->folha){
                TLSE *sub = mN(a->filho[i], N);
                resp = junta(resp, sub); // Correção: resp vem primeiro (ordem crescente)
            }
            return resp; // Paramos por aqui neste nó
        }
        if(!a->folha){
            TLSE *sub = mN(a->filho[i], N);
            resp = junta(resp, sub); // Junta o que veio do filho no final da resposta
        }
        resp = TLSE_ins_fim(resp, a->chave[i]);
    }
    if(!a->folha){
        TLSE *sub = mN(a->filho[i], N); // Aqui 'i' vale nchaves
        resp = junta(resp, sub);
    }
    return resp;
}

/*
(Q2) Retornar todas as informações ancestrais de um nó na árvore B, da raiz da árvore até o 
elemento passado como parâmetro, usando a biblioteca de lista encadeada - TLSEINT* misc(TARVB *a, int elem), onde:
*/



/*
(Q3) Refaça (Q1) e (Q2) com TARVBM;
*/

/*
(Q4) Dados dois arquivos texto que representam conjuntos inteiros (isto é, não há elementos repetidos nos arquivos), 
um elemento por linha, e fazendo SOMENTE uma leitura em cada arquivo, faça cada uma das questões utilizando tabelas hash em memória secundária:

(a) interseção dos conjuntos: void inter(char* arq1, char* arq2, char* saida);

(b) diferença simétrica de conjuntos: void dif_sim(char* arq1, char* arq2, char* saida);

(c) união de conjuntos: void uniao(char* arq1, char* arq2, char* saida); e
*/

/*
(Q5) Refaça (Q4) para memória principal, recebendo no lugar de nome de arquivo, um vetor e seu tamanho (isto é, int *vet, int n).
*/

/*
(Q6) Refaça as bibliotecas de heap para funcionar com heaps quaternárias. Assim, no lugar de termos funções de esquerda e direita, teremos funções que retornam os quatro possíveis filhos de um nó (isto é, escreva as funções filho_1, filho_2, filho3 e filho4);
*/

/*
(Q7) Refaça a operação max_heapfy de heap binária de máximo para a de mínimo (min_heapfy) em memórias primária e secundária.
*/
int *min_heapify(int *heap, int n, int pos){
  int menor = pos, e = esq(pos), d  = dir(pos);
  if((e<n)&&(heap[e]<heap[menor])) menor = e;
  if((d<n)&&(heap[d]<heap[menor])) menor = d;
  if(menor!=pos){
    int tmp = heap[pos];
    heap[pos] = heap[menor];
    heap[menor] = tmp;
    min_heapify(heap, n, menor);
  }
}