#include "GeneticAlgorithm.h"

using namespace std;

//Constructor of the class
GeneticAlgorithm::GeneticAlgorithm(int pop, int city,vector < vector <double> > coord){
    m_generator = new TRandom3();
    m_Npop=pop;
    m_Ncity=city;
    
    vector <int> vector_city;//Vector long Ncity (aka new elements for m_population)
    int city_coin;//Random variable to select city to put in the chromosome
    for( int individual=1; individual<=m_Npop; individual++ ){
        vector_city.clear();
        vector_city.push_back(1);//I will always start from the city one to reduce degeneration
        vector<int> city_list(31);
        iota(city_list.begin(), city_list.end(), 2);
        for( int city=2; city<=m_Ncity; city++ ){
            city_coin=int( m_generator->Uniform(0, city_list.size() ) );
            
            vector_city.push_back( city_list[city_coin] );
            city_list.erase (city_list.begin()+int(city_coin));
        }
        m_population.push_back( vector_city );
    }
    
    vector <double> x_y;
    for( int city=0; city<m_Ncity; city++ ){
        x_y.clear();//Coordinates of every city
        for( int x=0 ; x < 2 ; x++ ){
            x_y.push_back(coord[city][x]);//I take the coordinates of the cities
        }
        m_coordinates.push_back(x_y);
    }
    
    
    Fitness();//I calculate the fitness of the new population
    
    //Just to check:
    int print=0;
    if(print){
        cout<<"Starting Population: "<<endl;
        Print(m_population);//Print is a Function from "funzioni.h"
        //cout<<"m_coordinates: "<<endl;
        //Print(m_coordinates);
        //cout<<"fitness: "<<endl;
        //Print(m_fitness);
    }
    
}


//This method creates a New Generation of individuals
void GeneticAlgorithm::NewGeneration(){
    Fitness();//calculate the fitness of the new population
    vector < vector <int> > new_popolation,offspring;
    int coin;//Random variable
    do
    {//50% I crossover, 50% I select elements of the old generation
        coin = int( m_generator->Uniform(0,100) );
        if(coin<70)
            offspring=CrossOver();
        else
            offspring=Selection();
        new_popolation.push_back( offspring[0] );
        new_popolation.push_back( offspring[1] );
    }
    while( new_popolation.size()<m_Npop );
    //Pay attention: if m_Npop is odd you have to generate just one son/daughter per time
    if(new_popolation.size() != m_Npop){
        cerr<<"Npop is odd!!!"<<endl;
        exit(1);
    }
    
    m_population=new_popolation;
    //Fitness();//calculate the fitness of the new population
    
    //just to check:
    int print=0;
    if(print){
        cout<<"population: "<<endl;
        Print(m_population);
    }
}


//In this case the fitness is the length of the path (L^2 Norm)
void GeneticAlgorithm::Fitness(){
    m_fitness.clear();
    double cont=0.0;
    int city_n,city_n_2;
    for( int individual=0; individual<m_Npop; individual++ ){//cycle over the population
        cont=0.0;
        for( int city=0; city<m_Ncity-1; city++ ){//cycle over the city
            city_n = m_population[individual][city];
            city_n_2 = m_population[individual][city+1];
            for( int x=0 ; x < 2 ; x++ ){//cycle over the coordinates
                cont += pow( m_coordinates[city_n-1][x] - m_coordinates[city_n_2-1][x] ,2);
            }
        }
        city_n = m_population[individual][m_Ncity-1];
        city_n_2=1;//boundary condition: the salesman must come back home
        for( int x=0 ; x < 2 ; x++ ){
            cont += pow( m_coordinates[city_n-1][x] - m_coordinates[city_n_2-1][x] ,2);
        }
        m_fitness.push_back(cont);//fitness calculated as L2 norm
    }
    
    
    //setting The Best;
    vector <int> ordered_population;
    ordered_population = Sort_Indexes(m_fitness);//i sort indexes by the correspondent values (in the file funzioni.h)
    m_TheBestChromosome=m_population[ordered_population[0]];
    m_TheBestFitness=m_fitness[ordered_population[0]];
    
    //just to check:
    int print=0;
    if(print){
    cout<<"m_fitness: "<<endl;
    Print(m_fitness);
    }
    
}


