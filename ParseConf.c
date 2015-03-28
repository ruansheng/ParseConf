#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024

struct Line {
	char *key;
	char *value;
	struct Line *next;
};

typedef struct Line NODE;

NODE *Lines;

NODE * ParseConf(char *filePath){
	NODE *head;
	NODE *p1,*p2;
	p1=p2=(NODE*)malloc(sizeof(NODE));
	if(p1==NULL||p2==NULL){
		return NULL;
	}
	FILE *fin;
	char *one_line;

	if((fin = fopen(filePath, "r"))==NULL){  
		printf("can not open file \"%s\" !\n", filePath);
		return NULL;
	}
	head=NULL;
	one_line = (char*)malloc( MAX_LINE_SIZE * sizeof(char) );
	while( fgets(one_line, MAX_LINE_SIZE, fin) != NULL ){
		if(head==NULL){
			p1->key=one_line;
			head=p1;
		}else{
			p2->key=one_line;
			p1->next=p2;
			p1=p2;
		}
		p2=(NODE*)malloc(sizeof(NODE));
		one_line = (char*)malloc( MAX_LINE_SIZE * sizeof(char) );
	}
	p1->next=NULL;
	fclose(fin);
	return head;
}

int main(){
	char *filePath="./config.conf";

	Lines=ParseConf(filePath);
	while(Lines!=NULL){
		printf("%s",Lines->key);
		Lines=Lines->next;
	}

}
