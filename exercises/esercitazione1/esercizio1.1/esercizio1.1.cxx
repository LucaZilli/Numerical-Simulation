#include <iostream>
#include <fstream>
#include <cstdlib>
#include "random.h"

#include "funzioni.h"

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
                rnd.SetRandom(seed,p1,p2);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;

    rnd.SaveSeed();
   

    int M=1000000;//number of throws
    double r[M];//vector containing the data sampled
    int N=1000;//number of blocks
    int L=int(M/N);//number of data in each block
    
    vector <double> ave_media;
    vector <double>  av2_media;
    vector <double>  sum_medie_prog;
    vector <double>  su2_medie_prog;
    vector <double>  err_medie_prog;
    
    vector <double> ave_var;
    vector <double>  av2_var;
    vector <double>  sum_var_prog;
    vector <double>  su2_var_prog;
    vector <double>  err_var_prog;
    
    vector <double> R;
    
    for(int i=0; i<M; i++){
        r[i]=rnd.Rannyu();
        R.push_back(r[i]);
    }
    
    Print ( "dati.txt" , R );
    
    //first part: average
    
    for(int i=0;i<N;i++){
        double sum=0;
        for(int j=0;j<L;j++){
       
            sum+=r[j+i*L];
        }
        ave_media.push_back(sum/L);
        av2_media.push_back((sum/L)*(sum/L));
    }
    
    
    for(int i=0;i<N;i++){
        sum_medie_prog.push_back(0);
        su2_medie_prog.push_back(0);
        for(int j=0;j<i+1;j++){
            sum_medie_prog[i] += ave_media[j];
            su2_medie_prog[i] += av2_media[j];
        }
        sum_medie_prog[i]=sum_medie_prog[i]/(i+1);
        su2_medie_prog[i]=su2_medie_prog[i]/(i+1);
        err_medie_prog.push_back(error(sum_medie_prog,su2_medie_prog,i));
    }
    
    Print ( "valori_medie.txt" , sum_medie_prog );
    Print ( "errori_medie.txt" , err_medie_prog );
    
    //second part: variance
    
    for(int i=0;i<N;i++){
        double sum=0;
        for(int j=0;j<L;j++){
       
            sum+=(r[j+i*L]-0.5)*(r[j+i*L]-0.5);
        }
        ave_var.push_back(sum/L);
        av2_var.push_back((sum/L)*(sum/L));
    }
    
    for(int i=0;i<N;i++){
        sum_var_prog.push_back(0);
        su2_var_prog.push_back(0);
        for(int j=0;j<i+1;j++){
            sum_var_prog[i] += ave_var[j];
            su2_var_prog[i] += av2_var[j];
        }
        sum_var_prog[i]=sum_var_prog[i]/(i+1);
        su2_var_prog[i]=su2_var_prog[i]/(i+1);
        err_var_prog.push_back(error(sum_var_prog,su2_var_prog,i));
    }
    
    Print ( "valori_varianze.txt" , sum_var_prog );
    Print ( "errori_varianze.txt" , err_var_prog );
    
    
    //third part: chi^2----> look at jupyter notebook (made with python directly)
    
    
    return 0 ;
    
}


