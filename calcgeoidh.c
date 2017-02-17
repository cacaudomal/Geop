#include <math.h>
#include <stdio.h>
#include "calcgeoidh.h"
#include "geomlipsref.h"

#define PI 3.14159265359
#define A 6378137              //semimajor axis (m)
#define B 6356752.3141        // semiminor axis (m)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

int calc_nlat(double gridSize,double molon1,double molon2){

    int counter=0;
    double cont=0,modcont=0,size=0;

    cont=molon1-molon2;
    modcont=modulo(cont);

    do{

        size=size+gridSize;
        counter++;

        }while(size<modcont);

    return counter;

    }

void calc_rlocal(double *lat,double *rlocale,int counti,double primxect){
    int counter=0;
    double latpi[counti+1];

    printf(" counti: %d ",counti);

    do{

        latpi[counter] = 0;
        latpi[counter] = lat[counter]*(PI/180);

        rlocale[counter] = A * sqrt(1 - (primxect * (1-primxect) * pow(sin( latpi[counter] ) , 2)) / (1 - primxect * sin( latpi[counter] )) )  ;

        printf(" rlocal[%d]: %lf\n ",counter,rlocale[counter]);
        counter++;

        }while(counter<counti);

    }

// Compute normal gravity
void normal_Gravdouble (double *lat,double *YO,int counti,double primxect,double k){

    int counter=0;
    double latpi[counti+1];

    do{

        latpi[counter] = 0;
        latpi[counter] = lat[counter]*(PI/180);

        YO[counter] = YE*( (1 + k * pow(sin(latpi[counter]) , 2) ) / sqrt(1 - primxect * pow(sin(latpi[counter]) , 2)) );

       // printf("YO[%d] : %lf , latpi[%d] : %lf lat[%d]-90 : %lf  \n ",counter,YO[counter],counter,latpi[counter],counter,lat[counter]-90);
        counter++;

        }while(counter<counti);

    }
//latitude geocentrica
double latgce(double *lat,int counti){

    double var = 0,var2 = 0,rad = 0,latgc = 0;

    printf("\n\n 1plat: %lf",lat[counti]-90);

    var = B/A;
    var2 = pow( var,2 );
    rad = tan( (lat[counti]-90)*(PI/180) );
    var = var2*rad;
    latgc = atan( var );

    printf("\n[%d]var:%lf\nvar2:%lf,rad:%lf rad*var2:%lf,latgc=%lf",counti,var,var2,rad,var2*rad,latgc);

    return latgc;
    }

double colatgce(double *latgc,int counti){

    double torad=0,colatgc=0;

    torad = latgc[counti]*180/PI;
    colatgc = 90-torad;

    printf("\n colatgc[%d]: %lf \n ",counti,colatgc);
    return colatgc;
    }
//double calcLatitude(){
    // return();
   // }


//double calcGeoidAltura(){
   // return();
    //}
