#include <string.h>
#include "TAB.h"
#include "TLSE.h"

typedef struct arvbin{
  int info;
  struct arvbin *esq, *dir;
}TAB;

TAB *TAB_inicializa(void){
  return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = raiz;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

TAB *TAB_busca(TAB *a, int elem){
  if((!a) || (a->info == elem)) return a;
  TAB *resp = TAB_busca(a->esq, elem);
  if(resp) return resp;
  return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a){
  if(a){
    printf("%d ", a->info);
    TAB_imp_pre(a->esq);
    TAB_imp_pre(a->dir);
  }
}

void TAB_imp_pos(TAB *a){
  if(a){
    TAB_imp_pos(a->esq);
    TAB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TAB_imp_sim(TAB *a){
  if(a){
    TAB_imp_sim(a->esq);
    printf("%d ", a->info);
    TAB_imp_sim(a->dir);
  }
}

void imp_aux(TAB *a, int andar){
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

void TAB_imp_ident(TAB *a){
  imp_aux(a, 0);
}

void TAB_libera(TAB *a){
  if(a){
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
  }
}

int maior(int x, int y){
  if(x >= y) return x;
  return y;
}

int TAB_altura(TAB *a){
  if(!a) return -1;
  return maior(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
}

//Q4 - 2,0 PONTOS
int ordena(const void *a, const void *b){
  int *pA = (int*)a;
  int *pB = (int*)b;
  if(*pA>*pB) return -1;
  if(*pA<*pB) return 1;
  return 0;
}

int TAB_n(TAB *a){
  if(!a) return 0;
  return 1+TAB_n(a->esq)+TAB_n(a->dir);
}

void vet_aux(TAB *a, int *vet, int *ind){
  if(!a) return;
  vet_aux(a->esq, vet, ind);
  vet[(*ind)++] = a->info;
  vet_aux(a->dir, vet, ind);
}

int* faz_vet(TAB *a, int n){
  if(!a) return NULL;
  int *vet = (int*)malloc(sizeof(int)*n);
  int ind = 0;
  vet_aux(a, vet, &ind);
  return vet;
}

int remove_duplicados(int *vet, int n) {
    if (n == 0) return 0;
    int elem = 1, i;
    for (i=1;i<n;i++) {
        if (vet[i] != vet[i-1]) {
            vet[elem] = vet[i];
            elem++;
        }
    }
    return elem;
}

int mesmos_elementos(TAB* a1, TAB* a2){
    if(!a1 && !a2) return 1; 
    if(!a1 || !a2) return 0;
    int n1 = TAB_n(a1);
    int n2 = TAB_n(a2);
    int *v1 = faz_vet(a1, n1);
    int *v2 = faz_vet(a2, n2);
    qsort(v1, n1, sizeof(int), ordena);
    qsort(v2, n2, sizeof(int), ordena);
    int n1_unicos = remove_duplicados(v1, n1);
    int n2_unicos = remove_duplicados(v2, n2);
    if (n1_unicos!=n2_unicos) {
        free(v1);
        free(v2);
        return 0;
    }
    int i;
    for(i=0;i<n1_unicos;i++){
        if(v1[i]!=v2[i]){
            free(v1);
            free(v2);
            return 0; 
        }
    }
    free(v1);
    free(v2);
    return 1;
}

int main(void){
  int no, pai;
  printf("Digite a raiz da PRIMEIRA arvore... ");
  scanf("%d", &no);
  TAB *a1 = TAB_cria(no, NULL, NULL), *resp;
  char repete;
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a1, pai);
    if(!resp){
      TAB_libera(a1);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a1);
  printf("\n");
 
  printf("Digite a raiz da SEGUNDA arvore... ");
  scanf("%d", &no);
  TAB *a2 = TAB_cria(no, NULL, NULL);
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a2, pai);
    if(!resp){
      TAB_libera(a2);
      TAB_libera(a1);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a2);
  printf("\n");
 
  printf("%d\n", mesmos_elementos(a1, a2));
  
  TAB_libera(a1);
  TAB_libera(a2);
  return 0;
}
