
shell: main.o commandParser.o commands.o fileProcessing.o handler.o variables.o environment.o
	gcc main.o commandParser.o commands.o fileProcessing.o handler.o variables.o environment.o -o shell

main.o: main.c
	gcc -c main.c

commandParser.o: commandParser.c commandParser.h
	gcc -c commandParser.c

commands.o: commands.c commands.h
	gcc -c commands.c

fileProcessing.o: fileProcessing.c fileProcessing.h
	gcc -c fileProcessing.c

handler.o: handler.c handler.h
	gcc -c handler.c

variables.o: variables.c variables.h
	gcc -c variables.c

environment.o: environment.c environment.h
	gcc -c environment.c

clean:
	rm *.o shell
