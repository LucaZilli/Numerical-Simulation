esercizio2.1 : esercizio2.1.o Integrale.o FunzioneScalareBase.o RandomGen.o Vettore.o 
	g++ -o esercizio2.1 esercizio2.1.o Integrale.o FunzioneScalareBase.o RandomGen.o Vettore.o 

 
Integrale.o : Integrale.cxx Integrale.h
	g++ -c -o Integrale.o Integrale.cxx 

RandomGen.o : RandomGen.cxx RandomGen.h
	g++ -c -o RandomGen.o RandomGen.cxx

FunzioneScalareBase.o : FunzioneScalareBase.cxx FunzioneScalareBase.h
	g++ -c -o FunzioneScalareBase.o FunzioneScalareBase.cxx


Vettore.o : Vettore.cxx Vettore.h
	g++ -c -o Vettore.o Vettore.cxx

esercizio2.1.o : esercizio2.1.cxx FunzioneScalareBase.h Integrale.h Vettore.h funzioni.h
	g++ -c -o esercizio2.1.o esercizio2.1.cxx

cleanall :
	rm esercizio2.1
clean :
	rm *.o