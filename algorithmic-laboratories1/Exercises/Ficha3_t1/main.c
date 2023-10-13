#include <stdio.h>
#include "histograma.h"

int main() {
    char frase[500];
    int conta[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char letras[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    le_frase(frase);
    conta_letras(frase,conta,letras);
    imprime(conta,letras);
    max_array(conta);
    return 0;
}