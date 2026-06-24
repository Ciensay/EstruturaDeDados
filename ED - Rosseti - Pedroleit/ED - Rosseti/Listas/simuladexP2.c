#include <stdio.h>
#include <stdlib.h>

typedef struct arvb{
    int nchaves;
    int *chave;
    int folha;
    struct arvb **filho;
}TARVB;

typedef struct arvbmais{
    int nchaves;
    int *chave;
    int folha;
    struct arvbmais **filho, *prox;
}TARVBM;

/*
Refaça a biblioteca de heap para:
a) uma heap ternária.
*/
int pai_t(int ind){
    if(ind<=0) return -1;
    return (ind-1)/3;
}

int esq_t(int ind){
    return ind * 3 + 1;
}

int meio(int ind){
    return ind * 3 + 2;
}

int dir_t(int ind){
    return ind * 3 + 3;
}

void maxheapfy_t(int *heap, int n, int pos){
    int maior = pos, e = esq_t(pos), m = meio(pos), d = dir_t(pos);
    if((e<n)&&(heap[e]>heap[maior])) maior = e;
    if((m<n)&&(heap[m]>heap[maior])) maior = m;
    if((d<n)&&(heap[d]>heap[maior])) maior = d;
    if(maior!=pos){
        int tmp = heap[pos];
        heap[pos] = heap[maior];
        heap[maior] = tmp;
        maxheapfy_t(heap, n, maior);
    }
}

void buildmaxheap(int *heap, int n){
    int ult_pai = pai_t(n-1), i;
    for(i=ult_pai;i>=0;i--) maxheapfy_t(heap, n, i);
}

void heapsort(int *heap, int n){
    buildmaxheap(heap, n);
    int i;
    for(i=n-1;i!=0;i--){
        int tmp = heap[i];
        heap[i] = heap[0];
        heap[0] = tmp;
        maxheapfy_t(heap, i, 0);
    }
}

/*
Refaça a biblioteca de heap para:
b) uma heap com K filhos.
*/

/*
3) Faça a função max_heapfy em memória secundária.
max_heapfy(char* narq, int ind);
*/
void max_heapfy(char* narq, int tamarq, int ind){
    FILE *fp = fopen(narq, "rb+");
    if(!fp) exit(1);
    int maior = ind, maior_elem, aux, e = esq(ind), d = dir(ind);
    fseek(fp, maior, SEEK_SET);
    fread(&maior_elem, sizeof(int), 1, fp);

    if(e<tamarq){
        fseek(fp, e, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if(aux>maior_elem){
            maior = e;
            maior_elem = aux;
        }
    }

    if(d<tamarq){
        fseek(fp, d, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if(aux>maior_elem){
            maior = d;
            maior_elem = aux;
        }
    }
    
    if(maior!=ind){
        int tmp;                //tmp = heap[ind];
        fseek(fp, ind, SEEK_SET);
        fread(&tmp, sizeof(int), 1, fp);
        
        fseek(fp, maior, SEEK_SET);
        fwrite(&tmp, sizeof(int), 1, fp);

        fseek(fp, ind, SEEK_SET);
        fwrite(&maior_elem, sizeof(int), 1, fp);

        fclose(fp);
        if((tamarq - maior) > 4) max_heapfy(narq, tamarq, maior);
    }
    else fclose(fp);
}

/*
4) Fazendo uso de tabela(s) hash em memória secundária, faça
uma função que dada dois arquivos binários preenchidos com
inteiros, e um parâmetro K, preencha um arquivo de saída com
pares, tal que o resto do primeiro número com K, some K com o
resto do segundo número com K. Tente fazer com
complexidade de tempo menor que O(n2).
void misc(char *arqa, char *arqb, char *saida, int k);
*/

/*
5)Faça uma função que ache todas as chaves de algum índice
em uma árvore B.
int* todos_ind(TARVB *a, int ind, int *tam_vet);
*/
int* todos_ind(TARVB *a, int ind, int *tam_vet){

}

/*
6) Faça uma função que acha todos os elementos maiores que
N numa árvore B+.
int* mN(TARVBM *a, int N, int* tam_vet);
*/
void conta_elem(TARVBM *a, int N, int *tam_vet){
    if(!a) return;
    TARVBM *p = TARVBM_busca(a, N);
    while(p){
        for(int i=0;i<p->nchaves;i++){
            if(p->chave[i]>N) (*tam_vet)++;
        }
        p = p->prox;
    }
}

int* mN(TARVBM *a, int N, int* tam_vet){
    if(!a) return NULL;
    conta_elem(a, N, tam_vet);
    int *vet = (int*)malloc(sizeof(int)*(*tam_vet));
    TARVBM *p = TARVBM_busca(a, N);
    int cont = 0;
    while(p){
        for(int i=0;i<=p->nchaves-1;i++){
            if(p->chave[i]>N){ 
            vet[cont] = p->chave[i]; 
            cont++;
            }
        }
        p = p->prox;
    }
    return vet;
}

