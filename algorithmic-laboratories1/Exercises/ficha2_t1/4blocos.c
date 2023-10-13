//
// Created by Carlos Beiramar on 2019-02-21.
//
#include <stdio.h>
#include <stdlib.h>
void escreve_nib () {
    char str[21];
    int i, h = 0, j = 0, res = 0,tam,l=0;
    int nib[21];

    for (i = 0; i < 21; i++) {
        scanf(" %c", &str[i]); //guarda a string de números num array de char

    }
    for (h = 0; h < 21; h++) { //converte os char em inteiros e guarda num array de int
        char s;
        int tmp;
        s = str[h];
        tmp = s - '0';
        nib[h] = tmp;
    }

    for (j = 0; j < 21; j++) {
        if ((nib[j] >= 0) && (nib[j] <= 9)) { //verifica se no array só estão números
            res++;
        }
    }
    if (res==21){

        for(i=0;i<4;i++){
            printf("%d",nib[i]);    //imprimir o 4 números do banco
        }
        printf(" ");
        for (i=4; i<8 ; i++) {
            printf("%d",nib[i]);       //imprimir os 4 números da agência
        }
        printf(" ");

        tam=8;
        while (l!=1) {
            if (nib[tam] == 0) {
                tam++;
                l=0;                        // imprimir os números da conta sem os zeros à esquerda
            }
            else {
                for (i = tam; i < 19; i++) {
                    printf("%d", nib[i]);
                    l=1;
                }
            }
        }

        printf(" ");
        for (i=19;i<21;i++){
            printf("%d",nib[i]);
        }

    }else {
        printf("O seu NIB não é válido");
        abort();
    }

}