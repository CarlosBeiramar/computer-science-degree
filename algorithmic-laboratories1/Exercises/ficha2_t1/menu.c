//
// Created by Carlos Beiramar on 2019-02-18.
//
#include <stdio.h>
#include <stdlib.h>
#include "funções.h"

void menu () {
    int escolha;

    printf ("Escolha o que deseja:\n");

    printf("1 -\tLer NIB\n"
              "\ta) \tIndicar a agência do NIB.\n"
              "\tb) \tIndicar o banco do NIB.\n"
              "\tc) \tIndicar o número da conta.\n"
              "\td) \tIndicar os números de controlo.\n");
    printf("0 -\tsair do programa\n");

    scanf("%d",&escolha);

    switch (escolha){
        case 1:
            printf("Insira o seu NIB:");
            testa_nib();
            printf ("\n");
            printf ("\n");
            menu();
            break;
        default:
            printf("Programa terminado.");
            abort ();
    }
}

void menu2 () {
    printf("Indique o q deseja saber sobre o seu NIB\n");
    printf("1 -\tToda a informação.\n");
    printf("2 -\tNúmero da conta.\n");
    printf("3 -\tNúmero de controlo.\n");
    printf("4 -\tNome do banco.\n");
    printf("5 -\tNome da agência.\n");
    printf("0 -\tVoltar para o menu inicial.\n");

}