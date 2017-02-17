#ifndef CALCGEOP_H_
#define CALCGEOP_H_

//Parametros para o calculo dos coeficientes dos termos zonais pares do desenvolvimento em série de funções hamonicas esféricas do potencial gravitacional
 double jota2(double f/*achatamento do elipsoide de referência*/,double M /*ordem*/);

 double jota2n(double N /*grau*/,double f/*achatamento do elipsoide de referência*/,double e/*excentricidade do elipsoide*/,double J2);

//calculo dos coeficientes dos termos zonais pares do desenvolvimento em série de funções hamonicas esféricas do potencial gravitacional
double CoefTzonaispares(double GMg,double R,/*double f achatamento do elipsoide de referência,int M/*ordem,*/int N, /*grau*/double J2,double J2n,double k);
double SigCoefTzonaispares(double GMg,double R,/*double f achatamento do elipsoide de referência,int M/*ordem,*/int N /*grau*/,double CoefZ/*CTzonais  */);
#endif
