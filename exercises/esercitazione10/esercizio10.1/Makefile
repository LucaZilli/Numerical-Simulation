LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio10.1 : esercizio10.1.o SimulatedAnnealing.o
	g++ -o esercizio10.1 esercizio10.1.o SimulatedAnnealing.o ${INCS} ${LIBS}

 
SimulatedAnnealing.o : SimulatedAnnealing.cxx SimulatedAnnealing.h
	g++ -c -o SimulatedAnnealing.o SimulatedAnnealing.cxx ${INCS} ${LIBS}


esercizio10.1.o : esercizio10.1.cxx SimulatedAnnealing.h funzioni.h
	g++ -c -o esercizio10.1.o esercizio10.1.cxx ${INCS} ${LIBS}

cleanall :
	rm esercizio10.1
clean :
	rm *.o