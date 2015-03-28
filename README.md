#ParseConf
C language parse config file
==============
---
##Examples
```
#include <stdio.h>
#include "ParseConf.c"
int main(){
	char *filePath="./config.conf";
	Lines=ParseConf(filePath);
	return 0;
}
```
