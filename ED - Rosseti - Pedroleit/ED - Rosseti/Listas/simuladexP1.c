#include <stdio.h>

typedef struct lse{
    int info;
    struct lse *prox;
} TLSE;

typedef struct viz{ //VIZINHOS (horizontal) arestas
    int id_viz;
    struct viz *prox_viz;
}TVIZ;

typedef struct grafo{ // GRAFO (vertical) nós
    int id_no, visitado;
    TVIZ *prim_viz;
    struct grafo *prox_no;
}TG;

typedef struct arvbin{
    int info; //void *info; int tipo;
    struct arvbin *esq, *dir;
}TAB;

typedef struct ab{
    int info;
    struct ab *esq, *dir;
}TABB;

/*
3) Faça uma função que calcula a altura de uma árvore binária.
*/
int altura(TAB* a){
    if(!a) return 0;
    return 1 + max(a->dir, a->esq);
}

int max(int x, int y){
    if(x>=y) return x;
    return y;
}

/*
4) Faça uma função que calcula o nível de um nó em uma
árvore. Caso a árvore não tenha esse nó, retorne -1.
*/
int nivel(TAB* a, int k){
    if((!a)||(!TAB_busca(a, k))) return -1;
    TAB *p = TAB_busca(a, k);
    return altura(a) - altura(p);
}

/*
5) Faça uma função que verifica se uma árvore binária normal é
também uma árvore de busca binária.
*/
int eh_TABB(TAB* a){
    if(!a) return 0;
    if((a->esq->info < a->info)&&(a->dir->info > a->info)) return min(eh_TABB(a->esq), eh_TABB(a->dir));
    return 0;
}

int min(int x, int y){
    if(x<=y) return x;
    return y;
}

/*
6) Faça uma função que verifica se uma árvore binária de busca
é uma AVL.
*/
int abs(int x){
    if(x >= 0) return x;
    return -x;
}

int fb(TABB* a){
    if(!a) return -1;
    return altura(a->esq) - altura(a->dir);
}

int eh_AVL(TABB* a){
    if((!a)||(abs(fb(a)) >= 2)) return 0;
    if((eh_AVL(a->esq)+eh_AVL(a->dir))==2) return 1;
    return 0;
}

/*
7) Faça uma função que verifique se uma árvore binária de
busca possui um par de nós que somam S.
*/
int temPar(TABB* a, int S){
    if(!a) return 0;
    int alvo = S - a->info;
    if(TABB_busca(a, alvo)) return 1;
    if((temPar(a->esq, S))||temPar(a->dir, S)) return 1;
    return 0;
}

/*
8) Faça uma função que cria um vetor ordenado a partir de uma
árvore de busca binária, não use nenhum método de
ordenação.
*/
int* vet(TABB* a){
    if(!a) return 0;
    int n = size(a), i = -1;
    int *pI = &i;
    int* v = malloc(n * sizeof(int));
    return aux(a, v, pI);
}

int* aux(TABB *a, int* v, int* i){
    if(!a) return;
    v[(*i)++] = aux(a->esq, v, i);
    v[(*i)++] = aux(a->dir, v, i);
    return v;
}

/*
9) Faça uma função que verifica se um grafo é cíclico.
*/
int ciclo(TG* g);

/*
10) Faça uma função que retorne o tamanho do menor caminho
entre dois nós de um grafo sem pesos.
*/
int menor_cam(TG* g, int no1, int no2){
    if(!g) return NULL;
    TLSE *visit = NULL, *fila = NULL;
    int cont = 0, n = 100, achou;
    int *pred = (int*)malloc(n*sizeof(int));

    fila = TLSE_insere(fila, no1);
    visit = TLSE_insere(visit, no1);
    pred[no1] = -1;

    while(fila){
        int u_id = dequeue(&fila);
        if (u_id == no2) {
            achou = 1;
            break;
        }

        TG *u_g = TG_busca(g, u_id);
        TVIZ *v = u_g->prim_viz;
        while(v){
            int id_viz = v->id_viz;
            if(!TLSE_busca(visit, id_viz)){
                visit = TLSE_insere(visit, id_viz);
                pred[id_viz] = u_id;
                fila = enqueue(fila, id_viz);
            }
            v = v->prox_viz;
        }
    }
    free(fila);
    free(visit);

    if(achou){
        int rec = no2;
        while(pred[rec] != -1){
            cont++;
            rec = pred[rec];
        }
    }
    free(pred);
    return cont;
}

/*
11) Faça uma função que retorne o menor caminho entre dois
nós de um grafo com pesos. No caso de vários caminhos com o
mesmo tamanho, retorne qualquer um.
*/
TLSE* menor_caminho(TG* g, int no1, int no2){
    
}

/*
12) Faça uma função que conta quantos caminhos únicos têm
entre dois nós.
*/
int conta_cam(TG* g, int no1, int no2);

/*
Questão do grafo bipartido
*/
int bipartido(TG *g){
    if(!g) return 1;
    int MAX_NOS = 100, resp = 1;
    TLSE *fila = NULL;
    int *cores = (int*)calloc(MAX_NOS, sizeof(int));
    fila = enqueue(fila, g->id_no);
    int pintar[3] = {0, 2, 1};
    cores[g->id_no] = 1;

    while(fila){
        int u_id = dequeue(&fila);
        TG *u_g = TG_buscaNo(g, u_id);
        TVIZ *v = u_g->prim_viz;
        while(v){
            int v_id = v->id_viz;
            if(cores[v_id] == 0){
                cores[v_id] = pintar[cores[u_id]];
                fila = enqueue(fila, v_id);
            }
            else if(cores[v_id] == cores[u_id]) resp = 0; goto cleanup;
            v = v->prox_viz;
        }
    }

cleanup:
    TLSE_libera(fila);
    free(cores);
    return resp;
}
