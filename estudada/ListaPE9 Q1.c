#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
    int info;
    struct Lista *prox;
}TLSE;


TLSE *insere_inicio(TLSE *l, int info){
    TLSE *temp = (TLSE*)malloc(sizeof(TLSE));
    temp->prox = l;
    temp->info = info;
    return temp;
}

TLSE *inverte (TLSE *l){
    TLSE *yago = l;
    TLSE *marcio = NULL;
    while(yago){
        marcio = insere_inicio(marcio, yago->info);
        yago = yago->prox;

    }
    return marcio;
}

int igual(TLSE *l1, TLSE *l2){
    TLSE *temp1 = l1;
    TLSE *temp2 = l2;
    while(temp1 && temp2){
        if(temp1->info != temp2->info) return 0;
        temp1 = temp1->prox;
        temp2 = temp2->prox;
    }
    if (!temp1 && !temp2) return 1;
    return 0;
}

TLSE *desloca (TLSE *l, int n){
    TLSE *p = l;
    int temp, temp2;
    if(!l || !l->prox) return l;
    //Caso impar
    if(n % 2 == 1){
        temp = p->info;
        while(p->prox){
            p = p->prox;
            temp2 = p->info;
            p->info = temp;
            temp = temp2;
        }

        l->info = temp;
        return l;

}
        //caso par
        TLSE *ant = p;
        int temp2 = p->info;
        p = p->prox;

        while(p){
            ant->info = p->info;
            ant = ant->prox;
            p = p->prox;

        }
        ant ->info = temp2;
        return l;
}  

int main(){
    TLSE *Lista = NULL;
    Lista = insere_inicio(Lista, 3);
    Lista = insere_inicio(Lista, 2);
    Lista = insere_inicio(Lista, 1);
    desloca(Lista, 1);


    /*TLSE *l2 = NULL;
    l2 = insere_inicio(l2, 3);
    l2 = insere_inicio(l2, 3);
    l2 = insere_inicio(l2, 2);
    l2 = insere_inicio(l2, 1);
    printf("\n %d \n", igual(Lista,l2));*/
    
}

