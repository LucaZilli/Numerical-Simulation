esercizio5.1 : esercizio5.1.o FunzioneScalareBase.o random.o
	g++ -o esercizio5.1 esercizio5.1.o FunzioneScalareBase.o random.o
 
random.o : random.cxx random.h
	g++ -c -o random.o random.cxx

FunzioneScalareBase.o : FunzioneScalareBase.cxx FunzioneScalareBase.h
	g++ -c -o FunzioneScalareBase.o FunzioneScalareBase.cxx

esercizio5.1.o : esercizio5.1.cxx FunzioneScalareBase.h funzioni.h random.h
	g++ -c -o esercizio5.1.o esercizio5.1.cxx

cleanall :
	rm esercizio5.1
clean :
	rm *.o