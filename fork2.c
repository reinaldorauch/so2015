#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ITERACOES 50

void runMain() {
    for (int i = 0; i < ITERACOES; i++)
    {
        printf("Sou processo pai.\n");
        for (int i = 0; i < 500000; i++);
    }
}

void runError(int error) {
    printf("Erro ao forkar o processo: %d\n", error);
}

void runChild() {
    for (int i = 0; i < ITERACOES; i++)
    {
        printf("Sou o processo filho.\n");
        for (int i = 0; i < 500000; ++i);
    }
}

int main()
{
    int pid;

    pid = fork();

    if(pid > 0) {
        runMain();
    } else {
        if(pid < 0) {
            runError(pid);
        } else {
            runChild();
        }
    }

    return 0;
}