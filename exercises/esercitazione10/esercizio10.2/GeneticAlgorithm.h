#ifndef __GeneticAlgorithm__h__
#define __GeneticAlgorithm__h__

#include "random.h"
#include "funzioni.h"

class GeneticAlgorithm {

public:

    //Constructor and distructor of the class
    GeneticAlgorithm(Random*,int, int,vector < vector <double> >);
    ~GeneticAlgorithm(){;};
    
    //Methods needed to create new offspring
    void Fitness();
    void NewGeneration();
    vector < vector <int> > Selection();
    vector < vector <int> > CrossOver();
    vector <int> Comparing(const vector <int>& , const vector <int>& );
    
    //Methods to mutate the population
    void Mutation();
    template <typename T> vector <T> Permutation(const vector <T>&);
    template <typename T> vector <T> Inversion(const vector <T>&);
    
    //Methods to get privates variables
    vector < vector <int> > GetPopulation();
    vector <double> GetFitness();
    vector <int> GetTheBestChromosome();
    double GetTheBestFitness();
    double GetAverageFitness();
    
    //MPI
    //int* SendTheBest();
    void ReceiveTheBest(int*);
    
private:

    Random* m_generator;//To generate random number
    int m_Npop;//Number of population
    int m_Ncity;//Number of different genes (aka city for this particular code)
    vector < vector <int> > m_population;//Matrix of size NpopxNcity, which every row is a chromosome long Ncity
    vector <double> m_fitness;//Vector long Npop which contain for every chromosome the L2 norm of the legthness of the path
    vector < vector <double> > m_coordinates;//Matrix of size Ncityx2, which every rows contein the coordinates of one city
    vector <int> m_TheBestChromosome;//Variable made to remember the best chromosome
    double m_TheBestFitness;//the best fitness
    };

#endif
