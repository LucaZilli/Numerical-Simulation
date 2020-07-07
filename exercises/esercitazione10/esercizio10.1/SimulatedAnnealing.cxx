#include "SimulatedAnnealing.h"

using namespace std;

//Constructor of the class
SimulatedAnnealing::SimulatedAnnealing(double T, int city,vector < vector <double> > coord){
    m_generator = new TRandom3();
    m_beta=1./T;
    m_Ncity=city;
    
    vector <int> vector_city;//Vector long Ncity (aka new configuration)
    int city_coin;//Random variable to select city to put in the configuration
    
    vector_city.push_back(1);//I will always start from the city one to reduce degeneration
    vector<int> city_list(31);
    iota(city_list.begin(), city_list.end(), 2);
    for( int city=2; city<=m_Ncity; city++ ){
        city_coin=int( m_generator->Uniform(0, city_list.size() ) );
        vector_city.push_back( city_list[city_coin] );
        city_list.erase (city_list.begin()+int(city_coin));
    }
    m_Markov_Chain.push_back( vector_city );
    m_configuration=vector_city;

    m_TheBestEnergy=100000000000.;
    
    vector <double> x_y;
    for( int city=0; city<m_Ncity; city++ ){
        x_y.clear();//Coordinates of every city
        for( int x=0 ; x < 2 ; x++ ){
            x_y.push_back(coord[city][x]);//I take the coordinates of the cities
        }
        m_coordinates.push_back(x_y);
    }
    
    m_accepted=0.0;
    m_attempted=0.0;
    //Energy();//I calculate the energy of the new configuration, no i do not
    
    //Just to check:
    int print=1;
    if(print){
        cout<<"Markov_Chain at t=0: "<<endl;
        Print(m_Markov_Chain);//Print is a Function from "funzioni.h"
        //cout<<"m_coordinates: "<<endl;
        //Print(m_coordinates);
        //cout<<"fitness: "<<endl;
        //Print(m_fitness);
    }
    
}

void SimulatedAnnealing::SetBetha(double T){
    m_beta=1./T;
}


//This method move the markov chain
void SimulatedAnnealing::Move(){
    vector <int>  new_configuration,old_configuration;
    double energy_old,energy_new,p;//Random variable
    old_configuration=m_Markov_Chain[ m_Markov_Chain.size() - 1 ];
    new_configuration=Mutation(old_configuration);
    energy_old=Energy(old_configuration);
    energy_new=Energy(new_configuration);
    
    p = exp(m_beta*(energy_old-energy_new));
    if(p >= m_generator->Rndm())
      {
          m_Markov_Chain.push_back(new_configuration);
          m_accepted = m_accepted + 1.0;
      }
    else
         m_Markov_Chain.push_back(old_configuration);
    m_attempted = m_attempted + 1.0;
    
    //setting the best:
    if( energy_new < m_TheBestEnergy ){
        m_TheBestEnergy=energy_new;
        m_TheBestConfiguration=new_configuration;
    }
    //just to check:
    int print=0;
    if(print){
        cout<<"m_TheBestEnergy :"<<m_TheBestEnergy<<endl;
        cout<<"energy_old :"<<energy_old<<endl;
        cout<<"energy_new :"<<energy_new<<endl;
        //cout<<"Markov_Chain: "<<endl;
        //Print(m_Markov_Chain);
    }
}


//In this case the energy is the length of the path (L^2 Norm)
double SimulatedAnnealing::Energy(const vector <int> configuration){
    
    int city_n,city_n_2;
    double ene=0.0;
    for( int city=0; city<m_Ncity-1; city++ ){//cycle over the city
        city_n = configuration[city];
        city_n_2 = configuration[city+1];
        for( int x=0 ; x < 2 ; x++ ){//cycle over the coordinates
            ene += pow( m_coordinates[city_n-1][x] - m_coordinates[city_n_2-1][x] ,2);
        }
    }
    city_n = configuration[m_Ncity-1];
    city_n_2=1;//boundary condition: the salesman must come back home
    for( int x=0 ; x < 2 ; x++ ){
        ene += pow( m_coordinates[city_n-1][x] - m_coordinates[city_n_2-1][x] ,2);
    }
    
    
    return ene;
    
}



//This method calls, with fixed probability, all kinds of mutation that i created.
vector <int> SimulatedAnnealing::Mutation(const vector <int> configuration){
    int coin = int( m_generator->Uniform(0,100) );
    vector <int> newconfiguration;
    
    if(coin<50)
        newconfiguration=Permutation( configuration );
    else
        newconfiguration=Inversion( configuration );
    
    
    int print=0;
    if(print){
        cout<<"oldconfiguration: "<<endl;
        Print(configuration);
        cout<<endl<<"newconfiguration: "<<endl;
        Print(newconfiguration);
        cout<<endl;
    }
    
    return newconfiguration;
}


//First mutation's method: permutation of a piece of chromosome.
template <typename T> vector <T> SimulatedAnnealing::Permutation(const vector <T>& chromosome){
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
    
    next_permutation(piece.begin(), piece.end());//From "algorithm" library. It permutes the vector.
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
template <typename T> vector <T> SimulatedAnnealing::Inversion(const vector <T>& chromosome){
    vector <T> chromosome_copy=chromosome;
    int  length = int( m_generator->Rndm() * m_Ncity-1 )+2; //I select a numberbetween [2,Ncity]
    int start = int( m_generator->Uniform(1,m_Ncity) ); //I select a number between [1,Ncity-1]
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



//Below just some methods to get private staffs
vector <int> SimulatedAnnealing::GetTheBestConfiguration(){
    return m_TheBestConfiguration;
}
double SimulatedAnnealing::GetTheBestEnergy(){
    return m_TheBestEnergy;
}

double SimulatedAnnealing::GetAcceptance(){
    if (m_attempted==0){
        cerr<<endl<<"we did not start yet"<<endl;
        return 0;
    }

    return m_accepted/m_attempted;
}
