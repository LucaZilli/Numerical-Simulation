
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "random.h"
#include "funzioni.h"

using namespace std;

int main (int argc, char *argv[]){
    
    Random rnd;
    int seed[4];
    int p1, p2;
    ifstream Primes("Primes");
    if (Primes.is_open()){
        Primes >> p1 >> p2 ;
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("seed.in");
    string property;
    if (input.is_open()){
        while ( !input.eof() ){
            input >> property;
            if( property == "RANDOMSEED" ){
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd.SetRandom(seed,p2,p1);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;

    
    //first part
    

    double S_0=100;
    double T=1;
    double K=100;
    double r=0.1;
    double sigma=0.25;
    
    
    int M=100000;//number of data
    int N=100;//number of blocks
    int L=M/N;//number of data in each block
    
    //vector for the simulation of call-option
    vector <double> C_N;
    vector <double> C_N2;
    vector <double> C_N_prog;
    vector <double> C_N2_prog;
    vector <double> err_C_prog;
    
    //vector for the simulation of put-option
    vector <double> P_N;
    vector <double> P_N2;
    vector <double> P_N_prog;
    vector <double> P_N2_prog;
    vector <double> err_P_prog;
    
    
    double z;//normal standard
    double max_C;
    double max_P;
    double C;
    double P;
    
    
    
    for(int i=0 ; i<N ; i++){//cycle over blocks
        double sum_C=0;
        double sum_P=0;
        C_N.push_back(0);
        C_N2.push_back(0);
        P_N.push_back(0);
        P_N2.push_back(0);
        for(int j=0 ; j<L; j++){
            z=rnd.Gauss(0,1);
            double S_t=S_0*exp( (r-0.5*sigma*sigma)*T+sigma*z*sqrt(T));
            if(S_t>K){
                max_C=S_t-K;
                max_P=0;
            }
            else{
                max_C=0;
                max_P=-S_t+K;
            }
            
            C=exp(-r*T)*max_C;
            sum_C+=C;
            
            P=exp(-r*T)*max_P;
            sum_P+=P;
        }                   //here finish each block
        
        C_N[i]=sum_C/L;
        C_N2[i]=C_N[i]*C_N[i];
        
        P_N[i]=sum_P/L;
        P_N2[i]=P_N[i]*P_N[i];//are made the averages in each blocks
    }
    
    
    
    
    
    for(int i=0 ; i<N ; i++){
        C_N_prog.push_back(0);
        C_N2_prog.push_back(0);
        P_N_prog.push_back(0);
        P_N2_prog.push_back(0);
        for(int j=0 ; j<i+1 ; j++){
            C_N_prog[i]+=C_N[j];
            C_N2_prog[i]+=C_N2[j];
            
            P_N_prog[i]+=P_N[j];
            P_N2_prog[i]+=P_N2[j];
        }
        C_N_prog[i]=C_N_prog[i]/(i+1);//are made the progressive averages: in position i there is the average if i blocks
        C_N2_prog[i]=C_N2_prog[i]/(i+1);
        err_C_prog.push_back( error( C_N_prog, C_N2_prog, i) );
        
        P_N_prog[i]=P_N_prog[i]/(i+1);
        P_N2_prog[i]=P_N2_prog[i]/(i+1);
        err_P_prog.push_back( error( P_N_prog, P_N2_prog, i) );
    }
    
    Print("C_N_prog.txt",C_N_prog);
    Print("err_C_prog.txt",err_C_prog);
       
    Print("P_N_prog.txt",P_N_prog);
    Print("err_P_prog.txt",err_P_prog);
    
    
    
 
    
    
    
    //discret GBM
    
    vector <double> C_N_discreto;
    vector <double> C_N2_discreto;
    vector <double> C_N_discreto_prog;
    vector <double> C_N2_discreto_prog;
    vector <double> err_C_discreto_prog;
    
    vector <double> P_N_discreto;
    vector <double> P_N2_discreto;
    vector <double> P_N_discreto_prog;
    vector <double> P_N2_discreto_prog;
    vector <double> err_P_discreto_prog;
    
    
    vector <double> S_t_discreto;
    double dt=T/100.;
    double max;
    
    
    
    
    for(int i=0 ; i<N ; i++){  //N is the number of the blocks
        double sum_C=0;
        double sum_P=0;
        C_N_discreto.push_back(0);
        C_N2_discreto.push_back(0);
        P_N_discreto.push_back(0);
        P_N2_discreto.push_back(0);
        for(int j=0 ; j<L; j++){    //GBM is done L times in each blocks
            S_t_discreto.clear();
            S_t_discreto.push_back(S_0);
            for(int k=1 ; k<100 ; k++){
                z=rnd.Gauss(0,1);
                S_t_discreto.push_back( S_t_discreto[k-1]*exp( (r-0.5*sigma*sigma)*dt+sigma*z*sqrt(dt)) );
            }
                    
            if(S_t_discreto[99]>K){
                   max_C=S_t_discreto[99]-K;
                   max_P=0;
               }
            else{
                max_C=0;
                max_P=-S_t_discreto[99]+K;
            }
            
            C=exp(-r*T)*max_C;
            sum_C+=C;
            
            P=exp(-r*T)*max_P;
            sum_P+=P;
        }                           //are made the averages over each blocks
        C_N_discreto[i]=sum_C/L;
        C_N2_discreto[i]=C_N_discreto[i]*C_N_discreto[i];
        
        P_N_discreto[i]=sum_P/L;
        P_N2_discreto[i]=P_N_discreto[i]*P_N_discreto[i];
    }
    
    
    
    
    
    for(int i=0 ; i<N ; i++){
        C_N_discreto_prog.push_back(0);
        C_N2_discreto_prog.push_back(0);
        P_N_discreto_prog.push_back(0);
        P_N2_discreto_prog.push_back(0);
        for(int j=0 ; j<i+1 ; j++){
            C_N_discreto_prog[i]+=C_N_discreto[j];
            C_N2_discreto_prog[i]+=C_N2_discreto[j];
            
            P_N_discreto_prog[i]+=P_N_discreto[j];
            P_N2_discreto_prog[i]+=P_N2_discreto[j];
        }           //are made the progressive averages: in position i there is the average if i blocks
        C_N_discreto_prog[i]=C_N_discreto_prog[i]/(i+1);
        C_N2_discreto_prog[i]=C_N2_discreto_prog[i]/(i+1);
        err_C_discreto_prog.push_back( error( C_N_discreto_prog, C_N2_discreto_prog, i) );
        
        P_N_discreto_prog[i]=P_N_discreto_prog[i]/(i+1);
        P_N2_discreto_prog[i]=P_N2_discreto_prog[i]/(i+1);
        err_P_discreto_prog.push_back( error( P_N_discreto_prog, P_N2_discreto_prog, i) );
    }
    
    
    
    Print("C_N_discreto_prog.txt",C_N_discreto_prog);
    Print("err_C_discreto_prog.txt",err_C_discreto_prog);
       
    Print("P_N_discreto_prog.txt",P_N_discreto_prog);
    Print("err_P_discreto_prog.txt",err_P_discreto_prog);
    
    rnd.SaveSeed();
  

    return 0;
}









