#include <stdio.h>

typedef struct viz{ //VIZINHOS (horizontal) arestas
    int id_viz;
    struct viz *prox_viz;
}TVIZ;

typedef struct grafo{ // GRAFO (vertical) nós
    int id_no, cor;
    TVIZ *prim_viz;
    struct grafo *prox_no;
}TG;

/*
(Q1) descubra a quantidade de nós: int nn(TG *g);
*/
int nn(TG *g){
    TG *p = g;
    int cont = 0;
    while(p){
        cont++;
        p = p->prox_no;
    }
    return cont;
}

/*
(Q2) ache a quantidade de arestas: int na(TG *g);
*/
int na(TG *g){
    TG *p = g;
    int cont = 0;
    while(p){
        TVIZ *v = p->prim_viz;
        while(v){
            cont++;
            v = v->prox_viz;
        }
        p = p->prox_no;
    }
    return cont/2;
}

/*
(Q3) se esta estrutura tivesse um campo cor (int cor) na estrutura de grafo, teste se nós vizinhos não
tem a mesma cor. A função retorna um se os vizinhos não tem a mesma cor e zero, caso contrário:
int nao_tem_mesma_cor(TG *g);
*/
int nao_tem_mesma_cor(TG *g){
    TG *p = g;
    if (!p) return -1;
    int n = nn(g), cores[n];
    while(p){
        cores[p->id_no] = p->cor;
        p = p->prox_no;
    }
    p = g;
    TVIZ *v = p->prim_viz;
    while(v){
        if(cores[p->id_no] != cores[v->id_viz]) return 1;
        v = v->prox_viz;
    }
    return 0;
}

/*
(Q4) verificar se o grafo, passado como parâmetro de entrada, possui todos os nós com grau
igual a k - int testek(TG *g, int k); e
*/
int testek(TG *g, int k){
    TG *p = g;
    int cont_viz;
    while(p){
        TVIZ *v = p->prim_viz;
        while(v){
            cont_viz++;
            v = v->prox_viz;
        }
        if(cont_viz != k) return 0;
        cont_viz = 0;
    }
    return 1;
}

/*
(Q5) testar se dois grafos são iguais - int ig(TG *g1, TG *g2).
*/
int ig(TG *g1, TG *g2){
    TG *p1 = g1, *p2 = g2;
    if((!p1)||(!p2)) return 0;
    while((p1)&&(p2)){
        if(p1->id_no != p2->id_no) return 0;
        TVIZ *v1 = p1->prim_viz, *v2 = p2->prim_viz;
        while((v1)&&(v2)){
            if(v1->id_viz != v2->id_viz) return 0;
            v1 = v1->prox_viz;
            v2 = v2->prox_viz;
        }
        p1 = p1->prox_no;
        p2 = p2->prox_no;
    }
    return 1;
}