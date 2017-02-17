
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "leiturarq.h"
#include "geomlipsref.h"
#include "calcgeop.h"
#include "calcgeoidh.h"
#include "legendref.h"

#define PI 3.14159265359
#define A 6378137              //semimajor axis (m)
#define B 6356752.3141        // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

#define SIZE 50


int main(){

struct Dimensoes{

double lonW,lonE,latN,latS,gridSize/*Grid size of image, in deg*/;

};
struct matriz{
//parametros do geoide
    int L;//grau
    int M;//ordem
    double C;
    double S;
    double sigmaC;
    double sigmaS;
    };

struct Parametros{
 //   int cDegord;
 //   int cDados;
    double GMg;//constante gravitacional
    double R;//raio medio da terra
    int maxdeg;//grau maximo
    };

struct dados{
//dados obtidos do arquivo .gfc
    char TideSys[SIZE];
    char ModName[SIZE];//nomedo modelo
    char err[SIZE];//erro
    char norm[SIZE];//normalização
    char ProdTyp[SIZE];//tipo do produto
    };

struct constantes{

    double e;//primeira excentricidade
    double f;//achatamento
    double k;
    double M;

    };

struct processamentotzonaisp{
    double J2;
    double J2n;
    double Tzonais;
    double STzonais;
    };


//double  G=0/*const gravitacional*/, R=0/*raio medio da terra*/;
struct matriz entrada, *pentrada=NULL;// alocacao dinamica de matriz
struct Parametros cabe;
struct dados nomes;

int numL = 0 /*numero de linhas da matriz*/,count = 0/*CONTADOR*/;
char nomearq[SIZE]/*nome do arquivo*/, oqb[SIZE]/*parametro buscado no arquivo*/,formato[4]/*formato do arquivo*/;

// Abrir arquivo
//printf("\n\n\aENTRADA - Nome do arquivo: ");
//scanf("%s",nomearq);

strcpy(nomearq, "ITUGRACE16.gfc");

printf("Modelo do Geopotencial\n\n");
printf("Arquivo: %s\n", nomearq);

strcpy(oqb,"modelname");
lePrintArqChar(oqb,nomearq,nomes.ModName);

strcpy(oqb,"product_type");
lePrintArqChar(oqb,nomearq,nomes.ProdTyp);

strcpy( oqb,"earth_gravity_constant");
cabe.GMg = leituraArqDouble(oqb,nomearq);
printf ("\nearth_gravity_constant: %lf", cabe.GMg);

strcpy( oqb,"radius");
cabe.R = leituraArqDouble(oqb,nomearq);
printf ("\nradius                : %lf", cabe.R);

strcpy(oqb,"max_degree");
cabe.maxdeg = leituraArqInt(oqb,nomearq);
printf ("\nMax_degree            : %d", cabe.maxdeg);

strcpy(oqb,"errors");
lePrintArqChar(oqb,nomearq,nomes.err);

strcpy(oqb,"norm");
lePrintArqChar(oqb,nomearq,nomes.norm);

strcpy(oqb,"tide_system");
lePrintArqChar(oqb,nomearq,nomes.TideSys);

//==============================Fim Leitura do Cabeçalho=====================================

numL = ( ((cabe.maxdeg+1)*(cabe.maxdeg+1))+(cabe.maxdeg+1) )/2;//calcula o numero de linhas de dados apartir do grau maximo
pentrada = &entrada;//ponteiro para matriz de entrada

pentrada = malloc((numL+1)* sizeof (entrada)); // Aloca memoria para a matriz entrada dos parametro
  if (!pentrada)
         {
            printf ("** Erro: Memoria Insuficiente **");
            getchar();
            exit (1);
         };
//cabe.cDados = 4;cabe.cDegord = 2;//numero de colunas das respectivas matrizes

for (int count = 0;count < numL;count++){
	pentrada[count].sigmaS = 0; //Inicializa com 0.
	pentrada[count].S = 0; //Inicializa com 0.
	pentrada[count].C = 0; //Inicializa com 0.
	pentrada[count].sigmaC = 0; //Inicializa com 0.

	pentrada[count].L = 0; //Inicializa com 0.
	pentrada[count].M = 0; //Inicializa com 0.
    }

  //===================================fim da Alocaçao dinamica - Inicio aquisição dos dados=================================

FILE *fp1;
fp1=fopen(nomearq,"r");

if (fp1 == NULL) {//testa para ver se o arquivo abriu corretamente
    printf("\arquivo nao pode ser aberto");
    exit(1);
    }

char v[140];

do{//achar o começo dos dados
    fscanf(fp1,"%s",v);
    }while (strcmp("===============================================================================================",v));

for (int nl=0;nl<numL;nl++)
    {

  	fscanf(fp1,"%s %d %d %lf %lf %lf %lf",formato,&pentrada[nl].L ,&pentrada[nl].M, &pentrada[nl].C , &pentrada[nl].S, &pentrada[nl].sigmaC, &pentrada[nl].sigmaS);
   // printf("\n %s %d %d %1.14E %1.14E %1.14E %1.14E\n",formato, pentrada[nl].L, pentrada[nl].M, pentrada[nl].C, pentrada[nl].S, pentrada[nl].sigmaC, pentrada[nl].sigmaS);

    }

fclose(fp1);
fp1=NULL;

//==================================================fim da aquisição dos dados====================================================


//==================================================inicio do processamento=======================================================

//double a=0,b=0,f=0,e=0;
//int L=0,M=0,par=0;
double c2n = 0;
struct constantes cte;
//struct processamentotzonaisp *pproces,proces;

cte.f = AchatmtElipsRef(); //achatamento do elpsoide
//printf("\nf :%2.15f   a0",cte.f);
cte.e = PexctElipsRef();//primeira excentricidade
//printf("\ne :%le  ",cte.e);
cte.k = calcK();
//printf("\nk :%le  ",cte.k);
/*cte.M = calcm();
printf("\nm :%lf  ",cte.M);*/

/*pproces = malloc((cabe.maxdeg+2)*sizeof (proces));
if (!pproces)
    {
    printf ("** Erro: Memoria Insuficiente **");
    getchar();
    exit (1);
    };

//double vi=1,k=0,n1=0;

//pproces[1].J2=jota2(cte.f,vi);
//printf("  J2 :%0.20lf",pproces[nl].J2);

for(count = 1;count<cabe.maxdeg+1;count++){
    count = count+2;
    count = count-1;
    n1 = 1+n1;
    k = k+2;
    pproces[count].J2n=jota2n(n1,cte.f,cte.e,pproces[1].J2);
    //printf("\ndp nl :%d,n1 %lf ,k %lf \n\n ",nl,n1,k);
    //printf("  J2n :%4.5f \n",pproces[nl].J2n);
    pproces[count].Tzonais=CoefTzonaispares(cabe.GMg,cabe.R,n1,pproces[1].J2,pproces[count].J2n,k);
  //  printf("  Tzonais :%lf\n",pproces[count].Tzonais);
    pproces[count].STzonais=SigCoefTzonaispares(cabe.GMg,cabe.R,n1,pproces[count].Tzonais);
  //  printf("\nstzonais: %lf",pproces[count].STzonais);
    }*/

//free(pproces);
//Grid size to interpolation of data (in minutes).
//int GridGsd = 1;

struct Dimensoes bound;
double *plat,*plon,*Yo/* normal gravity */,*rlocal/*local ellipsoidal radius*/,*colatgc=NULL,*latgc=NULL,*u,*t;
double **pPnm,**panm,**pbnm;
double mlatS=0,mlatN=0,mlonW=0,mlonE=0,ll=1,l2=60,cont=0,size=0,modcont=0,absbound[4];
int counter=0,nlat,nlon;

//printf("Grid size of image, in deg insert:");
//scanf("%lf",bound.gridSize);

bound.gridSize = ll/l2;
printf("\n\ngridsize : %0.10f\n",bound.gridSize);

//printf("insert Boundary Data [LonW(deg) LonE(deg) LatS(deg) LatN(deg)]");
// Boundary Data [LonW(deg) LonE(deg) LatS(deg) LatN(deg)]

//scanf("%lf",bound.lonW);
bound.lonW=-48.35;
absbound[0]=180+bound.lonW;
//printf("lonw : %lf",bound.lonW);
//scanf("%lf",bound.lonE);
bound.lonE=-47.25;
absbound[1]=180+bound.lonE;
//printf("lone : %lf",bound.lonE);
//scanf("%lf",bound.latN);
bound.latS=-16.11;
absbound[2]=90+bound.latS;
//printf("latn : %lf",bound.latS);
//scanf("%lf",bound.latS);
bound.latN=-15.44;
absbound[3]=90+bound.latN;
//printf("lats : %lf",bound.latN);

mlatS=modulo(bound.latS);//printf(" lats : %lf ",mlatS);
mlatN=modulo(bound.latN);//printf(" latn : %lf ",mlatN);
mlonE=modulo(bound.lonE);
mlonW=modulo(bound.lonW);

count=calc_nlat(bound.gridSize,absbound[2],absbound[3]);
printf("count ;: %d",count);
nlat = count;

plat = malloc((count+2)*sizeof(double));
rlocal = malloc((count+2)*sizeof(double));
Yo = malloc((count+2)*sizeof(double));
colatgc = malloc((count+2)*sizeof(double));
latgc = malloc((count+2)*sizeof(double));

if(plat == NULL || rlocal == NULL || Yo == NULL || colatgc == NULL || latgc == NULL)
    {
        printf ("** Erro: Memoria Insuficiente **");
        getchar();
        exit (1);
    }

plat[0] = absbound[2];

calc_rlocal(plat,rlocal,0,cte.e);

counter = 0;

do{

    counter++;
    plat[counter]=plat[counter-1]+bound.gridSize;
    latgc[counter]=latgce(plat,counter);
    colatgc[counter]=colatgce(latgc,counter);

   // printf(" \n\n**counter: %d ",counter);
    //printf("  plat: %lf",plat[counter]-90);

    //printf("  la5tgc: %lf  ",latgc[counter]*180/PI);
    //printf("  colatgc: %lf \n ",colatgc[counter]);

    }while(counter<count);

calc_rlocal(plat,rlocal,count,cte.e);
normal_Gravdouble(plat,Yo,count,cte.e,cte.k);

count = calc_nlat(bound.gridSize,absbound[1],absbound[0]);
nlon = count;

printf("count2:%d",count);

plon = malloc((count+1)*sizeof(double));

if(plon == NULL)
    {

    printf("plon nao alocou memoria");
    getchar();

    exit(1);

    }

plon[0]=absbound[0];
counter=0;

free(latgc);

do{

    counter ++;
    plon[counter] = plon[counter-1] + bound.gridSize;
    //printf("\n plon: %lf ",plon[counter]-180);

    }while(counter < count);

panm = creat_double_matrix(cabe.maxdeg+1,cabe.maxdeg+1);
pbnm = creat_double_matrix(cabe.maxdeg+1,cabe.maxdeg+1);
pPnm = creat_double_matrix(cabe.maxdeg+1,cabe.maxdeg+1);

//pPnm[1][1]=1;
//panm[2][2]=sqrt(3);

u = malloc((cabe.maxdeg+1)*sizeof(double));
if(u == NULL){

    printf("plon nao alocou memoria");
    exit(1);

    }

t = malloc((cabe.maxdeg+1)*sizeof(double));
if(t == NULL){

    printf("plon nao alocou memoria");
    exit(1);

    }


for(count=0;count<cabe.maxdeg+1;count++)
    {

    t[count] = cos(colatgc[count]);
    u[count] = sin(colatgc[count]);

    }


//panm=Lg_fillingTA(cabe.maxdeg);
Lg_filling(panm,pbnm,cabe.maxdeg);
//Lg_first_rec(pPnm,panm,cabe.maxdeg,u);
//free(colatgc);
//printf("\n plon: %lf 564 counter%d",plon[counter],counter);
/*

for(int i=0;i<nlon;i++)
Legendre(pPnm,cabe.maxdeg,colatgc[i]);

*/
//t = cos(colat);
//u = sin(colat);
//Le_fillng(panm,pbnm,cabe.maxdeg);

//free_matrix(pPnm,cabe.maxdeg+1);

panm = dfre_matrix(panm,cabe.maxdeg+1,cabe.maxdeg+1);
//free_matrix(pbnm,cabe.maxdeg+1);
//free_double_matrix(pPnm,numL);
//free(plat);//[cabe.maxdeg+1][cabe.maxdeg+1]

//pPnm = fre_matrix(pPnm,cabe.maxdeg);
//panm = fre_matrix(panm,cabe.maxdeg);
//pbnm = fre_matrix(pbnm,cabe.maxdeg);

plat=NULL;
//
rlocal=NULL;
//Yo=NULL;
colatgc=NULL;
latgc=NULL;

getchar();
return 0;
}
