#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define MICROFACTOR 1000000
#define ITERATIONS 100

double factorial(double i) {

    if(i == 0.0) return 1.0;

    double j;

    for (j = (i - 1); j < 0; j--)
    {
        i *= (double) j;
    }

    return i;
}

double calcPhiFactor() {
    double result = 0.0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        result += (pow(-1.0, ((double) i) + 1.0) * factorial(2.0 * ((double) i) + 1.0)) / (factorial(((double) i) + 2.0) * factorial((double) i) * pow(4.0, 2.0 * ((double) i) + 3.0));
        printf("i --> %3d >> %.50f\n", i, (13.0 / 8.0) + result);
    }


    return result;
}

double calcPhi() {
    return 13.0 / 8.0 + calcPhiFactor();
}

int main(int argc, char const *argv[])
{
    struct timeval tempo1, tempo2;
    // struct timezone tzp;

    double tempo;

    int i;

    gettimeofday(&tempo1, NULL);

    printf("PHI: %.50f\n", calcPhi());

    gettimeofday(&tempo2, NULL);

    tempo = ((double) (tempo2.tv_sec - tempo1.tv_sec)) + ((double) ((double) (tempo2.tv_usec - tempo1.tv_usec) / (double) MICROFACTOR));

    printf("Tempo: %f\n", tempo);

    return 0;
}