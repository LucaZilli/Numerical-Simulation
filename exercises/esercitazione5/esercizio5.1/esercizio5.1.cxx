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
                rnd.SetRandom(seed,p2,p1);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;

    rnd.SaveSeed();
    
    
    //programme begin here
    
    double Bohr_radius = 5.291777721092e-11;
    double A;
    double T;
    double delta=Bohr_radius;
    double n_equilibration=10000;
    
    
    //blocks' parameters
    int nstep =10000000;//total number of steps
    int N=100;//number of blocks
    int L=int(nstep/(N));//number of steps in eachblock
    vector <double> data_a_100_unif;
    vector <double> data_a_100_gauss;
    vector <double> data_a_210_unif;
    vector <double> data_a_210_gauss;
    
    
    //state |n,l,m> = |1,0,0>
    vector <double> v_0_100;//setting initial position
    v_0_100.push_back(1.5*Bohr_radius);
    v_0_100.push_back(1.5*Bohr_radius);
    v_0_100.push_back(1.5*Bohr_radius);
    
    //unif
    vector <double> data_radius_100_unif;
    vector <double> ave_r_100_unif_prog;
    vector <double> av2_r_100_unif_prog;
    vector <double> err_r_100_unif_prog;
    vector <double> v_primo_100_unif;
    vector < vector <double> > v_n_100_unif;
    v_n_100_unif.push_back(v_0_100);
    
    //gauss
    vector <double> data_radius_100_gauss;
    vector <double> ave_r_100_gauss_prog;
    vector <double> av2_r_100_gauss_prog;
    vector <double> err_r_100_gauss_prog;
    vector <double> v_primo_100_gauss;
    vector < vector <double> > v_n_100_gauss;
    v_n_100_gauss.push_back(v_0_100);
    
    
    //state |n,l,m> = |2,1,0>
    vector <double> v_0_210;//setting initial position
    v_0_210.push_back(5*Bohr_radius);
    v_0_210.push_back(5*Bohr_radius);
    v_0_210.push_back(5*Bohr_radius);
    
    //unif
    vector <double> data_radius_210_unif;
    vector <double> ave_r_210_unif_prog;
    vector <double> av2_r_210_unif_prog;
    vector <double> err_r_210_unif_prog;
    vector <double> v_primo_210_unif;
    vector < vector <double> > v_n_210_unif;
    v_n_210_unif.push_back(v_0_210);
    
    //gauss
    vector <double> data_radius_210_gauss;
    vector <double> ave_r_210_gauss_prog;
    vector <double> av2_r_210_gauss_prog;
    vector <double> err_r_210_gauss_prog;
    vector <double> v_primo_210_gauss;
    vector < vector <double> > v_n_210_gauss;
    v_n_210_gauss.push_back(v_0_210);
    
    
    
    Funzione *P=new Funzione();
    P->set_Bohr_radius( Bohr_radius );

    
    for(int j=0 ; j < nstep+n_equilibration; j++ ){//simulation
        
        v_primo_100_unif.clear();
        v_primo_210_unif.clear();
        
        v_primo_100_gauss.clear();
        v_primo_210_gauss.clear();

        
        for(int k=0 ; k<3;k++){//I fill the 3 coordinates

            v_primo_210_unif.push_back( rnd.Rannyu( v_n_210_unif[j][k]-4.5*Bohr_radius, v_n_210_unif[j][k]+4.5*Bohr_radius ) );
            v_primo_100_unif.push_back( rnd.Rannyu( v_n_100_unif[j][k]-1.20*Bohr_radius, v_n_100_unif[j][k]+1.20*Bohr_radius ) );
            
            v_primo_100_gauss.push_back( rnd.Gauss( v_n_100_gauss[j][k], 0.75*Bohr_radius ) );
            v_primo_210_gauss.push_back( rnd.Gauss( v_n_210_gauss[j][k], 2.75*Bohr_radius ) );

        }
        
        //metropolis
        
        //state |n,l,m> = |1,0,0>
        
        //unif
        double P_Xn_100_unif = P->Eval_100(v_n_100_unif[j]);
        double P_Xprimo_100_unif = P->Eval_100(v_primo_100_unif);
        
        double alpha = ( P_Xprimo_100_unif ) / ( P_Xn_100_unif );
        if ( alpha < 1. )
            A=alpha;
        else
            A=1.;
        double r=rnd.Rannyu();
        if( r <= A )
            v_n_100_unif.push_back(v_primo_100_unif);
        else
            v_n_100_unif.push_back(v_n_100_unif[j]);
        if(j<n_equilibration)
            data_a_100_unif.push_back(A);
        
        //gauss
        double P_Xn_100_gauss = P->Eval_100(v_n_100_gauss[j]);
        double P_Xprimo_100_gauss = P->Eval_100(v_primo_100_gauss);
        
        alpha = ( P_Xprimo_100_gauss ) / ( P_Xn_100_gauss );
        if ( alpha < 1. )
            A=alpha;
        else
            A=1.;
        r=rnd.Rannyu();
        if( r <= A )
            v_n_100_gauss.push_back(v_primo_100_gauss);
        else
            v_n_100_gauss.push_back(v_n_100_gauss[j]);
        if(j<n_equilibration)
            data_a_100_gauss.push_back(A);
        
        
        //state |n,l,m> = |2,1,0>
        
        //unif
        double P_Xn_210_unif = P->Eval_210(v_n_210_unif[j]);
        double P_Xprimo_210_unif = P->Eval_210(v_primo_210_unif);
        
        alpha = ( P_Xprimo_210_unif ) / ( P_Xn_210_unif );
        if ( alpha < 1. )
            A=alpha;
        else
            A=1.;
        r=rnd.Rannyu();
        if( r <= A )
            v_n_210_unif.push_back(v_primo_210_unif);
        else
            v_n_210_unif.push_back(v_n_210_unif[j]);
        if(j<n_equilibration)
            data_a_210_unif.push_back(A);
        
        //gauss
        double P_Xn_210_gauss = P->Eval_210(v_n_210_gauss[j]);
        double P_Xprimo_210_gauss = P->Eval_210(v_primo_210_gauss);
        
        alpha = ( P_Xprimo_210_gauss ) / ( P_Xn_210_gauss );
        if ( alpha < 1. )
            A=alpha;
        else
            A=1.;
        r=rnd.Rannyu();
        if( r <= A )
            v_n_210_gauss.push_back(v_primo_210_gauss);
        else
            v_n_210_gauss.push_back(v_n_210_gauss[j]);
        if(j<n_equilibration)
            data_a_210_gauss.push_back(A);
        
    
        if( j%L == 0 and j>n_equilibration){// here I take the measurements, but only after the equilibration time
            int r=int(j/L);
            double media;
            //state |n,l,m> = |1,0,0>
            media=CalcolaMedia_R(v_n_100_unif,int((r-1)*L),int(r*L));
            data_radius_100_unif.push_back(media/Bohr_radius);
            media=CalcolaMedia_R(v_n_100_gauss,int((r-1)*L),int(r*L));
            data_radius_100_gauss.push_back(media/Bohr_radius);
            
            //state |n,l,m> = |2,1,0>
            media=CalcolaMedia_R(v_n_210_unif,int((r-1)*L),int(r*L));
            data_radius_210_unif.push_back(media/Bohr_radius);
            media=CalcolaMedia_R(v_n_210_gauss,int((r-1)*L),int(r*L));
            data_radius_210_gauss.push_back(media/Bohr_radius);
        }
        if( j%1000000 == 0)
            cout<<endl<<j<<" steps of simulation completed";
    }
    
    cout<<endl<<"simulation of 10^6 step ended"<<endl<<"let's calculate the block averages!!!!"<<endl;
    cout<<endl<<"acceptance average during the equilibration steps |100> unif "<< CalcolaMedia(data_a_100_unif) <<endl;
    cout<<endl<<"acceptance average during the equilibration steps |100> gauss "<< CalcolaMedia(data_a_100_gauss) <<endl<<endl;
    cout<<endl<<"acceptance average during the equilibration steps |210> unif "<< CalcolaMedia(data_a_210_unif) <<endl;
    cout<<endl<<"acceptance average during the equilibration steps |210> gauss"<< CalcolaMedia(data_a_210_gauss) <<endl<<endl;
   
    
    //classic block method
    
     
     for(int i=0;i<N;i++){
         ave_r_100_unif_prog.push_back(0);
         av2_r_100_unif_prog.push_back(0);
         ave_r_100_gauss_prog.push_back(0);
         av2_r_100_gauss_prog.push_back(0);
         
         ave_r_210_unif_prog.push_back(0);
         av2_r_210_unif_prog.push_back(0);
         ave_r_210_gauss_prog.push_back(0);
         av2_r_210_gauss_prog.push_back(0);
         
         for(int j=0;j<i+1;j++){
             ave_r_100_unif_prog[i] += data_radius_100_unif[j];
             av2_r_100_unif_prog[i] += data_radius_100_unif[j]*data_radius_100_unif[j];
             ave_r_100_gauss_prog[i] += data_radius_100_gauss[j];
             av2_r_100_gauss_prog[i] += data_radius_100_gauss[j]*data_radius_100_gauss[j];
             
             ave_r_210_unif_prog[i] += data_radius_210_unif[j];
             av2_r_210_unif_prog[i] += data_radius_210_unif[j]*data_radius_210_unif[j];
             ave_r_210_gauss_prog[i] += data_radius_210_gauss[j];
             av2_r_210_gauss_prog[i] += data_radius_210_gauss[j]*data_radius_210_gauss[j];
         }
         ave_r_100_unif_prog[i]=ave_r_100_unif_prog[i]/(i+1);
         av2_r_100_unif_prog[i]=av2_r_100_unif_prog[i]/(i+1);
         err_r_100_unif_prog.push_back(error(ave_r_100_unif_prog,av2_r_100_unif_prog,i));
         
         ave_r_210_unif_prog[i]=ave_r_210_unif_prog[i]/(i+1);
         av2_r_210_unif_prog[i]=av2_r_210_unif_prog[i]/(i+1);
         err_r_210_unif_prog.push_back(error(ave_r_210_unif_prog,av2_r_210_unif_prog,i));
         
         ave_r_100_gauss_prog[i]=ave_r_100_gauss_prog[i]/(i+1);
         av2_r_100_gauss_prog[i]=av2_r_100_gauss_prog[i]/(i+1);
         err_r_100_gauss_prog.push_back(error(ave_r_100_gauss_prog,av2_r_100_gauss_prog,i));
         
         ave_r_210_gauss_prog[i]=ave_r_210_gauss_prog[i]/(i+1);
         av2_r_210_gauss_prog[i]=av2_r_210_gauss_prog[i]/(i+1);
         err_r_210_gauss_prog.push_back(error(ave_r_210_gauss_prog,av2_r_210_gauss_prog,i));
         
     }
    
    cout<<"blocks' averages finished"<<endl<<"let's print all data"<<endl;
    
    Print_matrix ( "x_n_100_unif.txt" , v_n_100_unif, 0, int(2*n_equilibration) );
    Print_matrix ( "y_n_100_unif.txt" , v_n_100_unif, 1, int(2*n_equilibration) );
    Print_matrix ( "z_n_100_unif.txt" , v_n_100_unif, 2, int(2*n_equilibration) );
    
    Print_matrix ( "x_n_100_gauss.txt" , v_n_100_gauss, 0, int(2*n_equilibration) );
    Print_matrix ( "y_n_100_gauss.txt" , v_n_100_gauss, 1, int(2*n_equilibration) );
    Print_matrix ( "z_n_100_gauss.txt" , v_n_100_gauss, 2, int(2*n_equilibration) );
    
    Print_matrix ( "x_n_210_unif.txt" , v_n_210_unif, 0, int(2*n_equilibration) );
    Print_matrix ( "y_n_210_unif.txt" , v_n_210_unif, 1, int(2*n_equilibration) );
    Print_matrix ( "z_n_210_unif.txt" , v_n_210_unif, 2, int(2*n_equilibration) );
    
    Print_matrix ( "x_n_210_gauss.txt" , v_n_210_gauss, 0, int(2*n_equilibration) );
    Print_matrix ( "y_n_210_gauss.txt" , v_n_210_gauss, 1, int(2*n_equilibration) );
    Print_matrix ( "z_n_210_gauss.txt" , v_n_210_gauss, 2, int(2*n_equilibration) );
    
    
    Print ( "ave_r_100_unif.txt" , ave_r_100_unif_prog );
    Print ( "err_r_100_unif.txt" , err_r_100_unif_prog );
    
    Print ( "ave_r_210_unif.txt" , ave_r_210_unif_prog );
    Print ( "err_r_210_unif.txt" , err_r_210_unif_prog );
    
    Print ( "ave_r_100_gauss.txt" , ave_r_100_gauss_prog );
    Print ( "err_r_100_gauss.txt" , err_r_100_gauss_prog );
    
    Print ( "ave_r_210_gauss.txt" , ave_r_210_gauss_prog );
    Print ( "err_r_210_gauss.txt" , err_r_210_gauss_prog );
    
    
    Print ( "data_a_100_unif.txt" , data_a_100_unif );
    Print ( "data_a_100_gauss.txt" , data_a_100_gauss );
    
    Print ( "data_a_210_unif.txt" , data_a_210_unif );
    Print ( "data_a_210_gauss.txt" , data_a_210_gauss );
    
    return 0;
    
}

