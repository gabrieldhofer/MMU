#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <inttypes.h>


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
 *    Make new Page Table
 * 
 ***********************************************/
void init(){

}

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
void paging_simulation(){
  printf("Paging Simulation\n");
  int q, p, pid;
  printf("Number of processes: \n");
  scanf("%d", &q);
  printf("Number of pages: \n");
  scanf("%d", &p);

  for(int i=0;i<q;i++){
    pid = fork();
    if(pid != 0){
      init();

      // do something
    }
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
 *    Read a line from stdin, do something...
 * 
 ***********************************************/
void REPL(){
  char cwd[PATH_MAX];
  char * buf=NULL;
  size_t leng=64;
  for(;;){
    getcwd(cwd, sizeof(cwd));  
    printf("%s> ", cwd);
    getline(&buf, &leng, stdin);
    printf("%s", buf);
  }
}

/********************************************//**
 * 
 *    Start the REPL 
 * 
 ***********************************************/
void main(){
  REPL();
}







