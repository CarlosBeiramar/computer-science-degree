//
// Created by Carlos Beiramar on 2019-02-26.
//

#include <stdio.h>
#include <ctype.h>
#include "histograma.h"

void le_frase (char frase[500]){
    int i;
    printf("Insira uma frase para formar um histograma:");
    fgets(frase,500,stdin);

    /*for (i=0;frase[i]!='\0';i++){
        printf("%c",frase[i]);
    } */
}

int* conta_letras (char frase[500],int conta[],char letras[]){
    int i=0,j;
    //char letras[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    //int conta[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (i=0;frase[i]!='\0';i++){
        for(j=0;j<26;j++){
            if (frase[i]==letras[j] || frase[i]==toupper(letras[j])) {
                conta[j] = conta[j] + 1;
            }
        }
    }
    /*for(i=0;letras[i]!='\0' && i<26;i++){
        printf("%c %d\n",letras[i],conta[i]);
      }*/
    return conta;
}


void imprime (int *conta, char *letras) {
    int i = 0, j=0,maior=0;
    maior=max_array(conta);

    for(i=maior;i>0;i--)
    {
        if(maior>=i)
        {
            for(j=0;j<26;j++)
            {
                if (conta[j]==i)
                {
                    printf("* ");
                    conta[j]-=1;
                }
                else printf("  ");
            }
            printf("\n");
        }
        else printf("\n");
    }

    for (i=0;i<26;i++){
        printf("%c ",toupper(letras[i]));
    }
    printf("\n");

}

int max_array (int conta[]) {
    int i=0,t=0;
    for (i=1;i<26;i++){
        if (conta[i]>t){
            t=conta[i];
        }
    }
    return t;

}

