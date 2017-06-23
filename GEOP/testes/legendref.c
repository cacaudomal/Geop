#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "legendref.h"

#define PI 3.14159265359

double Lg_fillingTA2(double n,double snm,double mnm){
    double anm=0;

    anm = sqrt(((2 * n - 1) * (2*n + 1)) / (mnm * snm));
    //printf(" anm:%lf ",anm);
    return anm;
    }

    double Lg_fillingTA1(double n){
    double anm=0;

    anm = sqrt((2 * n + 1) / (2 * n));

    return anm;
    }

double Lg_fillingTB(double n, double snm, double mnm){
    double bnm=0;

    bnm = sqrt(((2 * n + 1) * (snm - 1) * (mnm - 1)) / (mnm * snm * (2 * n - 3))) ;

    return bnm;
    }

void Lg_filling(double **anm,double **bnm,int maxdeg){
    int l = 1,c = 0;
    double n = 1, m = 0, snm = 1, mnm = 1;

    for(c = 0;c < maxdeg-1; c++)
        {
        m = m + 1;
        n = m + 1;
        //printf("\n\n1.n: %d m:%d",l,c);
        for(l = c + 1; l < maxdeg; l++)
            {
            anm[l+1][c+1] = 0;
            bnm[l+1][c+1] = 0;

            anm[l+1][c+1] = Lg_fillingTA2(n,snm,mnm);
            bnm[l+1][c+1] = Lg_fillingTB(n,snm,mnm);

            printf(" \n\nanm[%d][%d] : %0.50lf \nbnm[%d][%d] : %0.50lf \n2.n: %d m:%d",l+1,c+1,anm[l+1][c+1],l+1,c+1,bnm[l+1][c+1],l,c);

            n++;
        //    printf("\nsnm ; %lf mnm :%lf",snm,mnm);
            snm = n + m;
            mnm = n - m;
            }
        printf("\n\n3.l: %d c : %d \n",l,c);
        }

    printf("\n\n4.l: %d c:%d",l,c);
    }



double Lg_first_rec(double Pnm,double anm1,double u)
    {
    double Pnm1 = 0;
    Pnm1 = anm1 * u * Pnm;

    return Pnm1;
    }

double Lg_second_rec(double Pnm,double anm,double t)
    {
    double nPnm = 0;
    nPnm  = anm * t * Pnm;

    return nPnm;
    }

double Lg_third_Rec(double Pnmn,double Pnmn1,double anm,double bnm,double t)
    {
    double nPnm=0;

    nPnm = anm * t * Pnmn - bnm * Pnmn1;

    return nPnm;
    }


double Lg_t(double colatg)
    {
    double colatR,pt;

    colatR= colatg * (PI/180);
    pt = cos(colatR);

    return pt;
    }

double Lg_u(double colatg)
    {
    double colatR=0,u;

    colatR = colatg * (PI/180);
    u = sin(colatR);

    return u;
    }


void Lg_Legendre(double **Pnm,double **anm,double **bnm,int maxdeg,double colatg){
    double t,u;
    int n,m;

    t = Lg_t(colatg);
    u = Lg_u(colatg);

    Pnm[1][1]=u*sqrt(3);
    for(n = 1; n < maxdeg; n++)
        {
        Pnm[n+1][n+1] = Lg_first_rec(Pnm[n][n],anm[n+1][n+1],u);
        printf("\n1.Pnm[%d][%d]=%10.100lf",n+1,n+1,Pnm[n+1][n+1]);
        }

    for(n = 0;n < maxdeg-1; n++)
        {
        Pnm[n+2][n+1] = Lg_second_rec(Pnm[n+1][n+1],anm[n+2][n+1],t);
        printf("\n2.Pnm[%d][%d]=%10.20lf",n+2,n+1,Pnm[n+2][n+1]);
        }

    for (m=0; m < maxdeg-1; m++)
        {
        for(n=m+2; n < maxdeg; n++)
            {
            Pnm[n+1][m+1] = Lg_third_Rec(Pnm[n][m+1],Pnm[n-1][m+1],anm[n+1][m+1],bnm[n+1][m+1],t);
            printf("\n3.Pnm[%d][%d]=%10.20lf",n+1,m+1,Pnm[n+1][m+1]);
            }
        }
    }

