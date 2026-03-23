#include <stdio.h>
#include <stdlib.h>

typedef struct ListaGenerica {
    void *Item;
    struct ListaGenerica *prox;
    int Tipo; // 1 = int, 2 = char, 3 = float
} TLG;

TLG *Inicializa(void) {
    return NULL;
}

TLG *Insere_Ini_Inteiros(TLG *l, int* Item) {
    TLG *novo = (TLG*)malloc(sizeof(TLG));
    novo->Item = Item; 
    novo->prox = l;
    return novo;        
}

TLG *Insere_Ini_Generico(TLG *l, void * Item, int Tipagem) {
    TLG *novo = (TLG*)malloc(sizeof(TLG));
    novo->Item = Item;
    novo->Tipo = Tipagem;
    novo->prox = l;
    return novo;        
}

void PrintaLista_Int(TLG *l) {
    if (!l) return;
    printf(" %d ", *(int *)l->Item); 
    PrintaLista_Int(l->prox);
}
void PrintaLista_Generico(TLG *l) {
    if (!l) return;
    if(l->Tipo == 1){
        printf(" %d ", *(int *)l->Item);


    }else if(l->Tipo == 2){
        printf(" %s ", (char *)l->Item);


    }
    PrintaLista_Generico(l->prox);
    
}

int main() {
    TLG *l = Inicializa();
    int i = 2, j = 4, k = 10; char* s = "Sorrisin";
    
    l = Insere_Ini_Generico(l, &i, 1);
    l = Insere_Ini_Generico(l, &j, 1);
    l = Insere_Ini_Generico(l, &k, 1);
    l = Insere_Ini_Generico(l, s, 2);


    PrintaLista_Generico(l);

    return 0;
}