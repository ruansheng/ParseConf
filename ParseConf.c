#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

struct Line {
	char *key;
	char *value;
	struct Line *next;
};

typedef struct Line NODE;

NODE *Lines;

/**
 * 过滤#注释
 * @return 返回过滤后的字符串
 */
char * filterSharp(char *str,int len){
	char tmp[len];
	memset(tmp,0,len);
	int i=0;
	while(*str!='\0'){
		if(*str=='#'||*str=='\n'){
			break;
		}else if(*str=='\t'){
			str++;
			continue;
		}else{
			tmp[i]=*str;
			i++;
			str++;
		}
	}
	return tmp;
}

/**
 * 查找某个字符在字符串中的位置
 * @return index
 * index=0 没有找到
 * index>0 找到,并且位置是index-1
 */
int getIndex(char *str,char aim){
	int index;
	int i=1;
	while(*str!='\0'){
		if(*str==aim){
			index=i;
			break;
		}else{
			i++;
		}
		str++;
	}
	return index;
}


char* join(char *s1, char *s2)  {
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    if (result == NULL) exit (1);

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

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
		char *key=(char *)malloc(sizeof(char));
		//获取字符串长度
		int len=strlen(one_line);
		//过滤#
		char *tmp=filterSharp(one_line,len);
//		printf("%s\n",tmp);
		//找到=位置
		int index=getIndex(one_line,'=');

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
