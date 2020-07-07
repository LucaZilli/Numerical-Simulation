
esercizio3.1 : esercizio3.1.o random.o
	g++ -o esercizio3.1 esercizio3.1.o Random.o 


random.o : random.cpp Random.h
	g++ -c -o Random.o random.cpp

esercizio3.1.o : esercizio3.1.cxx Random.h funzioni.h
	g++ -c -o esercizio3.1.o esercizio3.1.cxx 

cleanall :
	rm esercizio3.1
clean :
	rm *.o
