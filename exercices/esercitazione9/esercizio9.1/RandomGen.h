#ifndef __RANDOMGEN_H__
#define __RANDOMGEN_H__


//classe generatrice di numeri casuali implementata nel corso di calcolo2
class RandomGen {

public:

	RandomGen(unsigned int);

	void SetA(unsigned int a) {m_a=a;};
	void SetC(unsigned int c) {m_c=c;};
	void SetM(unsigned int m) {m_m=m;};

	double Rand();
	double Unif(double xmin, double xmax);
	double Exp(double mean);
	double Gaus(double mean, double sigma);
	double GausAR(double mean, double sigma , double xmin, double xmax);

private:
	
	unsigned int m_a, m_c, m_m;
	unsigned int m_seed;

};

#endif
