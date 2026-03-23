#include <stdio.h>
#include <stdbool.h>

// Função auxiliar recursiva para verificar se 'sub' é um prefixo de 'str'
bool is_prefix(const char *str, const char *sub) {
    // Se a substring acabou, significa que todos os caracteres anteriores bateram
    if (*sub == '\0') return true;
    
    // Se a string principal acabou antes da substring, não é prefixo
    if (*str == '\0') return false;
    
    // Se os caracteres forem diferentes, não é prefixo
    if (*str != *sub) return false;
    
    // Chamada recursiva para o próximo caractere de ambas
    return is_prefix(str + 1, sub + 1);
}

// Função recursiva principal para encontrar a posição da substring
int find_substring(const char *str, const char *sub) {
    // Tratamento de segurança: se a substring for vazia, retorna posição 0
    if (*sub == '\0') return 0;
    
    // Caso base: chegamos ao fim da string principal sem encontrar a substring
    if (*str == '\0') return -1;

    // Se a substring é um prefixo da string atual, encontramos a posição!
    if (is_prefix(str, sub)) {
        return 0; // Posição 0 relativa ao ponteiro atual
    }

    // Passo recursivo: tenta encontrar a substring a partir do próximo caractere
    int pos = find_substring(str + 1, sub);

    // Se o retorno foi -1, propaga o -1 (não encontrado no restante da string)
    if (pos == -1) {
        return -1;
    }

    // Como avançamos 1 caractere no ponteiro atual (str + 1), somamos 1 ao resultado
    return pos + 1;
}

// Função main para testar o código
int main() {
    const char *texto = "Inteligencia Artificial";
    const char *busca1 = "cial";
    const char *busca2 = "Arte";
    const char *busca3 = "Intel";

    printf("Posicao de '%s': %d\n", busca1, find_substring(texto, busca1)); // Esperado: 10
    printf("Posicao de '%s': %d\n", busca2, find_substring(texto, busca2)); // Esperado: -1
    printf("Posicao de '%s': %d\n", busca3, find_substring(texto, busca3)); // Esperado: 0

    return 0;
}