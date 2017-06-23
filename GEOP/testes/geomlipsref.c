
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geomlipsref.h"
#include "cabecalhostructs.h"
#include "calcgeoidh.h"

#define A 6378137              //semimajor axis (m)
#define B 6356752.3141       // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))


double GeoRef_radtodeg(double rad){
    double deg = 0;

    deg = 180 * rad/M_PI;

    return(deg);
	}

double GeoRef_degtorad(double deg){
    double rad=0;

    rad = deg * M_PI/180;

    return rad;
	}

double GeoRef_dist(double val1,double val2){
    double answ = 0, powe = 0;

    powe = val1 - val2;
    powe = pow(powe,2);
    answ = sqrt(powe);

    return (answ);
    }

double GeoRef_modulo(double val){
    if(val < 0) val = val * (-1);
    else val = val;

    return (val);
	}

double GeoRef_PexctElipsRef()//excentricidade elipsoide de referencia
	{
    double e=0,a2=0,b2=0,a=A,b=B;

    a2 = a * a;
    b2 = b * b;

    e = (a2 - b2)/a2;

    //printf("e : %le",e);

    return(e);
    }

double GeoRef_AchatmtElipsRef(){
    double f=0;

    f = (A - B)/A;
    return(f);
    }

double GeoRef_calcK(){
    double k=0;

    k = ((B * YP) - (A * YE))/(A * YE);	
    return(k);
    }

double GeoRef_calcm(){
    double m = 0;

    m = (pow(W,2) * pow(A,2) * B)/GM;
    return(m);
    }

struct Dimensoes GeoRef_Dimret(struct Dimensoes bound){

	bound.mlatS = GeoRef_modulo(bound.latS);
	bound.mlatN = GeoRef_modulo(bound.latN);
	bound.mlonE = GeoRef_modulo(bound.lonE);
	bound.mlonW = GeoRef_modulo(bound.lonW);

	bound.SizeLat = calcgh_nlat(bound.gridSize, bound.latN,bound.latS);
	bound.SizeLon = calcgh_nlat(bound.gridSize,bound.lonW,bound.lonE);

	return bound;
	}

struct Parametros GeoRef_parametrosElispref(struct Parametros cabe ){
	
	cabe.achatamento = GeoRef_AchatmtElipsRef();
	cabe.pextc = GeoRef_PexctElipsRef();
	cabe.k= GeoRef_calcK();

	return(cabe);
	}

void GeoRef_dfre_matrix(double **vetorSum,int nrows,int ncol){
    int i = 0;

    if (vetorSum == NULL) exit(1);
    else if (nrows < 1 || ncol < 1)
        {
        /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        exit(0);
        }
    else
        {
        for (i = 0 ; i < nrows ; i++) free (vetorSum[i]);//   vetorSum = NULL;
        }

    free( vetorSum );
	}


double **GeoRef_creat_double_matrix(int nrows,int ncol){
    int i;
    double **m;

    if (ncol < 1 || nrows < 1){ /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (NULL);
     };

    m =calloc(nrows,sizeof(double**));	/* Um vetor de m ponteiros para float */

    if (m == NULL)
    {
    printf("** Erro: Memoria Insuficiente **");
    return (NULL);
    };

    for( i = 0 ; i <= nrows ; i++)
        {
        m[i] = calloc(ncol+1,sizeof(double*));

        if (!m[i])
            {
            printf ("** Erro: Memoria Insuficiente **");
            return (NULL);
            };

        }

    return m;
	}



