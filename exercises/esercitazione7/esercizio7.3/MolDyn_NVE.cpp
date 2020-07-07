/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <stdlib.h>     // srand, rand: to generate random number
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "MolDyn_NVE.h"


using namespace std;

int main(){
    
    cout<<"data_g.size() "<<data_g.size()<<endl<<endl;
    Input();             //Inizialization
    int nconf = 1;
    //blocks' method parameters
    int N=100;
    int L=int(nstep/(10*N));//i divided by 10 because Measure() works one step out of ten
    //same algorithm
    for(int istep=1; istep <= nstep; ++istep){
        Move();           //Move particles with Verlet algorithm
        if(istep%iprint == 0) cout << "Number of time-steps: " << istep << endl;
        if(istep%10 == 0){
            Measure(); //Properties measurement (here i use the vectors data to save the values for blocks averages)
            //ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"!
            nconf += 1;
        }
    }
    ConfFinal();         //Write final configuration to restart
    cout<<"data_g.size() "<<data_g.size();
    
    //classic block method
    for(int i=0;i<N;i++){
        double sum_epot=0;
        double sum_ekin=0;
        double sum_etot=0;
        double sum_temp=0;
        vector <double> sum_g(100,0.);
        for(int j=0;j<L;j++){
            sum_epot+=data_epot[j+i*L];
            sum_ekin+=data_ekin[j+i*L];
            sum_etot+=data_etot[j+i*L];
            sum_temp+=data_temp[j+i*L];
            for(int k=0;k<nbins;k++){
                sum_g[k]+=data_g[j+i*L][k];
            }
            
        }
        ave_epot.push_back(sum_epot/L);
        av2_epot.push_back((sum_epot/L)*(sum_epot/L));
        ave_ekin.push_back(sum_ekin/L);
        av2_ekin.push_back((sum_ekin/L)*(sum_ekin/L));
        ave_etot.push_back(sum_etot/L);
        av2_etot.push_back((sum_etot/L)*(sum_etot/L));
        ave_temp.push_back(sum_temp/L);
        av2_temp.push_back((sum_temp/L)*(sum_temp/L));
        
        vector<double> zeros(100, 0.);
        ave_g.push_back( zeros );
        av2_g.push_back( zeros );
        for(int k=0;k<nbins;k++){
            double r;
            double volume;
            r=(k)*bin_size;
            volume=4.0/3.0*M_PI*( pow( r + bin_size ,3) - pow(r,3) );
            double g=sum_g[k]/L/((double)npart*rho*volume);
            ave_g[ave_g.size()-1][k]=g;
            av2_g[av2_g.size()-1][k]=g*g;
        }
    }
    
    
    for(int i=0;i<N;i++){
        ave_epot_prog.push_back(0);
        av2_epot_prog.push_back(0);
        
        ave_ekin_prog.push_back(0);
        av2_ekin_prog.push_back(0);
        
        ave_etot_prog.push_back(0);
        av2_etot_prog.push_back(0);
        
        ave_temp_prog.push_back(0);
        av2_temp_prog.push_back(0);
        
        vector<double> zeros(100, 0.);
        ave_g_prog.push_back( zeros );
        av2_g_prog.push_back( zeros );
        err_g_prog.push_back( zeros );
        
        for(int j=0;j<i+1;j++){
            ave_epot_prog[i] += ave_epot[j];
            av2_epot_prog[i] += av2_epot[j];
            
            ave_ekin_prog[i] += ave_ekin[j];
            av2_ekin_prog[i] += av2_ekin[j];
            
            ave_etot_prog[i] += ave_etot[j];
            av2_etot_prog[i] += av2_etot[j];
            
            ave_temp_prog[i] += ave_temp[j];
            av2_temp_prog[i] += av2_temp[j];
            
            for(int k=0;k<nbins;k++){
                ave_g_prog[i][k] += ave_g[j][k];
                av2_g_prog[i][k] += av2_g[j][k];
            }

        }
        ave_epot_prog[i]=ave_epot_prog[i]/(i+1);
        av2_epot_prog[i]=av2_epot_prog[i]/(i+1);
        err_epot_prog.push_back(error(ave_epot_prog,av2_epot_prog,i));
        
        ave_ekin_prog[i]=ave_ekin_prog[i]/(i+1);
        av2_ekin_prog[i]=av2_ekin_prog[i]/(i+1);
        err_ekin_prog.push_back(error(ave_ekin_prog,av2_ekin_prog,i));
        
        ave_etot_prog[i]=ave_etot_prog[i]/(i+1);
        av2_etot_prog[i]=av2_etot_prog[i]/(i+1);
        err_etot_prog.push_back(error(ave_etot_prog,av2_etot_prog,i));
        
        ave_temp_prog[i]=ave_temp_prog[i]/(i+1);
        av2_temp_prog[i]=av2_temp_prog[i]/(i+1);
        err_temp_prog.push_back(error(ave_temp_prog,av2_temp_prog,i));
        
        for(int k=0;k<nbins;k++){
            ave_g_prog[i][k]=ave_g_prog[i][k]/(i+1);
            av2_g_prog[i][k]=av2_g_prog[i][k]/(i+1);
            if(i==0)
                err_g_prog[i][k]=0;
            else{
                err_g_prog[i][k]=sqrt((av2_g_prog[i][k]-ave_g_prog[i][k]*ave_g_prog[i][k])/i);
            }
                                    
        }
    }
    
    Print ( "ave_epot.out" , ave_epot_prog );
    Print ( "errori_epot.out" , err_epot_prog );
    
    Print ( "ave_ekin.out" , ave_ekin_prog );
    Print ( "errori_ekin.out" , err_ekin_prog );
    
    Print ( "ave_etot.out" , ave_etot_prog );
    Print ( "errori_etot.out" , err_etot_prog );
    
    Print ( "ave_temp.out" , ave_temp_prog );
    Print ( "errori_temp.out" , err_temp_prog );
    
    Print ( "ave_g.out" , ave_g_prog[N-1] );
    Print ( "errori_g.out" , err_g_prog[N-1] );
    
    
    return 0;
}


