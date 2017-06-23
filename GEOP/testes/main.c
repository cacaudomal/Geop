
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "geopanom.h"
#include "leiturarq.h"
#include "geomlipsref.h"
#include "calcgeoidh.h"
#include "calcgeop.h"
#include "cabecalhostructs.h"
//#include "legendref.h"


#define A 6378137              //semimajor axis (m)
#define B 6356752.3141        // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

#define SIZE 50

int main(){

//=================================================Entradas do Usuario====================================
char nomearq[SIZE]/*nome do arquivo*/, oqb[SIZE]/*parametro buscado no arquivo*/,formato[4]/*formato do arquivo*/;
struct Dimensoes bound;
int i=0,j=0;

// Abrir arquivo
//printf("\n\n\aENTRADA - Nome do arquivo: ");
//scanf("%s",nomearq);

//printf("insert Boundary Data [LonW(deg) LonE(deg) LatS(deg) LatN(deg)]");
// Boundary Data [LonW(deg) LonE(deg) LatS(deg) LatN(deg)]

bound.lonW = -48.35;
//printf("lonw : %le",bound.lonW);
//scanf("%le",bound.lonW);
bound.lonE = -47.25;
//scanf("%le",bound.lonE);
//printf("lone : %le",bound.lonE);

bound.latS = -16.11;

//printf("latn : %le",bound.latS);
//scanf("%le",bound.latS);
bound.latN = -15.44;

//printf("lats : %le",bound.latN);
//scanf("%le",bound.latN);

//=================================================Leitura dos Arquivos======================================

//double  G=0/*const gravitacional*/, R=0/*raio medio da terra*/;
struct matriz entrada, *pentrada;// alocacao dinamica de matriz
struct Parametros cabe;
struct dados nomes;

int grau = 0, ordem = 0, numL = 0 /*numero de linhas da matriz*/,count = 0/*CONTADOR*/;


strcpy(nomearq,"ITUGRACE16.gfc");

printf("Modelo do Geopotencial\n\n");
printf("Arquivo: %s\n", nomearq);

strcpy(oqb,"modelname");
ArqGeop_lePrintArqChar(oqb,nomearq,nomes.ModName);

strcpy(oqb,"product_type");
ArqGeop_lePrintArqChar(oqb,nomearq,nomes.ProdTyp);

strcpy( oqb,"earth_gravity_constant");
cabe.GMg = ArqGeop_leituraArqDouble(oqb,nomearq);
printf ("\nearth_gravity_constant: %le", cabe.GMg);

strcpy( oqb,"radius");
cabe.R = ArqGeop_leituraArqDouble(oqb,nomearq);
printf ("\nradius                : %le", cabe.R);

strcpy(oqb,"max_degree");
cabe.maxdeg = ArqGeop_leituraArqInt(oqb,nomearq);
printf ("\nMax_degree            : %d", cabe.maxdeg);

strcpy(oqb,"errors");
ArqGeop_lePrintArqChar(oqb,nomearq,nomes.err);

strcpy(oqb,"norm");
ArqGeop_lePrintArqChar(oqb,nomearq,nomes.norm);

strcpy(oqb,"tide_system");
ArqGeop_lePrintArqChar(oqb,nomearq,nomes.TideSys);



//==============================Fim Leitura do Cabeçalho=====================================

numL = ( ((cabe.maxdeg + 1) * (cabe.maxdeg + 1)) + (cabe.maxdeg + 1) )/2;//calcula o numero de linhas de dados apartir do grau maximo
	//ponteiro para matriz de entrada

pentrada = malloc((numL + 1)* sizeof (entrada)); // Aloca memoria para a matriz entrada dos parametro
if (!pentrada)
	{
	printf ("** Erro: Memoria Insuficiente **");
	getchar();
	exit (1);
	};

for (int count = 0;count <= numL;count++)
	{
	pentrada[count].sigmaS = 0; //Inicializa com 0.
	pentrada[count].S = 0; //Inicializa com 0.
	pentrada[count].C = 0; //Inicializa com 0.
	pentrada[count].sigmaC = 0; //Inicializa com 0.

	pentrada[count].L = 0; //Inicializa com 0.
	pentrada[count].M = 0; //Inicializa com 0.
    }







  //===================================fim da Alocaçao dinamica - Inicio aquisição dos dados=================================

FILE *fp1;

if((fp1 = fopen("ITUGRACE16.gfc","r")) == NULL)
	{
	printf("o arquivo nao pode ser aberto 1 ");
	exit(1);
	}

char v[140];

do{//achar o começo dos dados
    fscanf(fp1,"%s",v);
    }while (strcmp("===============================================================================================",v));

for (int nl=0;nl<numL;nl++)
    {
  	fscanf(fp1,"%s %d %d %le %le %le %le",formato,&pentrada[nl].L ,&pentrada[nl].M, &pentrada[nl].C , &pentrada[nl].S, &pentrada[nl].sigmaC, &pentrada[nl].sigmaS);
   // printf("\n %s %d %d %1.14E %1.14E %1.14E %1.14E\n",formato, pentrada[nl].L, pentrada[nl].M, pentrada[nl].C, pentrada[nl].S, pentrada[nl].sigmaC, pentrada[nl].sigmaS);
    }

fclose(fp1);
fp1=NULL;







//==================================================fim da aquisição dos dados-Criando matrizes===============================================
double **C,**S;

C = (double **) malloc(cabe.maxdeg * sizeof *C);
S = (double **) malloc(cabe.maxdeg * sizeof *S);

for (i = 0; i <= cabe.maxdeg; i++)
	{
	C[i] = (double *) malloc(cabe.maxdeg * sizeof **C);
	S[i] = (double *) malloc(cabe.maxdeg * sizeof **S);
    }

for (i = 0; i <= cabe.maxdeg; i++)
	{
	for (int j = 0; j <= cabe.maxdeg; j++)
		{
		C[i][j] = 0.0;
		S[i][j] = 0.0;
		}
	}

//Convertendo vetor para matriz
for ( count = 0; count < numL; count++)
    {
    C[grau][ordem] = pentrada[count].C;
    S[grau][ordem] = pentrada[count].S;
   // printf("C[%d][%d]=%0.10lf ",grau,ordem,C[grau][ordem]);
	//printf("S[%d][%d]=%0.10lf\n",grau,ordem,S[grau][ordem]);
//OK!
	if(grau == cabe.maxdeg)
		{
		grau = ordem;
		ordem++;
		}

	grau++;
	}




//=====================================================BOUNDARY DATA=========================================

double *plat ,*plon;

bound.gridSize = 0.1;

printf("gridsize: %le",bound.gridSize);

bound.SizeLat = calcgh_nlat(bound.gridSize, bound.latN,bound.latS);
bound.SizeLon = calcgh_nlat(bound.gridSize,bound.lonW,bound.lonE);


//bound = GeoRef_Dimret(bound);
printf("\n\nbound sizelat : %d\nbound sizelon : %d",bound.SizeLat,bound.SizeLon);

plon = malloc((bound.SizeLon+2) * sizeof(double));
if (!plon)
	{
	printf ("** Erro: Memoria Insuficiente **");
	getchar();
	exit (1);
	};

plat = malloc((bound.SizeLat+2) * sizeof(double));
if (!plat)
	{
	printf ("** Erro: Memoria Insuficiente **");
	getchar();
	exit (1);
	};

plat[0] = bound.latS;
plon[0] = bound.lonW;

i = 1;
//printf("\n\ni : %d\n\n",i);

do
    {
    plon[i] = plon[i-1] + bound.gridSize;
    printf("\nplon[%d] = %le",i,plon[i]);
    i++;
    }while(i <= bound.SizeLon );

i = 1;

do
    {
    plat[i] = plat[i-1] + bound.gridSize;
	printf("\nplat[%d] = %le",i,plat[i]);
    i++;
    }while(i <= bound.SizeLat);






//================================================PARAMETROS DO ELIPSOIDE===================================

double *prlocal, *pYo , *platgce;

platgce = malloc((bound.SizeLat+1) * sizeof(double));
if (!platgce){
	printf ("** Erro: Memoria Insuficiente **");
	getchar();
	exit (1);
	};

prlocal = malloc((cabe.maxdeg+1) * sizeof(double));
if (!prlocal){
	printf ("** Erro: Memoria Insuficiente **");
	getchar();
	exit (1);
	};

pYo = malloc((bound.SizeLat+1) * sizeof(double));
if (!pYo)
	{
	printf ("** Erro: Memoria Insuficiente **");
	getchar();
	exit (1);
	};

cabe.achatamento = GeoRef_AchatmtElipsRef();
printf("\n\nachatamento: %le",cabe.achatamento);

cabe.pextc = GeoRef_PexctElipsRef();//calc primeira excentricidade
printf("\npextc: %le",cabe.pextc);
cabe.k = GeoRef_calcK();

i = 0;

for(i = 0;i < bound.SizeLat;i++)
    {
    prlocal[i] = calcgh_rlocal(plat[i],cabe.pextc);//calc raio local da terra

    pYo[i] = calcgh_normal_Gravdouble(plat[i],cabe.pextc,cabe.k);//calc gravidade normal

    printf("\n prlocal:%le,\n pYo:%le",prlocal[i],pYo[i]);

    platgce[i] = calcgh_latgce(plat[i]);//calc Latitude geocentrica
   // printf("\n lat %le\n",platgce[i]);

    platgce[i] = calcgh_colatgce(platgce[i]);//calc colatitude geocentrica
    printf("\n latgc%le\n\n",platgce[i]);
    }
//OK!
free(pentrada);





//====================================================LEGRENDRE===================================================
double **panm, **pbnm, **ppnm;

panm = (double **) malloc((cabe.maxdeg+10) * sizeof (double*));
pbnm = (double **) malloc((cabe.maxdeg+10) * sizeof *pbnm);
ppnm = (double **) malloc((cabe.maxdeg+10) * sizeof (*ppnm));

for ( i = 0; i <= cabe.maxdeg+1; i++)
    {
	panm[i] = (double *) malloc((cabe.maxdeg+10) * sizeof(double));
	pbnm[i] = (double *) malloc((cabe.maxdeg+10) * sizeof (double));
	ppnm[i] = (double *) malloc((cabe.maxdeg+10) * sizeof (double));
    }

for ( i = 0; i <= cabe.maxdeg; i++)
    {
	for ( j = 0; j <= cabe.maxdeg; j++)
        {
		panm[i][j] = 0.0;
     	pbnm[i][j] = 0.0;
     	ppnm[i][j] = 0.0;
		//printf("panm %lf ppnm %lf pbnm %lf",panm[i][j],ppnm[i][j],pbnm[i][j]);
        }
     }


//calcgh_legendre(platgce[1],maxdeg,panm,pbnm,ppnm);


//=============================================Calculo deltaC e deltaS e Termos Zonais Pares===============
double j2 = 0,*J2n,M = 0,*Coefz,*pdC,*ScoefZ;


pdC = malloc((cabe.maxdeg + 1) * sizeof(double));
J2n = malloc((cabe.maxdeg + 1) * sizeof(double));
Coefz = malloc((cabe.maxdeg + 1) * sizeof(double));
ScoefZ =malloc((cabe.maxdeg + 1) * sizeof(double));

j2 = calcgp_jota2(cabe.achatamento);
//printf(" \n\nj2 : %0.100lf\n",j2);

count = 0;
double K = 0;

for(grau= 0;grau <= cabe.maxdeg;grau = grau + 2)
    {
    J2n[grau] = 0;
    J2n[grau] = calcgp_jota2n(M,cabe.pextc,j2);

    Coefz[grau] = calcgp_CoefTzonaispares(K,j2,J2n[grau]);
    ScoefZ[grau] = calcgp_CoefTzonaispares_p2(cabe.GMg,cabe.R,M,Coefz[grau]);

    pdC[grau] = C[grau][0] - ScoefZ[grau];

    //printf(" \nj2n : %le, M:%4.0lf, count %d, grau :%d, Coefz:%le,cnm:%le pdC:%le, ", J2n[grau], M, count,  grau, ScoefZ[grau],C[grau][0], pdC[grau]);

	M = M + 1;
	K = K + 2;
    }
	//OK!

free(Coefz);
free(J2n);







//================================================CALCULO DA ONDULAÇAO e ANOMALIA GEOIDAL=======================================

double **V,**N,**Ag,**GeopAnom;

V = (double **) malloc(cabe.maxdeg * sizeof (double*));
N = (double **) malloc(cabe.maxdeg * sizeof *N);
Ag = (double **) malloc(cabe.maxdeg * sizeof *Ag);
GeopAnom = (double **) malloc(cabe.maxdeg * sizeof *GeopAnom);

for ( i = 0; i <= cabe.maxdeg; i++)
	{
	V[i] = ( double *) malloc(cabe.maxdeg * sizeof **V);
    N[i] = (double *) malloc(cabe.maxdeg * sizeof **N);
    Ag[i] = (double *) malloc(cabe.maxdeg * sizeof **Ag);
    GeopAnom[i] = (double *) malloc(cabe.maxdeg * sizeof **GeopAnom);
	}

for ( i = 0; i <= cabe.maxdeg; i++)
	{
	for ( j = 0; j <= cabe.maxdeg; j++)
		{
		V[i][j] = 0.0;
		N[i][j] = 0.0;
		Ag[i][j] = 0.0;
		GeopAnom[i][j] = 0.0;
		}
	}

int cgrau = 0,cordem = 0;

double  d = 0;
	panm[1][1] = pow(3,0.5);

	//Altura Geoidal

	for(i=0;i < bound.SizeLat;i++)
	{
	calcgh_legendre(platgce[i],cabe.maxdeg,panm,pbnm,ppnm);
	printf("fora de legendre1");

	for( j = 0;j < bound.SizeLon;j++)
		{
		for(grau = 2;grau < cabe.maxdeg;grau++)//algum erro nos fors nao sei o q  o i e o j parecem estar certos, provavelmente eh no grau e ordem ou na funcao geoidalOndu
			{
			/* grau =2;ordem=0; */
			for (ordem = 0;ordem <= grau;ordem++)
				{
				cgrau = grau;
				cordem = ordem;
				//printf("\n 1.V = %le",V[i][j]);
				d = ganom_calcGeoidalOndu(cabe.R,prlocal[i],cgrau,cordem,C[cgrau][cordem],S[cgrau ][cordem],plon[j],ppnm[cgrau][cordem]);
				V[i][j] = V[i][j] + d;

				printf("\nprlocal[%d]=%le C[%d][%d] =%le plon[%d]=%le S[%d][%d] = %le ppnm[%d][%d]=%le\n",i,prlocal[i],cgrau,cordem,C[cgrau][cordem], j, plon[j], cgrau,cordem,S[grau][ordem],cgrau,cordem,ppnm[cgrau][cordem ]);
				}
			}

		printf("\n V [%d][%d]= %le, ",i,j,V[i][j]);
		N[i][j] = (cabe.GMg/(prlocal[i] * pYo[i])) * V[i][j];

		printf("  N = %le",N[i][j]);
		getchar();
		}
		printf("\n");
	}

for ( i = 0; i <= cabe.maxdeg; i++)
	{
	for ( j = 0; j <= cabe.maxdeg; j++)
		{
		V[i][j] = 0.0;
			
		}
	}

	//Anomalia de Gravidade
for(i = 0;i <= bound.SizeLat - 1;i++)
	{
	calcgh_legendre(platgce[i],cabe.maxdeg,panm,pbnm,ppnm);
	printf("fora de legendre2");


	for( j = 0;j <= bound.SizeLon;j++)
        {
		for(grau = 2;grau <= cabe.maxdeg;grau++)
            {
           /* grau =2;ordem=0; */
			for (ordem = 0;ordem < grau;ordem++)
				{
				//printf("\n 1.V = %le",V[i][j]);
				d = ganom_calcGeoidalAnom(cabe.R, prlocal[i],grau , ordem, C[grau + 1][ordem + 1], S[grau+1][ordem+1], plon[j], ppnm[grau+1][ordem+1]);
				V[i][j] = V[i][j] + d;

				// printf("\nprlocal[%d]=%le C[%d][%d] =%le plon[%d]=%le S[%d][%d] = %le \n",i,prlocal[i],grau+1,ordem+1,C[grau+1][ordem+1],j,plon[j],grau+1,ordem+1,S[grau+1][ordem+1]);
				//printf("\n V = %le, i=%d, j = %d",V[i][j],i,j);
				}
			}

		Ag[i][j] = (cabe.GMg/pow(prlocal[i],2)) * V[i][j];
		GeopAnom[i][j] = Ag[i][j] * pow(10,5);
        printf("  N = %le, Ag=%le , GeopAnom =%le\n",N[i][j],Ag[i][j],GeopAnom[i][j]);
		}
     printf("\n");
    }

char arqnom[SIZE];
strcpy(arqnom,"GeopAnomtc.txt");

FILE *Resul1 = NULL;

if((Resul1 = ArqGeop_guardaCabecalho(cabe, nomes , bound, arqnom, Resul1)) == NULL)
	{
	printf("o arquivo nao pode ser aberto 2 ");
	exit(1);
	}

//===============================================Gravando Dados em Arquivo==========================================

if((Resul1=fopen(arqnom,"a")) == NULL)
	{
	printf("o arquivo nao pode ser aberto");
	exit(1);
	}

for(i = 1;i < bound.SizeLat;i++)
	{
	for(int j = 1;j < bound.SizeLon;j++)
		{
		fprintf(Resul1,"\nlat %3.3lf   long %3.3lf     V[%d][%d] = %le   N[%d][%d] = %le \nAg = %le Geopanom = %le\n",plat[i],plon[j],i,j,V[i][j],i,j,N[i][j],Ag[i][j],GeopAnom[i][j]);
		}
	 }

fclose(Resul1);
fflush(Resul1);


free(plon);
free(plat);

printf("fim da gravacao");

getchar();
return(0);
}
