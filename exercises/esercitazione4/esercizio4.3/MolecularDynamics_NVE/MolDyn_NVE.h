/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include "funzioni.h"

//BOOlean parameter
double m_BOOL;

//parameters, observables
const int m_props=4;
int n_props;
int iv,ik,it,ie;
double stima_pot, stima_kin, stima_etot, stima_temp;

// averages
double acc,att;

//configuration
const int m_part=108;
double x[m_part],y[m_part],z[m_part],xold[m_part],yold[m_part],zold[m_part];
double vx[m_part],vy[m_part],vz[m_part];

// thermodynamical state
int npart;
double energy,temp,vol,rho,box,rcut;

// simulation
int nstep, iprint, seed;
double delta;

//functions
void Input(void);
void Move(void);
void ConfFinal(void);
void ConfXYZ(int);
void Measure(void);
double Force(int, int);
double Pbc(double);

//blocks
vector <double> data_epot;
vector <double> ave_epot;
vector <double> av2_epot;
vector <double> ave_epot_prog;
vector <double> av2_epot_prog;
vector <double> err_epot_prog;

vector <double> data_ekin;
vector <double> ave_ekin;
vector <double> av2_ekin;
vector <double> ave_ekin_prog;
vector <double> av2_ekin_prog;
vector <double> err_ekin_prog;

vector <double> data_etot;
vector <double> ave_etot;
vector <double> av2_etot;
vector <double> ave_etot_prog;
vector <double> av2_etot_prog;
vector <double> err_etot_prog;

vector <double> data_temp;
vector <double> ave_temp;
vector <double> av2_temp;
vector <double> ave_temp_prog;
vector <double> av2_temp_prog;
vector <double> err_temp_prog;

//constants of Argon in IS units
double Kb = 1.380658e-23;
double epsilon = 120. * Kb;
double sigma = 0.34e-9;
double m = 1.6605e-27 * 39.948;


/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
