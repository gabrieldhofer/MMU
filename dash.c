#include <stdio.h>

/********************************************//**
 * p is the number address bits used 
 * for the page offset
 ***********************************************/
const int p = 12;


/********************************************//**
 * R - resident bit
 * D - dirty bit
 * PPN - physical page number
 ***********************************************/
char R[16];
char D[16];
char PPN[16];

int SelectLRUPage(){ }
void ReadPage(int a, int b){ }
void WritePage(int a, int b){ }
int DiskAdr[16];

/********************************************//**
 * Handle a missing page
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
 *        Vaddr --> Paddr
 * @return physical address
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
 ***********************************************/
void paging(){
  int q;
  printf("Number of processes: \n");
  scanf("%d", &q);
  printf("Number of pages: \n");
}


/********************************************//**
 * Read a line from stdin, do something...
 ***********************************************/
void REPL(){
  char * buf=NULL;
  size_t leng=64;
  for(;;){
    getline(&buf, &leng, stdin);
    printf("%s", buf);
  }
}

/********************************************//**
 * Start the REPL 
 ***********************************************/
void main(){
  REPL();
}

