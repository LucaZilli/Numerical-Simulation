#include "SimulatedAnnealing.h"
#include <iostream>
#include <cmath>
#include <TRandom3.h>

using namespace std;

//Random generator
TRandom3* generator;

//function that I need to read the coordinates of the cities from file sorted in the exercise 9.1
vector < vector<double> > ReadRows( const char* filename , int N,int M);


int main(){
    
    double T=27.005;//Initial temperature
    int nstep1=500000;//first set of steps
    int nstep2=300000;//second set of steps
    int nstep3=1000000;//third set of steps
    int Ncity=32;
    generator=new TRandom3;
    vector <double> x_y;
    
    
    //Coordinates on the cyrcle:
    vector < vector <double> > coordinates_cyrcle;
    coordinates_cyrcle=ReadRows("coordinates_cyrcle.txt",32,2);
    vector <double> BestPath_Length2_cyrcle;
    vector <int> BestPath_cyrcle;
    
    
    //Coordinates in the square:
    vector < vector <double> > coordinates_square;
    coordinates_square=ReadRows("coordinates_square.txt",32,2);
    vector <double> BestPath_Length2_square;
    vector <int> BestPath_square;
    

    //I create object of class SimulatedAnnealing
    SimulatedAnnealing MySA_square(T,Ncity,coordinates_square);
    SimulatedAnnealing MySA_cyrcle(T,Ncity,coordinates_cyrcle);

    //I move the markov chain nstep1+nstep2+nstep3 times
    double dT=0.5;
    cout<<endl<<endl<<"first set of steps nstep="<<nstep1<<endl<<endl;
    for(int i=0 ; i< nstep1; i ++)
    {
        MySA_cyrcle.Move();
        MySA_square.Move();
        if(i%10000==0)
        {
            T-=dT;
            MySA_cyrcle.SetBetha(T);
            MySA_square.SetBetha(T);
            cout<<"number of steps: "<<i<<endl;
            cout<<"T: "<<T<<endl;
            BestPath_Length2_cyrcle.push_back( MySA_cyrcle.GetTheBestEnergy() );
            BestPath_Length2_square.push_back( MySA_square.GetTheBestEnergy() );
        }
    }
    
    
    dT=0.05;
    cout<<endl<<endl<<"second set of steps nstep="<<nstep2<<endl<<endl;
    for(int i=0 ; i< nstep2; i ++)
    {
        MySA_cyrcle.Move();
        MySA_square.Move();
        if(i%10000==0)
        {
            T-=dT;
            MySA_cyrcle.SetBetha(T);
            MySA_square.SetBetha(T);
            cout<<"number of steps: "<<i<<endl;
            cout<<"T: "<<T<<endl;
            BestPath_Length2_cyrcle.push_back( MySA_cyrcle.GetTheBestEnergy() );
            BestPath_Length2_square.push_back( MySA_square.GetTheBestEnergy() );
        }
    }
    
    dT=0.005;
    cout<<endl<<endl<<"third set of steps nstep="<<nstep3<<endl<<endl;
    for(int i=0 ; i< nstep3; i ++)
    {
        MySA_cyrcle.Move();
        MySA_square.Move();
        if(i%10000==0)
        {
            T-=dT;
            MySA_cyrcle.SetBetha(T);
            MySA_square.SetBetha(T);
            cout<<"number of steps: "<<i<<endl;
            cout<<"T: "<<T<<endl;
            BestPath_Length2_cyrcle.push_back( MySA_cyrcle.GetTheBestEnergy() );
            BestPath_Length2_square.push_back( MySA_square.GetTheBestEnergy() );
        }
    }
    
    
    //output cyrcle:
    cout<<endl<<endl<<"On the cyrcle: "<<endl;
    BestPath_cyrcle=MySA_cyrcle.GetTheBestConfiguration();
    cout<<"The Best path: "<<endl;
    Print( BestPath_cyrcle );
    cout<<endl<<"The Best Length^2: "<<BestPath_Length2_cyrcle[ BestPath_Length2_cyrcle.size()-1 ]<<endl;
    Print("BestPath_Length2_cyrcle.txt",BestPath_Length2_cyrcle);
    Print("BestPath_cyrcle.txt",BestPath_cyrcle);
    
    
    
    //output square:
    cout<<endl<<endl<<"In the square: "<<endl;
    BestPath_square=MySA_square.GetTheBestConfiguration();
    cout<<"The Best path: "<<endl;
    Print( BestPath_square );
    cout<<endl<<"The Best Length^2: "<<BestPath_Length2_square[ BestPath_Length2_square.size()-1 ]<<endl;
    
    Print("BestPath_Length2_square.txt",BestPath_Length2_square);
    Print("BestPath_square.txt",BestPath_square);

    
    cout<<endl;
    
    return 0;
}

//implementatio  of the function needed to read coordinates
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
