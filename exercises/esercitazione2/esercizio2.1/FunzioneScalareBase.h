#ifndef _FunzioneScalareBase_h__
#define _FunzioneScalareBase_h__
#include <cmath>
#include "Vettore.h"




using namespace std;

class FunzioneScalareBase {
    
    public:
        virtual double Eval(const int, const vettore&) const = 0;
        virtual double Eval_imp(const int, const vettore&) const = 0;
    
};




class Funzione : public FunzioneScalareBase {
    
    public:
    
        double Eval(const int, const vettore&) const;
        double Eval_imp(const int, const vettore&) const;
    
    private:
    
        float m_a;
    
    
};

#endif



