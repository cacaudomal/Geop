//
//  geopanom.c
//  GEOP
//
//  Created by Clara on 04/06/17.
//
//

#include <stdio.h>
#include <math.h>
#include "geopanom.h"

double ganom_calcGeoidalOndu(double RaioMedio, double prlocal, int grau,int ordem,double C, double S,double plon , double ppnm){
	double GeiodHeight;

	GeiodHeight = pow((RaioMedio / prlocal),(grau + 1)) * (C * cos(ordem * (plon * M_PI/180)) + S * sin(ordem * (plon * M_PI/180))) * ppnm;

	return (GeiodHeight);
	}


double ganom_calcGeoidalAnom(double RaioMedio, double prlocal, int grau,int ordem,double C, double S,double plon , double ppnm)
	{
	double GeoidAnom=0;

	GeoidAnom = pow((RaioMedio / prlocal),(grau))*((grau - 1)/prlocal) * (C * cos(ordem * (plon * M_PI/180)) + S * sin(ordem * (plon * M_PI/180))) * ppnm;

	return(GeoidAnom);
	}

double ganom_OnduGeoid(double GMg,double prlocal,double pYo,double V){
	double N=0;

	N = (GMg/(prlocal * pYo)) * V;

	return N;
	}

double ganom_Ag(double GMg,double prlocal,double V){
	double Ag=0;
	Ag = (GMg/pow(prlocal,2)) * V;
	return Ag;
	}

double ganom_GeopAnom(double Ag){
	double GeopAnom=0;
	GeopAnom = Ag * pow(10,5);
	return GeopAnom;
	}
