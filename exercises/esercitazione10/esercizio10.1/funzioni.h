#include <iostream>
#include <fstream>
#include <assert.h>

#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>


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
    
    
    for( int k=0 ; k<v.size() ; k++ ) cout << v[k] <<" ";
    
    
}


template <typename T> void Print ( const vector< vector<T> >& v ) {
    
    for( int k=0 ; k<v.size() ; k++ ){
        for(int j=0 ; j<v[k].size() ; j++) cout << v[k][j] << " " ;
        cout<<endl;
    }
    cout<<endl;
    
}


template <typename T> void Print ( const char* filename , const vector<T>& v) {
    
    ofstream fout(filename);
    
    if(!fout)
        cerr<< "non posso creare il file "<<filename<<endl;
    
    for( int k=0 ; k<v.size(); k++ ) fout << v[k] << endl;
    
    fout.close();
    
}


template <typename T> void Print ( const char* filename , const vector< vector<T> >& v ) {
    
    ofstream fout(filename);
    
    if(!fout)
        cerr<< "non posso creare il file "<<filename<<endl;
    
    for( int k=0 ; k<v.size() ; k++ ){
        for(int j=0 ; j<v[k].size() ; j++) fout << v[k][j] << " " ;
        fout<<endl;
    }
    fout<<endl;
    
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

// references at link https://stackoverflow.com/questions/17554242/how-to-obtain-the-index-permutation-after-the-sorting

template <typename T>
vector<int> Sort_Indexes( const vector<T> &v) {// Pay attention: it works only if you have positive values in the vector!!!!!
    //cout<<"1 check"<<endl;
    vector<T> v_copy=v;
    vector<int> index(v_copy.size(), 0);
    for (int i = 0 ; i != index.size() ; i++) {
        index[i] = i;
    }
    //cout<<"index: "<<endl;
    //Print(index);
    //cout<<"v_copy: "<<endl;
    //Print(v_copy);
    double min;
    int index_min;
    vector<T> v_copy_ordered;
    
    for (int i = 0 ; i < v_copy.size() ; i++){
        v_copy_ordered=v_copy;
        sort(v_copy_ordered.begin(),v_copy_ordered.end());
        min=v_copy_ordered[v_copy_ordered.size()-1];
        index_min=0;
        for(int j = 0 ; j < v_copy.size() ; j++){
            if(min>=v_copy[j] && v_copy[j] != -1 ){
                min=v_copy[j];
                index_min=j;
            }
           
        }
        v_copy[index_min]=-1;
        index[i]=index_min;
        //v_copy.erase(v_copy.begin()+index[i]-i);
        //cout<<"v_copy: "<<endl;
        //Print(v_copy);
    }
    
    return index;
}




