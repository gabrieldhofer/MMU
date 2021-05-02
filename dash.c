#include <stdio.h>

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
