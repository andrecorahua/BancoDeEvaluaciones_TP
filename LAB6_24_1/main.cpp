#include "Bibliotecas/Funciones.h"
#define MAX_CANT_ALUMNOS 100
/*
 *
 */
int main(int argc, char** argv) {

    int arrCodAlumnos[MAX_CANT_ALUMNOS];
    int arrNumCursos[MAX_CANT_ALUMNOS] {};
    double arrSumaPonderada[MAX_CANT_ALUMNOS] {};
    double arrNumCreditos[MAX_CANT_ALUMNOS] {};
    int cantAlumnos, codFacultad;


    //cout << "Ingrese el codigo de la facultad";
    //cin >> codFacultad;

    codFacultad = 500017;

    procesarCalificaciones(arrCodAlumnos, arrNumCursos, arrSumaPonderada, arrNumCreditos,
            cantAlumnos);

    verificarArreglos(arrCodAlumnos, arrNumCursos, arrSumaPonderada, arrNumCreditos,
            cantAlumnos);

    elaborarReporte(codFacultad, arrCodAlumnos, arrNumCursos, arrSumaPonderada, arrNumCreditos,
            cantAlumnos);


    return 0;
}
