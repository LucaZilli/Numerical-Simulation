#include <cmath>
#include "funzioni.h"
#include "random.h"
#include "FunzioneScalareBase.h"


using namespace std;

int main(int argc, char *argv[]){
    
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
    
    
    //programme begin here
    
    double mu = 0.790;
    double sigma2 = 0.375;
    //double mu = 0.69;
    //double sigma2 = 0.375;
    double sigma = sqrt(sigma2);
    Funzione *MyF=new Funzione();
    MyF->set_mean( mu );
    MyF->set_sigma2( sigma2 );
    
    
    double A;

    //blocks' parameters
    int nstep =10000000;
    int M=10000;
    int N=100;
    int L=int(M/(N));
    
    
    //psi
    double v_0_psi=0.0;
    vector <double> data_psi;
    vector <double> ave_psi;
    vector <double> av2_psi;
    vector <double> ave_psi_prog;
    vector <double> av2_psi_prog;
    vector <double> err_psi_prog;
    double v_primo_psi;
    vector <double> v_n_psi;
    v_n_psi.push_back( v_0_psi );
 
    cout<<endl<<"value mu "<<mu;
    cout<<endl<<"value sigma2 "<<sigma2<<endl<<endl;
    //H
    vector <double> data_H;
    vector <double> ave_H;
    vector <double> av2_H;
    vector <double> ave_H_prog;
    vector <double> av2_H_prog;
    vector <double> err_H_prog;
    vector <double> v_n_H;
    v_n_H.push_back( MyF->EvalF(v_0_psi) );
    
    //Pay attention: start your algorithm using Bohr radius' unit, otherwise the probability density gonna end too small!!!!!

    double accepted=0.;
    double attempted=0.;
    vector <double> data_a_psi;
    
    
    for(int j=1 ; j < nstep; j++ ){

        v_primo_psi = rnd.Rannyu( v_n_psi[j-1] - 0.20, v_n_psi[j-1] + 0.20 );
        double r;
        
        //minimun
        double P_Xn_psi = MyF->EvalP(v_n_psi[j-1]);
        double P_Xprimo_psi = MyF->EvalP(v_primo_psi);
        
        double alpha = ( P_Xprimo_psi ) / ( P_Xn_psi );
        if ( alpha >= 1. )
            v_n_psi.push_back(v_primo_psi);
        else{
            A=alpha;
            r=rnd.Rannyu();
            if( r <= A ){
                v_n_psi.push_back(v_primo_psi);
                accepted+=1.;
            }
            else
                v_n_psi.push_back(v_n_psi[j-1]);
        }
        attempted+=1.;
        
        
        data_a_psi.push_back(accepted/attempted);
        v_n_H.push_back( MyF->EvalF( v_n_psi[j] ) );
        
        if( j%1000 == 0){
            double media;
            //media=CalcolaMedia(v_n_psi);
            //data_psi.push_back(media);
            
            media=CalcolaMedia(v_n_H);
            data_H.push_back(media);
        }
        if( j%100000 == 0)
            cout<<endl<<j<<" steps of simulation completed";
            //cout<<endl<<"accepted "<<accepted;
            //cout<<endl<<"attempted "<<attempted;
            //cout<<endl<<"A "<<A;
            //cout<<endl<<"v_primo_H "<<v_primo_H;
            //cout<<endl<<"r "<<r;
            //cout<<endl<<"v_n_psi[j] "<<v_n_psi[j];
            //cout<<endl<<"v_n_H[j] "<<v_n_H[j];

    }
    //cout<<endl<<"ave_data_H  "<<CalcolaMedia(v_n_H)<<endl<<endl;
    cout<<endl<<"simulation of 10^6 step ended"<<endl<<"let's calculate the block averages!!!!"<<endl;
    cout<<endl<<" average acceptance "<< CalcolaMedia(data_a_psi) <<endl<<endl;
    
    //classic block method
    
    
     for(int i=0;i<N;i++){
         double sum_H=0.;
         //double sum_psi=0.;

         for(int j=0;j<L;j++){
             sum_H+=data_H[j+i*L];
             //sum_psi+=data_psi[j+i*L];
         }
         ave_H.push_back(sum_H/L);
         av2_H.push_back((sum_H/L)*(sum_H/L));
         //ave_psi.push_back(sum_psi/L);
         //av2_psi.push_back((sum_psi/L)*(sum_psi/L));
     }
     
     
     for(int i=0;i<N;i++){
         ave_H_prog.push_back(0);
         av2_H_prog.push_back(0);
         //ave_psi_prog.push_back(0);
         //av2_psi_prog.push_back(0);
         
         for(int j=0;j<i+1;j++){
             ave_H_prog[i] += ave_H[j];
             av2_H_prog[i] += av2_H[j];
             //ave_psi_prog[i] += ave_psi[j];
             //av2_psi_prog[i] += av2_psi[j];
             
         }
         ave_H_prog[i]=ave_H_prog[i]/(i+1);
         av2_H_prog[i]=av2_H_prog[i]/(i+1);
         err_H_prog.push_back(error(ave_H_prog,av2_H_prog,i));
         
         //ave_psi_prog[i]=ave_psi_prog[i]/(i+1);
         //av2_psi_prog[i]=av2_psi_prog[i]/(i+1);
         //err_psi_prog.push_back(error(ave_psi_prog,av2_psi_prog,i));
     }
    
    cout<<"blocks' averages finished"<<endl<<"let's print all data"<<endl;
    cout<<"ave_H  "<< ave_H_prog[N-1] <<endl<<endl;
    

    Print ( "ave_H.txt" , ave_H_prog );
    Print ( "err_H.txt" , err_H_prog );
    Print ( "psi2.txt" , v_n_psi );
    
    
    return 0;
    
}

