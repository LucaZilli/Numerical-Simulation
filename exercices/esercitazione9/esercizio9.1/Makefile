LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

esercizio9.1 : esercizio9.1.o GeneticAlgorithm.o RandomGen.o 
	g++ -o esercizio9.1 esercizio9.1.o GeneticAlgorithm.o RandomGen.o ${INCS} ${LIBS}

 
GeneticAlgorithm.o : GeneticAlgorithm.cxx GeneticAlgorithm.h
	g++ -c -o GeneticAlgorithm.o GeneticAlgorithm.cxx ${INCS} ${LIBS}

RandomGen.o : RandomGen.cxx RandomGen.h
	g++ -c -o RandomGen.o RandomGen.cxx


esercizio9.1.o : esercizio9.1.cxx GeneticAlgorithm.h RandomGen.h funzioni.h
	g++ -c -o esercizio9.1.o esercizio9.1.cxx ${INCS} ${LIBS}

cleanall :
	rm esercizio9.1
clean :
	rm *.o