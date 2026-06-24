#include <stdio.h>
#include <stdlib.h>

typedef struct viz {
	int id_viz;
	struct viz *prox_viz;
}TVIZ;

typedef struct grafo{
	int id_no, cor_no;
	TVIZ *prim_viz;
	struct grafo *prox_no;
}TG;


TG* TG_inicializa(){
  return NULL;
}

void TG_imprime(TG *g){
  while(g){
    printf("Vizinhos do No %d (cor = %d):\n", g->id_no, g->cor_no);
    TVIZ *v = g->prim_viz;
    while(v){
      printf("%d ", v->id_viz);
      v = v->prox_viz;
    }
    printf("\n");
    g = g->prox_no;
  }
}

void TG_libera_viz(TVIZ *v){
  while(v){
    TVIZ *temp = v;
    v = v->prox_viz;
    free(temp);
  }
}

void TG_libera(TG *g){
  while(g){
    TG_libera_viz(g->prim_viz);
    TG *temp = g;
    g = g->prox_no;
    free(temp);
  }
}

TG* TG_busca_no(TG* g, int x){
  if((!g) || (g->id_no == x)) return g;
  return(TG_busca_no(g->prox_no, x));
}

TVIZ* TG_busca_aresta(TG *g, int no1, int no2){
  TG *p1 = TG_busca_no(g,no1), *p2 = TG_busca_no(g,no2);
  if((!p1) || (!p2)) return NULL;
  TVIZ *resp = p1->prim_viz;
  while((resp) && (resp->id_viz != no2)) resp = resp->prox_viz;
  return resp;
}

TG* TG_ins_no(TG *g, int x, int cor){
  TG *p = TG_busca_no(g, x);
  if(!p){
    p = (TG*) malloc(sizeof(TG));
    p->id_no = x;
    p->cor_no = cor;
    p->prox_no = g;
    p->prim_viz = NULL;
    g = p;
  }
  return g;
}

void TG_ins_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1);
  TVIZ *nova = (TVIZ *) malloc(sizeof(TVIZ));
  nova->id_viz = no2;
  nova->prox_viz = p->prim_viz;
  p->prim_viz = nova;
}

void TG_ins_aresta(TG *g, int no1, int no2){
  TVIZ *v = TG_busca_aresta(g, no1, no2);
  if(v) return;
  TG_ins_um_sentido(g, no1, no2);
  TG_ins_um_sentido(g, no2, no1);
}

void TG_retira_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1);
  if(!p) return;
  TVIZ *ant = NULL, *atual = p->prim_viz;
  while((atual)&&(atual->id_viz != no2)){
    ant = atual;
    atual = atual->prox_viz;
  }
  if(!ant) p->prim_viz = atual->prox_viz;
  else ant->prox_viz = atual->prox_viz;
  free(atual);
}

void TG_retira_aresta(TG *g ,int no1, int no2){
  TVIZ* v = TG_busca_aresta(g,no1,no2);
  if(!v) return;
  TG_retira_um_sentido(g,no1,no2);
  TG_retira_um_sentido(g,no2,no1);
}

TG* TG_retira_no(TG *g, int no){
  TG *p = g, *ant = NULL;
  while((p)&& (p->id_no != no)){
    ant = p;
    p = p->prox_no;
  }
  if(!p) return g;
  while(p->prim_viz) TG_retira_aresta(g, no, p->prim_viz->id_viz);
  if(!ant) g = g->prox_no;
  else ant->prox_no = p->prox_no;
  free(p);
  return g;
}

//Q5 - 3,0 PONTOS
int idx(int v[], int tam, int k){
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
    int n_cores = 0; 
    while(p){
        int cor_atual = p->cor_no;
        int ja_existe = 0;
        for(int i=0; i < n_cores; i++){
            if(cores[i] == cor_atual) {
                ja_existe = 1;
                break;
            }
        }
        if(!ja_existe){
            if(n_cores < 3){
                cores[n_cores] = cor_atual;
                n_cores++;
            } else {
                return 0; 
            }
        }
        p = p->prox_no;
    }
    if(n_cores != 3) return 0;
    p = g; 
    int cont[3] = {0, 0, 0}; 
    while(p){
        TVIZ *v = p->prim_viz;
        int indice_cor_p = idx(cores, 3, p->cor_no);
        if(indice_cor_p == -1) return 0; 
        while(v){
            TG *u = TG_busca_no(g, v->id_viz);
            if(p->cor_no == u->cor_no) return 0;
            cont[indice_cor_p]++;
            v = v->prox_viz;
        }
        p = p->prox_no;
    }
    int i;
    for(i=0;i<3;i++) {
        if(cont[i] != (k * 2)) return 0;
    }
    return 1;
}

int main(void){
  TG *g = TG_inicializa();
  printf("Digite o no do grafo e sua cor (pare quando um numero menor ou igual a zero for fornecido para o no)...\n");
  int no1, no2, cor;
  while(1){
    scanf("%d", &no1);
    if(no1 <= 0) break;
    scanf("%d", &cor);
    g = TG_ins_no(g, no1, cor);    
  }
 
  printf("Digite as arestas (pare quando um dos nos nao pertencer ao grafo)...\n");
  while(1){
    scanf("%d%d", &no1, &no2);
    if(!TG_busca_no(g, no1) || !TG_busca_no(g, no2)) break;
    TG_ins_aresta(g, no1, no2);
  }
  TG_imprime(g);
   
  printf("Digite o valor de k... ");
  int k;
  scanf("%d", &k);
  printf("%d\n", tripartido_k_arestas(g, k));
  
  TG_libera(g);
  return 0;
}

/*
1 1
2 1
3 2
4 2
5 3
6 3
0  

1 3
1 5
1 6
2 3
2 4
2 6
3 5
4 5
4 6
0 0
*/