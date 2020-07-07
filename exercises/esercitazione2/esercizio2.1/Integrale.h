#ifndef __integrale__h__
#define __integrale__h__

#include "FunzioneScalareBase.h"
#include "RandomGen.h"


class Integrale {

public:

    //constructor integrator
    Integrale(unsigned int seed){m_myRand=new RandomGen(seed);};
    ~Integrale(){;};
    
    double IntegraleMultidimAVE(int dim, const vettore& inf, const vettore& sup, FunzioneScalareBase *f, int punti );
    double IntegraleMultidim_imp(int dim, const vettore& inf, const vettore& sup, FunzioneScalareBase *f, int punti);
    
private:

    RandomGen *m_myRand;
    const FunzioneScalareBase* m_f;
    int m_dim;
    
};

#endif
