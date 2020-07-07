#ifndef _FunzioneScalareBase_h__
#define _FunzioneScalareBase_h__
#include <cmath>
#include <vector>
#include <iostream>


//classe usata per implementare la funzione che passo all'integrale

using namespace std;

class FunzioneScalareBase {
    
    public:
        virtual double EvalP( const double) const = 0;
        virtual double EvalF( const double) const = 0;

};




class Funzione : public FunzioneScalareBase {
    
    public:
    
        double EvalP(const double) const;
        double EvalF(const double) const;
        void set_mean(double);
        void set_sigma2(double);
    
    private:
        double m_mu;
        double m_sigma2;
    
};




#endif



