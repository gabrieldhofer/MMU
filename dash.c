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
 *    Physical Memory (Array)
 *    All threads share this physical memory
 ***********************************************/
int PHYSICAL_MEMORY[2048];

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
 *    8 bits in the offset 
 *    per the example in the
 *    MIT OpenCourseWare slides
 ***********************************************/
const int p = 8;


int SelectLRUPage(){ }
void ReadPage(int a, int b){ }
void WritePage(int a, int b){ }


/********************************************//**
 *    Secondary Memory Storage (Disk)
 ***********************************************/
int DiskAdr[16];

/********************************************//**
 *    Handle a missing page
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
 *    1. Allocate new Page Table for thread
 *    2. Access virtual memory by calling VtoP()
 *
 ***********************************************/
void * makeTableAndRequests(void *threadid){
  long tid = (long)threadid;
  printf("thread ID, %ld\n", tid);

  /* thread allocates its own page table */
  char * R = malloc(16);
  char * D = malloc(16);
  int * PPN = malloc(16);

  /* access virtual memory multiple times */
  for(int i=0;i<8;i++){
    // random access 
    int r = rand() % 16;

  }

  pthread_barrier_wait(&barrier);
  pthread_exit(NULL);
}

/********************************************//**
 *
 *    Each process gets its own page table
 *
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
 *
 *    All processes share same page table
 *
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
 *
 *              THE SIMULATION
 *
 ***********************************************/
void simulation(){
  printf("--------------  Paging Simulation  --------------\n");

  int q, p, pid;
  printf("\nNumber of processes: ");
  scanf("%d", &NUM_THREADS);
  printf("\nNumber of pages: ");
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
 *    Two commands exists in the shell: 
 * 
 *            dash> simulation
 *            dash> exit
 * 
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
 * 
 *    Start the shell
 * 
 ***********************************************/
void main(){
  REPL();
}


