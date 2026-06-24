#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

typedef struct ab{
int info;
struct ab *esq, *dir;
}TABB;

////////////////////////////////////////////////////////////////////////

/*1) Fa�a uma fun��o que soma todos os elementos de n�vel �mpar em uma �rvore bin�ria simples e
subtrai todos os de n�vel par - int misc1(TAB *a).*/

int aux_misc1(TAB*a, int nivel){
	if (!a) return 0;
	int soma = 0;
	TAB* aux = a;
	if (nivel%2==0) soma -= aux->info;
	else soma += aux->info;
	return soma + aux_misc1(aux->esq,nivel+1) + aux_misc1(aux->dir,nivel+1);
}

int misc1(TAB* a){
	if (!a) return 0;
	return aux_misc1(a,0);
}

///////////////////////////////////////////////////////////////////////

/*2) Fa�a uma fun��o que encontra a m�dia simples de elementos em cada n�vel de uma �rvore bin�ria
simples - int *media(TAB *a, int *tam_vet).*/

int altura(TAB *a) {
    if (!a) return 0;
    int e = altura(a->esq);
    int d = altura(a->dir);
    if (e>d) return 1 + e;
    return 1 + d;
} //descobre o tamanho do vetor

void aux_media(TAB*a,int *valor, int *qtd, int nivel){
	if (!a) return;
	valor[nivel] += a->info;
	qtd[nivel] ++;
	aux_media(a->esq,valor,qtd,nivel+1);
	aux_media(a->dir,valor,qtd,nivel+1);
}

int *media(TAB*a,int *tam_vet){
	if (!a) return NULL;
	*tam_vet = altura(a);
	int *vetor_valor = (int*)calloc(*tam_vet,sizeof(int));
	int *vetor_qtd = (int*)calloc(*tam_vet,sizeof(int));
	aux_media(a,vetor_valor,vetor_qtd,0);
	for(int i=0;i<(*tam_vet);i++){
		vetor_valor[i] = vetor_valor[i]/vetor_qtd[i];
	}
	free(vetor_qtd);
	return vetor_valor;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*3) Fa�a uma fun��o que encontra todos os elementos maiores que N em uma ABB e retorne num
vetor ordenado, n�o utilize nenhum algoritmo de ordena��o - int *maioresN(TABB *a, int N, int
*tam_vet).*/

void aux_maioresN(TABB *a, int **vetor, int *tam_vet, int N) {
    if (!a) return;
    if (a->info > N) {
        aux_maioresN(a->esq, vetor, tam_vet, N);
        *vetor = (int*)realloc(*vetor, (*tam_vet + 1) * sizeof(int));
        (*vetor)[*tam_vet] = a->info;
        (*tam_vet)++;
        aux_maioresN(a->dir, vetor, tam_vet, N);
    } else aux_maioresN(a->dir, vetor, tam_vet, N);
}

int *maioresN(TABB *a, int N, int *tam_vet) {
    if (!a) return NULL;
    int *vetor = NULL;
    *tam_vet = 0;
    aux_maioresN(a, &vetor, tam_vet, N);
    return vetor;
}

//se for em um n�
/*void aux_maioresN(TABB*a,int **vetor, int *tam_vet){
	if (!a) return;
	aux_maioresN(a->esq,vetor,tam_vet);
	*vetor = (int*)realloc(*vetor,((*tam_vet)+1)*sizeof(int));
	(*vetor)[*tam_vet] = a->info;
	(*tam_vet)++;
	aux_maioresN(a->dir,vetor,tam_vet);
}

int *maioresN(TABB *a, int N, int *tam_vet){
	if (!a) return NULL;
	TABB* aux = a;
	while (aux && aux->info<=N){
		if (N>aux->info) aux = aux->dir;
		else aux = aux->esq;
	}
	if (!aux ||!aux->dir) return NULL;
	int *vetor = NULL; //1 posi��o s� mas vai ser arrumado
	(*tam_vet) = 0;
	aux_maioresN(aux->dir,&vetor,tam_vet);
	return vetor;
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////

/*4) Fa�a uma fun��o que encontra todos os elementos menores que N em uma ABB e retorne num vetor
ordenado, n�o utilize nenhum algoritmo de ordena��o - int *menoresN(TABB *a, int N, int *tam_vet).*/

