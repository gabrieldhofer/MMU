#include <stdio.h>

/********************************************//**
 *  p is the number of bits in a page
 ***********************************************/
const int p = 12;

/********************************************//**
 * @param R - resident bit
 * @param D - dirty bit
 * @param PPN - physical page number
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
 * @return physical address
 ***********************************************/
int VtoP(int Vaddr){
  int VPageNo = Vaddr >> p;
  int PO = Vaddr & ((1 << p) - 1);

  if(R[VPageNo] == 0)
    PageFault(VPageNo);
  return (PPN[VPageNo] << p) | PO;
}



void REPL(){
  char * buf=NULL;
  size_t leng=64;
  for(;;){
    getline(&buf, &leng, stdin);
    printf("%s", buf);
  }
}

void main(){
  REPL();
}

