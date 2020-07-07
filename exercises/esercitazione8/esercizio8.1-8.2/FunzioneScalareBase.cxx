#include "FunzioneScalareBase.h"


double Funzione::EvalP( const double x) const {
   
    double psi_T = exp( - (x-m_mu)*(x-m_mu) / (2.*m_sigma2) ) + exp( - (x+m_mu)*(x+m_mu) / (2.*m_sigma2) ) ;
    
    return psi_T*psi_T;
}
    
double Funzione::EvalF( const double x) const {
   
    double psi_T = exp( - (x-m_mu)*(x-m_mu) / (2.*m_sigma2) ) + exp( - (x+m_mu)*(x+m_mu) / (2.*m_sigma2) ) ;
    
    //double D2_psi_T = -exp( - (x+m_mu)*(x+m_mu) / (2.*m_sigma2) ) * ( exp(2.*m_mu*x/m_sigma2) * ( (m_mu-x)*(m_mu-x) - m_sigma2 ) + (m_mu+x)*(m_mu+x) - m_sigma2 ) / m_sigma2*m_sigma2 ;
    
    //double D2_psi_T = exp( - (x+m_mu)*(x+m_mu) / (2.*m_sigma2) ) * (x+m_mu)*(x+m_mu)/m_sigma2*m_sigma2 + exp( - (x-m_mu)*(x-m_mu) / (2.*m_sigma2) ) * (x-m_mu)*(x-m_mu)/m_sigma2*m_sigma2 - exp( - (x-m_mu)*(x-m_mu) / (2.*m_sigma2) )/m_sigma2 - exp( - (x+m_mu)*(x+m_mu) / (2.*m_sigma2) )/m_sigma2;
    
    //double D2_psi_T = exp( - (x-m_mu)*(x-m_mu) / (2.*m_sigma2) ) * (x*x - 2.*m_mu*x + m_mu*m_mu + m_sigma2) /m_sigma2*m_sigma2 + exp( - (x+m_mu)*(x+m_mu) / (2.*m_sigma2) ) * (x*x + 2.*m_mu*x + m_mu*m_mu + m_sigma2) / m_sigma2*m_sigma2 ;
    
    double add_minus = exp( - (x-m_mu)*(x-m_mu) / (2.*m_sigma2) ) * ( (m_mu-x)*(m_mu-x) - m_sigma2 );
    
    double add_plus = exp( - (x+m_mu)*(x+m_mu) / (2.*m_sigma2) ) * ( (m_mu+x)*(m_mu+x) - m_sigma2 );
    
    double D2_psi_T = ( add_minus + add_plus ) / (m_sigma2*m_sigma2);
    //remember we are implying that m=1 and h=2pi
    //using potential: v=x^4-5/2x^2
    double H_psi_T = -0.5*D2_psi_T + ( x*x*x*x - 5./2.*x*x )*psi_T ;
    
    
    return H_psi_T/psi_T;
}


void Funzione::set_mean(double a) {
    m_mu = a;
}

void Funzione::set_sigma2(double a) {
    m_sigma2 = a;
}
