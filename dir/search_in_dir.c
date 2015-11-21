/**
 * Programa que procura na árvore de diretórios do diretório
 * atual por um arquivo vindo na linha de comando
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

struct node
{
    char *dir;
    struct node* next;
    struct node* prev;
};

typedef struct node t_node;

int found = 0;

t_node *stack = NULL;

void push(char dir[]) {

    t_node *newNode = (t_node*) calloc(1, sizeof(t_node)), *actual = NULL;

    newNode->dir = dir;
    newNode->prev = stack;
    newNode->next = NULL;

    if(stack == NULL) {
        stack = newNode;
    } else {
        actual = stack;

        while(actual->next != NULL) {
            actual = actual->next;
        }

        actual->next = newNode;
    }

}

t_node *pop() {
    t_node *actual = stack;

    while(actual->next != NULL) {
        actual = actual->next;
    }

    return actual;
}

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
    char resolved[PATH_MAX];

    currdir = opendir(dirname);
    // push(currdir);

    while(direntry = readdir(currdir)) {
        // printf("Direntry: %s\n", direntry->d_name);
        if(strcmp(direntry->d_name, filename) == 0) {
            found++;
            printf("Found %s/%s ", getenv("PWD"), direntry->d_name);
        } else if(notSpecialDirs(direntry)) {

        }
    }

    closedir(currdir);

    // searchInDir(direntry->d_name, filename);
}

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("Parâmetros inválidos, uso: %s <nome_do_arquivo>", argv[0]);
        return 1;
    }

    searchInDir("./", argv[1]);

    if(!found) {
        puts("Didn't found the file");
    }

    return 0;
}
