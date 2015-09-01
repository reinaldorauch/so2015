#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#define ITERACOES 1000000000
#define MICROFACTOR 1000000
#define MAX_FORK 0
#define SHARED_MEMORY_KEY 6660999

int resultPipe[2];

/**
 * Calcula o PI iterndo ITERACOES vezes
 * @return Valor do PI aproximado ITERACOES Vezes
 */
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

/**
 * Calcula a diferença de tempo entre os timestamps
 * @param  tempo1 Tempo inicial
 * @param  tempo2 Tempo final
 * @return        Double com o tempo decorrido
 */
double getDiffTime(struct timeval tempo1,struct timeval tempo2) {
    return ((double) (tempo2.tv_sec - tempo1.tv_sec)) + ((double) ((double) (tempo2.tv_usec - tempo1.tv_usec) / (double) MICROFACTOR));
}

/**
 * Job que rodaria em um main normal encapsulado para rodar em subprocessos
 */
double jobRun() {
    // Timers
    struct timeval tempo1, tempo2;

    // Captura o timestamp na ao começar a execução do job
    gettimeofday(&tempo1, NULL);

    // Executa o job de calcular o PI
    printf("%.50f\n", calcPi());

    // Captura o tempo no término do job para calcular o tempo de execução
    gettimeofday(&tempo2, NULL);

    // Calcula o tempo de execução e mostra
    return getDiffTime(tempo1, tempo2);
}

/**
 * Calcula a média dos tempos
 */
void calcMedia() {
    // Guarda a soma
    double sum = 0;
    // Guarda um resultado
    double resRead;

    // Itera sobre o número de resultados esperados
    for(int i = 0; i <= MAX_FORK; i++) {
        // Lê um resultado do pipe
        read(resultPipe[0], &resRead, sizeof(resRead));
        printf("%f\n", resRead);
        // Adiciona esse resultado ao acumulador
        sum += resRead;
    }

    // Fecha os pipes
    close(resultPipe[0]);
    close(resultPipe[1]);

    // Imprime a média
    printf("Média: %.10f\n", sum / (double) (MAX_FORK + 1));
}

/**
 * Forka recursivamente os processos até o limite definido em constante
 * @param counter Contador dos forks
 */
void forkRecursive(int counter) {
    int childPid;

    // Forka um subprocesso e testa se a execução é
    if((childPid = fork()) > 0) {
        // Roda o job no parent e atribui à uma variável result
        double result = jobRun();
        // Escreve no pipe o valor do resultado
        write(resultPipe[1], &result, sizeof(double));
        // Espera o término do processo filho
        wait(NULL);

        // Testa se é o processo pai root
        if(counter == 0) {
            // Se for, calcula a média lendo o pipe
            calcMedia();
        }
    } else {
        // Teste de validade do child
        if(childPid < 0) {
            printf("Error %d, stop forking....", childPid);
        } else {
            // Se não chegou no limite de forks, chama novamente a forkRecursive
            // para forkar um novo subprocesso
            if(counter < MAX_FORK) {
                forkRecursive(++counter);
            }
        }
    }
}

/**
 * Programa principal
 * @return status da execução
 */
int main()
{
    // Criando o pipe para coletar os resultados
    pipe(resultPipe);
    // Chama a função recursiva pra forkar os processos
    forkRecursive(0);
    return 0;
}