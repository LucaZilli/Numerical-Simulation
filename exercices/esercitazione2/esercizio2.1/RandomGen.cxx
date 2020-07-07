#include "RandomGen.h"
#include <cmath>
#include <iostream>

using namespace std;


RandomGen::RandomGen(unsigned int seed){

	m_seed=seed;
	SetA(1664525);
	SetC(1013904223);
	SetM(pow(2,31)); 

}

double RandomGen::Rand(){
       
	m_seed= (m_a*m_seed+m_c)%m_m;

	return (double)m_seed/(m_m-1); 

}

double RandomGen::Unif(double xmin, double xmax){

	return xmin+(xmax-xmin)*Rand();

}

double RandomGen::Exp(double mean){

	
	return -1/mean*log(1-Rand());

}


double RandomGen::Gaus(double mean, double sigma){
	double s=Rand();
	double t=Rand();
	double x=sqrt(-2.*log(s))*cos(2.*M_PI*t);
	return mean+x*sigma;
}


double RandomGen::GausAR(double mean, double sigma, double xmin, double xmax){
    
    if(xmin > xmax){
        
        double ric=xmin;
        xmin=xmax;
        xmax=ric;
        
    }
    
    double s=Rand();
    double t=Rand();
    double x=xmin + (xmax-xmin)*s;
    double z=1/(sqrt(2*M_PI)*sigma)*exp((-0.5)*((x-mean)/sigma)*((x-mean)/sigma));
    double y=t*1/(sqrt(2*M_PI)*sigma);

    if(y < z)
        return x;
    else
        return GausAR( mean, sigma, xmin, xmax);
}




