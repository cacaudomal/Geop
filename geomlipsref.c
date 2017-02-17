
#include <stdio.h>
#include <math.h>
#include "geomlipsref.h"

#define PI 3.14159265359
#define A 6378137              //semimajor axis (m)
#define B 6356752.3141       // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

double radtodeg(double rad){
double deg=0;
    deg=180*rad/PI;
    return(deg);
    }

double degtorad(double deg){
double rad=0;

    rad=deg*PI/180;
    return rad;
    }

double dist(double val1,double val2){
double answ,powe;

    powe=val1-val2;
    printf(" \nd=%lf ",powe);
    powe=pow(powe,2);
    printf(" d=%lf ",powe);

    answ=sqrt(powe);
    printf("answ=%lf \n",answ);

    return (answ);
    }

double modulo(double val){

if(val<0){
    val=val*-1;
    }

else{
    val=val;
    }

return (val);
}

double PexctElipsRef(){

    double e=0,a2=0,b2=0,d=0,a=A,b=B;

    a2=a*a;
    b2=b*b;
    d=a2-b2;

    e=d/a2;

    return(e);

    }

double AchatmtElipsRef(){

    double f=0;

    f=(A-B)/A;

    return(f);

    }

double calcK(){

    double k=0;

    k = ((B*YP)-(A*YE))/(A*YE);

    return(k);

    }

double calcm(){

    double m=0,W2=0,A2=0;

    W2=pow(W,2);
    A2=pow(A,2);
    m = ((W2)*(A2)*B)/GM;

    return(m);

    }