//This method select parents
vector < vector <int> > GeneticAlgorithm::Selection(){
    vector <int> ordered_population;
    ordered_population = Sort_Indexes(m_fitness);//I sort indexes by the correspondent values
    vector < vector <int> > population_copy;
    for(int i=0;i<m_Npop;i++){
        population_copy.push_back( m_population[ordered_population[i]] );//Now is sorted by fitness
    }
    double p=5.0;
    //double p=3.0;
    int mom,dad;
    mom = int( pow( m_generator->Rndm(), p ) * m_Npop );
    do
        dad = int( pow( m_generator->Rndm(), p ) * m_Npop );
    while(mom==dad);//I want dad be different from mum
    vector < vector <int> > parents;
    parents.push_back( population_copy[mom] );
    parents.push_back( population_copy[dad] );
    
    //just to check:
    int print=0;
    if(print){
    cout<<"ordered_population:"<<endl;
    Print(ordered_population);
    //cout<<"parents: "<<endl;
    //Print(parents);
    }
    
    return parents;
    
}

//Method in which make crossover operations
vector < vector <int> > GeneticAlgorithm::CrossOver(){
    vector < vector <int> > Parents=Selection();
    vector <int> mom=Parents[0];
    vector <int> dad=Parents[1];
    vector <int> daughter=Parents[0];//at the beginning daughter is equal to mom
    vector <int> son=Parents[1];//at the beginning son is equal to dad
    //piece_* vectors exist because i do not change all the genes at time: just a piece.
    vector <int> piece_son;
    vector <int> piece_daughter;
    vector <int> piece_mom;
    vector <int> piece_dad;
    
    int  length = int( m_generator->Rndm() * m_Ncity/2 ); //I select a number between [0,15]
    int start = int( m_generator->Uniform(1,m_Ncity-length) ); //I select a number between [1,Ncity-1]
   
       for(int i=1 ; i < length; i++ )
       {
           piece_mom.push_back( mom[start+i] );
           piece_dad.push_back( dad[start+i] );
       }
    //"Comparing" implements crossover operations
    piece_son=Comparing(mom,piece_dad);
    piece_daughter=Comparing(dad,piece_mom);
    for(int i=1 ; i < length; i++ )
    {
        daughter[start+i]= piece_daughter[i-1];
        son[start+i]= piece_son[i-1];
    }
    vector < vector <int> > OffSpring;
    OffSpring.push_back( daughter );
    OffSpring.push_back( son );
    return OffSpring;
}


//This method calls, with fixed probability, all kinds of mutation that i created.
void GeneticAlgorithm::Mutation(){
    int coin1 = int( m_generator->Uniform(0,100) );
    int coin2 = int( m_generator->Uniform(0,100) );
    int chromosome;
    for(chromosome=0;chromosome<m_Npop;chromosome++)
    {
        if(coin1<10)//2
            m_population[chromosome]=Permutation( m_population[chromosome] );
        if(coin2<10)
            m_population[chromosome]=Inversion( m_population[chromosome] );
    }
    
    int print=0;
    if(print){
    cout<<"m_population: "<<endl;
    Print(m_population);
    }
}


