#ifndef LEGENDREF_H_
#define LEGENDREF_H_

double **dfre_matrix(double **vetorSum,int nrows,int ncol);
double **creat_double_matrix(int nrows,int ncol);

void Lg_filling(double **anm,double **bnm,int nmax);
double **Lg_fillingTA(int nmax);
double **Lg_fillingTB(double **bnm,int nmax);

void Lg_first_rec(double **Pnm,double**anm,int nmax,double u);
void Lg_second_rec(double **Pnm,double**anm,int nmax,double t);
void Lg_third_Rec(double **Pnm,double**anm,double **bnm,int nmax,double t);

void Lg_Legendre(double **Pnm,int nmax,double colat);

#endif