void aux_menoresN(TABB *a, int **vetor, int *tam_vet, int N) {
    if (!a) return;
    if (a->info < N) {
        aux_menoresN(a->esq, vetor, tam_vet, N);
        *vetor = (int*)realloc(*vetor, (*tam_vet + 1) * sizeof(int));
        (*vetor)[*tam_vet] = a->info;
        (*tam_vet)++;
        aux_menoresN(a->dir, vetor, tam_vet, N);
    } else aux_menoresN(a->esq, vetor, tam_vet, N);
}

int *menoresN(TABB *a, int N, int *tam_vet) {
    if (!a) return NULL;
    int *vetor = NULL;
    *tam_vet = 0;
    aux_menoresN(a, &vetor, tam_vet, N);
    return vetor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*5) Retorne o n� de maior n�vel que � ancestral tanto de N quanto de M - TAB* maior_nivel(TAB *a, int
N, int M).*/

TAB* maior_nivel(TAB *a, int N, int M){
	if (!a) return a;
	if (!busca(a,N)||!busca(a,M)) return NULL;
	if (a->info>N && a->info>M) return maior_nivel(a->esq,N,M);
	if (a->info<N && a->info<M) return maior_nivel(a->dir,N,M);
	return a;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*6) Retorne a quantidade de caminhos que somam N em uma �rvore bin�ria simples - int
quant_caminhos(TAB *a, int N).*/

int aux_caminhos(TAB* a, int N){
	if (!a) return 0;
	int contador = 0;
	int info = a->info;
	if (info == N) contador++;
	return contador + aux_caminhos(a->esq,N-info) + aux_caminhos(a->dir,N-info);
}

int quant_caminhos(TAB *a, int N){
	if (!a) return 0;
	return aux_caminhos(a,N)+quant_caminhos(a->esq,N)+quant_caminhos(a->dir,N);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*7) Fa�a uma fun��o que descubra se um grafo n�o direcionado � c�clico - int dir_ciclico(TG *g)
(prestar aten��o com os ponteiros)*/

int aux_ciclico(TG* g, int atual, int pai, TLSE** visitados){
	if (!g) return 0;
	*visitados = TLSE_insere(*visitados,atual);
	TG* no_atual = TG_busca_no(g,atual);
	TVIZ* viz = no_atual->prim_viz;
	while (viz){
		int id_viz = viz->id_viz;
		if (!TLSE_busca(*visitados,id_viz)){
			if (aux_ciclico(g,id_viz,atual,visitados)) return 1;
		}
		else if (id_viz!=pai) return 1;
		viz = viz->prox_viz;
	}
	return 0;
}

int dir_ciclico(TG* g){
	if (!g) return 0;
	TLSE* visitados = NULL; //precisa ver isso com todos os n�s
	TG* aux = g;
	while(aux){
		if (!TLSE_busca(visitados,aux->id_no)){
			if (aux_ciclico(g,aux->id_no,-1,&visitados)){
				TLSE_libera(visitados);
				return 1;
			}
		}
		aux = aux->prox_no;
	}
	TLSE_libera(visitados);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*8) Fa�a uma fun��o que descubra se um grafo n�o direcionado � conectado - int dir_conect(TG *g).*/

int existeNoForaVisit(TG *g,TLSE *visit){
	if (!g) return 0;
	TG* aux = g;
	while (aux){
		if (!TLSE_busca(visit,aux->id_no)) return 0;
		aux = aux->prox_no;
	}
	return 1;
}