void Input(void){ //Prepare all stuff for the simulation
    ifstream ReadInput,ReadConf;
    double ep, ek, pr, et, vir;
    
    cout << "Classic Lennard-Jones fluid        " << endl;
    cout << "Molecular dynamics simulation in NVE ensemble  " << endl << endl;
    cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
    cout << "The program uses Lennard-Jones units " << endl;
    
    seed = 1;    //Set seed for random numbers
    srand(seed); //Initialize random number generator
    
    ReadInput.open("input.dat"); //Read input
    
    ReadInput >> m_BOOL;

    ReadInput >> temp;

    ReadInput >> npart;
    cout << "Number of particles = " << npart << endl;
    
    ReadInput >> rho;
    cout << "Density of particles = " << rho << endl;
    vol = (double)npart/rho;
    cout << "Volume of the simulation box = " << vol << endl;
    box = pow(vol,1.0/3.0);
    cout << "Edge of the simulation box = " << box << endl;
    
    ReadInput >> rcut;
    ReadInput >> delta;
    ReadInput >> nstep;
    ReadInput >> iprint;

    cout << "The program integrates Newton equations with the Verlet method " << endl;
    cout << "Time step = " << delta << endl;
    cout << "Number of steps = " << nstep << endl << endl;
    ReadInput.close();

//Prepare array for measurements
    iv = 0; //Potential energy
    ik = 1; //Kinetic energy
    ie = 2; //Total energy
    it = 3; //Temperature
    n_props = 4; //Number of observables
    
    
//measurement of g(r)
    nbins = 100;
    bin_size = (box/2.0)/(double)nbins;
    //cout<<"bin_size "<<bin_size<<endl;


//Read initial configuration
    cout << "Read initial configuration from file config.0 " << endl << endl;
    
    ReadConf.open("config.0");
    for (int i=0; i<npart; ++i){
        ReadConf >> x[i] >> y[i] >> z[i];
        x[i] = x[i] * box;
        y[i] = y[i] * box;
        z[i] = z[i] * box;
    }
    
    ReadConf.close();

    if(m_BOOL==1){
        ReadConf.open("old.0");
        for (int i=0; i<npart; ++i){
            ReadConf >> xold[i] >> yold[i] >> zold[i];
            xold[i] = xold[i] * box;
            yold[i] = yold[i] * box;
            zold[i] = zold[i] * box;
        }
        ReadConf.close();
        Move();
    }
    
    
    
//Prepare initial velocities
    cout << "Prepare random velocities with center of mass velocity equal to zero " << endl << endl;
    double sumv[3] = {0.0, 0.0, 0.0};
    
    if(m_BOOL==0){
        for (int i=0; i<npart; ++i){
            vx[i] = rand()/double(RAND_MAX) - 0.5;
            vy[i] = rand()/double(RAND_MAX) - 0.5;
            vz[i] = rand()/double(RAND_MAX) - 0.5;
            
            sumv[0] += vx[i];
            sumv[1] += vy[i];
            sumv[2] += vz[i];
        }
    }
    
    else{
        
        for (int i=0; i<npart; ++i){
            vx[i] = (x[i] - xold[i])/delta;
            vy[i] = (y[i] - yold[i])/delta;
            vz[i] = (z[i] - zold[i])/delta;

            sumv[0] += vx[i];
            sumv[1] += vy[i];
            sumv[2] += vz[i];
        }
        
    }
    
    for (int idim=0; idim<3; ++idim) sumv[idim] /= (double)npart;
    double sumv2 = 0.0, fs;
    for (int i=0; i<npart; ++i){
        vx[i] = vx[i] - sumv[0];
        vy[i] = vy[i] - sumv[1];
        vz[i] = vz[i] - sumv[2];

        sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
    }
    sumv2 /= (double)npart;
    
    fs = sqrt(3 * temp / sumv2);   // fs = velocity scale factor
    for (int i=0; i<npart; ++i){
        vx[i] *= fs;
        vy[i] *= fs;
        vz[i] *= fs;

        xold[i] = Pbc(x[i] - vx[i] * delta);
        yold[i] = Pbc(y[i] - vy[i] * delta);
        zold[i] = Pbc(z[i] - vz[i] * delta);
    }
    
    return;
}


