#include <cstdlib>
#include "Vettore.h"
#include <assert.h>



vettore::vettore() {
m_N = 0;
m_V = NULL;
}

vettore::vettore(int N) {
assert((N>=0) && "errore:deve essere positivo");
if(N<0){cerr << "deve essere positivo" << endl;
exit(4);
}else{ 
m_N = N;
m_V = new double[N];
for(int k =0 ; k<N ; k++ ) m_V[k]=0;
}}


vettore::~vettore() {
delete[] m_V;
}



void vettore::setcomponent(int N, double X){
assert((N<m_N) && "sbagliato");
if(N>m_N){
cerr << " N troppo grande " << endl;
exit(5);
}
else{
m_V[N]=X;
}
}


double vettore::getcomponent(int i) const {
/*assert((i<m_N) && "sbagliato");
if(i>m_N){
cerr<<" i troppo grande "<<endl;
exit(6);
}
else{*/
return m_V[i];
}


void vettore::scambia(int N,int M){
assert((N < m_N && M < m_N) && "sbagliato");
if(N > m_N || M > m_N){
cerr<<" indici troppo grande "<<endl;
exit(7);
}
else{
double x = m_V[N];
m_V[N]=m_V[M];
m_V[M]=x;
}}


vettore::vettore(const vettore& v){
m_N=v.getN();
m_V=new double[m_N];
for(int k=0 ; k<m_N ; k++ ) m_V[k]=v.getcomponent(k);
}


vettore& vettore::operator=(const vettore& v) {
m_N = v.getN();
if(m_V) delete [] m_V;
m_V = new double[m_N];
for(int i=0; i < m_N ; i++) m_V[i] = v.getcomponent(i);
return *this;
}













