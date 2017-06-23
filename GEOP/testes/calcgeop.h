//
//  calcgeop.h
//  GEOP
//
//  Created by Clara on 25/05/17.
//
//

#ifndef calcgeop_h
#define calcgeop_h

#define A 6378137              //semimajor axis (m)
#define B 6356752.3141        // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

//Parametros para o calculo dos coeficientes dos termos zonais pares do desenvolvimento em série de funções hamonicas esféricas do potencial gravitacional

// double calcgp_jota2(double f/*achatamento do elipsoide de referência*/,double M /*ordem*/);
double calcgp_jota2(double f);
double calcgp_jota2n(double N ,double e,double J2);

//calculo dos coeficientes dos termos zonais pares do desenvolvimento em série de funções hamonicas esféricas do potencial gravitacional

double calcgp_CoefTzonaispares(int K,double J2,double J2n);
double calcgp_CoefTzonaispares_p2(double GMg,double R,int N /*grau*/,double CoefZ/*CTzonais*/);

double calcgp_CorrecaoC(double N,double K,double GMg,double R,double e,double f);
#endif /* calcgeop_h */
