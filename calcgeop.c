
#include <stdio.h>
#include <math.h>
#include "calcgeop.h"


#define A 6378137               //semimajor axis (m)
#define B 6356752.3141         // semiminor axis (m)
#define W 7292115e-11           // angular velocity (rad/s)
#define GM 3986005e8            // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715         // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685         // Polar normal gravity (m/s^2)

 double jota2(double f,double M){
 double J2=0,foto2=0,d=0,ff2=0,m2=0,v=0,vi=0,l=0;

    ff2=f*f;
    m2=M/2;
    v=(2/3);
    d=m2*(1-( (2*f)/7 + (11*ff2)/49  ) );
    vi=f*( 1- (f/2) );
    l=vi-d;
    J2 =(2*l)/3; // printf("\n\nf :%2.20f  ",f);
    //printf("\nm :%d",M);
    //printf("\nf2 :%2.20f  ",ff2);
    // printf("\nd :%lf",d);
    //printf("\nvi :%2.20f  ",vi);
    // printf("\nvi-d :%2.20f  ",l);
    //printf("\nJ2 :%2.20f  ",J2);
    return(J2);
    }

double jota2n(double N /*grau*/,double f/*achatamento do elipsoide de referência*/,double e/*excentricidade do elipsoide*/,double J2){
 double J2n=0,en=0,e2=0,ng=0,nm=0,t;
    //N tem que variar de 2 em dois e ser par
   // printf("\n\nN :%lf ",N);
    nm=N*2;
   // printf("\n\nn2 :%lf  ",nm);
   en=pow(e,nm);
   // printf("\nen :%2.20f  ",en);
    e2=pow(e,2);
 //   printf("\ne2 :%2.20f  ",e2);
    ng=pow(-1,N+1);
  //  printf("\nng :%2.20f  ",ng);
    J2n=ng*((3*en)/((nm+1)*(nm+3)))*(1-N+((5*N)/e2)*J2);
  //  printf("\nJ2n :%2.20f l  ",J2n);
    return(J2n);
    }

double CoefTzonaispares(double GMg,double R,/*double f achatamento do elipsoide de referência,int M/*ordem,*/int N ,/*grau*/double J2,double J2n,double k){
double coefZ=0,n=0,l=0,ar=0,c=0;

    l=2*k+1;
  //  printf("\nl :%2.20f l  ",l);
    n=sqrt(l);
   //  printf("\nn :%2.20f l  ",n);
    c=GM/GMg;
  //  printf("\nc :%2.20f l  ",c);
    ar=A/R;
  //  printf("\nar:%2.20f l  ",ar);
    ar=pow(ar,N);
  //  printf("\nar:%2.20f l  ",ar);
    coefZ=J2n/n;
 //   printf("\ncoefZ:%2.20f l  ",coefZ);
    //coefZ=coefZ*ar*(GM/GMg);
    //printf("\ncoefZ:%2.20f l  ",coefZ);

    return(coefZ);
    }

double SigCoefTzonaispares(double GMg,double R,/*double f achatamento do elipsoide de referência,int M/*ordem,*/int N ,double coefZ/*Tzonais  */){
    double ScoefZ=0,n=0,l=0,ar=0,c=0;

    ar=A/R;
    ScoefZ=coefZ*ar*(GM/GMg);
   // printf("\ncoefZ:%2.20f l  ",coefZ);

     return(ScoefZ);
    }
