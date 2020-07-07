#include "FunzioneScalareBase.h"


double Funzione::Eval_100( const vector<double>& v) const {
    if(v.size() != 3){
        cerr<<endl<<"position must be 3D dimensional"<<endl;
        exit(3);
    }
    
    double r = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    
    // r = r / m_a0;
    
    return pow(m_a0,-3) / M_PI * exp(-2 * r / m_a0 );
    
    
}
    
double Funzione::Eval_210( const vector<double>& v) const {
    
    if(v.size() != 3){
           cerr<<endl<<"position must be 3D dimensional"<<endl;
           exit(3);
       }
       
    
    double r = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    
    r = r ;
    
    //double theta = asin( sqrt( v[0]*v[0] + v[1]*v[1] ) / r );
    
    return pow(m_a0,-5) / (32.*M_PI) * pow(r,2) * exp(- r / m_a0 ) ;
    //return pow(m_a0,-5) / (32.*M_PI) * pow(r,2) * exp(- r / m_a0 ) * cos( theta );
}


void Funzione::set_Bohr_radius(double a) {
    m_a0 = a;
}
