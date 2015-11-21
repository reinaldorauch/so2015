/**
 * Programa que procura na árvore de diretórios do diretório
 * atual por um arquivo vindo na linha de comando
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


int main(int argc, char const *argv[]) {
    DIR *dir;
    struct dirent *direntry;

    if(argc != 2) {
        printf("Parâmetros inválidos, uso: %s <nome_do_arquivo>", argv[0]);
        return 1;
    }

    dir = opendir(argv[1]);

    while(direntry = readdir(dir)) {
        switch(direntry->d_type) {
            case DT_UNKNOWN:
            case DT_REG:
            case DT_DIR:
            case DT_FIFO:
            case DT_SOCK:
            case DT_CHR:
            case DT_BLK:
            case DT_LNK:
        }
    }

    return 0;
}