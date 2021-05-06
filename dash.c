#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/********************************************//**
 * 
 *    The user decides the number of processes
 *    to run in the simulation.
 * 
 *    For our implementation, a thread will 
 *    represent a process in the simulation
 * 
 ***********************************************/
uint32_t NUM_THREADS;


/********************************************//**
 * 
 *    p is the number address bits used 
 *    for the page offset
 * 
 ***********************************************/
const int p = 12;

/********************************************//**
 * 
 *    R - resident bit
 *    D - dirty bit
 *    PPN - physical page number
 * 
 ***********************************************/
char R[16];
char D[16];
char PPN[16];

int SelectLRUPage(){ }
void ReadPage(int a, int b){ }
void WritePage(int a, int b){ }
int DiskAdr[16];

/********************************************//**
 * 
 *    Handle a missing page
 * 
 ***********************************************/
void PageFault(int VPageNo){
  int i;

  i = SelectLRUPage();
  if(D[i] == 1)
    WritePage(DiskAdr[i],PPN[i]);
  R[i] = 0;

  PPN[VPageNo] = PPN[i];
  ReadPage(DiskAdr[VPageNo], PPN[i]);
  R[VPageNo] = 1;
  D[VPageNo] = 1;
}

/********************************************//**
 *              
 *    Virtual Address --> Physical Address
 *              
 *    @return physical address
 *              
 ***********************************************/
int VtoP(int Vaddr){
  int VPageNo = Vaddr >> p;
  int PO = Vaddr & ((1 << p) - 1);

  if(R[VPageNo] == 0)
    PageFault(VPageNo);
  return (PPN[VPageNo] << p) | PO;
}


/********************************************//**
 *
 *
 *
 ***********************************************/
void *makeRequest(void *threadid){
  long tid = (long)threadid;
  printf("thread ID, %ld\n", tid);
}

/********************************************//**
 *
 *    Each process gets its own page table
 *
 ***********************************************/
void separatePageTables(){
  pthread_t threads[NUM_THREADS];
  int rc;
  for(int i=0; i<NUM_THREADS; i++){
    rc = pthread_create(&threads[i], NULL, makeRequest, (void *)i);
    if(rc){
      fprintf( stderr, "Error: unable to create thread, %d\n", rc);
      exit(-1);
    }
  }
}

/********************************************//**
 *
 *    All processes share same page table
 *
 ***********************************************/
void invertedPageTable(){


}

/********************************************//**
 *
 *    THE SIMULATION
 *
 ***********************************************/
void simulation(){
  printf("Paging Simulation\n");
  int q, p, pid;
  printf("Number of processes: \n");
  scanf("%d", &NUM_THREADS);
  printf("Number of pages: \n");
  scanf("%d", &p);

  int option;
  printf("\n\t1. Separate Page Tables\n");
  printf("\t2. Hashed Page Table\n\n");
  scanf("%d", &option);

  switch(option){
    case 1: 
      separatePageTables();      
      break;
    case 2: 
      invertedPageTables();
      break;
    default:
      printf("Invalid Option\n");
      break;
  }

}

/********************************************//**
 *
 *
 *
 ***********************************************/
void page_replacement_simulation(){
  printf("Page Replacement Simulation\n");

}

/********************************************//**
 * 
 *    Only one command exists in the shell: 
 * 
 *            dash> simulation
 * 
 ***********************************************/
void REPL(){
  char cwd[PATH_MAX];
  char * buf=NULL;
  size_t leng=64;
  for(;;){

    simulation();

    getcwd(cwd, sizeof(cwd));  
    printf("%s> ", cwd);
    getline(&buf, &leng, stdin);
    printf("%s", buf);
  }
}

/********************************************//**
 * 
 *    Start the shell
 * 
 ***********************************************/
void main(){
  REPL();
}


