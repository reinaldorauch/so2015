#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 1000
#define RUNS 10

typedef struct {
    int pid;
    int size;
} proc_t;

proc_t processos[SIZE];

void spawn() {
   for (int i = 0; i < SIZE; i++)
   {
       processos[i].pid = i + 1;
       processos[i].size = rand() % 100;
   }
}

void kill() {
    int randPid;
    for (int i = 0; i < (SIZE / 2); i++)
    {
        randPid = rand() % 1000;

        if(processos[randPid].pid == -1) {
            i--;
            continue;
        }

        processos[randPid].size = processos[randPid].pid = -1;
    }
}

int countProc() {
    int counter = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if(processos[i].pid != -1) {
            counter++;
        }
    }

    return counter;
}

int countSpaces() {
    int counter = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if(processos[i].pid == -1 && processos[i-1].pid != -1) {
            counter++;
        }
    }

    return counter;
}

int main()
{
    int proc = 0, spaces = 0;

    srand((unsigned) time(NULL));

    for (int i = 0; i < RUNS; i++)
    {
        spawn();
        kill();
        proc += countProc();
        spaces += countSpaces();
    }

    printf("Média em %d execuções:\n\n", RUNS);
    printf("Buracos:   %f\n", (double) spaces / (double) RUNS);
    printf("Processos: %f\n", (double) proc /  (double) RUNS);

    return 0;
}