#include <stdio.h>
#include "TABB.c"

int contamn(TABB *a, int n){
    if(!a) return 0;
    else if(a->info<n){
        return 1+contamn(a->dir, n)+contamn(a->esq, n);

    }
    return contamn(a->esq, n);
}
int *mn(TABB *a, int n){
    int *vet = (int *)malloc(sizeof(int) * contamn(a, n));
    int i = 0;
    insere_vet(a, vet, n, &i);
    return vet;
}
void insere_vet(TABB *a, int *vet, int n, int *i){
    if(!a) return;
    else if(a->info<n){
        vet[(*i)] = a->info;
        (*i)++;
        insere_vet(a->dir, vet, n, i);


    }
    insere_vet(a->esq, vet, n, i);


}

int main(){
    TABB *teste = TABB_inicializa();
    teste = TABB_insere(teste, 5);
    teste = TABB_insere(teste, 3);
    teste = TABB_insere(teste, 8);
    teste = TABB_insere(teste, 7);
    teste = TABB_insere(teste, 4);
    teste = TABB_insere(teste, 2);
    int *vetor = mn(teste, 7);
    for(int i = 0; i<contamn(teste, 7); i++){
        printf("\n %d\n", vetor[i]);
    }


    printf("\n%d\n", contamn(teste, 7));
    free(vetor);
    TABB_libera(teste);





    return 0;
}