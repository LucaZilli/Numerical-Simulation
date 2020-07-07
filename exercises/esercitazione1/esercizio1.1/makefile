esercizio1.1 : esercizio1.1.o random.o
	g++ -o esercizio1.1 esercizio1.1.o random.o


esercizio1.1.o : esercizio1.1.cxx funzioni.h random.h
	g++ -c -o esercizio1.1.o esercizio1.1.cxx 

random.o : random.cxx random.h
	g++ -c -o random.o random.cxx 

clean:
	rm esercizio1.1

