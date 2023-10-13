#include <stdio.h>


void le_imprime (char matriz[][100]){
    FILE *ficheiro;
    int linhas=0,colunas=0,i=0,j=0;
    ficheiro = fopen("/Users/carlosbeiramar/CLionProjects/Ficha4/cmake-build-debug/tabuleiro.txt","r");

    fscanf(ficheiro,"%d %d",&linhas,&colunas);
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            fscanf(ficheiro," %c",&matriz[i][j]);
            printf(" %c", matriz[i][j]);

        }
        printf("\n");
    }
    fclose(ficheiro);
}

void altera_matriz (char matriz[] [100]){
    int mlinha=0,mcoluna=0;
    int linhas=0,colunas=0,i=0,j=0;
    char sub;
    //----------------------------------------------------------------------------------------------------------------
    FILE *ficheiro;
    ficheiro = fopen("/Users/carlosbeiramar/CLionProjects/Ficha4/cmake-build-debug/tabuleiro.txt","r");
    fscanf(ficheiro,"%d %d",&linhas,&colunas);

    for(i=0;i<linhas;i++) {
        for (j = 0; j < colunas; j++) {
            fscanf(ficheiro, " %c", &matriz[i][j]);
        }
    }
    fclose(ficheiro);

     //----------------------------------------------------------------------------------------------------------------
    printf("Insira que posicao pretende alterar\n");
    printf("linha: ");
    scanf("%d",&mlinha);

    if (mlinha>2){
        printf("Linha invalida\n"
               "Insira novamente:");
        scanf("%d",&mlinha);
    }
    printf("coluna:");

    scanf("%d",&mcoluna);

    if (mcoluna>3){
        printf("Coluna invalida\n"
               "Insira novamente:");
        scanf("%d",&mcoluna);
    }

    printf("Quer por um X ou um O?\n");
    scanf(" %c",&sub);

    if(matriz[mlinha][mcoluna]=='.'){
        matriz[mlinha][mcoluna]=sub;
    }else{
        printf("posicao invalida\n");
    }

    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++) {
            printf(" %c", matriz[i][j]);
        }
        printf("\n");
    }

}

void guarda_ficheiro(char matriz[][100]){
    FILE *ficheiro;
    int linhas=3,colunas=4,i=0,j=0;

    ficheiro = fopen("/Users/carlosbeiramar/CLionProjects/Ficha4/cmake-build-debug/tabuleiro.txt","w");
    fprintf(ficheiro,"%d %d\n",linhas,colunas);

    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++) {
            fprintf(ficheiro," %c",matriz[i][j]);
        }
        fprintf(ficheiro,"\n");
    }
    fclose(ficheiro);

}


void menu (char matriz[][100]){
    char escolha;


        printf("\n");
        printf("Escolha o que deseja:\n");
        printf("\n");
        printf("[1] -\tImprimir o ficheiro.\n");
        printf("[2] -\tAlterar o tabuleiro.\n");
        printf("[0] -\tTerminar programa.\n");

        scanf(" %c", &escolha);
        switch (escolha) {
            case '1':
                le_imprime(matriz);
                menu(matriz);
                break;
            case '2':
                altera_matriz(matriz);
                guarda_ficheiro(matriz);
                menu(matriz);
                break;
            default:
                printf("Programa Terminado");
                break;
        }
}



int main() {
    char matriz[100][100];
    menu(matriz);
    return 0;
}