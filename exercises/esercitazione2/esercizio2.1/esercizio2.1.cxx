#include "Integrale.h"
#include <iostream>
#include <cmath>
#include "funzioni.h"


using namespace std;

int main(){
    
    
    //immissione dei parametri del problema
    int punti;
    int n;
    int sup;
    int inf;
    cout<<endl<<"hello, we will calculate an integral with the montecarlo method of the average"<<endl<<"how many points do you want to use?   ";
    cin>>punti;
    cout<<endl<<"which is the lower extreme?   ";
    cin>>inf;
    cout<<endl<<"which is the upper extreme?   ";
    cin>>sup;
    
    int N=100;
    vector <double> ave_I;
    vector <double>  av2_I;
    vector <double>  sum_I_prog;
    vector <double>  su2_I_prog;
    vector <double>  err_I_prog;
    
   
    //dimension of the integral
    n=1;
    
    //constructor of "integrale"
    Integrale myintegrator(1);
    
    //vector of extremes of the integral: for this case n=1
    vettore vett_inf(n);
    vettore vett_sup(n);
    
    for(int k=0; k<n ;k++){//this class works only on hyper-square domains
        
        vett_inf.setcomponent(k,inf);
        vett_sup.setcomponent(k,sup);
        
    }
    
    //pointer to the object "funzione"
        Funzione* myF = new Funzione();
           
    
    for(int i=0;i<N;i++){
        double I=myintegrator.IntegraleMultidimAVE(n, vett_inf, vett_sup, myF, punti);
        ave_I.push_back(I);
        av2_I.push_back(I*I);
    }
    
     
     for(int i=0;i<N;i++){
         sum_I_prog.push_back(0);
         su2_I_prog.push_back(0);
         for(int j=0;j<i+1;j++){
             sum_I_prog[i] += ave_I[j];
             su2_I_prog[i] += av2_I[j];
         }
         sum_I_prog[i]=sum_I_prog[i]/(i+1);
         su2_I_prog[i]=su2_I_prog[i]/(i+1);
         err_I_prog.push_back(error(sum_I_prog,su2_I_prog,i));
     }
     
     Print ( "valori_integrali.txt" , sum_I_prog );
     Print ( "errori_integrali.txt" , err_I_prog );
    
    
    //part2: important sampling
    
    vector <double> ave_I_imp;
    vector <double>  av2_I_imp;
    vector <double>  sum_I_imp_prog;
    vector <double>  su2_I_imp_prog;
    vector <double>  err_I_imp_prog;
    
    //pointer to the object "funzione"
    Funzione* myF_imp = new Funzione();
    
    
    for(int k=0; k<n ;k++){
        
        vett_inf.setcomponent(k,inf);
        vett_sup.setcomponent(k,sup);
        
    }
    
        
    //data blocking method
    for(int i=0;i<N;i++){
        double I=myintegrator.IntegraleMultidim_imp(n, vett_inf, vett_sup, myF_imp, punti);
        ave_I_imp.push_back(I);
        av2_I_imp.push_back(I*I);
    }
    
     
     for(int i=0;i<N;i++){
         sum_I_imp_prog.push_back(0);
         su2_I_imp_prog.push_back(0);
         for(int j=0;j<i+1;j++){
             sum_I_imp_prog[i] += ave_I_imp[j];
             su2_I_imp_prog[i] += av2_I_imp[j];
         }
         sum_I_imp_prog[i]=sum_I_imp_prog[i]/(i+1);
         su2_I_imp_prog[i]=su2_I_imp_prog[i]/(i+1);
         err_I_imp_prog.push_back(error(sum_I_imp_prog,su2_I_imp_prog,i));
     }
     
     Print ( "valori_integrali_imp.txt" , sum_I_imp_prog );
     Print ( "errori_integrali_imp.txt" , err_I_imp_prog );
     
    
    
    return 0;
    
}

