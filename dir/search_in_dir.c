/**
 * Programa que procura recursivamente na árvore de diretórios do diretório
 * atual por um arquivo vindo na linha de comando
 */
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int found = 0;

void concatDirNames(const char main[], const char dest[], int isSubdir, char *path) {
    path[0] = '\0';
    strcat(path, main);
    strcat(path, dest);
    if(isSubdir) {
        strcat(path, "/");
    }
}

int notSpecialDirs(struct dirent *direntry) {
    int sd = direntry->d_type == DT_DIR;
    sd = sd && strcmp(direntry->d_name, ".") != 0;
    sd = sd && strcmp(direntry->d_name, "..") != 0;
    return sd;
}

void searchInDir(char const dirname[], char const filename[]) {
    DIR *currdir;
    struct dirent *direntry;
    char relativePath[PATH_MAX + 1], realPath[PATH_MAX + 1];

    currdir = opendir(dirname);

    while(direntry = readdir(currdir)) {
        if(strcmp(direntry->d_name, filename) == 0) {
            found++;
            concatDirNames(dirname, direntry->d_name, 0, relativePath);
            printf("Found %s in these paths: \"%s\" and \"%s\"\n", filename, relativePath, realPath);
        } else if(notSpecialDirs(direntry)) {
            concatDirNames(dirname, direntry->d_name, 1, relativePath);
            searchInDir(relativePath, filename);
        }
        closedir(currdir);
    }
}

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        puts("Parâmetros inválidos, uso: search_in_dir <nome_do_arquivo>");
        return 1;
    }

    searchInDir("./", argv[1]);

    if(!found) {
        puts("Didn't found the file");
    }

    return 0;
}