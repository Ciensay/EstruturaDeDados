#include "TABB.c"
TABB *menor(TABB *a){
    if(!(a->esq) || (!a)) return a;
    return menor(a->esq);
}


int main(){
    TABB *teste = TABB_inicializa();
    teste = TABB_insere(teste, 5);
    teste = TABB_insere(teste, 3);
    teste = TABB_insere(teste, 8);
    teste = TABB_insere(teste, 7);
    teste = TABB_insere(teste, 4);
    teste = TABB_insere(teste, 2);
    printf("\n  %d \n", menor(teste)->info);
    printf("Oi uaa");
    TABB_libera(teste);


    return 0;
}
