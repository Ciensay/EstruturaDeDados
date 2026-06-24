// Percorrer arquivos textos e retornando um arquivo saida com todos os divisiveis por um vetor
#include <stdio.h>
#include <stdlib.h>


void arq_divisiveis(char **lista_arquivos, int n_arquivos, char *saida, int *vet_divisiveis, int n_divisiveis){
    FILE *s = fopen(saida, "wb");
    if(!s) exit(1);

    TH_inicializa("Hash", "dados", n_divisiveis);

    for(int i = 0; i < n_arquivos; i++){
        FILE *f = fopen(lista_arquivos[i], "rb");
        if(!f) exit(1);

        int num;
        while(fread(&num, sizeof(int), 1, f)){
            int div = 1;
            for(int j = 0; j < n_divisiveis; j++){
                if(num % vet_divisiveis[j] != 0){
                    div = 0;
                    break;
                }
            }
            if(!div) continue;

            TH_insere("Hash", "dados", n_divisiveis, num);
            
            // ATENÇÃO: Essa lógica de escrita direta assume que não há 
            // repetições do mesmo número dentro de um mesmo arquivo.
            TP *numero = TH_busca("Hash", "dados", n_divisiveis, num);
            if(numero && numero->qtd == n_arquivos){
                fwrite(&num, sizeof(int), 1, s);
            }
            
        }
        fclose(f);
    }

    // TH_libera("Hash", "dados");
    fclose(s);
}