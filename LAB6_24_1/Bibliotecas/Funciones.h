#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#ifndef FUNCIONES_H
#define FUNCIONES_H
void procesarCalificaciones(int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPonderada,
        double *arrNumCreditos, int &cantAlumnos);

void procesarNotasCurso(ifstream &archCalificaciones, double cantCreditos, int *arrCodAlumnos,
       int *arrNumCursos, double *arrSumaPonderada, double *arrNumCreditos, int &cantAlumnos);

int buscarAlumno(int codAlumno, int *arrCodAlumnos, int cantAlumnos);

void insertarAlumno(int codAlumno, int nota, double cantCreditos, int *arrCodAlumnos,  int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos, int &cantAlumnos);

void verificarArreglos(int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPonderada,
        double *arrNumCreditos, int cantAlumnos);
void elaborarReporte(int codFacultad, int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPonderada,
        double *arrNumCreditos, int cantAlumnos);
void elaborarEncabezadoReporte(ofstream &archReporte, ifstream &archFacultades, int codFacultad);
void escribirLinea(char c, int cant, ofstream &arch);
void imprimirNombreFacultad(char *nombreFacultad, ofstream &archReporte);
void imprimirNombreAlumno(char *nombreCompleto, ofstream &archReporte);

void convertirCadena(char *cadena);

#endif /* FUNCIONES_H */
