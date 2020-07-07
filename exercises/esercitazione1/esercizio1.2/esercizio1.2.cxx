#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TAxis.h"

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

	TApplication app("app",0,0);

	int nmax = 1000000;

	
    TH1F Exp("exp", "exp", 100, 0, 100);// preparing an histogram to check immediatly if the simulation works

	for(int k=0 ; k < nmax ; k++){

		Exp.Fill(rnd.Exp(1));

	}

	TCanvas can_exp("Exp","Exp");
	can_exp.cd();
	Exp.GetXaxis()->SetTitle("x [EXP]");
	Exp.GetYaxis()->SetTitle("N");
	Exp.Draw();
    
    
    TH1F Cauchy("Cauchy", "Cauchy", 100, -2, 2);

    for(int k=0 ; k < nmax ; k++){

        Cauchy.Fill(rnd.Cauchy(0,1));
        
    }

    TCanvas can_Cauchy("Cauchy","Cauchy");
    can_Cauchy.cd();
    Cauchy.GetXaxis()->SetTitle("x [Cauchy]");
    Cauchy.GetYaxis()->SetTitle("N");
    Cauchy.Draw();
	

    //vector containing the data sampled
    vector <double> Data_Unif_S1;
    vector <double> Data_Cauchy_S1;
    vector <double> Data_Exp_S1;
    
    vector <double> Data_Unif_S2;
    vector <double> Data_Cauchy_S2;
    vector <double> Data_Exp_S2;
    
    vector <double> Data_Unif_S10;
    vector <double> Data_Cauchy_S10;
    vector <double> Data_Exp_S10;
    
    vector <double> Data_Unif_S100;
    vector <double> Data_Cauchy_S100;
    vector <double> Data_Exp_S100;
    
    for(int i=0 ; i < 10000 ; i++){//sampling of data
        Data_Unif_S1.push_back( rnd.Rannyu() );
        Data_Unif_S2.push_back( Data_Unif_S1[i] + rnd.Rannyu() );
        Data_Unif_S10.push_back( Data_Unif_S2[i] );
        
        Data_Cauchy_S1.push_back( rnd.Cauchy(0,1) );
        Data_Cauchy_S2.push_back( Data_Cauchy_S1[i] + rnd.Cauchy(0,1) );
        Data_Cauchy_S10.push_back( Data_Cauchy_S2[i] );
        
        Data_Exp_S1.push_back( rnd.Exp(1) );
        Data_Exp_S2.push_back( Data_Exp_S1[i] + rnd.Exp(1) );
        Data_Exp_S10.push_back( Data_Exp_S2[i] );
        
        for(int k=0 ; k < 8 ; k++){
            Data_Cauchy_S10[i]+=rnd.Cauchy(0,1);
            Data_Exp_S10[i]+=rnd.Exp(1);
            Data_Unif_S10[i]+=rnd.Rannyu();
        }
        
        Data_Cauchy_S100.push_back( Data_Cauchy_S10[i]);
        Data_Exp_S100.push_back( Data_Exp_S10[i]);
        Data_Unif_S100.push_back( Data_Unif_S10[i]);
        
        for(int k=0 ; k < 90 ; k++){
            Data_Cauchy_S100[i]+=rnd.Cauchy(0,1);
            Data_Exp_S100[i]+=rnd.Exp(1);
            Data_Unif_S100[i]+=rnd.Rannyu();
        }
        
        Data_Unif_S2[i]=Data_Unif_S2[i]/2.;
        Data_Unif_S10[i]=Data_Unif_S10[i]/10.;
        Data_Unif_S100[i]=Data_Unif_S100[i]/100.;
        
        Data_Cauchy_S2[i]=Data_Cauchy_S2[i]/2.;
        Data_Cauchy_S10[i]=Data_Cauchy_S10[i]/10.;
        Data_Cauchy_S100[i]=Data_Cauchy_S100[i]/100.;
        
        Data_Exp_S2[i]=Data_Exp_S2[i]/2.;
        Data_Exp_S10[i]=Data_Exp_S10[i]/10.;
        Data_Exp_S100[i]=Data_Exp_S100[i]/100.;
        
        if(i%100==0)
            cout<<endl<<"steps "<<i<<" on 10^4"<<endl;
        
        
    }
    
    Print("Data_Unif_S1.txt",Data_Unif_S1);
    Print("Data_Unif_S2.txt",Data_Unif_S2);
    Print("Data_Unif_S10.txt",Data_Unif_S10);
    Print("Data_Unif_S100.txt",Data_Unif_S100);
    
    Print("Data_Cauchy_S1.txt",Data_Cauchy_S1);
    Print("Data_Cauchy_S2.txt",Data_Cauchy_S2);
    Print("Data_Cauchy_S10.txt",Data_Cauchy_S10);
    Print("Data_Cauchy_S100.txt",Data_Cauchy_S100);
    
    Print("Data_Exp_S1.txt",Data_Exp_S1);
    Print("Data_Exp_S2.txt",Data_Exp_S2);
    Print("Data_Exp_S10.txt",Data_Exp_S10);
    Print("Data_Exp_S100.txt",Data_Exp_S100);
    
    app.Run();

    return 0;
}









