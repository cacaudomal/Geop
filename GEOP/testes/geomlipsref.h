//
//  geomlipsref.h
//  GEOP
//
//  Created by Clara on 25/05/17.
//
//

#ifndef geomlipsref_h
#define geomlipsref_h

#define A 6378137              //semimajor axis (m)
#define B 6356752.3141        // semiminor axis (m)
#define W 7292115e-11          // angular velocity (rad/s)
#define GM 3986005e8           // geocentric gravitational constant (m^3/s^2)
#define YE 9.7803267715        // Equatorial normal gravity (m/s^2)
#define YP 9.8321863685        // Polar normal gravity (m/s^2))

double GeoRef_radtodeg(double rad);
double GeoRef_degtorad(double deg);

double GeoRef_dist(double val1,double val2);
double GeoRef_modulo(double val);

//Calculo da primeira execentricidade
double GeoRef_PexctElipsRef();
//calculo do achatamento
double GeoRef_AchatmtElipsRef();
double GeoRef_calcK();
double GeoRef_calcm();

struct Dimensoes GeoRef_Dimret(struct Dimensoes bound);
struct Parametros GeoRef_parametrosElispref(struct Parametros cabe );

void GeoRef_dfre_matrix(double **vetorSum,int nrows,int ncol);
double **GeoRef_creat_double_matrix(int nrows,int ncol);

#endif /* geomlipsref_h */
