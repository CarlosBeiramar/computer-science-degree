//
// Created by Carlos Beiramar on 2019-02-18.
// NIB = 001812300049912345678
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "funções.h"

void testa_nib () {
    char str[21];
    int i, h = 0, j = 0, res = 0, escolha2,l=0,tam;
    int nib[21];

    for (i = 0; i < 21; i++) {
        scanf(" %c", &str[i]); //guarda a string de números num array de char

    }
    for (h = 0; h < 21; h++) { //supostamente converte os char em inteiros e guarda num array de int
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

    if (res == 21) {
        printf("O seu NIB é válido."); //se for válido tem q imprimir tudo, numero de conta, banco, agencia, numeros de controlo
        printf("\n\n");
        menu2();
        scanf("%d", &escolha2);

        switch (escolha2) {
            //---------------------------------OPÇÃO-INFORMAÇÃO TOTAL---------------------------------------------------
            //------------------------------------IMPRIMIR O NIB COM ESPAÇO ENTRE BLOCOS--------------------------------
            case 1:
                printf("       NIB \t\t\t\t\t Números de Conta \t Números de Controlo \t\t Banco \t\t\t     Agência\n");

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
                //------------------------IMPRIMIR OS NÚMEROS DA CONTA SEM OS ZERO À ESQUERDA---------------------------
                printf("          ");
                l=0;
                tam=8;
                while (l!=1) {
                    if (nib[tam] == 0) {
                        tam++;
                        l=0;                        // imprimir os números da conta sem os zeros à esquerda
                        }                                           //número de conta
                     else {
                        for (i = tam; i < 19; i++) {
                            printf("%d", nib[i]);
                            l=1;
                        }
                    }
                }
                //---------------------------------IMPRIMIR O BANCO-----------------------------------------------------
                printf("               ");

                for (i = 19; i < 21; i++) {
                    printf("%d", nib[i]);
                }

                printf("              ");

                if (nib[0] == 0 && nib[1] == 0 && nib[2] == 0 && nib[3] == 7) {
                    printf("0007-Novo Banco");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 1 && nib[3] == 0) {
                    printf("0010-BPI");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 1 && nib[3] == 8) {
                    printf("0018-Santander Totta");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 1 && nib[3] == 9) {
                    printf("0019-BBVA");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 2 && nib[3] == 3) {
                    printf("0023-Activo Bank");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 2) {
                    printf("0032-Barclays");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 3) {
                    printf("0033-Millenium BCP");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 6) {
                    printf("0036-Montepio Geral");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 8) {
                    printf("0038-Banif");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 4 && nib[3] == 5) {
                    printf("0045-Crédito Agrícola");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 4 && nib[3] == 6) {
                    printf("0046-Banco Popular");
                }
                else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 7 && nib[3] == 9) {
                    printf("0079-BIC");
                }
                else if (nib[0] == 0 && nib[1] == 1 && nib[2] == 9 && nib[3] == 3) {
                    printf("0193-Banco CTT");
                }
                else if (nib[0] == 5 && nib[1] == 1 && nib[2] == 8 && nib[3] == 0) {
                    printf("5180-CCCAM");
                }
                else {
                    printf("Não existe");
                }

                //-------------------------------IMPRIMIR O NÚMERO DA AGÊNCIA-------------------------------------------
                    printf("           ");                 //número da agência
                    for (i = 4; i < 8; i++) {
                        printf("%d", nib[i]);
                    }
                    break;

            case 2:
                printf("Número de conta: ");
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
                    break;

            case 3:
                        printf("Número de controlo: ");
                    for (i = 19; i < 21; i++) {           //número de controlo
                        printf("%d", nib[i]);
                    }
                    break;

            case 4:
                        printf("O seu banco é: ");

                    if (nib[0] == 0 && nib[1] == 0 && nib[2] == 0 && nib[3] == 7) {
                        printf("0007-Novo Banco.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 1 && nib[3] == 0) {
                        printf("0010-BPI.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 1 && nib[3] == 8) {
                        printf("0018-Santander Totta.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 1 && nib[3] == 9) {
                        printf("0019-BBVA.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 2 && nib[3] == 3) {
                        printf("0023-Activo Bank.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 2) {
                        printf("0032-Barclays.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 3) {
                        printf("0033-Millenium BCP.");
                    }
                    else  if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 6) {
                        printf("0036-Montepio Geral.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 3 && nib[3] == 8) {
                        printf("0038-Banif.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 4 && nib[3] == 5) {
                        printf("0045-Crédito Agrícola.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 4 && nib[3] == 6) {
                        printf("0046-Banco Popular.");
                    }
                    else if (nib[0] == 0 && nib[1] == 0 && nib[2] == 7 && nib[3] == 9) {
                        printf("0079-BIC.");
                    }
                    else if (nib[0] == 0 && nib[1] == 1 && nib[2] == 9 && nib[3] == 3) {
                        printf("0193-Banco CTT.");
                    }
                    else if (nib[0] == 5 && nib[1] == 1 && nib[2] == 8 && nib[3] == 0) {
                        printf("5180-Caixa Central de Crédito Agrícula Mútuo.");
                    }else {
                        printf("Valor do banco inválido");
                    }
                    break;

            case 5:
                        printf("Número da agência: ");
                    for (i = 4; i < 8; i++) {
                        printf("%d", nib[i]);

                    }
                    break;
            default:
                menu();
                break;
        }
    }
        else {
            printf("O seu NIB não é válido");
            abort();
        }
    }