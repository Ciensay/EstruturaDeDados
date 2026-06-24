#include <stdio.h>

/*
* Motivação: Alternativa a indexação por B ou B+
* Uso de mais memória para fazê-lo
*/

/*
* Algumas características da funções de hash:
    - Eficiência.
    - Dist. uniforme.
    - Determinística.
    - Divisor deve ser primo, exceto 2.
*/

// 1) Tratamento de colisões por encadeamento exterior(ou externo) em MP
typedef struct aluno{
    int mat;
    float cr;
    int info;
    struct aluno *prox;
    int status;
}TA;

#define MAXTAM 101

typedef TA * TH[MAXTAM];

int hash(int mat, int tam){ 
    return mat%tam;
}

void TH_inicializa(TH tab, int n){
    int i;
    for(i=0;i<n;i++) tab[i] = NULL;
}

TA *TA_aloca(int mat, float cr){
    TA *a = (TA*)malloc(sizeof(TA));
    a->cr = cr;
    a->mat = mat;
    a->prox = NULL;
    return a;
}

void TH_insere(TH tab, int n, int mat, float cr){
    int h = hash(mat, n);
    TA *ant = NULL, *p = tab[h];
    while((p)&&(p->mat<mat)){
        ant = p;
        p = p->prox;
    }
}

TA *TH_busca(TH tab, int n, int mat){
    int h = TH_hash(mat, n);
    TA *resp = tab[n];
    while(resp){
        if(resp->info==mat) return resp;
        if(resp->info>mat) return NULL;
        resp = resp->prox;
    }
    return NULL;
}

float TH_retira(TH tab, int n, int mat){
    int h = TH_hash(mat, n);
    if(!tab[h]) return -1.0;
    TA *p = tab[h], *ant = NULL;
    while((p)&&(p->info<n)){
        ant = p;
        p = p->prox;
    }
    if((!p)||(p->info>n)) return -1.0;
    float cr = p->cr;
    if(!ant) tab[h] = p->prox;
    else ant->prox = p->prox;
    free(p);
    return cr;
}

void TH_libera(TH tab, int n){
    int i;
    for(i=0;i<n;i++){
        if(tab[i]){
            TA *p = tab[i], *t;
            while(p){
                t = p;
                p = p->prox;
                free(t);
            }
        }
    }
}

void TH_insere(char *hash, char *dados, int n, int mat, float cr){
    FILE *fph = fopen(hash, "rb+");
    if(!fph) exit(1);
    int h = TH_hash(mat, n), pos;
    fseek(fph, (h*sizeof(int)), SEEK_SET);
    fread(&pos, sizeof(int), 1, fph);
    int ant, ppl;
    ant = ppl = -1;
    TA aux;
    FILE *fpd = fopen(dados, "rb+");
    if(!fpd) exit(1);
    while(pos!=-1){
        fseek(fpd, pos, SEEK_SET);
        fread(&aux, sizeof(int), 1, fpd);
        if(aux.mat==mat){
            aux.cr = cr;
            aux.status = 1;
            fseek(fpd, pos, SEEK_SET);
            fwrite(&aux, sizeof(TA), 1, fpd);
            fclose(fph); fclose(fpd);
            return;
        }
        if((!aux.status)&&(ppl==-1)) ppl = pos;
        ant = pos;
        pos = aux.prox;
    }
    TA elem;
    elem.mat = mat; elem.cr = cr; elem.status = 1;
    if(ppl==-1){
        elem.prox = -1;
        fseek(fpd, 0L, SEEK_END);
        pos = ftell(fpd);
        fwrite(&elem, sizeof(TA), 1, fpd);
        if(ant==-1){
            fseek(fph, (h*sizeof(int)), SEEK_SET);
            fwrite(&pos, sizeof(int), 1, fph);
        }
        else{
            aux.prox = ant;
            fseek(fpd, ant, SEEK_SET);
            fwrite(&aux, sizeof(TA), 1, fpd);
        }
        fclose(fph); fclose(fpd);
        return;
    }
    fseek(fpd, ppl, SEEK_SET);
    fread(&aux, sizeof(TA), 1, fpd);
    aux.mat = mat; aux.status = 1; aux.cr = cr;
    fseek(fpd, ppl, SEEK_SET);
    fwrite(&aux, sizeof(TA), 1, fpd);
    fclose(fph); fclose(fpd);
}