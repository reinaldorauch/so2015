#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

/**
 * Define um pid nulo, ou seja, um buraco na memória
 */
#define PID_NULL 0

/**
 * Memórias para tipos diferentes de alocação de memória
 *
 * ff -> First Fit
 * bf -> Best Fit
 * wf -> Worst Fit
 * nf -> Next fit
 */
unsigned *ff = NULL, *bf = NULL, *wf = NULL, *nf = NULL;

/**
 * Tamanho da memória alocada
 */
unsigned memAllocated = 0;

/**
 * Contador de pid
 */
unsigned pidCounter = 0;

/**
 * Imprime o menu na tela
 */
void menu(){
  puts("##############################################");
  puts("#                  MENU                      #");
  puts("#                                            #");
  puts("#     Digite a opção desejada                #");
  puts("#                                            #");
  puts("#      0 = Alocar memória                    #");
  puts("#      1 = Criar processo                    #");
  puts("#      2 = Matar  processo                   #");
  puts("#      3 = Visualizar processos              #");
  puts("#      4 = Reiniciar a memoria               #");
  puts("#      9 = Sair                              #");
  puts("#                                            #");
  puts("##############################################");
}

/**
 * Limpa o buffer de entrada para capturar somente um caractere
 * @param fp o descritor de arquivo para limpar
 */
void clearBuffer(FILE *fp) {
  char ch;

  while((ch = fgetc(fp)) != '\n' || ch == EOF);
}

/**
 * Aloca x de memória
 * @return tamanho de memória alocada
 */
unsigned allocateMemory(unsigned size) {
  if(size == 0) {
    puts("Tamanho inválido. Tente novamente");
    return 0;
  }

  ff = (unsigned*) calloc(size, sizeof(unsigned));

  if(ff == NULL) {
    puts("Erroooo, tente novamente");
    return 0;
  }

  wf = (unsigned*) calloc(size, sizeof(unsigned));

  if(wf == NULL) {
    puts("Erroooo, tente novamente");
    free(ff);
    return 0;
  }

  bf = (unsigned*) calloc(size, sizeof(unsigned));

  if(bf == NULL) {
    puts("Erroooo, tente novamente");
    free(ff);
    free(wf);
    return 0;
  }

  nf = (unsigned*) calloc(size, sizeof(unsigned));

  if(nf == NULL) {
    puts("Erroooo, tente novamente");
    free(ff);
    free(wf);
    free(bf);
    return 0;
  }

  return size;
}

/**
 * Captura o tamanho da memória necessária a ser alocada
 * @return o tamanho da memória alocada
 */
unsigned allocateMemory() {
  unsigned size = 0;

  puts("Digite o tamanho da memória a ser alocada (um inteiro):");

  scanf("%u", &size);

  return allocateMemory(size);
}

/**
 * Verifica se a memória está alocada
 */
unsigned checkAllocated() {
  if(!(ff == NULL && wf == NULL && bf == NULL && nf == NULL)) {
    return 1;
  }

  return 0;
}

/**
 * Cria um processo
 */
void createProcess() {
  puts("Não implementado");
}

/**
 * Mata o processo
 */
void killProcess() {
  puts("Não implementado");
}

/**
 * Imprime a linha separadora
 * @param padding tamanho da linha
 */
void printSeparator(unsigned padding){

  for (int i = 0; i < padding; i++)
  {
    printf("+------------");
  }
  puts("+");

}

/**
 * Imprime uma memória na tela
 * @param memory a memória a ser impressa
 */
void printMemory(unsigned *memory) {

  printSeparator(memAllocated);

  for (int i = 0; i < memAllocated; i++)
  {
    printf("| %10u ", *(memory + i));
  }
  puts("|");

  printSeparator(memAllocated);

}

/**
 * Imprime a representação das memórias na tela
 */
void printMemories() {

  puts("First fit:");
  printMemory(ff);

  puts("Best fit:");
  printMemory(bf);

  puts("Worst fit:");
  printMemory(wf);

  puts("Next fit:");
  printMemory(nf);

}

/**
 * Desaloca as memórias
 */
void deallocateMemory() {
  puts("Deallocating memories");
  free(ff);
  free(wf);
  free(bf);
  free(nf);
  ff = wf = bf = nf = NULL;
  puts("Done.");
}

/**
 * Limpa as memórias
 */
void clearMemories() {

  puts("Limpando memórias");
  deallocateMemory();
  allocateMemory(memAllocated);
  puts("Done.");

}

/**
 * Main program
 * @return Exit estate
 */
int main() {

  char option;

  while(1) {
    menu();

    option = getchar();

    clearBuffer(stdin);

    switch(option) {
      // Opção de alocar a memória
      case '0':
        if(checkAllocated()) {
          puts("Memória já alocada, desaloque-a e tente novamente");
          break;
        }
        memAllocated = allocateMemory();
        break;
      // Opção de criar um processo
      case '1':
        if(!checkAllocated()) {
          puts("Memória não alocada, aloque-a e tente novamente");
          break;
        }
        createProcess();
        break;
      // Opção de matar um processo
      case '2':
        if(!checkAllocated()) {
          puts("Memória não alocada, aloque-a e tente novamente");
          break;
        }
        killProcess();
        break;
      // Imprime as memórias na tela
      case '3':
        if(!checkAllocated()) {
          puts("Memória não alocada, aloque-a e tente novamente");
          break;
        }
        printMemories();
        break;
      // Opção de limpar as memórias
      case '4':
        if(!checkAllocated()) {
          puts("Memória não alocada, aloque-a e tente novamente");
          break;
        }
        clearMemories();
        break;
      // Opção de sair do programa
      case '9':
        puts("Sayonara");
        if(checkAllocated()) {
          deallocateMemory();
        }
        exit(0);
        break;
      default:
        printf("Debug: %c <-- opção escolhida\n", option);
        puts("Try again!");
        break;
    }
  }

  return 1;
}
