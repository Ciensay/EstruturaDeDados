#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void RetRepet(char *ArqEnt, char *ArqSaida){
    FILE *ar_entrada = fopen(ArqEnt, "r");
    if (ar_entrada == NULL) {
        printf("Erro: Não foi possível abrir ou criar o arquivo.\n");
        return; // Encerra o programa com erro
    }
    FILE *arq_saida = fopen(ArqSaida, "w");
    if(!arq_saida){
        fclose(ar_entrada);
        printf("Erro no arq saida\n");
        return;
    }

    char palavra[50];
    char anterior[50] = "";
    while(fscanf(ar_entrada, "%49s", palavra) == 1){
        if(!strcmp(palavra, anterior)){
            continue;
        }
        fprintf(arq_saida, " %s ", palavra);
        strcpy(anterior, palavra);
    }
    fclose(ar_entrada);
    fclose(arq_saida);

}

int main(){

    RetRepet("entrada.txt", "saida.txt");







    return 0;
}