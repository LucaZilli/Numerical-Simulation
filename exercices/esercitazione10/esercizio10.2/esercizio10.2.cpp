#include "GeneticAlgorithm.h"
#include <iostream>
#include <cmath>
#include "mpi.h"

using namespace std;

vector < vector<double> > ReadRows( const char* filename , int N,int M);

int main (int argc, char *argv[]){
    
    int size, rank, itag=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status stat1;
    
    if(size != 4){
        cerr<<endl<<"use 4 processors"<<endl;
        return 1;
    }
    
    Random* rnd1;
    rnd1=new Random;
 
    //Random rnd;
    int seed[4];
    int p1, p2,t1,t2;
    ifstream Primes("Primes");
    if (Primes.is_open()){
        for(int i=0; i<size; i++) {
            Primes >> t1 >> t2;
            if(rank==i) {
                p1=t1;
                p2=t2;
            }
        }
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("seed.in");
    string property;
    if (input.is_open()){
        while ( !input.eof() ){
            input >> property;
            if( property == "RANDOMSEED" ){
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd1->SetRandom(seed,p1,p2);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;
    

    //Initialization of the variables of the GA
    int Npop=100;
    int Ncity=32;
    int Ngen=600;
    int Nprocess=4;
    int imigration=20;
    vector <double> x_y;
    
    int Bestsend[Ncity];
    int Bestreceive[Ncity];
    int order[Nprocess+1];
    
    
    //Coordinates:
    vector < vector <double> > coordinates_square;
    coordinates_square=ReadRows("coordinates_square.txt",32,2);
    vector <double> BestPath_Length2_square;
    vector <double> BestHalf_Length2_square;
    vector <int> BestPath_square;
    
    
    //I create object of class GA
    GeneticAlgorithm MyGA_sqaure(rnd1,Npop,Ncity,coordinates_square);

    //I create a new offspring 5000 times
    for(int i=0 ; i< Ngen; i ++)
    {
        MyGA_sqaure.NewGeneration();
        /*
        cout<<"Bestsend:"<<endl;
        for(int j=0 ; j< Ncity; j ++){
            cout<<Bestsend[j]<<endl;
        }
         */
        if(i%50==0)
        {
            //I calculate the Legth of path:
            cout<<"number of steps: "<<i<<endl;
            BestPath_Length2_square.push_back( MyGA_sqaure.GetTheBestFitness() );
            BestHalf_Length2_square.push_back( MyGA_sqaure.GetAverageFitness() );
        }
        if((i%imigration==0)&&(i!=0)) {
            /*
            if(rank==0){
                cout<<endl<<"i am the rank "<<rank<<" and the best is : "<<MyGA_sqaure.GetTheBestFitness()<<endl;
            }
            if(rank==1){
                cout<<endl<<"i am the rank "<<rank<<" and the best is :"<<MyGA_sqaure.GetTheBestFitness()<<endl;
            }
            if(rank==2){
                cout<<endl<<"i am the rank "<<rank<<" and the best is :"<<MyGA_sqaure.GetTheBestFitness()<<endl;
            }
            if(rank==3){
                cout<<endl<<"i am the rank "<<rank<<" and the best is :"<<MyGA_sqaure.GetTheBestFitness()<<endl;
            }
            cout<<endl;
             */
            if(rank==0) {
                vector<int> rank_list(4);
                iota(rank_list.begin(), rank_list.end(), 0);
                rank_list.push_back(0);
                //cout<<endl<<"rank list:"<<endl;Print(rank_list);cout<<endl;
               
                random_shuffle(rank_list.begin()+1, rank_list.end()-1);
                //cout<<endl<<"rank list:"<<endl;Print(rank_list);cout<<endl;

                for(int i=0; i<=size; i++) order[i]=rank_list[i];
            }
        
            MPI_Bcast(order,size+1,MPI_INT,0, MPI_COMM_WORLD);//I want that all the ranks are aware of the order
            //labelsend=MyGA_sqaure.SendTheBest();
            vector <int> Best(32);
            Best=MyGA_sqaure.GetTheBestChromosome();
            for(int k=0; k<Ncity; k++)Bestsend[k]=Best[k];
            //for(int k=0; k<Ncity; k++)cout<<Bestsend[k]<<" ";cout<<endl;
            
            for(int iorder=0; iorder<size; iorder++) {
                if(rank==order[iorder]) {
                    itag=1;
                    MPI_Send(Bestsend, Ncity, MPI_INT, order[iorder+1], itag, MPI_COMM_WORLD);
                }
                if(rank==order[iorder+1]) {
                    itag=1;
                    MPI_Recv(Bestreceive, Ncity, MPI_INT, order[iorder], itag, MPI_COMM_WORLD, &stat1);
                }
            }
            //for(int k=0; k<Ncity; k++)cout<<Bestreceive[k]<<" ";cout<<endl;
            MyGA_sqaure.ReceiveTheBest(Bestreceive);
            /*
            if(rank==0){
                        cout<<endl<<"i am the rank "<<rank<<" and the best is : "<<MyGA_sqaure.GetTheBestFitness()<<endl;
                       }
            if(rank==1){
                        cout<<endl<<"i am the rank "<<rank<<" and the best is :"<<MyGA_sqaure.GetTheBestFitness()<<endl;
                       }
            if(rank==2){
                        cout<<endl<<"i am the rank "<<rank<<" and the best is :"<<MyGA_sqaure.GetTheBestFitness()<<endl;
                        }
            if(rank==3){
                        cout<<endl<<"i am the rank "<<rank<<" and the best is :"<<MyGA_sqaure.GetTheBestFitness()<<endl;
                       }
                       cout<<endl;
             */
             
        }
            if(i !=Ngen-1 )
                MyGA_sqaure.Mutation();
    }
    
  
    //output:
    cout<<endl<<endl<<"In the square: "<<endl;
    BestPath_square=MyGA_sqaure.GetTheBestChromosome();
    cout<<"The Best path: "<<endl;
    Print( BestPath_square );
    cout<<endl<<"The Best Length^2: "<<BestPath_Length2_square[ BestPath_Length2_square.size()-1 ]<<endl;
    
    string string_best_path_L2="BestPath_Length2_rank" + to_string(rank) + ".txt";
    string string_best_half_L2="BestHalf_Length2_rank" + to_string(rank) + ".txt";
    string string_best_path="BestPath_rank" + to_string(rank) + ".txt";
    
    Print(string_best_path_L2,BestPath_Length2_square);
    Print(string_best_half_L2,BestHalf_Length2_square);
    Print(string_best_path,BestPath_square);
    
    cout<<endl;
    
    MPI_Finalize();

    rnd1->SaveSeed();
    return 0;
}


vector < vector<double> > ReadRows( const char* filename , int N,int M) {

    vector < vector<double> > v;
    vector<double> x_y;
    ifstream fin (filename);
    assert(fin && "file non esiste");
    if( !fin )
    {
        cout << "file non esistente" << endl;
        exit(0);
    }
    else
    {
        for( int k=0 ; k<N ; k++) {
            x_y.clear();
            for( int j=0 ; j<M ; j++){
                double valore=0;
                fin >> valore;
                x_y.push_back(valore);
               }
                v.push_back(x_y);
        
                assert(!(fin.eof()) && "lettura file terminata");
        
                if( fin.eof() ) {
                    cout << "ho finito i dati" << endl;
                    exit(1);
                }
        }
           
    }
    return v;
}
