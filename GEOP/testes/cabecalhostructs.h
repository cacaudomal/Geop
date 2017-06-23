//
//  cabecalhostructs.h
//  GEOP
//
//  Created by Clara on 08/06/17.
//
//

#ifndef cabecalhostructs_h
#define cabecalhostructs_h

#define A 6378137              //semimajor axis (m)
#define B 6356752.3141        // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

#define SIZE 50

//raio local, colatitudes e afins
struct Coorde{
	double plat/*vetor de latitudes*/;
	double plon/*vetor de longitude*/;
	double Yo/* normal gravity ponto a ponto */;
	double rlocal/*local ellipsoidal radius*/;
	double colatgc/*colatitude geocentrica*/;
	double latgc;
	//latitude geocentrica
	};

//termos Zonais
struct processamentotzonaisp{
	double J2;
	double J2n;
	double Tzonais;
	double STzonais;
	};

//parametros do geoide
struct matriz{
	int L;//grau
	int M;//ordem
	double C;
	double S;
	double sigmaC;
	double sigmaS;
	};



struct Dimensoes{
	double lonW,lonE,latN,latS,gridSize/*Grid size of image, in deg*/;
	double mlatS,mlatN,mlonW,mlonE;//modulo dos angulos dos extremos da regiao
	int SizeLat,SizeLon;
	};

struct Parametros{
	double GMg;//constante gravitacional
	double R;//raio medio da terra
	int maxdeg;//grau maximo
	double k;
	double achatamento;
	double pextc;
	double m;
	};

struct dados{
	//dados obtidos do arquivo .gfc
	char TideSys[SIZE];
	char ModName[SIZE];//nomedo modelo
	char err[SIZE];//erro
	char norm[SIZE];//normalização
	char ProdTyp[SIZE];//tipo do produto
	};

#endif /* cabecalhostructs_h */
