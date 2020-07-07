
CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio10.2 : esercizio10.2.o random.o GeneticAlgorithm.o
	mpicxx random.o GeneticAlgorithm.o esercizio10.2.o -o esercizio10.2 

esercizio10.2.o : esercizio10.2.cpp GeneticAlgorithm.h random.h funzioni.h
	mpicxx -c esercizio10.2.cpp -o esercizio10.2.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

GeneticAlgorithm.o : GeneticAlgorithm.cpp GeneticAlgorithm.h
	$(CC) -c GeneticAlgorithm.cpp -o GeneticAlgorithm.o $(CFLAGS)


clean :
	rm *.o esercizio10.2 seed.out