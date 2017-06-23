//
//  calcgeoid.h
//  GEOP
//
//  Created by Clara on 25/05/17.
//
//

#ifndef calcgeoidh_h
#define calcgeoidh_h

#define A 6378137              //semimajor axis (m)
#define B 6356752.3141         // semiminor axis (m)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

//raio local, colatitudes e afins


/*struct Parametros{
	double GMg;//constnte gravitacional
	double R;//raio medio da terra
	int maxdeg;//grau maximo
	double k;
	double achatamento;
	double pextc;
	};
*/ 
int calcgh_nlat(double gridsize, double maiorlon, double menorlon);

// Compute local ellipsoidal radius (rlocal)
double calcgh_rlocal(double lat, double primxect);

// Compute normal gravity Yo
double calcgh_normal_Gravdouble (double lat,double primxect,double k);

//double **calcgh_GeoidOndu(double **pnm,double **anm,double **bnm, struct processamentotzonaisp pproces[], struct matriz dados[], double *rlocal/*rlocal*/, double *lon, double *lat,struct Parametros cabe,double *y0,int sizecolat,int sizelong,double colatgc[]);

//latitude geocentrica
double calcgh_latgce(double lat);
double calcgh_colatgce(double latgc);


double calcgh_anmI(double grau);
double calcgh_anmII(double grau,double ordem);
double calcgh_bnm(double grau,double ordem);
void calcgh_legendre(double colatg, int nmax, double **anm, double **bnm, double **pnm);
//double calcLatitude();
//double calcGeoidAltura();

#endif /* calcgeoid_h */
