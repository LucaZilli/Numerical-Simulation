
esercizio1.3 : esercizio1.3.o random.o
	g++ -o esercizio1.3 esercizio1.3.o Random.o 


random.o : random.cpp Random.h
	g++ -c -o Random.o random.cpp

esercizio1.3.o : esercizio1.3.cxx Random.h funzioni.h
	g++ -c -o esercizio1.3.o esercizio1.3.cxx 

cleanall :
	rm esercizio1.3
clean :
	rm *.o
