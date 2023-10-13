
#include <stdio.h>
#include <math.h>

int main() {
    // input
    // calculo com erros sintáticos
    // erros semânticos
    // print
    // calcular as raizes do polinomio ax^2 + bx + c = 0
    float a, b, c,x1, x2;
    //
    printf("Introduza os valores dos termos a,b e c do polinómio ax^2 + bx + c:\n ");
    scanf("%f %f %f", &a, &b, &c);
    if (a!=0) {
        x1 = (float) ((-1.0 * b + sqrt(powf(b, 2) - 4.0 * a * c)) / (2.0 * a));
        x2 = (float) ((-1.0 * b - sqrt(powf(b, 2) - 4.0 * a * c)) / (2.0 * a));
        printf("raizes x1 = %f \n e x2 = %f \n", x1, x2);
    }
    return 0;
}