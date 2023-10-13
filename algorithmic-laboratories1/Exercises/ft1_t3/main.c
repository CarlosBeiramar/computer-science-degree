#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alinea_a () {
    int res,a,b,c;

    printf ("Insira três medidas para um triângulos:\n");
    scanf("%d %d %d",&a,&b,&c);

    if (a>0 && b>0 && c>0) {

        if ((abs(b-c) < a) && (a < b+c) && (abs(a-c) < b) && (b < a+c) && (abs(a-b) < c) && (c < (a+b))) {
            printf("É um triângulo.\n");
            res=1;
        }else {
            printf("Não é um triângulo.\n");
            res=0;
        }
    }else {
        printf("Não é um triângulo.\n");
        res=0;
    }
}

void alinea_b () {
    int res,a,b,c;

    /*printf("Insira três medidas para um triângulo:\n");
       scanf("%f %f %f",&a,&b,&c);*/

         if (res == 1) {

                if (a == b && a == c && b == c) {
                    printf("O triângulo é equilátero.\n");
                 }

                if ((a==b && a!=c && b!=c) || (a==c && a!=b && c!=b) || (b==c && b!=a && c!=a)) {
                    printf("O triângulo é isósceles.\n");
                }

                if (a!=b && a!=c && b!=c) {
                    printf("O triângulo é escaleno.\n");
                }
         }
    }

void alinea_c () {
    int res,a,b,c;
    float x,s;

    /*printf ("Insira três medidas para um triângulo:\n");
      scanf ("%d %d %d",&a,&b,&c); */

    if (res==1) {
        s = (float) (a+b+c)/2;
        x = sqrtf(s*(s-a)*(s-b)*(s-c));
        printf("A área é de: %f.\n",x);
    }
}

int main() {
    alinea_a();
    alinea_b();
    alinea_c();
    return 0;
}
