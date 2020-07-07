#ifndef _FunzioneScalareBase_h__
#define _FunzioneScalareBase_h__
#include <cmath>
#include <vector>
#include <iostream>


//classe usata per implementare la funzione che passo all'integrale

using namespace std;

class FunzioneScalareBase {
    
    public:
        virtual double Eval_100( const vector<double>&) const = 0;
        virtual double Eval_210( const vector<double>&) const = 0;
    
};




class Funzione : public FunzioneScalareBase {
    
    public:
    
        double Eval_100(const vector<double>&) const;
        double Eval_210( const vector<double>&) const;
        void set_Bohr_radius(double);
    
    private:
        double m_a0; //reference: wikipedia
    
};




#endif



