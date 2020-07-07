#include "GeneticAlgorithm.h"
#include <iostream>
#include <cmath>
#include <TRandom3.h>

using namespace std;

TRandom3* generator;//pseudo-random number generator

int main(){
    
    int Npop=100;
    int Ncity=32;
    generator=new TRandom3;
    vector <double> x_y;
    
    //Coordinates in the square:
    vector < vector <double> > coordinates_square;
    double L=10.0;
    for( int i=0;i<Ncity;i++){
        x_y.clear();
        x_y.push_back( generator->Uniform(0,L) );
        x_y.push_back( generator->Uniform(0,L) );
        coordinates_square.push_back(x_y);
    }
    vector <double> BestPath_Length2_square;
    vector <double> BestHalf_Length2_square;
    vector <int> BestPath_square;
    
    //Coordinates on the cyrcle:
    vector < vector <double> > coordinates_cyrcle;
    //double delta_theta = 2*M_PI/(double)Ncity;
    double theta;
    double R=10.0;
    for( int i=0;i<Ncity;i++){
        x_y.clear();
        theta=generator->Uniform(0,2*M_PI);
        x_y.push_back(R*cos(theta));
        x_y.push_back(R*sin(theta));
        coordinates_cyrcle.push_back(x_y);
    }
    vector <double> BestPath_Length2_cyrcle;
    vector <double> BestHalf_Length2_cyrcle;
    vector <int> BestPath_cyrcle;
    
    
    

    //I create object of class GA
    GeneticAlgorithm MyGA_sqaure(Npop,Ncity,coordinates_square);
    GeneticAlgorithm MyGA_cyrcle(Npop,Ncity,coordinates_cyrcle);

    //I create a new offspring 5000 times
    for(int i=0 ; i< 5001; i ++)
    {
        MyGA_cyrcle.Mutation();
        MyGA_cyrcle.NewGeneration();
        MyGA_sqaure.Mutation();
        MyGA_sqaure.NewGeneration();
        if(i%100==0)
        {
            //I calculate the Legth of path:
            cout<<"number of steps: "<<i<<endl;
            BestPath_Length2_cyrcle.push_back( MyGA_cyrcle.GetTheBestFitness() );
            BestHalf_Length2_cyrcle.push_back( MyGA_cyrcle.GetAverageFitness() );
            BestPath_Length2_square.push_back( MyGA_sqaure.GetTheBestFitness() );
            BestHalf_Length2_square.push_back( MyGA_sqaure.GetAverageFitness() );
        }
    }
    
    
    //output cyrcle:
    cout<<endl<<endl<<"On the cyrcle: "<<endl;
    BestPath_cyrcle=MyGA_cyrcle.GetTheBestChromosome();
    cout<<"The Best path: "<<endl;
    Print( BestPath_cyrcle );
    cout<<endl<<"The Best Length^2: "<<BestPath_Length2_cyrcle[ BestPath_Length2_cyrcle.size()-1 ]<<endl;
    
    Print("BestPath_Length2_cyrcle_GA.txt",BestPath_Length2_cyrcle);
    Print("BestHalf_Length2_cyrcle.txt",BestHalf_Length2_cyrcle);
    Print("BestPath_cyrcle_GA.txt",BestPath_cyrcle);
    Print("coordinates_cyrcle.txt",coordinates_cyrcle);
    
    
    //output square:
    cout<<endl<<endl<<"In the square: "<<endl;
    BestPath_square=MyGA_sqaure.GetTheBestChromosome();
    cout<<"The Best path: "<<endl;
    Print( BestPath_square );
    cout<<endl<<"The Best Length^2: "<<BestPath_Length2_square[ BestPath_Length2_square.size()-1 ]<<endl;
    
    Print("BestPath_Length2_square_GA.txt",BestPath_Length2_square);
    Print("BestHalf_Length2_square.txt",BestHalf_Length2_square);
    Print("BestPath_square_GA.txt",BestPath_square);
    Print("coordinates_square.txt",coordinates_square);
    
    cout<<endl;
    
    return 0;
}

