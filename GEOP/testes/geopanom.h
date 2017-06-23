//
//  geopanom.h
//  GEOP
//
//  Created by Clara on 04/06/17.
//
//

#ifndef geopanom_h
#define geopanom_h

double ganom_calcGeoidalOndu(double RaioMedio, double prlocal, int grau,int ordem,double C, double S,double plon , double ppnm);
double ganom_calcGeoidalAnom(double RaioMedio, double prlocal, int grau,int ordem,double C, double S,double plon , double ppnm);

double ganom_OnduGeoid(double GMg,double prlocal,double Yo,double V);
double ganom_Ag(double GMg,double prlocal,double V);
double ganom_GeopAnom(double Ag);


#endif /* geopanom_h */
