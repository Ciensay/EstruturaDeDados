#include "TABB.c"
TABB *maior(TABB *a){
    if(!(a->dir) || (!a)) return a;
    return maior(a->dir);
}


int main(){
    TABB *teste = TABB_inicializa();
    teste = TABB_insere(teste, 5);
    teste = TABB_insere(teste, 3);
    teste = TABB_insere(teste, 8);
    teste = TABB_insere(teste, 7);
    teste = TABB_insere(teste, 4);
    teste = TABB_insere(teste, 2);
    printf("\n  %d \n", maior(teste)->info);
    printf("Oi uaa");
    TABB_libera(teste);


    return 0;
}
