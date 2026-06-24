#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Dados dois arquivos de texto ordenados, gere um
terceiro ordenado, sem usar estruturas de dados.
*/
void ordena1(char *arq1, char *arq2, char *saida){
    FILE *f1 = fopen(arq1, "r"),
         *f2 = fopen(arq2, "r"),
         *fs = fopen(saida, "w");
    if((!f1)||(!f2)||(!fs)) exit(1);
    int n1, r1, n2, r2;
    r1 = fscanf(arq1, "%d", &n1);
    r2 = fscanf(arq2, "%d", &n2);
    while((r1 == 1)||(r2 == 1)){
        if((r2 != 1)||(n1<=n2)){
            fprintf(fs, "%d\n", n1);
            r1 = fscanf(arq1, "%d", &n1);
            if(r1 != 1) n1 = INT_MAX;
        }
        if((r1 != 1)||(n1>n2)){
            fprintf(fs, "%d\n", n2);
            r2 = fscanf(arq2, "%d", &n2);
            if(r2 != 1) n2 = INT_MAX;
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(fs);
}

void vet2arqbin(int *vet, int n, char *arqbin){
    if(n <= 0) return;
    FILE *fp = fopen(arqbin, "wb");
    if(!fp) exit(1);
    fwrite(vet, sizeof(int), n, fp);
    fclose(fp);
}

void arqbin2vet(char *arqbin, int *vet, int n){
    if(n<=0) return;
    FILE *fp = fopen(arqbin, "rb");
    if(!fp) exit(1);
    fread(vet, sizeof(int), n, fp);
    fclose(fp);
}

void selSort(int *vet, int n){
    if(n<=1) return;
    int i;
    for(i = 0;i<n;i++){
        int menor = i, j;
        for(j = i+1;j<n;j++){
            if(vet[j]<vet[menor]) menor = j;
        }
        if(menor != i){
            int tmp = vet[i];
            vet[i] = vet[menor];
            vet[menor] = tmp;
        }
    }
}

void ss_arq(char *arq){
    FILE *fp = fopen(arq, "rb+");
    if(!fp) exit(1);
    int i, elem_i, j, elem_j, r, s, menor, menor_elem;
    while(1){
        i = ftell(fp);
        r = fread(&elem_i, sizeof(int), 1, fp);
        if(r == 1){
            menor = i;
            menor_elem = elem_i;
            while(1){
                j = ftell(fp);
                s = fread(&elem_j, sizeof(int), 1, fp);
                if(s != 1) break;
                if(elem_j < menor_elem){
                    menor_elem = elem_j;
                    menor = j;
                }
            }
            if(elem_i != menor_elem){
                fseek(fp, menor, SEEK_SET);
                fwrite(&elem_i, sizeof(int), 1, fp);
                fseek(fp, i, SEEK_SET);
                fwrite(&menor_elem, sizeof(int), 1, fp);
            } else fseek(fp, i+sizeof(int), SEEK_SET);
        } else break;
    }
    fclose(fp);
}

int bb(int *vet, int n, int x){
    int ini = 0, fim = n - 1, meio;
    while(ini<=fim){
        meio = (ini+fim)/2;
        if(vet[meio] == x) return meio;
        if(vet[meio] > x) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int bb_arq(char *arq, int x){
    FILE *fp = fopenn(arq, "rb");
    if(!fp) exit(1);
    int ini = 0, fim, meio, elem;
    fseek(fp, 0L, SEEK_END);
    fim = ftell(fp) - sizeof(int);
    while(ini<=fim){
        meio = (((ini + fim)/sizeof(int))/2)*sizeof(int);
        fseek(fp, meio, SEEK_SET);
        fread(&elem, sizeof(int), 1, fp);
        if(x==elem){
            fclose(fp);
            return meio;
        }
        if(x>elem) ini = meio + sizeof(int);
        else fim = meio - sizeof(int);
    }
    fclose(fp);
    return -1;
}

int bubble_sort(int *v, int x);

int class_interna(char *arq, char *prefixo, int m){
    FILE *fp = fopen(arq, "r");
    if(!fp) exit(1);
    int vet[m], qtd = 0;
    while(1){
        int i = 0, r, aux;
        while(i<m){
            r = fscanf(arq, "%d", &aux);
            if(r!=1) break;
            vet[i++] = aux;
        }
        if(!i){
            fclose(fp);
            return qtd;
        }
        qtd++;
        qsort(vet, i, sizeof(int), cmp_int);
        char npart[51];
        geraNomePart(prefixo, qtd, npart);
        FILE *fs = fopen(npart, "w");
        if(!fs) exit(1);
        for(int j = 0;j<i;j++){
            fprintf(arq, "%d\n", vet[j]);
        }
        fclose(fs);
    }
}

void geraNomePart(char *prefixo, int n, char *saida){
    strcpy(saida, prefixo);
    char aux[15];
    sprintf(aux, "%d.txt", n);
    strcat(saida, aux);
}

int cmp_int(const void *x, const void *y){
    int *ix = (int *) x,
        *iy = (int *) y;
    if((*ix)<(*iy)) return -1;
    if((*ix)>(*iy)) return 1;
    return 0;
}

typedef struct misc{
    FILE *arq;
    char nome[31];
    int menor;
}TMISC;

// HEAPS
int pai(int ind){
    if(ind<=0) return -1;
    return (ind-1)/2;
}

int esq(int ind){
    return ind*2 + 1;
}

int dir(int ind){
    return ind*2 + 2;
}
//