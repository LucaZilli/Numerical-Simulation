#include <iostream>
#include <fstream>
#include <assert.h>

#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;


template <typename T> vector <T> Read( const char* filename , int N) {
    
    vector<T> v;
    
    ifstream fin (filename);
    
    assert(fin && "file non esiste");
    
    if( !fin ) {
        
        cout << "file non esistente" << endl;
        
        exit(0);
        
    } else { for( int k=0 ; k<N ; k++) {
        
        T valore=0;
        
        fin >> valore;
        
        v.push_back(valore);
        
        assert(!(fin.eof()) && "lettura file terminata");
        
        if( fin.eof() ) {
            
            cout << "ho finito i dati" << endl;
            
            exit(1);
            
        } } }
    
    return v;
    
    
}



template <typename T> void Print ( const vector<T>& v ) {
    
    
    for( int k=0 ; k<v.size() ; k++ ) cout << v[k] <<endl;
    
    
}



template <typename T> void Print ( const char* filename , const vector<T>& v) {
    
    ofstream fout(filename);
    
    if(!fout)
        cerr<< "non posso creare il file "<<filename<<endl;
    
    for( int k=0 ; k<v.size(); k++ ) fout << v[k] << endl;
    
    fout.close();
    
}

template <typename T> void Print_matrix ( const char* filename , const vector< vector<T> >& v, int riga, int N ) {
    
    ofstream fout(filename);
    
    if(!fout)
        cerr<< "non posso creare il file "<<filename<<endl;
    
    
        for( int k=0 ; k<N; k++ )
            fout << v[k][riga] << endl;
        
        
    
    fout.close();
    
}



template <typename T> double CalcolaMedia( const vector<T>& v ) {
    
    double media = 0;
    
    for(int k=0 ; k<v.size() ; k++ ) {
        
        media += v[k];
        
    }
    
    media = media / double (v.size());
    
    return media;
    
}


template <typename T> double CalcolaMedia_R( const vector< vector<T> >& v , int inf, int sup) {
    
    double media = 0;
    
    for(int k=inf ; k<sup ; k++ ) {
        
        double r=0.;
        for(int i=0 ; i<v[k].size() ; i++ ){
            
            r += v[k][i] * v[k][i];
            
        }
        r = sqrt(r);
        media += r;
        
    }
    
    media = media / double (sup-inf);
    
    return media;
    
}


template <typename T> double CalcolaVarianza( const vector<T>& v ) {
    
    double media = CalcolaMedia( v );
    
    double varianza = 0;
    
    for ( int k=0 ; k<v.size() ; k++ ) {
        
        varianza += ( v[k] - media )*( v[k] - media );
        
    }
    
    varianza = varianza / double ( v.size() ) ;
    
    return varianza;
    
}


template <typename T> double CalcolaMediana( vector<T> v ) {
    
    vector<T> w=v;
    
    sort ( w.begin(), w.end() );
    
    double mediana=0;
    
    if( w.size()%2 == 0 ) {
        
        mediana = ( w[w.size()/2 - 1] + w[w.size()/2] )/ 2. ;
        
    } else {
        
        mediana = w[ w.size()/2 ];
        
    }
    
    return mediana;
    
}


template <typename T> double error(vector<T> AV,vector<T> AV2,int n){
    if (n==0)
        return 0;
    else
        return sqrt((AV2[n] - AV[n]*AV[n])/n);
    
}





