#ifndef __SimulatedAnnealing__h__
#define __SimulatedAnnealing__h__

#include "funzioni.h"
#include <TRandom3.h>
#include <algorithm>
#include <iostream>
#include <cmath>

class SimulatedAnnealing {

public:

    //Constructor and distructor of the class
    SimulatedAnnealing(double, int,vector < vector <double> >);
    ~SimulatedAnnealing(){;};
    void SetBetha(double);
    
    //Methods needed to move
    double Energy(const vector <int>);
    void Move();
    
    //Methods to mutate the configuration
    vector <int> Mutation( const vector <int>);
    template <typename T> vector <T> Permutation(const vector <T>&);
    template <typename T> vector <T> Inversion(const vector <T>&);
    
    //Methods to get privates variables
    vector <int> GetTheBestConfiguration();
    double GetTheBestEnergy();
    double GetAcceptance();
    
    
private:

    TRandom3* m_generator;//To generate random number
    double m_beta;//1/T
    int m_Ncity;//Number of different cities
    vector < vector <int> > m_Markov_Chain;//vector of configuration
    double m_accepted;
    double m_attempted;
    vector <int> m_configuration;//vector long Ncity which remember the current configuration
    vector<double> m_Energy;//vector of energy at each iteration of the algorithm
    vector < vector <double> > m_coordinates;//Matrix of size Ncityx2, which every rows contain the coordinates of one city
    vector <int> m_TheBestConfiguration;//Variable made to remember the best configuration
    double m_TheBestEnergy;//the best energy
    };

#endif
