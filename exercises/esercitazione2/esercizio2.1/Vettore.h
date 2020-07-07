#ifndef __vettore_h__
#define __vettore_h__

#include <iostream>

using namespace std;

class vettore{

public:

vettore();
vettore(int N);
~vettore();

int getN()const { return m_N;}
void setcomponent(int,double);
double getcomponent(int) const;
void scambia (int, int);
vettore(const vettore&);
vettore& operator=(const vettore&);


private:

int m_N;

double* m_V;

};

#endif