void Move(void){ //Move particles with Verlet algorithm
    double xnew, ynew, znew, fx[m_part], fy[m_part], fz[m_part];

    for(int i=0; i<npart; ++i){ //Force acting on particle i
        fx[i] = Force(i,0);
        fy[i] = Force(i,1);
        fz[i] = Force(i,2);
    }
    
    for(int i=0; i<npart; ++i){ //Verlet integration scheme

        xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
        ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
        znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

        vx[i] = Pbc(xnew - xold[i])/(2.0 * delta);
        vy[i] = Pbc(ynew - yold[i])/(2.0 * delta);
        vz[i] = Pbc(znew - zold[i])/(2.0 * delta);

        xold[i] = x[i];
        yold[i] = y[i];
        zold[i] = z[i];

        x[i] = xnew;
        y[i] = ynew;
        z[i] = znew;
    }
    return;
}

double Force(int ip, int idir){ //Compute forces as -Grad_ip V(r)
    double f=0.0;
    double dvec[3], dr;

    for (int i=0; i<npart; ++i){
        if(i != ip){
            dvec[0] = Pbc( x[ip] - x[i] );  // distance ip-i in pbc
            dvec[1] = Pbc( y[ip] - y[i] );
            dvec[2] = Pbc( z[ip] - z[i] );
            
            dr = dvec[0]*dvec[0] + dvec[1]*dvec[1] + dvec[2]*dvec[2];
            dr = sqrt(dr);

            if(dr < rcut){
                f += dvec[idir] * (48.0/pow(dr,14) - 24.0/pow(dr,8)); // -Grad_ip V(r)
            }
        }
    }
  
    return f;
}

