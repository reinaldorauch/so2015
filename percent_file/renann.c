//
// Contar a porcentagem de tipos de arquivos
// contidos na pasta atual e nos diretorios raizes
//
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char const *argv[]) {
    DIR *dirstream;
    struct dirent *direntry;
    char buffer[50] = "./";
    int i = 0,
        unk = 0,
        wht = 0,
        diretorio = 0,
        fifo = 0,
        socket = 0,
        bloco = 0,
        cd = 0,
        link = 0,
        aux = 0,
        tipo,
        reg = 0;

    if (argc == 2) {
        dirstream = opendir(argv[1]);
    } else {
        dirstream = opendir(buffer);
    }

    while(direntry = readdir(dirstream)) {
        printf("%20s -> type: ", direntry->d_name);
        aux++;
        switch(direntry->d_type) {
            case DT_UNKNOWN:
                unk++;
                puts("Unknown");
                break;
            case DT_FIFO:
                fifo++;
                puts("FIFO");
                break;
            case DT_CHR:
                cd++;
                puts("Character device");
                break;
            case DT_DIR:
                diretorio++;
                puts("Directory");
                break;
            case DT_BLK:
                bloco++;
                puts("Block device");
                break;
            case DT_REG:
                reg++;
                puts("Normal file");
                break;
            case DT_LNK:
                link++;
                puts("Link file");
                break;
            case DT_SOCK:
                socket++;
                puts("Socket file");
                break;
            default:
                perror("tipo invalido\n");
        }
    }

    closedir(dirstream);

    /**
     * Calculo da porcentagem
     */

    printf("Arquivo tipo desconhecido = %3d%% (total = %d, type = %d)\n", (unk * 100) / aux, aux, unk);
    printf("Arquivo tipo normal       = %3d%% (total = %d, type = %d)\n", (reg * 100) / aux, aux, reg);
    printf("Arquivo tipo diretorio    = %3d%% (total = %d, type = %d)\n", (diretorio * 100) / aux, aux, diretorio);
    printf("Arquivo tipo fifo         = %3d%% (total = %d, type = %d)\n", (fifo * 100) / aux, aux, fifo);
    printf("Arquivo tipo socket       = %3d%% (total = %d, type = %d)\n", (socket * 100) / aux, aux, socket);
    printf("Arquivo tipo cd           = %3d%% (total = %d, type = %d)\n", (cd * 100) / aux, aux, cd);
    printf("Arquivo tipo bloco        = %3d%% (total = %d, type = %d)\n", (bloco * 100) / aux, aux, bloco);
    printf("Arquivo tipo link         = %3d%% (total = %d, type = %d)\n", (link * 100) / aux, aux, link);
    return 0;
}