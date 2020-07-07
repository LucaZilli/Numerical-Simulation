
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
                rnd.SetRandom(seed,p1,p2);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;



	int nthrows = 1000;//number of times a needle is thrown in each experiment made
    int nexp=100;//number of experiment in each block
    int nblocks=100;//number of blocks

	
    int D=3;//distance between the lines
    double L=2.95;//length of the needle
    int Nh=0;//number of times the needle hit one of the lines
    int Nt=0;//number of throws
    
    double x,y;
    //check to see immediatly if the algorithm works
    for(int i=0 ; i < nthrows ; i++){
        double theta;
        double y_cm=rnd.Rannyu(0,D);
        //find theta:
        do{
            x=rnd.Rannyu(-1,1);
            y=rnd.Rannyu(0,1);
        }
        while( x*x + y*y >1 );
        
        theta=acos(x/( pow(x*x+y*y,0.5) ));
        
        //hitting condition
        if( (y_cm + L*0.5*sin(theta) > D) or (y_cm - L*0.5*sin(theta) < 0) ){
            Nh++;
            Nt++;
        }
        else{
            Nt++;
        }
        
    }
    
    double PI=(2.*L*Nt)/(Nh*D);
    cout<<"check exp:"<<endl;
    cout<<endl<<"PI è ... "<<PI<<endl;
    cout<<endl<<"Nh è ... "<<Nh<<endl;
    cout<<endl<<"Nt è ... "<<Nt<<endl<<endl;
    
    cout<<"number of blocks: "<<nblocks<<endl;
    cout<<"number of simulations per blocks: "<<nexp<<endl<<endl;
    

    vector <double> Data;//vector containing, in each position, the average of each block of experiments
    
    
    for(int k=0 ; k <nblocks  ; k++){//cycle over the blocks
        Data.push_back(0);
        for(int m=0 ; m <nexp  ; m++){//cycle over the experiments in each block
            
            for(int i=0 ; i < nthrows ; i++){//an experiment that consists in nthrows number of throws of the needle
            
                double y_cm=rnd.Rannyu(0,D);
                double theta;
                //find theta:
                do{
                    x=rnd.Rannyu(-1,1);
                    y=rnd.Rannyu(0,1);
                }
                while( x*x + y*y >1 );
            
                theta=acos(x/( pow(x*x+y*y,0.5) ));
            
        
                if( (y_cm + L*0.5*sin(theta) > D) or (y_cm - L*0.5*sin(theta) < 0) ){
                    Nh++;
                    Nt++;
                }
                else{
                    Nt++;
                }
            
            }
            double PI=(2.*L*Nt)/(Nh*D);
            Data[k] +=PI;
        }
        
        if(k%10==0) cout<<"block number "<<k<<" on "<<nblocks<<endl;
        
        double PI=(2.*L*Nt)/(Nh*D);
        
        Data[k]=Data[k]/(double)nexp;
        
    }
    
    
    
    
    
    vector <double> Datasum_prog;
    vector <double> Datasu2_prog;
    vector <double> Dataerr_prog;
    
    
    for(int i=0 ; i < nblocks ; i++){//progressive averages
        Datasum_prog.push_back(0);
        Datasu2_prog.push_back(0);
        
        for(int k=0 ; k <i+1  ; k++){
            Datasum_prog[i]+=Data[k];
            Datasu2_prog[i]+=Data[k]*Data[k];
    
        }
        
        Datasum_prog[i]=Datasum_prog[i]/(i+1);
        Datasu2_prog[i]=Datasu2_prog[i]/(i+1);
        Dataerr_prog.push_back(error(Datasum_prog,Datasu2_prog,i));
    
    }
    
    Print("Datasum_prog.txt",Datasum_prog);
    Print("Datasu2_prog.txt",Datasu2_prog);
    Print("Dataerr_prog.txt",Dataerr_prog);
    

    rnd.SaveSeed();
    return 0;
}









