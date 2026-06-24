/*
Heaps (Lista de prioridades):
    * Motivação: 
        - ED com prioridade
    * Ex: Servidor de imporessão
    * Operações:
        - Seleção do prioritário(S);
        - Retirada do prioritário(R);
        - Inserção de um elemento(I);
        - Alterção de prioridade(A);
    * Implementação:
        (a) Lista
            S: O(n)
            R: O(n)
            I: O(1)
            A: O(n)
        (b) Lista ordenada
            S: O(1)
            R: O(1)
            I: O(n)
            A: O(n)
        (c) Vetor
            S: O(n)
            R: O(n)
            I: O(1)
            A: O(n)
        (d) Vetor ordenado
            S: O(1)
            R: O(n)
            I: O(n)
            A: O(n)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    * Solução: Heaps -> ED linear mais eficiente que vetores ou listas:
        S: O(1)
        R: O(log(n))
        I: O(log(n))
        A: O(log(n))
    * Conceitos:
        - Pai (ind)
        - esq (ind)
        - dir (ind)
*/

int pai(int ind){
    if(ind<=0) return -1;
    return (ind-1)/2;
}

int esq(int ind){
    return 2*ind+1;
}

int dir(int ind){
    return 2*ind+2;
}

/*
* Propriedade de heap máximo:
    - Para todo elemento da posição ind, 
    exceto ind=0(raiz), Heap[pai(ind)] >= Heap[ind]

* Heap máximo: HEAPSORT
* Heap Mínimo: Lista de prioridade
*/

void maxheapfy(int *heap, int n, int pos){
    int maior = pos, e = esq(pos), d = dir(pos);
    if((e<n)&&(heap[e]>heap[maior])) maior = e;
    if((d<n)&&(heap[d]>heap[maior])) maior = d;
    if(maior!=pos){
        int tmp = heap[pos];
        heap[pos] = heap[maior];
        heap[maior] = tmp;
        maxheapfy(heap, n, maior);
    }
}

void buildmaxheap(int *heap, int n){
    int ult_pai = pai(n-1), i;
    for(i=ult_pai;i>=0;i--) maxheapfy(heap, n, i);
}

void heapsort(int *heap, int n){
    buildmaxheap(heap, n);
    int i;
    for(i=n-1;i!=0;i--){
        int tmp = heap[i];
        heap[i] = heap[0];
        heap[0] = tmp;
        maxheapfy(heap, i, 0);
    }
}

/*
Heaps binários em MS
*/
int pai_s(int end_ms);
int esq_s(int end_ms);
int dir_s(int end_ms);

void max_heapfy(char *arq, int end_ms_pos){
    int maior = end_ms_pos, e = esq_s(end_ms_pos), d = dir_s(end_ms_pos), fim;
    FILE *fp = fopen(arq, "rb+");
    if(!fp) exit(1);
    fseek(fp, 0L, SEEK_END);
    fim = ftell(fp)-sizeof(int);
    int elem_pos, elem_maior, aux;
    fseek(fp, elem_pos, SEEK_SET);
    fread(&elem_pos, sizeof(int), 1, fp);
    elem_pos = elem_maior;
    if(e<fim){
        fseek(fp, e, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if(aux>elem_maior){
            maior = e;
            elem_maior = aux;
        }
    }
    if(maior!=end_ms_pos){
        fseek(fp, maior, SEEK_SET);
        fwrite(&elem_pos, sizeof(int), 1, fp);
        fseek(fp, end_ms_pos, SEEK_SET);
        fwrite(&elem_maior, sizeof(int), 1, fp);
        fclose(fp);
        max_heapfy(arq, maior);
    }
    else fclose(fp);
}