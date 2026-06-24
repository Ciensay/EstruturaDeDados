#include <stdio.h>
#include <string.h>

/*
(Q1) Desenvolva um procedimento que receba o nome de um arquivo texto e retire deste texto
palavras consecutivas repetidas. O seu programa deve retornar, no arquivo de saída, informado
como parâmetro dessa função, a resposta desta questão. Por exemplo, se o conteúdo de um arquivo
texto for: "Isto e um texto texto repetido repetido repetido . Com as repeticoes
repeticoes fica fica sem sem sentido . Sem elas elas elas melhora melhora um um
pouco .", a saída do seu programa será um arquivo com o seguinte texto: "Isto e um texto
repetido . Com as repeticoes fica sem sentido . Sem elas melhora um um pouco ."
- void RetRepet(char *ArqEnt, char *ArqSaida).
*/
void RetRepet(char *ArqEnt, char *ArqSaida){
    FILE *fp = fopen(ArqEnt, "r"), *fs = fopen(ArqSaida, "w");
    if((!fp)||(!fs)) exit(1);
    char s1[100], s2[100];
    int r1 = fscanf(ArqEnt, "%s", s1), r2 = 1;
    while(r2==1){
        r1 = fscanf(ArqEnt, "%s", s1);
        r2 = fscanf(ArqEnt, "%s", s2);
        if(strcmp(s1, s2) == 1) continue;
        fprintf(ArqSaida, "%s ", s2);
    }
    fclose(fp);
    fclose(fs);
}

/*
(Q2) Implemente um algoritmo que receba como parâmetro de entrada, o nome de um arquivo
texto, cujo conteúdo são o nome do aluno e as duas notas dos alunos do curso, uma em cada linha, e
que ordene o arquivo de saída em ordem crescente pela média do aluno. Isto é, se eu tiver como
entrada o arquivo: "P C/10.0/10.0-J J/3.0/4.0-G G/7.0/7.0-A A/0.5/1.5-I I/5.0/6.0", a
saída será um arquivo com o seguinte texto: "A A/1.0-J J/3.5-I I/5.5-G G/7.0-P C/10.0" -
void media(char *ArqEnt, char *ArqSaida).
*/
void media(char *ArqEnt, char *ArqSaida){

}

/*
(Q3) Escreva um procedimento que receba o nome de um arquivo texto, cujo conteúdo são valores
inteiros e imprima na tela o número de vezes que cada elemento aparece e em quais linhas – void
resumo(char *Arq).
*/
void resumo(char *Arq){
    FILE *fp = fopen(Arq, "r");
    if(!fp) exit(1);
    int r1, n1, linha, tam_numeros = 0, vezes[256], numeros[256];
    r1 = fscanf(Arq, "%d", &n1);
    while(r1==1){
        
        r1 = fscanf(Arq, "%d", &n1);
    }
}