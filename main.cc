#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

double side = 0.5;
double cycles = 1000;
double delta_t = 0.1;
double n_particles = 1000;

//=======================================================================================================================================

class Particle{

public:

Particle(double xi, double yi, double vxi, double vyi, int ji):p_x(xi),p_y(yi),v_x(vxi),v_y(vyi),j(ji){};

double GetX(){
  return p_x;
}
double GetY(){
  return p_y;
}
double GetVX(){
  return v_x;
}
double GetVY(){
  return v_y;
}
double Distance2D(Particle Particle){
  double dist = sqrt(pow(p_x+Particle.GetX(),2)+pow(p_y+Particle.GetY(),2));
  return dist;
}
 //posizioni, velocità, numero di particelle, indice del ciclo più grande
double ForceX(vector<Particle> Particles){
  double force = 0;
  for(unsigned int i = 0; i<Particles.size(); i++){
    if(i==j){continue;}
    else force+=(epsilon*24.0/pow(Distance2D(Particles.at(i)),2))*(2*pow(sigma/Distance2D(Particles.at(i)),12)-pow(sigma/Distance2D(Particles.at(i)),6))*(Particles.at(i).GetX()-p_x);
  }
  return force;
}

double ForceY(vector<Particle> Particles){
  double force = 0;

  for(unsigned int i = 0; i<Particles.size(); i++){
    if(i==j){continue;}
    else force+=(epsilon*24.0/pow(Distance2D(Particles.at(i)),2))*(2*pow(sigma/Distance2D(Particles.at(i)),12)-pow(sigma/Distance2D(Particles.at(i)),6))*(Particles.at(i).GetY()-p_y);
  }
  return force;
}

void EvolvePos(vector<Particle> Particles,double delta_t){
    p_x+=v_x*delta_t+(0.5*ForceX(Particles)*delta_t*delta_t);
    p_y+=v_y*delta_t+(0.5*ForceY(Particles)*delta_t*delta_t);

    return;
  }


void EvolveVel(vector<Particle> Particles,vector<Particle> ParticlesPreviousStep,double delta_t){

    v_x+=(ForceX(Particles)+ForceX(ParticlesPreviousStep)*delta_t*0.5);
    v_y+=(ForceY(Particles)+ForceY(ParticlesPreviousStep)*delta_t*0.5);

    return;
  }

private:
  double p_x;
  double p_y;
  double epsilon = 1;
  double sigma = 1;
  double v_x;
  double v_y;
  int j;

};

//=======================================================================================================================================

int main() {

  srand(time(NULL));

  vector<Particle> Particles;
  ofstream fout("LENNARD.txt");
  for (unsigned int j=0; j<n_particles-1; j++){
    Particles.push_back(Particle(static_cast <double> (rand())/static_cast <double> (RAND_MAX/side),static_cast <double> (rand())/static_cast <double> (RAND_MAX/side),0,0,j));

  }

  Particles.push_back(Particle(static_cast <double> (rand())/static_cast <double> (RAND_MAX/side),static_cast <double> (rand())/static_cast <double> (RAND_MAX/side),0.0001,0.0001,n_particles-1));

  vector <Particle> temp = Particles;

  for(unsigned int i=0; i<cycles; i++){

    for(unsigned int j=0; j<temp.size(); j++){
      temp.at(j).EvolvePos(temp,delta_t);

    }

    for(unsigned int j=0; j<temp.size(); j++){
      temp.at(j).EvolveVel(temp,Particles,delta_t);

    }

    Particles = temp;

    fout << Particles.at(n_particles-1).GetX() << " " << Particles.at(n_particles-1).GetY() << endl;
  }



  return 0;
}
