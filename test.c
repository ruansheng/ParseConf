/*
 * test.c
 *
 *  Created on: Apr 8, 2015
 *      Author: root
 */
#include <stdio.h>
#include "ParseConf.c"

/**
 * test main
 */
int main(){
	char *filePath="./config.conf";

	Lines=ParseConf(filePath);
	displayKeyValue(Lines);
	char *value=getValue(Lines,"b");
	printf("%s\n",value);
	freeConf(Lines);
//	while(Lines!=NULL){
//		printf("%s=%s\n",Lines->key,Lines->value);
//		Lines=Lines->next;
//	}
}


