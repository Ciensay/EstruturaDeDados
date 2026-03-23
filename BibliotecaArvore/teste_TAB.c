#include <string.h>
#include "TAB.c"

/*
Dada uma árvore binária, preencha os elementos dessa árvore num vetor em pós-ordem: int* ab2vet_pos(TAB *a)
*/

int conta(TAB* a){
  if(!a) return 0;
  return 1 + conta(a->esq) + conta(a->dir);
}

void aux(TAB* a, int* vet, int* pos){
  if(!a) return;
  aux(a->esq, vet, pos);
  aux(a->dir, vet, pos);
  vet[(*pos)] = a->info;
  (*pos)++;
}
 
int* ab2vet_pos(TAB *a, int *tam){
  (*tam) = 0;
  if(!a) return NULL;
  //int vet[conta(a)]; //ERRADO!!!
  int *vet;
  int n = conta(a), pos = 0;
  vet = (int *)malloc(sizeof(int) * n);
  (*tam) = n;
  aux(a, vet, &pos);
  return vet;
}

int main(void){
  int no, pai;
  printf("Digite a raiz da arvore... ");
  scanf("%d", &no);
  TAB *a = TAB_cria(no, NULL, NULL), *resp;
  char repete;
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido na arvore e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a, pai);
    if(!resp){
      TAB_libera(a);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a);
  printf("\n");

  int i, tam, *vet = ab2vet_pos(a, &tam);
  for(i = 0; i < tam; i++) printf("vet[%d] = %d\n", i, vet[i]);
  free(vet);
   
  TAB_libera(a);
  return 0;
}
