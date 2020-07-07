esercizio8.1 : esercizio8.1.o FunzioneScalareBase.o random.o
	g++ -o esercizio8.1 esercizio8.1.o FunzioneScalareBase.o random.o
 
random.o : random.cxx random.h
	g++ -c -o random.o random.cxx

FunzioneScalareBase.o : FunzioneScalareBase.cxx FunzioneScalareBase.h
	g++ -c -o FunzioneScalareBase.o FunzioneScalareBase.cxx

esercizio8.1.o : esercizio8.1.cxx FunzioneScalareBase.h funzioni.h random.h
	g++ -c -o esercizio8.1.o esercizio8.1.cxx

cleanall :
	rm esercizio8.1xs
clean :
	rm *.o