ParseConf:ParseConf.o
	gcc -o ParseConf ParseConf.o
ParseConf.o:ParseConf.c
	gcc -o ParseConf.o -c ParseConf.c
clean:
	rm ParseConf ParseConf.o


