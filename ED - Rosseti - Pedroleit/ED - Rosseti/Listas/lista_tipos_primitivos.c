#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Q1) Implemente um programa que, infinitamente, receba, como parâmetro de entrada, um número
n e retorne os n primeiros números primos existentes. Seu programa para quando n for menor ou
igual a zero.
*/

int main_q1(void){
    int n, divisores, cont = 0;
    do {
        scanf("%d", &n);
        int primos[n];

        for (int i = 0;cont<n;i++){
            for (int j = 0;j<i;j++){
                if(i % j == 0) divisores++;
            }

            primos[cont] = i;
            if (divisores == 2) cont++;
        }


    } while (n <= 0);
    return 0;
}