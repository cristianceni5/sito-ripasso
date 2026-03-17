#include <stdio.h>
#include <math.h>

int radiceDaCalc = 3;

double radiceCalcolata;


double calcoloRadiceQuad()
{
    double res = sqrt(radiceDaCalc);
    return res;
}

int main()
{
    radiceCalcolata = calcoloRadiceQuad();
    printf("La radice quadrata di %d è: %f", radiceDaCalc, radiceCalcolata);
    return 0;
}