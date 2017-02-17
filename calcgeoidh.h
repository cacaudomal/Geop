#ifndef CALCGEOIDH_H_
#define CALCGEOIDH_H_

int calc_nlat(double gridsize,double molon1,double molon2);

// Compute local ellipsoidal radius (rlocal)
void calc_rlocal(double *lat,double *rlocale,int counti,double primxect);

// Compute normal gravity Yo
void normal_Gravdouble (double *lat,double *YO,int counti,double primxect,double k);

double latgce(double *lat,int counti);
double colatgce(double *latgc,int counti);

//double calcLatitude();
//double calcGeoidAltura();

#endif
