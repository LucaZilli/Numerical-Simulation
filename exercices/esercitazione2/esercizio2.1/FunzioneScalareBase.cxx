#include "FunzioneScalareBase.h"


double Funzione::Eval(const int dim, const vettore& v) const {
    
    return M_PI/2*cos(M_PI*v.getcomponent(0)/2);
}


double Funzione::Eval_imp(const int dim, const vettore& v) const {
    
    return ( M_PI/2*cos(M_PI*v.getcomponent(0)/2) )/(2-2*v.getcomponent(0));
}



//3/2(1-x^2)