int dir_conect(TG* g){
	if (!g) return 0;
	TLSE *visit = NULL, *nvisit = TLSE_insere(NULL,g->id_no);
	while(nvisit){
		int x = nvisit->info;
		TG *p = TG_busca_no(g,x);
		TVIZ *v = p->prim_viz;
		while(v){
			if (!TLSE_busca(nvisit,v->id_viz)&&!TLSE_busca(visit,v->id_viz))
				nvisit = TLSE_insere(nvisit,v->id_viz);
			v = v->prox_viz;
		}
		nvisit = TLSE_remove(nvisit,x);
		visit = TLSE_insere(visit,x);
	}
	int resp = existeNoForaVisit(g,visit);
	TLSE_libera(nvisit);
	TLSE_libera(visit);
	if (resp) return 0;
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*9) Retornar todas as informa��es ancestrais de um n� na �rvore bin�ria, da raiz da �rvore at� o
elemento passado como par�metro, usando a biblioteca de lista encadeada - TLSEINT* misc(TAB *a,
int elem), onde:
typedef struct lseint{
int lim_inf, lim_sup;
struct lseint *prox;
} TLSEINT;*/

typedef struct lseint{
int lim_inf, lim_sup;
struct lseint *prox;
} TLSEINT;

TLSEINT* TLSEINT_insere(TLSEINT *l, int inf, int sup){
  TLSEINT *novo = (TLSEINT *) malloc(sizeof(TLSEINT));
  novo->prox = l;
  novo->lim_inf = inf;
  novo->lim_sup = sup;
  return novo;
}

TLSEINT* aux_misc(TAB*a,int elem){
	if (a->info==elem) return NULL;
	int min = INT_MIN, max = INT_MAX;
	if (a->info > elem) max = a->info;
	else min = a->info;
	if (TAB_busca(a->esq,elem)) return TLSE_insere(aux_misc(a->esq,elem),min,max);
	return TLSE_insere(aux_misc(a->dir,elem),min,max);
}

TLSEINT* misc(TAB *a,int elem){
	if (!a || !TAB_busca(a,elem)) return NULL;
	return aux_misc(a,elem);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*11) Escreva uma fun��o que receba uma �rvore bin�ria e teste as seguintes propriedades: (a) se
o n� se encontra no n�vel par, ele tem ZERO ou dois filhos; e (b) se ele est� no n�vel �mpar, ele
s� pode ter UM filho. A fun��o retorna UM, se a �rvore segue essas propriedades, e ZERO, caso 
contr�rio. A fun��o deve ter o seguinte prot�tipo: int teste_arv(TAB* a);*/

int aux_teste_arv(TAB* a, int nivel){
	if(!a) return 1;
	if (nivel%2==0){
		if((a->esq && !a->dir)||(!a->esq && a->dir)) return 0;
	}
	else{
		if ((a->esq&&a->dir)||(!a->esq&&!a->dir)) return 0;
	}
	return aux_teste_arv(a->esq,nivel+1) && aux_teste_arv(a->dir,nivel+1);
}

