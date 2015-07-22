#include <stdio.h>
#include <stdlib.h>

void runMain(int p, int c) {
    printf("Eu sou o pai (%d), o meu filho (%d)\n", p, c);
    sleep(1);
}

void runChild() {
    printf("Eu sou o filho (%d), o meu pai: (%d)\n", getpid(), getppid());
}

void checkError(error) {
    printf("Deu erro na bagaça, ta aqui ó -> (%d)\n", error);
}

int main() {
    int childPid = 0;
    int ourPid = getpid();

    printf("Ainda existe apenas um processo (%d)\n", ourPid);

    childPid = fork();

    printf("Agora somos dois (%i)\n", getpid());

    if(childPid > 0) {
        runMain(ourPid, childPid);
    } else {
        if(childPid < 0) {
            checkError(childPid);
        } else {
            runChild();
        }
    }

    return 0;
}