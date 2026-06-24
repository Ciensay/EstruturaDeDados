#include "TABB.c"
<<<<<<< HEAD
TABB *maior(TABB *a){
    if(!(a->dir) || (!a)) return a;
    return maior(a->dir);
=======
TABB *menor(TABB *a){
    if(!(a->esq) || (!a)) return a;
    return menor(a->esq);
>>>>>>> 6720d02993260359e91c5550dfbf0de561a3bed6
}


int main(){
    TABB *teste = TABB_inicializa();
    teste = TABB_insere(teste, 5);
    teste = TABB_insere(teste, 3);
    teste = TABB_insere(teste, 8);
    teste = TABB_insere(teste, 7);
    teste = TABB_insere(teste, 4);
    teste = TABB_insere(teste, 2);
<<<<<<< HEAD
    printf("\n  %d \n", maior(teste)->info);
=======
    printf("\n  %d \n", menor(teste)->info);
>>>>>>> 6720d02993260359e91c5550dfbf0de561a3bed6
    printf("Oi uaa");
    TABB_libera(teste);


    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 6720d02993260359e91c5550dfbf0de561a3bed6