int teste_arv(TAB* a){
    if (!a) return 1;
    return aux_teste_arv(a,0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*13) Dado um grafo conectado, verifique se ele pode ser transformado em uma �rvore bin�ria. Se ele
pode ser uma �rvore bin�ria, retorne um. Se n�o, retorne zero. DICA: use TLSE para resolver esta
quest�o: int teste (TG *g);*/

int teste (TG *g){
	if (!g) return 0;
	if (!dir_conect(g) || dir_ciclico(g)) return 0;
	TG *aux = g;
	while(aux){
		TVIZ *viz = aux->prim_viz;
		int contador = 0;
		while(viz){
			contador++;
			if (contador>3) return 0;
			viz = viz->prox_viz;
		}
		aux = aux->prox_no;
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/*14) Dados um grafo, dois n�s x e y, retorne um caminho qualquer entre x e y. Se n�o tiver 
caminho, o retorno � NULL: TLSE *caminho (TG *g, int x, int y).*/

TLSE *aux_caminho(TG*g,int atual,int destino, TLSE* visitados, TLSE* resposta){
	if (!g) return NULL;
	if (atual==destino) return TLSE_insere(resposta,atual);
	
	TG* no_atual = TG_busca_no(g,atual);
	TVIZ* viz = no_atual->prim_viz;
	
	while(viz){
		if (!TLSE_busca(visitados,viz->id_viz)){
			visitados = TLSE_insere(visitados,viz->id_viz);
			resposta = aux_caminho(g,viz->id_viz,destino,visitados,resposta);
			if (resposta) return TLSE_insere(resposta,atual);
		}
		viz = viz->prox_viz;
	}
	return NULL;
}

TLSE *caminho (TG *g, int x, int y){
	if (!TG_busca_no(g,x) || !TG_busca_no(g,y)) return NULL;
	TLSE *visitados = NULL, *resposta = NULL;
	resposta = aux_caminho(g,x,y,visitados,resposta);
	TLSE_libera(visitados);
	return resposta;
}

////////////////////////////////////////////////////////////////////////////////////////////////

/*
15 - Verifique se um grafo � bipartido, retorne 1 caso sim e 0 caso n�o, � permitido o uso da 
estrutura TLSE para auxiliar. int teste(TG* g)

Defini��o de bipartido: Um grafo ao qual podemos separar em duas parti��es, como exemplo uma U 
e outra V, na qual, os n�s de U somente se ligam aos n�s de V e os de V somente aos de U. Al�m 
disso, o grafo deve ser todo conectado para configurar como um grafo bipartido.

Dica: Para entender melhor, um grafo bipartido, olhado na implementa��o de sua estrutura (n�s 
principais e n�s de vizinhos), se trata de um grafo ao qual podemos dividir em 2 grafos, um em 
que os n�s principais s�o somente do conjunto U e os vizinhos todos somente de V, e no outro 
vice-versa, desenhe e ficar� mais vis�vel a defini��o de fato de um grafo bipartido.
*/

typedef struct cor{
	int id;
	int cor; //0 ou 1
	struct cor *prox;
}TLSECOR;

TLSECOR *TLSECOR_insere(TLSECOR*lista, int id,int cor){
	TLSECOR *novo = (TLSECOR*)malloc(sizeof(TLSECOR));
	novo->cor = cor;
	novo->id = id;
	novo->prox = lista;
	return novo;
}

int TLSECOR_busca(TLSECOR* lista, int id) {
    TLSECOR* p = lista;
    while(p){
        if (p->id == id) return p->cor;
        p = p->prox;
    }
    return -1;
}

void TLSECOR_free(TLSECOR* lista){
    TLSECOR* aux;
    while(lista){
        aux = lista;        
        lista = lista->prox;
        free(aux);         
    }
}

int aux_teste_cor(TG *backup, TG *g, TLSECOR **coloridos, int cor){
	if (!g) return 0;
	if (!TLSECOR_busca(*coloridos,g->id_no)) *coloridos = TLSECOR_insere(*coloridos,g->id_no,cor);
	TVIZ* viz = g->prim_viz;
	if (!viz) return 0;
	while(viz){
		int vizcor = TLSECOR_busca(*coloridos,viz->id_viz);
		if (vizcor==-1){
			TG* no = TG_busca_no(g,viz->id_viz);
			if (!aux_teste_cor(backup,no,coloridos,1-cor)) return 0;
		}else{
			if (vizcor!=cor) return 0;
		}
		viz = viz->prox_viz;
	}
	//agora verificar se � conectado
	TG* b = backup;
	while(b){
		if (TLSECOR_busca(*coloridos,b->id_no)==-1) return 0;
		b = b->prox_no;
	}
	return 1;
}

int teste_cor(TG*g){
	if (!g) return 0;
	//como vou fazer: colorir o primeiro n�. os vizinhos dele ter�o a cor oposta.
	TLSECOR *coloridos = NULL;
	coloridos = TLSECOR_insere(coloridos,g->id_no,0); //primeiro n� com cor 0
	int resp = aux_teste_cor(g,g,&coloridos,0);
	TLSECOR_libera(coloridos);
	return resp;
}
