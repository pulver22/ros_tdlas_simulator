#include "Filamentproperties.h"
#include <iostream>
#include <sstream>
#include <sys/select.h>
#include <ros/ros.h>
#include <stdio.h>

  float density;
  int option;
  float Chemicalvalue[10];
  float molarmass[10];

  double red=0;
  double green=0;
  double blue=0;
  double r=0;
  double g=0;
  double b=0;



  void plume_start() {

//ROS_INFO("\t Enter the gas number");
//ROS_INFO("\n ethanol=0;\n methane=1;\n hydrogen=2;\n propanol=3;\n chlorine=4;\n flurorine=5;\n acetone=6;\n neon=7;\n helium=8;\n hot air=9");

	Chemicalvalue[0]= 789;//ethanol     //these three gases can be sensed by the simulated sensor
	Chemicalvalue[1]= 0.717;//methane
	Chemicalvalue[2]= 0.08988;//hydrogen

	Chemicalvalue[3]= 803.4;//propanol   //gases heavier then air
	Chemicalvalue[4]= 3.2;//chlorine
	Chemicalvalue[5]= 1.696;//flurorine
	Chemicalvalue[6]= 1140;//acetone

	Chemicalvalue[7]= 0.9 ;//neon       //gases lighter than air
	Chemicalvalue[8]= 0.1786;//helium
	Chemicalvalue[9]= 0.93;//hot_air
	
//			std::cin>>option;
//			std::cout<<option;

}

  void color_width(double *aa, double *bb, double *cc)
				{

		if(*aa>=1)  
			{ 
			g=0.6; 
			r=0.4; 
			}
				else	
				{  
				g = *aa;  
				r=1; 
				}
  *aa=r;
  *bb=g;
  *cc=b;
   return;
	}


  void color_concentration(double *aa, double *bb, double *cc)
				{

  //float high=15000;
  //float middle= 2000;

   r=0;
   g=0;
   b=0;

	if(*aa>= HIGH_CONCENTRATION_THR){   r=1; g=0.3;}
        if(*aa> MID_CONCENTRATION_THR && *aa<HIGH_CONCENTRATION_THR){  r=1; g=0.8; } 
        if(*aa> LOW_CONCENTRATION_THR && *aa<MID_CONCENTRATION_THR){   g=1;b=0.4; } 
        if(*aa<= LOW_CONCENTRATION_THR){   g=0.8;b=1; } 

  *aa=r;
  *bb=g;
  *cc=b;
   return;
	}