void Measure(){ //Properties measurement
    int bin;
    double v, t, vij;
    double dx, dy, dz, dr;
    ofstream Epot, Ekin, Etot, Temp;

    Epot.open("output_epot.dat",ios::app);
    Ekin.open("output_ekin.dat",ios::app);
    Temp.open("output_temp.dat",ios::app);
    Etot.open("output_etot.dat",ios::app);

    v = 0.0; //reset observables
    t = 0.0;

    //cycle over pairs of particles
    for (int i=0; i<npart-1; ++i){
        for (int j=i+1; j<npart; ++j){

            dx = Pbc( xold[i] - xold[j] );
            dy = Pbc( yold[i] - yold[j] );
            dz = Pbc( zold[i] - zold[j] );

            dr = dx*dx + dy*dy + dz*dz;
            dr = sqrt(dr);
            
            //update of the histogram of g(r)
            bin=int(dr/bin_size);
            //cout<<"bin "<<bin<<endl;
            //cout<<"bin_size "<<bin_size<<endl;
            //cout<<"dr "<<dr<<endl;
            data_g[data_g.size()-1][bin] += 2.0;

            if(dr < rcut){
                vij = 4.0/pow(dr,12) - 4.0/pow(dr,6);

                //Potential energy
                v += vij;
            }
        }
    }
    vector<double> zeros(1000, 0.);
    data_g.push_back( zeros );
        

    //Kinetic energy
    for (int i=0; i<npart; ++i) t += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
   
    //just saving data in vectors to use later for blocks averages
    stima_pot = v/(double)npart; //Potential energy per particle
    data_epot.push_back(stima_pot*epsilon);
    stima_kin = t/(double)npart; //Kinetic energy per particle
    data_ekin.push_back(stima_kin*epsilon);
    stima_temp = (2.0 / 3.0) * t/(double)npart; //Temperature
    data_temp.push_back(stima_temp*epsilon/Kb);
    stima_etot = (t+v)/(double)npart; //Total energy per particle
    data_etot.push_back(stima_etot*epsilon);

    Epot << stima_pot  << endl;
    Ekin << stima_kin  << endl;
    Temp << stima_temp << endl;
    Etot << stima_etot << endl;
    
    Epot.close();
    Ekin.close();
    Temp.close();
    Etot.close();

    return;
}


void ConfFinal(void){ //Write final configuration
    ofstream WriteConf;

    cout << "Print final configuration to file config.final " << endl << endl;
    
    WriteConf.open("config.final");
    for (int i=0; i<npart; ++i){
        WriteConf << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
    }
    WriteConf.close();
    
    WriteConf.open("old.final");
    for (int i=0; i<npart; ++i){
        WriteConf << xold[i]/box << "   " <<  yold[i]/box << "   " << zold[i]/box << endl;
    }
    WriteConf.close();
    
    return;
}

void ConfXYZ(int nconf){ //Write configuration in .xyz format
    ofstream WriteXYZ;

    WriteXYZ.open("frames/config_" + to_string(nconf) + ".xyz");
    WriteXYZ << npart << endl;
    WriteXYZ << "This is only a comment!" << endl;
    for (int i=0; i<npart; ++i){
        WriteXYZ << "LJ  " << Pbc(x[i]) << "   " <<  Pbc(y[i]) << "   " << Pbc(z[i]) <<     endl;
    }
    WriteXYZ.close();
}

double Pbc(double r){  //Algorithm for periodic boundary conditions with side L=box
        return r - box * rint(r/box);
}
/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/