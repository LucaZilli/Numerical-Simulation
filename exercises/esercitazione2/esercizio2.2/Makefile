esercizio2.2 : esercizio2.2.o random.o
	g++ -o esercizio2.2 esercizio2.2.o Random.o 


random.o : random.cpp Random.h
	g++ -c -o Random.o random.cpp

esercizio2.2.o : esercizio2.2.cxx Random.h funzioni.h
	g++ -c -o esercizio2.2.o esercizio2.2.cxx 

cleanall :
	rm esercizio2.2
clean :
	rm *.o