//First mutation's method: permutation of a piece of chromosome.
template <typename T> vector <T> GeneticAlgorithm::Permutation(const vector <T>& chromosome){
    vector <T> chromosome_copy=chromosome;
    int  length = int( m_generator->Rndm() * m_Ncity-1 )+2; //I select a numberbetween [1,32]
    int start = int( m_generator->Uniform(1,m_Ncity) ); //I select a number between [2,Ncity]
    vector <T> piece;
    for(int i=1 ; i < length; i++ )
    {
        //Boundary condition: if you exceed the limit, you start from the position 1 (not 0)
        if( (start+i) >= m_Ncity)
            piece.push_back( chromosome_copy[start+i-m_Ncity+1] );
        else
            piece.push_back( chromosome[start+i] );
    }
    
    next_permutation(piece.begin(), piece.end());//From algorithm library, it permutes the vector.
      for(int i=1 ; i < length; i++ )
      {
          //Boundary condition: if you exceed the limit, you start from the position 1 (not 0)
          if( (start+i) >= m_Ncity)
              chromosome_copy[start+i-m_Ncity+1]= piece[i-1];
          else
              chromosome_copy[start+i]= piece[i-1];
      }
    return chromosome_copy;
}

//Second mutation's method: inversion of a piece of chromosome.
template <typename T> vector <T> GeneticAlgorithm::Inversion(const vector <T>& chromosome){
    vector <T> chromosome_copy=chromosome;
    int  length = int( m_generator->Rndm() * m_Ncity-1 )+2; //I select a numberbetween [1,32]
    int start = int( m_generator->Uniform(1,m_Ncity) ); //I select a number between [2,Ncity]
    vector <int> piece;
    for(int i=1 ; i < length; i++ )
    {
        //Boundary condition: if you exceed the limit, you start from the position 1 (not 0)
        if( (start+i) >= m_Ncity)
            piece.push_back( chromosome_copy[start+i-m_Ncity+1] );
        else
            piece.push_back( chromosome[start+i] );
    }
    reverse(piece.begin(),piece.end());//From algorithm library, it inverses the vector.
    for(int i=1 ; i < length; i++ )
    {
        //Boundary condition: if you exceed the limit, you start from the position 1 (not 0)
        if( (start+i) >= m_Ncity)
            chromosome_copy[start+i-m_Ncity+1]= piece[i-1];
        else
            chromosome_copy[start+i]= piece[i-1];
    }
    return chromosome_copy;
}

/*
 This method implements the mechanism of the crossover operator:
 given a vector(v_compared) to be compared and a vector (v_to_change) to be changed (of smaller size),
 such that all the values of v_to_change are included in v_compared, "Comparing" changes the order of v_to_change in the
 same order you can find this values in v_compared.
 */
//Pay attention it works only if you have positive values in the vectors
vector <int> GeneticAlgorithm::Comparing(const vector <int>& v_compared, const vector <int>& v_to_change){
    vector <int> v_changed;//vector changed
    vector <int> v_compared_copy=v_compared;//vector must be compared
    int contained;//Boolen variable
    for(int city=0; city<v_compared.size(); city++){
        contained=0;
        for(int i=0; i<v_to_change.size(); i++)
        {
            if( v_compared_copy[city] == v_to_change[i] )
                contained=1;
        }
        if(!contained)
            v_compared_copy[city]=-1;// if you have negative values change this condition!
    }
    for(int city=0; city<v_compared.size(); city++){
        if( v_compared_copy[city] !=-1)
            v_changed.push_back( v_compared_copy[city] );
    }
    
    return v_changed;
}


//Below just some methods to get private staffs
vector < vector <int> > GeneticAlgorithm::GetPopulation(){
    return m_population;
}
vector <double> GeneticAlgorithm::GetFitness(){
    return m_fitness;
}
vector <int> GeneticAlgorithm::GetTheBestChromosome(){
    return m_TheBestChromosome;
}
double GeneticAlgorithm::GetTheBestFitness(){
    return m_TheBestFitness;
}
double GeneticAlgorithm::GetAverageFitness(){
    vector <int> ordered_population;
    ordered_population = Sort_Indexes(m_fitness);//i sort indexes by the correspondent values
    vector <int> best_half;
    for(int chromosome=0;chromosome<int(m_Npop/2);chromosome++)
        best_half.push_back( m_fitness[ ordered_population[chromosome] ] );
    
    return CalcolaMedia(best_half);//You can find this function in "funzioni.h"
}
