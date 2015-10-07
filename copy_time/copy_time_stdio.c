#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE_1_BYTE 1

#define MICROFACTOR 1000000
#define NUM_RUNS 5

#define FILE_1_BYTE "file1byte.txt"
#define FILE_1_KBYTE "file1kbyte.txt"
#define FILE_1_MBYTE "file1mbyte.txt"
#define FILE_20_MBYTE "file20mbyte.txt"
#define FILE_VOID "file.out"

/**
 * Copy function with stdio
 * @param filename      Origin filepath
 * @param filename_dest Destination filepath
 */
void copy(const char filename[], const char filename_dest[]) {
    int c;
    FILE *in, *out;

    in = fopen(filename, "r");
    out = fopen(filename_dest, "w");

    while((c = fgetc(in)) != EOF) {
        fputc(c, out);
    }
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

double copy1byte() {
    struct timeval start, finish;
    double runtime;

    gettimeofday(&start, NULL);
    copy(FILE_1_BYTE, FILE_VOID);
    gettimeofday(&finish, NULL);

    runtime = getDiffTime(start, finish);

    printf("Run time %.10f\n", runtime);

    return runtime;
}

double copy1kbyte() {
    struct timeval start, finish;
    double runtime;

    gettimeofday(&start, NULL);
    copy(FILE_1_KBYTE, FILE_VOID);
    gettimeofday(&finish, NULL);

    runtime = getDiffTime(start, finish);

    printf("Run time %.10f\n", runtime);

    return runtime;
}

double copy1mbyte() {
    struct timeval start, finish;
    double runtime;

    gettimeofday(&start, NULL);
    copy(FILE_1_MBYTE, FILE_VOID);
    gettimeofday(&finish, NULL);

    runtime = getDiffTime(start, finish);

    printf("Run time %.10f\n", runtime);

    return runtime;
}

double copy20mbyte() {
    struct timeval start, finish;
    double runtime;

    gettimeofday(&start, NULL);
    copy(FILE_20_MBYTE, FILE_VOID);
    gettimeofday(&finish, NULL);

    runtime = getDiffTime(start, finish);

    printf("Run time %.10f\n", runtime);

    return runtime;
}

int main() {
    int i;
    double media = 0.0;

    /**
     * 1B Run
     */

    for (i = 0; i < NUM_RUNS; i++) {
        media += copy1byte();
    }

    printf("Averages for 1 byte and %d runs: %.10f\n", NUM_RUNS, media / NUM_RUNS);

    /**
     * 1KB Run
     */

    media = 0.0;

    for (i = 0; i < NUM_RUNS; i++) {
        media += copy1kbyte();
    }

    printf("Averages for 1 kbyte and %d runs: %.10f\n", NUM_RUNS, media / NUM_RUNS);

    /**
     * 1MB Run
     */

    media = 0.0;

    for (i = 0; i < NUM_RUNS; i++) {
        media += copy1mbyte();
    }

    printf("Averages for 1 mbyte and %d runs: %.10f\n", NUM_RUNS, media / NUM_RUNS);

    /**
     * 20MB Run
     */

    media = 0.0;

    for (i = 0; i < NUM_RUNS; i++) {
        media += copy20mbyte();
    }

    printf("Averages for 20 mbyte and %d runs: %.10f\n", NUM_RUNS, media / NUM_RUNS);

    return 0;
}

