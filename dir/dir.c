/**
 * exemplo de manipulação de diretório
 */
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void putsDirType (int type) {
    switch(type) {
        case DT_UNKNOWN:
            puts("The type is unknown.");
            break;
        case DT_REG:
            puts("A regular file.");
            break;
        case DT_DIR:
            puts("A directory.");
            break;
        case DT_FIFO:
            puts("A named pipe, or FIFO. See FIFO Special Files.");
            break;
        case DT_SOCK:
            puts("A local-domain socket.");
            break;
        case DT_CHR:
            puts("A character device.");
            break;
        case DT_BLK:
            puts("A block device.");
            break;
        case DT_LNK:
            puts("A symbolic link.");
            break;
        default:
            perror("Invalid direntry type");
    }
}

int main(int argc, char const *argv[]) {
    DIR *dirstream;
    struct dirent *direntry;
    int i = 0;

    dirstream = opendir ("./");

    if (!dirstream) {
        perror ("Não pude abrir esse diretorio\n");
        return 1;
    }

    while (direntry = readdir(dirstream)) {
        puts("-------------------");
        puts(direntry->d_name);
        putsDirType(direntry->d_type);
        puts("-------------------\n");
    }

    closedir(dirstream);
    return 0;
}
