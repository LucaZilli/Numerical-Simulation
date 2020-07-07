#include "Integrale.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

//codice integratore metodo media
double Integrale::IntegraleMultidimAVE(int dim, const vettore& inf, const vettore& sup, FunzioneScalareBase *f, int punti){
    
    m_dim=dim;
    double yf=0.;//variabile locale a cui assegno il valore della funzione ad ogni ciclo for
    double contf=0.;//contatore che utilizzo per segnare la somma dei valori della funzione
    
    
    //copio i vettori dati come parametro per non modificarli
    vettore m_inf(m_dim);
    vettore m_sup(m_dim);
       
    for(int k=0; k<m_dim ;k++){
    
        m_inf.setcomponent(k, inf.getcomponent(k) );
        m_sup.setcomponent(k, sup.getcomponent(k) );
           
    }
    
    //vettore di variabili uniformemente distribuite nell'intervallo di integrazione
    vettore x(m_dim);
    
    for(int k=0 ; k < punti; k++){
        
        //a ogni ciclo k sommo il valore della funzione a contf
        
        for(int r=0 ; r < m_dim ; r++){
            
            //variabile casuale distribuita tra 0 e 1
            double s=m_myRand->Rand();
        
            //riempo ogni posizione di una variabile compresa tra gli estremi noti
            x.setcomponent( r, m_inf.getcomponent(r) + s* ( m_sup.getcomponent(r) - m_inf.getcomponent(r) ) );
        
        }
        
        //valuto la funzione nel vettore di variabili distribuite uniformemente tra gli estremi
        yf=f->Eval(m_dim, x);
    
        contf = contf + yf;
    

    }
   
    //valuto l'intervallo (A) d'integrazione generalizzato in n dimensioni
    double A=1.;
    
    for(int k=0 ; k < m_dim; k++){
        
        A = A*( sup.getcomponent(k) - inf.getcomponent(k) );
        
    }
  
    //restituisco la stima dell'integrale fatta con il metodo della media
    return A*contf/(punti);
    
}











double Integrale::IntegraleMultidim_imp(int dim, const vettore& inf, const vettore& sup, FunzioneScalareBase *f, int punti){
    
    m_dim=dim;
    double yf=0.;//variabile locale a cui assegno il valore della funzione ad ogni ciclo for
    double contf=0.;//contatore che utilizzo per segnare la somma dei valori della funzione
    
    
    //copio i vettori dati come parametro per non modificarli
    vettore m_inf(m_dim);
    vettore m_sup(m_dim);
       
    for(int k=0; k<m_dim ;k++){
    
        m_inf.setcomponent(k, inf.getcomponent(k) );
        m_sup.setcomponent(k, sup.getcomponent(k) );
           
    }
    
    //vettore di variabili uniformemente distribuite nell'intervallo di integrazione
    vettore x(m_dim);
    
    for(int k=0 ; k < punti; k++){
        
        //a ogni ciclo k sommo il valore della funzione a contf
        
        for(int r=0 ; r < m_dim ; r++){
            
            //variabile casuale distribuita tra 0 e 1
            double s=1-sqrt(1-m_myRand->Rand());
        
            //riempo ogni posizione di una variabile compresa tra gli estremi noti
            x.setcomponent( r, m_inf.getcomponent(r) + s* ( m_sup.getcomponent(r) - m_inf.getcomponent(r) ) );
        
        }
        
        //valuto la funzione nel vettore di variabili distribuite uniformemente tra gli estremi
        yf=f->Eval_imp(m_dim, x);
    
        contf = contf + yf;
    

    }
   
    //valuto l'intervallo (A) d'integrazione generalizzato in n dimensioni
    double A=1.;
    
    for(int k=0 ; k < m_dim; k++){
        
        A = A*( sup.getcomponent(k) - inf.getcomponent(k) );
        
    }
  
    //restituisco la stima dell'integrale fatta con il metodo della media
    return A*contf/(punti);
    
}


