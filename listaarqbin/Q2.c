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
void consulta(char *arq, char *cpf) {
    FILE *f = fopen(arq, "rb");
    if (!f) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    
    TP pessoa = {0}; 
    
    
    while (fread(&pessoa, sizeof(TP), 1, f) == 1) {
        
       
        if (strncmp(pessoa.cpf, cpf, 11) == 0) {
            
            printf(" %s | %s | CC: %d | Ag: %d | Saldo: %.2f\n", 
                   pessoa.nome, pessoa.cpf, pessoa.conta_corrente, pessoa.agencia, pessoa.saldo);
            
            fclose(f);
            return; 
        }
    }
    
    printf(" O CPF %s nao foi encontrado.\n", cpf);
    fclose(f); 
}
int main(){
    criar_arquivo_teste();
    consulta("clientes.bin", "22222222222");




    return 0;
}