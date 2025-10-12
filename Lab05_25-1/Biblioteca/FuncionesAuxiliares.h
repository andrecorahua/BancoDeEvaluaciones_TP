
#ifndef LAB05_25_1_FUNCIONESAUXILIARES_H
#define LAB05_25_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void procesarEmpresas(int *arrDni,int &cantEmpresas);

void procesarPlacas(int *arrDniPlacas,char *arrC1,int *arrN1,int *arrN2,int &cantPlacas);

void procesarTabla(char *arrGra,int *arrCodMulta,double *arrValorMulta,int &cantMultas);

void procesarInfracciones(int *arrDni,int *arrDniPlacas,char *arrC1,int *arrN1,int *arrN2,char *arrGra,int *arrCodMulta,double *arrValorMulta,
                        int *arrCantL,int *arrCantM,int *arrCantMG,double *arrMultaL,double *arrMultaM,double *arrMultaMG,
                        int cantEmpresas,int cantPlacas,int cantMultas,int *arrCantCod);

void crearReporte(int *arrDni,int *arrDniPlacas,char *arrC1,int *arrN1,int *arrN2,char *arrGra,int *arrCodMulta,double *arrValorMulta,
                        int *arrCantL,int *arrCantM,int *arrCantMG,double *arrMultaL,double *arrMultaM,double *arrMultaMG,
                        int cantEmpresas,int cantPlacas,int cantMultas,int *arrCantCod);
void crearCabeceraCompanias(ofstream &archReporte);

void crearCabeceraInfraccion(ofstream &archReporte);

void ordenarEmpresas(int *arrDni,int *arrCantL,int *arrCantM,int *arrCantMG,double *arrMultaL,double *arrMultaM,double *arrMultaMG,int cantEmpresas);
void ordenarMultas(char *arrGra,int *arrCodMulta,double *arrValorMulta,int *arrCantCod,int cantMultas);
void cambiarInt(int *arr,int i,int j);
void cambiarDouble(double *arr,int i,int j);
void cambiarChar(char *arrGra,int i,int j);

int buscarIndiceEmpresa(int dni,int *arrDni,int cantEmpresas);
int buscarIndicePlaca(char c1,char *arrC1,int n1,int *arrN1,int n2,int *arrN2,int cantPlacas);
int buscarIndiceInfraccion(char gra,char *arrGra,int codMulta,int *arrCodMulta,int cantMultas);
void lineas(int cantLineas,char c,ofstream &archReporte);


#endif //LAB05_25_1_FUNCIONESAUXILIARES_H