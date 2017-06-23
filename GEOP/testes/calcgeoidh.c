#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "calcgeoidh.h"
#include "geomlipsref.h"
//#include "legendref.h"

#define PI 3.14159265359
#define A 6378137              //semimajor axis (m)
#define B 6356752.3141         // semiminor axis (m)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2)

int calcgh_nlat(double gridSize,double maiorlon,double menorlon){
    int counter = 0;
    double cont = 0, modcont = 0;

    cont = maiorlon - menorlon;
    modcont = GeoRef_modulo(cont);

	cont = 0;

    do	{
        cont = cont + gridSize;
        counter++;
        }while(cont < modcont);

    return counter;
    }

//local elipsoidal radius(rlocale)
double calcgh_rlocal(double lat,double primxect){
    double rlocale = 0;

    rlocale = A * sqrt(1 - (primxect * (1 - primxect) * pow(sin(lat* (M_PI/180)) , 2)) / (1 - primxect * sin(lat * (M_PI/180)) ));
    printf(" rlocal: %le\n ",rlocale);
    return rlocale;
    }

// Compute normal gravity
double calcgh_normal_Gravdouble(double lat,double primxect,double k){
	double YO = 0;

    YO = YE * ((1 + k * pow(sin(lat* (M_PI/180)) , 2)) / sqrt(1 - primxect * pow(sin(lat * (M_PI/180)) , 2)));
    printf("YO: %le \n ",YO);

    return YO;
    }

//latitude geocentrica
double calcgh_latgce(double lat){
    double var = 0,latgc = 0;

    var = B / A;
    var = pow(var,2) * tan(lat * (M_PI/180));
    latgc = atan(var);

    return latgc;
    }

double calcgh_colatgce(double latgc){
    double torad=0,colatgc=0;

    torad = GeoRef_radtodeg(latgc);
    colatgc = 90 - torad;

    return colatgc;
    }

double calcgh_anmI(double grau){
	double anm=0;
	anm= pow(((2 * grau + 1)/(2 * grau)),0.5);
	return anm;
	}

double calcgh_anmII(double grau,double ordem){
	double anm=0;
	anm = pow((((2*grau-1)*(2*grau+1))/((grau-ordem)*(grau+ordem))),0.5);
	return anm;
	}

double calcgh_bnm(double grau,double ordem){
	double bnm=0;
	bnm= pow((((2*grau+1)*(grau+ordem-1)*(grau-ordem-1))/((grau-ordem)*(grau+ordem)*(2*grau-3))),0.5);
	return bnm;
	}


void calcgh_legendre(double colatg, int nmax, double **anm, double **bnm, double **pnm){

	int grau=0, ordem=0;

	double colatR=0.0, t=0.0, u=0.0, r=0.0, l=0.0;

	colatR = colatg * (M_PI/180);
	
	t = cos(colatR);
	u = sin(colatR);

	anm[1][1] = pow(3,0.5);

	for (grau = 2; grau<= nmax; grau++)
		{
		r = grau;
		anm[grau][grau] = pow(((2 * r + 1)/(2 * r)),0.5);
		}

	for (ordem = 0; ordem <= nmax; ordem++)
		{
		for (grau = ordem + 1; grau <= nmax; grau++)
			{
			r = grau;
			l = ordem;

			anm[grau][ordem] = pow((((2*r-1)*(2*r+1))/((r-l)*(r+l))),0.5);
			bnm[grau][ordem] = pow((((2*r+1)*(r+l-1)*(r-l-1))/((r-l)*(r+l)*(2*r-3))),0.5);

			//  printf("anm: %le ,bnm:%le\n",anm[grau][ordem],bnm[grau][ordem]);
			}
		}

	pnm[0][0]=1;

	// 1st recursion
	for (grau = 1; grau < nmax;grau++)
		{
		pnm[grau][grau] = anm[grau][grau] * u * pnm[grau-1][grau-1];
		//  printf("\n1.pnm[%d][%d]=%le",grau,grau,pnm[grau][grau]);
		}

	// 2nd recursion
	for (ordem = 1;ordem < nmax;ordem++)
		{
		pnm[ordem][ordem - 1] = anm[ordem][ordem - 1] * t * pnm[ordem - 1][ordem - 1];
		// printf("\n2.pnm[%d][%d]=%le",ordem,ordem - 1,pnm[ordem][ordem - 1]);
		}

	// 3nd recursion
	/*for (ordem = 0;ordem <= nmax;ordem++)
		{
		for(grau = ordem + 2;grau < nmax;grau++)
			{
			pnm[grau][ordem] = anm[grau][ordem] * t * pnm[grau - 1][ordem] - bnm[grau][ordem] * pnm[grau - 2][ordem];
			printf("\n3.pnm[%d][%d] = %le",grau,ordem,pnm[grau][ordem]);
			}
		}*/
	ordem = 0;
	grau = 0;
	do
		{

		grau = ordem + 2;
		while (grau < nmax)
			{
			pnm[grau][ordem] = anm[grau][ordem] * t * pnm[grau - 1][ordem] - bnm[grau][ordem] * pnm[grau - 2][ordem];
			printf("\n3.pnm[%d][%d] = %le",grau,ordem,pnm[grau][ordem]);
			grau++;
			};
		ordem++;
		}
	while (ordem <= nmax-1);

	printf("\n3.2pnm[%d][%d] = %le\n",grau,ordem,pnm[grau][ordem]);

	
	}
/*
double **calcgh_GeoidOndu(double **pnm,double **anm,double **bnm, struct matriz *dados, double *rlocal rlocal*//*, double *lon, double *lat,struct Parametros cabe,double *y0,int sizecolat,int sizelong,double colatgc[]){

    int i=1,j=1,m,n;
    double **V, **N;

    V = creat_double_matrix(cabe.maxdeg,cabe.maxdeg);
    N = creat_double_matrix(cabe.maxdeg,cabe.maxdeg);

    for(i=1;i<sizecolat;i++)
        {
        Lg_Legendre(pnm,anm,bnm,cabe.maxdeg,colatgc[i]);

        for(j=1;j<sizelong;j++)
            {
            for(n=2;n<cabe.maxdeg;n++)
                {
                for (m=0;m<n;m++)
                    {
                    V[i][j] = V[i][j] + pow((cabe.R/rlocal[i]),(n+1))*(dados[(n + 1) * (m + 1)].C * cos(m * (lon[j] * M_PI/180)) + dados[(n+1) * (m+1)].S * sin(m * (lon[j] * M_PI/180))) * pnm[n+1][m+1];
                    printf("V[%d][%d]=%le",i,j,V[i][j]);
                    }
                }
            N[i][j]= (cabe.GMg/(rlocal[i] * y0[i])) * V[i][j];
            printf("  N[%d][%d]=%le/n",i,j,N[i][j]);
            }
        }
    return V;
    }

*/
