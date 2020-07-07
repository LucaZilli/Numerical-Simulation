LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio1.2 : esercizio1.2.o random.o
	g++ -o esercizio1.2 esercizio1.2.o Random.o ${INCS} ${LIBS}


random.o : random.cpp Random.h
	g++ -c -o Random.o random.cpp

esercizio1.2.o : esercizio1.2.cxx Random.h funzioni.h
	g++ -c -o esercizio1.2.o esercizio1.2.cxx ${INCS} ${LIBS}

cleanall :
	rm esercizio1.2
clean :
	rm *.o
