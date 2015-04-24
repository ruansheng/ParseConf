#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* link max size */
#define MAX_LINE_SIZE 1024

//type
typedef struct ConfLine {
	char key[40];
	char value[40];
	struct ConfLine *next;
} ConfNODE;

ConfNODE *Lines;

/**
 * 过滤#注释
 * @return 返回过滤后的字符串
 */
int str_split(char *str,char *key,char *value){
	int flag=0;
	while(*str!='\0'){
		if(*str=='#'||*str=='\n'){
			break;
		}else if(*str=='\t'){
			str++;
			continue;
		}else{
			if(*str=='='){
				flag=1;
				str++;
				continue;
			}
			if(flag==0){
				*key++=*str++;
			}else if(flag==1){
				*value++=*str++;
			}
		}
	}
	*key='\0';
	*value='\0';

	return 0;
}

/**
 *遍历显示Linked
 */
int displayKeyValue(ConfNODE *head){
	ConfNODE *p=head;
	while(p!=NULL){
		printf("key:%s	value:%s\n",p->key,p->value);
		p=p->next;
	}
	return 0;
}

/**
 * 查找字符内容
 * @return char*
 */
char* getValue(ConfNODE *head,char *key){
	ConfNODE *p=head;
	int flag=1;
	while(p!=NULL){

		if(strcmp(p->key,key)==0){
			flag=0;
			break;
		}
		p=p->next;
	}
	if(flag==0){
		return p->value;
	}else{
		return NULL;
	}
}

/**
 * 解析配置文件
 * return ConfNODE *
 */
ConfNODE * ParseConf(char *filePath){
	ConfNODE *head;
	ConfNODE *p1,*p2;
	p1=p2=(ConfNODE*)malloc(sizeof(ConfNODE));
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
		//获取字符串长度
		int len=strlen(one_line);
		char *key=(char *)malloc(sizeof(char));
		char *value=(char *)malloc(sizeof(char));

		int flag=str_split(one_line,key,value);

		if(strlen(key)>=1&&strlen(value)>=1){
			if(head==NULL){
				strcpy(p1->key,key);
				strcpy(p1->value,value);
				head=p1;
			}else{
				strcpy(p2->key,key);
				strcpy(p2->value,value);
				p1->next=p2;
				p1=p2;
			}
		}

		p2=(ConfNODE*)malloc(sizeof(ConfNODE));
		one_line = (char*)malloc( MAX_LINE_SIZE * sizeof(char) );
	}
	p1->next=NULL;
	fclose(fin);
	return head;
}

/**
 *释放内存
 */
void freeConf(ConfNODE *head){
	ConfNODE *p=head;
	while(p!=NULL){
		free(p);
		p=p->next;
	}
}

