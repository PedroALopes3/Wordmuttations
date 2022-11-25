wrdmttns: Main.o Dicionario.o Arestas.o Dijkstra.o
    
	gcc -Wall -std=c99 -O3 -o wrdmttns Main.o Dicionario.o Arestas.o Dijkstra.o

Main.o: Main.c Dicionario.h Arestas.h Dijkstra.h
    
	gcc -Wall -std=c99 -O3 -c Main.c

Dicionario.o: Dicionario.c Dicionario.h 
    
	gcc -Wall -std=c99 -O3 -c Dicionario.c
	
Dijkstra.o: Dijkstra.c Dijkstra.h Arestas.h

	gcc -Wall -std=c99 -O3 -c Dijkstra.c 

Arestas.o: Arestas.c Arestas.h
    
	gcc -Wall -std=c99 -O3 -c Arestas.c





