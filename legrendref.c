#include <math.h>
#include <stdio.h>
#include<stdlib.h>
#include "legendref.h"

#define PI 3.14159265359

double **dfre_matrix(double **vetorSum,int nrows,int ncol){

    int i = 0;

    if (vetorSum == NULL) return (NULL);

    if (nrows < 1 || ncol < 0) {

        /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        exit(0);

        }

    else{

        for (i = 0 ; i < nrows ; i++) free (vetorSum[i]);

        free( vetorSum );
        vetorSum = NULL;

        }

    return vetorSum;

    }

double **creat_double_matrix(int nrows,int ncol){

    int i;
    double **m;

    if (ncol < 1 || nrows < 1)
     { /* verifica parametros recebidos */

     printf ("** Erro: Parametro invalido **\n");
     return (NULL);

     };

    m = (double**) calloc(nrows,sizeof(double*));	/* Um vetor de m ponteiros para float */

    if (m == NULL)
    {

    printf ("** Erro: Memoria Insuficiente **");
    return (NULL);

    };

    for( i = 0 ; i <= nrows ; i++)
        {

        m[i] = calloc(ncol,sizeof(double));

        if (!m[i]){

            printf ("** Erro: Memoria Insuficiente **");
            return (NULL);

            };

        }

    return m;

    }



void Lg_filling(double **anm,double **bnm,int nmax){

    int l = 1,c = 0;
    double n = 1,m = 0,snm = 1,mnm = 1;

    while(c < 9)
        {

        m = m + 1;
        c = c + 1;
        n = m + 1;
        l = c + 1;

        //printf("\n\n1.n: %d m:%d",l,c);

        while(l < 10)
            {

            anm[l+1][c+1] = 0;
            bnm[l+1][c+1] = 0;

            anm[l+1][c+1] = sqrt( (( 2*n - 1 ) * (2*n + 1)) / ((mnm) * (snm)) );
            bnm[l+1][c+1] = sqrt( ((2*n + 1) * (snm- 1) * (mnm - 1)) / ((mnm) * (snm) * (2*n -3)) );

            printf(" \n\nanm[%d][%d] : %0.50lf \nbnm[%d][%d] : %0.50lf \n2.n: %d m:%d",l+1,c+1,anm[l+1][c+1],l+1,c+1,bnm[l+1][c+1],l,c);
            printf("\nsnm ; %lf mnm :%lf",snm,mnm);

            n++;
            l++;

            snm=n+m;
            mnm=n-m;

            };

        printf("\n\n3.l: %d c : %d \n",l,c);

        };

    printf("\n\n4.l: %d c:%d",l,c);

    }

double **Lg_fillingTA(int nmax){

    int l=1,c=0;
    double n=1,m=0,snm=1,mnm=1,**anm;

    anm=creat_double_matrix(nmax+1,nmax+1);
    printf("\nnmax %d",nmax);
    while(c <=8){

        m =m + 1;
        c=c+1;
        n = m + 1;
     //   l = c+1;

        printf("\n\n1.n: %d m:%d",l,c);

        while(l <10){

            anm[l+1][c+1]=0;
            anm[l+1][c+1] = sqrt( ( ( 2*n - 1 ) * (2*n + 1) ) / ( (mnm) * (snm) ) );

            printf(" \n\nanm[%d][%d] : %0.50lf \n \n2.n: %d m:%d",l+1,c+1,anm[l+1][c+1],l,c);
            printf("\nsnm ; %lf mnm :%lf",snm,mnm);

            n++;
            l++;

            snm=n+m;
            mnm=n-m;

            }

        printf("\n\n3.l: %d c : %d \n",l,c);

        }

//    printf("\n\n4.l: %d c:%d",l,c);

    return anm;
    }

double **Lg_fillingTB(double **bnm,int nmax){

    int l=1,c=0;
    double n=1,m=0,snm=1,mnm=1;

    while(c <9) {

        m =m + 1;
        c=c+1;
        n = m + 1;
        l = c+1;

        printf("\n\n1.n: %d m:%d",l,c);

        while(l <10){

            bnm[l+1][c+1]=0;
            bnm[l+1][c+1] = sqrt( ((2*n + 1) * (snm- 1) * (mnm - 1)) / ((mnm) * (snm) * (2*n -3)) );

            //printf(" \n\ \nbnm[%d][%d] : %0.50lf \n2.n: %d m:%d",l+1,c+1,bnm[l+1][c+1],l,c);
//          printf("\nsnm ; %lf mnm :%lf",snm,mnm);

            n++;
            l++;

            snm=n+m;
            mnm=n-m;

            }

        printf("\n\n3.l: %d c : %d \n",l,c);

        }

    printf("\n\n4.l: %d c:%d",l,c);

    return bnm;

    }



void Lg_first_rec(double **Pnm,double**anm,int nmax,double u){

    int l=0,c=0;

    for(c=2;c<=nmax;c++){
    //    anm[c+1][c+1]=sqrt((2*c+1)/(2*c));

        }

    for(c=1;c<=nmax;c++){

        Pnm[c+1][c+1]=0;
        Pnm[c+1][c+1]=anm[c+1][c+1]*u*Pnm[c][c];

        printf(" \n\ \nbnm[%d][%d] : %0.50lf \n2.c: %d ",c+1,c+1,Pnm[l+1][c+1],c);

        }

    }

void Lg_second_rec(double **Pnm,double**anm,int nmax,double t){

    int l,c;

    for(l=0;l<=nmax-1;l++){

        Pnm[l+2][l+1]  =anm[l+2][l+1]*t*Pnm[l][l];

        }

    }

void Lg_third_Rec(double **Pnm,double**anm,double **bnm,int maxdeg,double t){

    int l=0,c=0;
    c=l+2;

    for(l=0;l<=maxdeg-1;l++)
        {

        while(c<maxdeg)
            {

            Pnm[c+1][l+1] = anm[c+1][l+1]*t*Pnm[c][l+1]-bnm[c+1][l+1]*Pnm[c-1][l+1];
            printf("%d",l);
            c++;

            }

        c=l+2;

        }

    }

void Lg_Legendre(double **Pnm,int maxdeg,double colatg){

    double colatR=0,t=0,u=0;
    int l=0,c=0,n,m;

    printf("%d",maxdeg);


    colatR = colatg*(PI/180);

    t = cos(colatR);
    u = sin(colatR);

    for(l=0;l<=maxdeg+1;l++)
        {

        for(c=0;c<=maxdeg+1;c++)
            {

            }

        }

    for (m=0;m <= maxdeg-1;m++){

        for( n=0;n <= maxdeg;n++){

           // anm[n+1][m+1] = (((2*n-1)*(2*n+1))/sqrt((n-m)*(n+m)));
           // bnm[n+1][m+1]= (((2*n+1)*(n+m-1)*(n-m-1))/sqrt((n-m)*(n+m)*(2*n-3)));
         //   printf("n: %d m:%d anm: %lf bnm :%lf\n",n,m,anm[n+1][m+1],bnm[n+1][m+1]);

            }

        }

    }

