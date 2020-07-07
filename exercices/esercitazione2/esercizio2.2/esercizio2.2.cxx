
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

    rnd.SaveSeed();


    int n_step = 100;
    int a=1;
    int N_exp=10000;//total number of experiments
    int nblocks=100;//number of blocks
    int L=int(N_exp/nblocks);//number of experiments in each block
    
    
    
    //discrete random walk
    
    vector < vector<double> > Random_Range2_data;//values of sqrt(r^2) for a RW of every lengthness
    vector <double>  Random_Range2_data_m;//elements of the vector defined above
    vector <int> Random_walk_x;
    vector <int> Random_walk_y;
    vector <int> Random_walk_z;
    
    
    
    //continuos random walk
    
    vector < vector<double> > Random_Range2_cont_data;
    vector <double> Random_Range2_cont_data_m;
    vector <double> Random_walk_x_cont;
    vector <double> Random_walk_y_cont;
    vector <double> Random_walk_z_cont;
    
    for(int m=0 ; m < n_step ; m++){//cycle over random walks of step m
        Random_Range2_data_m.clear();
        Random_Range2_cont_data_m.clear();
        for(int k=0 ; k < N_exp ; k++){
            Random_walk_x.clear();
            Random_walk_y.clear();
            Random_walk_z.clear();
            Random_walk_x.push_back(0);
            Random_walk_y.push_back(0);
            Random_walk_z.push_back(0);
            
            Random_walk_x_cont.clear();
            Random_walk_y_cont.clear();
            Random_walk_z_cont.clear();
            Random_walk_x_cont.push_back(0);
            Random_walk_y_cont.push_back(0);
            Random_walk_z_cont.push_back(0);
            for(int t=1; t< m+2 ; t++){
                
                //discrete:
                double BOOL=rnd.Rannyu();
                int sign;
                if(BOOL<0.5)
                    sign=-1;
                else
                    sign=1;
                BOOL=rnd.Rannyu(0,3);
                if(BOOL<1.){
                    Random_walk_x.push_back( Random_walk_x[t-1] + sign*a );
                    Random_walk_y.push_back( Random_walk_y[t-1] + 0 );
                    Random_walk_z.push_back( Random_walk_z[t-1] + 0 );
                }
                else if( (BOOL > 1.) and (BOOL < 2.) ){
                    Random_walk_x.push_back( Random_walk_x[t-1] + 0 );
                    Random_walk_y.push_back( Random_walk_y[t-1] + sign*a );
                    Random_walk_z.push_back( Random_walk_z[t-1] + 0 );
                }
                else if ( BOOL > 2. ){
                    Random_walk_x.push_back( Random_walk_x[t-1] + 0 );
                    Random_walk_y.push_back( Random_walk_y[t-1] + 0 );
                    Random_walk_z.push_back( Random_walk_z[t-1] + sign*a );
                }
                
                //continous
                double theta=rnd.Rannyu(0,M_PI);
                double phi=rnd.Rannyu(0,2*M_PI);
                
                Random_walk_x_cont.push_back( Random_walk_x_cont[t-1] + sin(theta)*cos(phi)*a );
                Random_walk_y_cont.push_back( Random_walk_y_cont[t-1] + sin(theta)*sin(phi)*a );
                Random_walk_z_cont.push_back( Random_walk_z_cont[t-1] + cos(theta)*a );
            }
            Random_Range2_data_m.push_back( Random_walk_x[m+1]*Random_walk_x[m+1] + Random_walk_y[m+1]*Random_walk_y[m+1]+ Random_walk_z[m+1]*Random_walk_z[m+1] ) ;
            
            Random_Range2_cont_data_m.push_back( Random_walk_x_cont[m+1]*Random_walk_x_cont[m+1] + Random_walk_y_cont[m+1]*Random_walk_y_cont[m+1]+ Random_walk_z_cont[m+1]*Random_walk_z_cont[m+1]  );
            
        }
        Random_Range2_data.push_back(Random_Range2_data_m);
        Random_Range2_cont_data.push_back(Random_Range2_cont_data_m);
        cout<<"Rw of step "<<m<<" done!!"<<endl;
    }
    
    //vectors for data blocking analysis
    vector < vector<double> > Random_Range2_ave;
    vector < vector<double> > Random_Range2_av2;
    vector <double> Random_Range2_ave_m;
    vector <double> Random_Range2_av2_m;
    vector < vector<double> >  sum_Random_Range2_prog;
    vector < vector<double> >  su2_Random_Range2_prog;
    vector < vector<double> >  err_Random_Range2_prog;
    vector <double>  sum_Random_Range2_prog_m;//the element i contain the data blcking averages of a Range of a RW long i
    vector <double>  su2_Random_Range2_prog_m;
    vector <double>  err_Random_Range2_prog_m;
    
    
    vector < vector<double> > Random_Range2_cont_ave;
    vector < vector<double> > Random_Range2_cont_av2;
    vector <double> Random_Range2_cont_ave_m;
    vector <double> Random_Range2_cont_av2_m;
    vector < vector<double> >  sum_Random_Range2_cont_prog;
    vector < vector<double> >  su2_Random_Range2_cont_prog;
    vector < vector<double> >  err_Random_Range2_cont_prog;
    vector <double>  sum_Random_Range2_cont_prog_m;//the element i contain the data blocking averages of a Range of a RW long i
    vector <double>  su2_Random_Range2_cont_prog_m;
    vector <double>  err_Random_Range2_cont_prog_m;
    
    
    double sum;
    double sum_cont;
    for(int m=0 ; m < n_step ; m++){
        Random_Range2_ave_m.clear();
        Random_Range2_av2_m.clear();
        
        Random_Range2_cont_ave_m.clear();
        Random_Range2_cont_av2_m.clear();
        for(int i=0;i<nblocks;i++){
            sum=0.0;
            sum_cont=0.0;
            int k;
            for(int j=0;j<L;j++){
                k=i*L+j;
                sum+=Random_Range2_data[m][k];
                sum_cont+=Random_Range2_cont_data[m][k];
            }
            Random_Range2_ave_m.push_back( (double)sum/L );
            Random_Range2_av2_m.push_back( Random_Range2_ave_m[i]*Random_Range2_ave_m[i] );
            
            Random_Range2_cont_ave_m.push_back( (double)sum_cont/L );
            Random_Range2_cont_av2_m.push_back( Random_Range2_cont_ave_m[i]*Random_Range2_cont_ave_m[i] );
        }
        Random_Range2_ave.push_back(Random_Range2_ave_m);
        Random_Range2_av2.push_back(Random_Range2_av2_m);
        
        Random_Range2_cont_ave.push_back(Random_Range2_cont_ave_m);
        Random_Range2_cont_av2.push_back(Random_Range2_cont_av2_m);
    }
    
    
    for(int m=0 ; m < n_step ; m++){//cycle over the random walks of step m
        sum_Random_Range2_prog_m.clear();
        su2_Random_Range2_prog_m.clear();
        err_Random_Range2_prog_m.clear();
        
        sum_Random_Range2_cont_prog_m.clear();
        su2_Random_Range2_cont_prog_m.clear();
        err_Random_Range2_cont_prog_m.clear();
        for(int i=0;i<nblocks;i++){//cycle over the blocks
            sum_Random_Range2_prog_m.push_back(0);
            su2_Random_Range2_prog_m.push_back(0);
            
            sum_Random_Range2_cont_prog_m.push_back(0);
            su2_Random_Range2_cont_prog_m.push_back(0);
            for(int j=0;j<i+1;j++){
                sum_Random_Range2_prog_m[i] += Random_Range2_ave[m][j];
                su2_Random_Range2_prog_m[i] += Random_Range2_av2[m][j];
                
                sum_Random_Range2_cont_prog_m[i] += Random_Range2_cont_ave[m][j];
                su2_Random_Range2_cont_prog_m[i] += Random_Range2_cont_av2[m][j];
            }
            sum_Random_Range2_prog_m[i]=sum_Random_Range2_prog_m[i]/(i+1);
            su2_Random_Range2_prog_m[i]=su2_Random_Range2_prog_m[i]/(i+1);
            err_Random_Range2_prog_m.push_back(error(sum_Random_Range2_prog_m,su2_Random_Range2_prog_m,i));
            
            sum_Random_Range2_cont_prog_m[i]=sum_Random_Range2_cont_prog_m[i]/(i+1);
            su2_Random_Range2_cont_prog_m[i]=su2_Random_Range2_cont_prog_m[i]/(i+1);
            err_Random_Range2_cont_prog_m.push_back(error(sum_Random_Range2_cont_prog_m,su2_Random_Range2_cont_prog_m,i));
        }
        sum_Random_Range2_prog.push_back( sum_Random_Range2_prog_m );
        su2_Random_Range2_prog.push_back( su2_Random_Range2_prog_m );
        err_Random_Range2_prog.push_back( err_Random_Range2_prog_m );
        
        sum_Random_Range2_cont_prog.push_back( sum_Random_Range2_cont_prog_m );
        su2_Random_Range2_cont_prog.push_back( su2_Random_Range2_cont_prog_m );
        err_Random_Range2_cont_prog.push_back( err_Random_Range2_cont_prog_m );
    }
    
    vector <double> Best_range;
    vector <double> Best_error;
    Best_range.push_back(0);
    Best_error.push_back(0);
    
    vector <double> Best_range_cont;
    vector <double> Best_error_cont;
    Best_range_cont.push_back(0);
    Best_error_cont.push_back(0);
    for (int i=0;i<n_step;i++){
        Best_range.push_back( sum_Random_Range2_prog[i][nblocks-1] );
        Best_error.push_back( err_Random_Range2_prog[i][nblocks-1] );
        
        Best_range_cont.push_back( sum_Random_Range2_cont_prog[i][nblocks-1] );
        Best_error_cont.push_back( err_Random_Range2_cont_prog[i][nblocks-1] );
    }
    
    
    //output
    Print ( "values_RW_discr.txt" , Best_range );
    Print ( "errors_RW_discr.txt" , Best_error );
    
    
    Print ( "values_RW_cont.txt" , Best_range_cont );
    Print ( "errors_RW_cont.txt" , Best_error_cont );
    
    


    return 0;
}









