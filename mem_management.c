#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

/**
 * Define um pid nulo, ou seja, um buraco na memória
 */
#define PID_NULL 0

struct void {
  unsigned init;
  unsigned end;
  unsigned size;
  struct void *next;
};

typedef struct void t_void;

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
 * Faz o first fit do processo
 * @param pid  Pid do processo
 * @param size Tamanho do processo
 */
void firstFit(unsigned pid, unsigned size) {
  int init = -1, end = -1;
  unsigned found = 0;

  for (int i = 0; i < memAllocated; i++)
  {
    if(init == -1) {
      if(*(ff + i) == PID_NULL) {
        init = i;
        end = 1;
      }
    } else {
      end++;
      if(end == size) {
        end = i;
        found = 1;
        break;
      } else if(*(ff + i) != PID_NULL) {
        init = end = -1;
      }
    }
  }

  if(found) {
    for(int i = init; i <= end; i++) {
      *(ff + i) = pid;
    }
  } else {
    puts("Não foi encontrado um espaço com First Fit");
  }

}

/**
 * Adiciona um buraco à lista encadeada de buracos
 * @param  voids Lista encadeada de voids
 * @param  init  posição inicial do buraco
 * @param  end   posição final do buraco
 * @return       ponteiros à lista de voids
 */
t_void *pushVoids(t_void *voids, unsigned init, unsigned end) {
  t_void *newVoid = (t_void*) calloc(1, sizeof(t_void)), actualVoid = NULL;

  if(newVoid == NULL) {
    puts("Erro ao procurar os buracos");
    return voids;
  }

  newVoid->init = init;
  newVoid->end = end;
  newVoid->size = end - init + 1;
  newVoid->next = NULL;

  if(voids == NULL) {
    voids = newVoid;
  } else {
    actualVoid = voids;
    while(actualVoid->next == NULL) {
      actualVoid = actualVoid->next;
    }

    actualVoid->next = newVoid;
  }

  return voids;
}

void sortVoids(t_void *voids, t_void *lo, t_void *hi) {
  pa

  if(lo->size < hi->size) {

  }

}

t_void *getLowest(t_void *voids) {
  t_void *actual = voids;
  unsigned lowest = voids->size;

  while(actual->next != NULL) {
    if(actual->size < lowest) {
      lowest = actual->size;
    }

    actual = actual->next;
  }

  return actual;
}

t_void *getBestMatch(t_void *voids, unsigned size) {
  sortVoids(voids, getLowest(voids), getBiggest(voids));

  t_void *actual = voids;


}

/**
 * Faz o best fit do processo
 * @param pid  Pid do processo
 * @param size Tamanho do processo
 */
void bestFit(unsigned pid, unsigned size) {
  int init = -1, end = -1;
  unsigned found = 0;

  t_void *voids = NULL, *match = NULL;

  for (int i = 0; i < memAllocated; i++)
  {
    if(init == -1) {
      if(*(ff + i) == PID_NULL) {
        init = i;
        end = 1;
      }
    } else {
      end++;
      if(end == size) {
        end = i;
        found = 1;
        break;
      } else if(*(ff + i) != PID_NULL) {
        voids = pushVoids(voids, init, end);
        init = end = -1;
      }
    }
  }

  match = getBestMatch(voids, size);

  if(match == NULL) {
    puts("Não foi encontrado um espaço com First Fit");
  } else {
    init = match->init;
    end = match->end;
    for(int i = init; i <= end; i++) {
      *(ff + i) = pid;
    }
  }

  freeVoids(voids);
  free(match);
}

/**
 * Faz o worst fit do processo
 * @param pid  Pid do processo
 * @param size Tamanho do processo
 */
void worstFit(unsigned pid, unsigned size) {
}

/**
 * Faz o next fit do processo
 * @param pid  Pid do processo
 * @param size Tamanho do processo
 */
void nextFit(unsigned pid, unsigned size) {
}

/**
 * Cria um processo
 */
void createProcess() {
  unsigned size = 0;
  pidCounter++;

  puts("Criando um processo. Digite o tamanho do processo:");
  scanf("%d", &size);

  if(size == 0) {
    puts("tamanho vazio, tente novamente");
    return;
  }

  if(size > memAllocated) {
    puts("Tamanho maior da memória alocada, não foi possível inserir. Tente novamente");
    return;
  }

  firstFit(pidCounter, size);
  bestFit(pidCounter, size);
  worstFit(pidCounter, size);
  nextFit(pidCounter, size);
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
