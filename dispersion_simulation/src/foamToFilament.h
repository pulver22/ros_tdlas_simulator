#ifdef __cplusplus
 extern "C" {
 #endif

#ifndef FOAMTOFILAMENT_H
#define FOAMTOFILAMENT_H

#include <string.h>

#define st2 "/U"
#define startTime 0
#define endTime 100
#define dT "001.0"
#define deltaT 1
#define sT "../"

#define nX 60 //300
#define nY 20 
#define nZ 5




//typedef char* string;

//class foamToFilament
//{
//private:
	void setNext1(char* st);
	void setNext2(char* st);
//public:
//	foamToFilament();
	int convert();
//};

#endif //FOAMTOFILAMENT_H

#ifdef __cplusplus
 }
 #endif
