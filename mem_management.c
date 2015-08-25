#include <stdio.h>
#include <stdlib.h>

/**
 * Define um pid nulo, ou seja, um buraco na memória
 */
#define PID_NULL = 0;

/**
 * Se há memória alocada para a simulação ou não.
 * Guarda a quantidade de processos alocados
 */
int memory_allocated = 0;

/**
 * Estrutura de um processo, contendo seu pid e tamanho
 */
struct process {
  int pid;
  int size;
};

/**
 * Definindo o tipo para os processos
 */
typedef struct process t_process;

/**
 * Estrutura para a memória
 */
struct memory {
  int max_size;
  t_process *procs;
};

/**
 * Definindo o tipo para as memórias
 */
typedef struct memory t_memory;

/**
 * Memórias para tipos diferentes de alocação de memória
 *
 * ff -> First Fit
 * bf -> Best Fit
 * wf -> Worst Fit
 * nf -> Next fit
 */
t_memory ff, bf, wf, nf;

/**
 * Aloca a quantidade de memória definida pelo usuário
 */
void alocateMemory() {
  int nproc;
  puts("\nDeseja alocar quanto de memória?");
  scanf("%d", &nproc);

  if(nproc < 1) {
    puts("Quantidade inválida, tente novamente");
    return;
  }

  ff.procs = (t_process*) calloc(1, sizeof(t_process));

  if(ff.procs == NULL) {
    puts("eroooo, falta de memória");
    return;
  }

  ff.max_size = nproc;

  bf.procs = (t_process*) calloc(1, sizeof(t_process));

  if(bf.procs == NULL) {
    puts("eroooo, falta de memória");
    free(ff.procs);
  }

  bf.max_size = nproc;

  wf.procs = (t_process*) calloc(1, sizeof(t_process));

  if(wf.procs == NULL) {
    puts("eroooo, falta de memória");
    free(ff.procs);
    free(bf.procs);
  }

  wf.max_size = nproc;

  nf.procs = (t_process*) calloc(1, sizeof(t_process));

  if(nf.procs == NULL) {
    puts("eroooo, falta de memória");
    free(ff.procs);
    free(bf.procs);
    free(wf.procs);
  }

  wf.max_size = nproc;

  memory_allocated = 1;

  puts("Memória alocada com sucesso");
}

/**
 * Cria um processo a ser alocado nas memórias
 */
void criar_processo() {

  /*
    code
  */

}

/**
 * remove um processo nas memorias
 */
void matar_processo() {

  /*
    code
  */

}

/**
 * reinicia as memorias
 */
void reset_processo() {

  /*
    code
  */

}

/**
 * Imprime o processo na tela
 * @param proc Ponteiro para o processo no vetor
 */
void printProcesso(t_process *proc) {
  printf("PID: %8d, TAM: %8d", proc->pid, proc->size);
}

void printSepRow(int qtd) {
  for (int i = 0; i < qtd; i++)
  {
    printf("+------------------------------");
  }
  puts("+");
}

void printMemory(t_process *procs) {
  printSepRow(memory_allocated);
  for (int i = 0; i < memory_allocated; i++)
  {
    printf("| ");
    printProcesso((procs + (sizeof(t_process) * i)));
    printf(" ");
  }
  puts("|");
  printSepRow(memory_allocated);
  puts("\n\n");
}

/**
 * exibe os processos das memorias
 */
void visualizarMemorias() {
  if(!memory_allocated) {
    puts("Memórias não inicializadas, tente novamente");
    return;
  }

  puts("Imprimindo as memórias");
  puts("\n");
  puts("First fit:");
  printMemory(ff.procs);
  puts("Best fit:");
  printMemory(bf.procs);
  puts("Worst fit:");
  printMemory(wf.procs);
  puts("Next fit:");
  printMemory(nf.procs);
}

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
 * Verifica se há memória alocada ou não
 * @return se há ou não memória alocada
 */
int checkAllocated() {
  if(memory_allocated) {
    puts("Memória alocada");

  } else {
    puts("Memória não alocada");
  }
  return memory_allocated;
}

/**
 * Desaloca os segmentos de memória alocada para a simulação
 */
void deallocateMemory() {

  memory_allocated = 0;

  free(ff.procs);
  ff.procs = NULL;

  free(bf.procs);
  bf.procs = NULL;

  free(wf.procs);
  wf.procs = NULL;

  free(nf.procs);
  nf.procs = NULL;

  puts("Memórias desalocadas com sucesso");

}

void reiniciarMemorias() {
  deallocateMemory();
}

void initMemories() {
  nf.max_size = wf.max_size = bf.max_size = ff.max_size = 0;
  nf.procs = wf.procs = bf.procs = ff.procs = NULL;
}

int main() {

  initMemories();

  char option;

  while(1) {
    menu();

    option = getchar();

    clearBuffer(stdin);

    switch(option) {
      case '0':
        alocateMemory();
        break;
      case '1':
        if(!checkAllocated()) {
          break;
        }
        criar_processo();
        break;
      case '2':
        if(!checkAllocated()) {
          break;
        }
        matar_processo();
        break;
      case '3':
        visualizarMemorias();
        break;
      case '4':
        reiniciarMemorias();
        break;
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

  return 0;
}
