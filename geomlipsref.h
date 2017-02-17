#ifndef GEOMLIPSREF_H_
#define GEOMLIPSREF_H_

#define A 6378137              //semimajor axis (m)
#define B 6356752.3141        // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

double radtodeg(double rad);
double degtorad(double deg);
double modulo(double val);
double dist(double val1,double val2);
//Calculo da primeira execentricidade
double PexctElipsRef();
//calculo do achatamento
double AchatmtElipsRef();
double calcK();
double calcm();

#endif // GEOMELIPSREF_H_INCLUDED
