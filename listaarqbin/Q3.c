#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[40];
    char cpf[11];
    int conta_corrente;
    int agencia;
    float saldo;
} TP;
int tam_clientes(char *arq){
    int resp;
    FILE *f = fopen(arq, "rb");
    if(!f) exit(1);
    fseek(f, 0, SEEK_END);
    long tamanho_bytes = ftell(f);
    resp = tamanho_bytes/sizeof(TP);
    printf("Quantidade de pessoas: %d", resp);
    fclose(f);
    return resp;
}
typedef struct{
    int pos;
    float saldo;
}TS;

void criar_arquivo_teste() {
    FILE *arq = fopen("clientes.bin", "wb");
    if (!arq) {
        printf("Erro ao criar o arquivo clientes.bin\n");
        exit(1);
    }

    // 2. Criando o Cliente 1 (Inicializando com {0} para limpar lixo)
    TP c1 = {0};
    strcpy(c1.nome, "Joao da Silva");
    strncpy(c1.cpf, "11111111111", 11); // Usando strncpy para respeitar os 11 bytes exatos
    c1.conta_corrente = 1001;
    c1.agencia = 3300;
    c1.saldo = 1500.50;

    // 3. Criando o Cliente 2
    TP c2 = {0};
    strcpy(c2.nome, "Maria de Oliveira");
    strncpy(c2.cpf, "22222222222", 11);
    c2.conta_corrente = 1002;
    c2.agencia = 3300;
    c2.saldo = 3250.75;

    // 4. Criando o Cliente 3
    TP c3 = {0};
    strcpy(c3.nome, "Carlos Eduardo");
    strncpy(c3.cpf, "33333333333", 11);
    c3.conta_corrente = 1003;
    c3.agencia = 4400;
    c3.saldo = 150.00;

    // 5. Gravando os blocos no HD
    fwrite(&c1, sizeof(TP), 1, arq);
    fwrite(&c2, sizeof(TP), 1, arq);
    fwrite(&c3, sizeof(TP), 1, arq);

    fclose(arq);
    printf("SUCESSO: Arquivo 'clientes.bin' gerado com 3 registros!\n");
    printf("CPFs validos para o seu teste: 11111111111, 22222222222 e 33333333333\n\n");
}

void inicializa_indices(char *arq){
    FILE *f = fopen(arq, "wb");
    if(!f) exit(1);
    fclose(f);
}

void copia_saldo_endereco(FILE *f1, FILE *f2){
    //f1 ta sendo lido, f2 ta sendo escrito
    TS temp;
    TP p_lida;
    rewind(f1);
    int temppos = 0;
    while(fread(&p_lida, sizeof(TP), 1, f1) == 1){
        temp.pos = temppos;
        temp.saldo = p_lida.saldo;
        fwrite(&temp, sizeof(TS),1,f2);
        temppos = ftell(f1);
    }
}
void ordena_bin(FILE *f){
    rewind(f);
    TS menor, atual, temp;
    int i, i_menor, r1, r2, j;
    
    i = ftell(f);
    r1 = fread(&menor, sizeof(TS), 1, f);
    while(r1 == 1){
        i_menor = i;
        temp = menor;

        j = ftell(f);
        r2 = fread(&atual, sizeof(TS), 1, f);
        while(r2 == 1)
        {
            if(menor.saldo > atual.saldo){
                menor = atual;
                i_menor = j;
            }

            j = ftell(f);
            r2 = fread(&atual, sizeof(TS), 1, f);
        }
        if(i_menor != i){
            fseek(f, i_menor, SEEK_SET);
            fwrite(&temp, sizeof(TS), 1, f);
            fseek(f, i, SEEK_SET);
            fwrite(&menor, sizeof(TS), 1, f);
        }
        
        fseek(f, i + sizeof(TS), SEEK_SET);
        

        i = ftell(f);
        r1 = fread(&menor, sizeof(TS), 1 , f);
    }
}

 void gera_indices(char *arq, char*arq_indices){
    FILE *f = fopen("temp.bin", "wb+");
    FILE *cl = fopen(arq, "rb");
    FILE *index = fopen(arq_indices, "wb");
    int n = tam_clientes("clientes.bin");
    if(!f || !cl || !index){
        printf("Erro no arquivo\n");
        exit(1);
    }
    copia_saldo_endereco(cl, f);
    ordena_bin(f);
    rewind(f);
    TS temp;
    while(fread(&temp, sizeof(TS), 1, f)==1){
        printf("A primeira posicao e do saldo %.2f\n", temp.saldo);
        fwrite(&temp.pos, sizeof(int), 1, index);
    }
    fclose(f);
    fclose(cl);
    fclose(index);
 }



int main(){
    criar_arquivo_teste();
    gera_indices("clientes.bin", "indices.bin");


    return 0;
}