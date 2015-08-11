#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define ITERACOES 10000000000
#define MICROFACTOR 1000000
#define MAX_FORK 10

double calcPi() {
    long int a = 1, b = 2;
    double result = 1.0;

    for (long int i = 0; i < ITERACOES; i++)
    {
        result *= (double) b / (double) a;

        if(i % 2 == 0) {
            a += 2;
        } else {
            b += 2;
        }
    }

    return result * 2.0;
}

double getDiffTime(struct timeval tempo1,struct timeval tempo2) {
    return ((double) (tempo2.tv_sec - tempo1.tv_sec)) + ((double) ((double) (tempo2.tv_usec - tempo1.tv_usec) / (double) MICROFACTOR));
}

void jobRun() {
    struct timeval tempo1, tempo2;

    double tempo;

    gettimeofday(&tempo1, NULL);

    printf("%.50f\n", calcPi());

    gettimeofday(&tempo2, NULL);

    printf("Tempo: %f\n", getDiffTime(tempo1, tempo2));
}

void forkRecursive(int counter) {
    int childPid;

    if((childPid = fork()) > 0) {
        jobRun();
    } else {
        if(childPid < 0) {
            printf("Error %d, stop forking....", childPid);
        } else {
            if(counter < MAX_FORK) {
                forkRecursive(++counter);
            }
        }
    }
}

int main()
{
    forkRecursive(0);

    return 0;
}