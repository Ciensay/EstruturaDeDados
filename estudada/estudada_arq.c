#include <stdio.h>



int main(){

    int x = 1; int y = 2;
    y = (x=x*2)+ ++y;

    printf("\n %d \n", y);
    printf("\n %d \n", x);

    return 0;
}