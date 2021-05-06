/********************************************//**
 *     
 *  Author: Gabriel Hofer
 *  Date: May 06, 2021
 *  Course: CSC-458
 * 
 *  Sources: 
 * 
 *    https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-004-computation-structures-spring-2017/c16/c16s1/
 *    https://www.tutorialspoint.com/multithreading-in-c
 *    https://stackoverflow.com/questions/30941549/pthread-barrier-wait-hangs-after-creation-of-all-threads
 *    http://www.qnx.com/developers/docs/qnxcar2/index.jsp?topic=%2Fcom.qnx.doc.neutrino.getting_started%2Ftopic%2Fs1_procs_barriers.html
 * 
 * 
 ***********************************************/


#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


/********************************************//**
 *    For synchronizing threads
 ***********************************************/
pthread_barrier_t   barrier;

/********************************************//**
 *    The user decides the number of processes
 *    to run in the simulation.
 *    For our implementation, a thread will 
 *    represent a process in the simulation
 ***********************************************/
uint32_t NUM_THREADS;

/********************************************//**
 *    8 bits in the page offset 
 *    4 bits for the virtual page number
 *    3 bits for the physical page number
 ***********************************************/
const int v = 4;
const int m = 3;
const int p = 8;

/********************************************//**
 *    Page Replacement Algorithm: 
 *    Least Frequently Used (LFU)
 ***********************************************/
int SelectLRUPage(int * pageFrequency){ 
  // change to SelectLFUPage()
  int idx=0;
  int mn=100000;
  printf("\tpageFrequency[]: ");
  for(int i=0;i<16;i++){
    printf("%d ",pageFrequency[i]);
    if(pageFrequency[i]<mn){
      mn = pageFrequency[i];
      idx = i;
    }
  }
  printf("\n");
  pageFrequency[idx] = 1;
  printf("\tLeast Frequency Page: %d\n", idx);
  return idx;
}

void ReadPage(int a, int b){ }
void WritePage(int a, int b){ }

/********************************************//**
 *    Physical Memory (Array)
 *    All threads share this physical memory
 ***********************************************/
int PhysicalMemory[2048];

/********************************************//**
 *    Secondary Memory Storage (Disk)
 ***********************************************/
int DiskAdr[16];

/********************************************//**
 *    Handle a missing page
 ***********************************************/
void PageFault(int VPageNo, char * R, char * D, int * PPN, int * pageFrequency){
  printf("\tPage Fault occurred\n");
  int i;
  i = SelectLRUPage(pageFrequency);
  if(D[i] == 1)
    WritePage(DiskAdr[i],PPN[i]);
  R[i] = 0;

  PPN[VPageNo] = PPN[i];
  ReadPage(DiskAdr[VPageNo], PPN[i]);
  R[VPageNo] = 1;
  D[VPageNo] = 1;
}

/********************************************//**
 *    Virtual Address --> Physical Address
 *    @return physical address
 ***********************************************/
int VtoP(int Vaddr, char * R, char * D, int * PPN, int * pageFrequency){
  int VPageNo = Vaddr >> p;
  int PO = Vaddr & ((1 << p) - 1);

  pageFrequency[VPageNo] += 1;
  if(R[VPageNo] == 0)
    PageFault(VPageNo, R, D, PPN, pageFrequency);

  return (PPN[VPageNo] << p) | PO;
}


/********************************************//**
 *    1. Allocate new Page Table for thread
 *    2. Access virtual memory by calling VtoP()
 ***********************************************/
void * makeTableAndRequests(void *threadid){
  long tid = (long)threadid;
  printf("Thread ID, %ld\n", tid);

  /* Thread allocates its own page table */
  /*  Allocate 2^v pages in page table */
  char * R = malloc( (1<<v) * sizeof(char));
  char * D = malloc( (1<<v) * sizeof(char));
  int * PPN = malloc( (1<<v) * sizeof(int));
  int * pageFrequency = malloc( (1<<v) * sizeof(int));

  /* Access virtual memory multiple times */
  for(int i=0;i<16;i++){

    /*  produce random address in virtual memory */
    int r = rand() % (1<<(v+p));
    printf("Thread %ld requesting address: %d\n", tid, r);

    /*  request access to virtual memory location */
    VtoP(r, R, D, PPN, pageFrequency);
  }

  pthread_barrier_wait(&barrier);
  pthread_exit(NULL);
}

/********************************************//**
 *    Each process gets its own page table
 ***********************************************/
void separatePageTables(){
  printf("------------  Separate Page Tables  -------------\n");

  pthread_barrier_init (&barrier, NULL, NUM_THREADS+1 );

  pthread_t threads[NUM_THREADS];
  int rc;
  for(int i=0; i<NUM_THREADS; i++){
    rc = pthread_create( &threads[i], NULL, makeTableAndRequests, (void *)i);
    if(rc){
      fprintf( stderr, "Error: unable to create thread, %d\n", rc);
      exit(-1);
    }
  }

  pthread_barrier_wait( &barrier );
  for(int i=0; i<NUM_THREADS; i++)
    pthread_join(threads[i], NULL);
  pthread_exit(NULL);
}

/********************************************//**
 *    All processes share the same page table
 ***********************************************/
void invertedPageTables(){
  printf("------------  Inverted Page Tables  -------------\n");

  pthread_barrier_init (&barrier, NULL, NUM_THREADS+1 );

  pthread_t threads[NUM_THREADS];
  int rc;
  for(int i=0; i<NUM_THREADS; i++){
    rc = pthread_create( &threads[i], NULL, makeTableAndRequests, (void *)i);
    if(rc){
      fprintf( stderr, "Error: unable to create thread, %d\n", rc);
      exit(-1);
    }
  }

  pthread_barrier_wait( &barrier );
  for(int i=0; i<NUM_THREADS; i++)
    pthread_join(threads[i], NULL);
  pthread_exit(NULL);
}

/********************************************//**
 *    Simulation Menu  
 ***********************************************/
void simulation(){
  printf("--------------  Paging Simulation  --------------\n");

  /* Ask user for number of processes and number of pages */
  int q, p, pid;
  printf("\nNumber of processes: ");
  scanf("%d", &NUM_THREADS);

  /* Ask user which type of page table to simulate */
  int option;
  printf("Choose page table simulation type: \n");
  printf("\n\t1. Separate Page Tables\n");
  printf("\t2. Inverted Page Table\n\n");
  printf("Option: ");
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
 *    Two commands exist in the shell: 
 * 
 *            dash> simulation
 *            dash> exit
 ***********************************************/
void REPL(){
  char cwd[PATH_MAX];
  char * buf=NULL;
  size_t leng=64;
  char str[] = "simulation\n\0exit\n\0";
  for(;;){
    getcwd(cwd, sizeof(cwd));  
    printf("%s> ", cwd);
    getline(&buf, &leng, stdin);
    if(!strcmp(buf, str)) simulation();
    else if(!strcmp(buf, &str[12])) return;
  }
}

/********************************************//**
 *    Start the diagnostic shell
 ***********************************************/
void main(){
  REPL();
}


