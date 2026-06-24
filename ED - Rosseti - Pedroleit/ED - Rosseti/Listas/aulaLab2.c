#include <stdio.h>

typedef struct lseint{
    int lim_inf, lim_sup;
    struct lseint *prox;
} TLSEINT;

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

TG *TG_buscaNo(TG *g, int x){
    TG *p = g;
    while (p && (p->id_no != x)){
        p = p->prox_no;
    }
    return p;
}

/*
(Q1) Retornar todas as informações ancestrais de um nó na árvore binária, 
da raiz da árvore até o elemento passado como parâmetro, usando a biblioteca 
de lista encadeada - TLSEINT* misc(TAB *a, int elem), onde:
*/
TLSEINT* misc(TAB *a, int elem){
    
}

/*
(Q2) Reescreva (Q1) com TABB;
*/


/*
(Q3) Escreva uma função que receba uma árvore binária e teste as seguintes propriedades: 
(a) se o nó se encontra no nível par, ele tem ZERO ou dois filhos; e 
(b) se ele está no nível ímpar, ele só pode ter UM filho. A função retorna UM, se a árvore 
segue essas propriedades, e ZERO, caso contrário.
A função deve ter o seguinte protótipo: int teste_arv(TAB* a); e
*/


/*
(Q4) Refaça (Q3) com TABB.
*/


/*
(Q5) Exercícios de grafos do Instagram/Facebook.
*/


/*
(Q6) Dado um grafo conectado, verifique se ele pode ser transformado em uma árvore binária. 
Se ele pode ser uma árvore binária, retorne um. Se não, retorne zero. 
DICA: use TLSE para resolver esta questão: int teste (TG *g); e
*/
int teste(TG *g){
    if(!g) return 0;

}

int conec(TG *g){
    if(!g) return 0;
    TLSE *visit = NULL, *nvisit = TLSE_insere(g->id_no, NULL);
    while(nvisit){
        int x = nvisit->info;
        TG *p = TG_busca(g, x);
        TVIZ *v = p->prim_viz;
        while(v){
            if((!TLSE_busca(nvisit, v->id_viz))&&(!TLSE_busca(visit, v->id_viz))) nvisit = TLSE_insere(nvisit, v->id_viz);
            v = v->prox_viz;
        }
        nvisit = TLSE_retira(nvisit, x);
        visit = TLSE_insere(visit, x);
    }
    TLSE_libera(nvisit);
    int resp = existeNoForaVisit(g, visit);
    TLSE_libera(visit);
    return resp;
}

int ehCiclicoAux(TG *no_atual, TG *g, int pai) {
    no_atual->visitado = 1;
    TVIZ *viz = no_atual->prim_viz;
    while(viz){
        TG *no_vizinho = TG_buscaNo(g, viz->id_viz);
        if (!no_vizinho->visitado) {
            if (ehCiclicoAux(no_vizinho, g, no_atual->id_no))
                return 1;
        }
        else if (no_vizinho->id_no != pai) {
            return 1; 
        }
        viz = viz->prox_viz;
    }
    return 0;
}

int ehCiclico(TG *g) {
    if (!g) return 0;
    TG *p = g;
    while(p){
        if (!p->visitado) {
            if (ehCiclicoAux(p, g, -1)) {
                return 1;
            }
        }
        p = p->prox_no;
    }
    return 0; 
}

//-----------------------------
int aux_ciclico(TG *g, int atual, int pai, TLSE *visitados){
	visitados = insere_inicio(visitados,atual);
	TG* no_atual = TG_busca_no(g,atual);
	TVIZ* viz = no_atual->prim_viz;
	
	while (viz){
		int id_viz = viz->id_viz;
		
		//se o vizinho ainda n foi visitado
		if (!buscar_elemento(visitados,id_viz)){
			if (aux_ciclico(g,id_viz,atual,visitados)) return 1; //encontrou ciclo
		}
		else if (id_viz != pai) return 1; //tbm encontrou
		viz = viz->prox_viz;
	}
	return 0; //se n encontrou nada e a função rolou toda
}

int ciclico(TG *g){
	if (!g) return 0;
	TLSE *visitados = NULL;
	TG* aux = g;
	int resp = 0;

	while (aux){
		if (!buscar_elemento(visitados,aux->id_no)){
			if (aux_ciclico(g,aux->id_no,-1,visitados)){
				resp = 1; //tem ciclo
                break;
			}
		}
		aux = aux->prox_no;
	}
	liberar(visitados);
	return resp;
}
//---------------------------

int estruturaArv(TG *g){

}

/*
(Q7) Dados um grafo, dois nós x e y, retorne um caminho qualquer entre x e y. Se não tiver caminho, o retorno é NULL: TLSE *caminho (TG *g, int x, int y).
*/
TLSE *caminho(TG *g, int x, int y) {
    if (!g) return NULL;

    // 1. PREPARAÇÃO
    // Vamos precisar saber o tamanho do grafo para alocar os arrays.
    // Se você não tiver essa informação, precisará calcular primeiro.
    // Vamos supor um tamanho máximo para simplificar.
    int MAX_NOS = 1000; 
    int *visitado = (int*) calloc(MAX_NOS, sizeof(int));
    int *predecessor = (int*) calloc(MAX_NOS, sizeof(int));
    TLSE *fila = NULL;
    int encontrado = 0;

    // 2. INÍCIO DA BUSCA
    fila = queue(fila, x);
    visitado[x] = 1;
    predecessor[x] = -1; // -1 indica o início do caminho

    // 3. A TRAVESSIA - BFS
    while(fila){
        int u_id = dequeue(&fila);
        if (u_id == y) {
            encontrado = 1;
            break;
        }

        TG *u_no = TG_buscaNo(g, u_id);
        TVIZ *v_viz = u_no->prim_viz;
        while(v_viz){
            int v_id = v_viz->id_viz;
            if(!visitado[v_id]){
                visitado[v_id] = 1;
                predecessor[v_id] = u_id;
                fila = queue(fila, v_id);
            }
            v_viz = v_viz->prox_viz;
        }
    }
    TLSE_libera(fila); // Libera o que sobrou da fila

    // 4. RECONSTRUÇÃO DO CAMINHO
    TLSE *lista_caminho = NULL;
    if(encontrado){
        int atual_id = y;
        while(atual_id != -1) {
            // Insere NO INÍCIO para que o caminho fique na ordem correta (x -> y)
            lista_caminho = TLSE_insere(lista_caminho, atual_id);
            atual_id = predecessor[atual_id];
        }
    }
    free(visitado);
    free(predecessor);
    return lista_caminho; // Retorna a lista (ou NULL se não encontrado)
}