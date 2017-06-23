
#include <stdio.h>
#include <math.h>
//#include "calcgeop.h"
#include "geomlipsref.h"

#define A 6378137               //semimajor axis (m)
#define B 6356752.3141         // semiminor axis (m)
#define W 7292115e-11           // angular velocity (rad/s)
#define GM 3986005e8            // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715         // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685         // Polar normal gravity (m/s^2)


 double calcgp_jota2(double f){
    double M = 0,j2 = 0;

    M = GeoRef_calcm();
    j2 = (2 * ((f * (1 - (f/2))) - ((M/2) * (1 - ((2 * f)/7) + (11 * f * f)/49))))/3;

    return(j2);
    }


double calcgp_jota2n(double N ,double e,double J2)
    {
    double J2n=0,ng=0;

    ng = pow(-1,N+1);
    J2n = ng * ((3 * pow(e,N)) / ((2 * N + 1) * (2 * N  + 3)) ) * (1 - N + ((5 * N)/e)  * J2);

    return(J2n);
    }


double calcgp_CoefTzonaispares(int K,double J2,double J2n)
    {
    double coefZ=0,n=0,l=0;

    l = 2 * K + 1;
    n = sqrt(l);
    coefZ = (-1)*J2n/n;

    return(coefZ);
    }


double calcgp_CoefTzonaispares_p2(double GMg,double R,int N ,double coefZ/*Tzonais*/)
    {
    double ScoefZ = 0,ar = 0;

    ar = A/R;
    ScoefZ = coefZ * pow(ar,N) * (GM/GMg);

    return(ScoefZ);
    }//c2n, vetor

double calcgp_CorrecaoC(double N,double K,double GMg,double R,double e,double f)
	{
	double CorrecaoC = 0, M = 0, j2 = 0, ScoefZ = 0, ar = 0, J2n=0, ng=0, coefZ=0, n=0, l=0,count = 0;
	M = GeoRef_calcm();
	j2 = (2 * ((f * (1 - (f/2))) - ((M/2) * (1 - ((2 * f)/7) + (11 * f * f)/49))))/3;

	ng = pow(-1, N + 1);
	J2n = ng * ((3 * pow(e, N))/((2 * N + 1) * (2 * N  + 3))) * (1 - N + ((5 * N) * j2)/e);


	l = 2 * K + 1;
	n = sqrt(l);
	coefZ = (-1)*J2n/n;

	ar = A/R;
	CorrecaoC = coefZ * pow(ar,N) * (GM/GMg);

	return CorrecaoC;
	}
