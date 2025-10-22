#include "Funciones.h"
#define CANT_MAX_LINEA 140

void procesarCalificaciones(int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPonderada,
        double *arrNumCreditos, int &cantAlumnos){

    ifstream archCalificaciones("ArchivoDeDatos/Calificaciones.txt", ios::in);

    if (not archCalificaciones.is_open()){
        cout << "ERROR, No se ha podido abrir el archivo Calificaciones.txt" << endl;
        exit(1);
    }

    char codCurso[10];
    double cantCreditos;
    cantAlumnos = 0;
    while (true){
        archCalificaciones >> codCurso;
        if (archCalificaciones.eof()) break;
        archCalificaciones >> cantCreditos;
        procesarNotasCurso(archCalificaciones, cantCreditos, arrCodAlumnos, arrNumCursos, arrSumaPonderada,
                arrNumCreditos, cantAlumnos);
    }
}
void procesarNotasCurso(ifstream &archCalificaciones, double cantCreditos, int *arrCodAlumnos,
       int *arrNumCursos, double *arrSumaPonderada, double *arrNumCreditos, int &cantAlumnos){

    int codAlumno, nota, posAlumno;
    while (true){
        archCalificaciones >> codAlumno >> nota;
        posAlumno = buscarAlumno(codAlumno, arrCodAlumnos, cantAlumnos);
        if (posAlumno != -1){   // ACTUALIZA
            arrNumCursos[posAlumno] = arrNumCursos[posAlumno] + 1;
            arrSumaPonderada[posAlumno] = arrSumaPonderada[posAlumno] + (nota * cantCreditos);
            arrNumCreditos[posAlumno] = arrNumCreditos[posAlumno] + cantCreditos;
        } else {
            insertarAlumno(codAlumno, nota, cantCreditos, arrCodAlumnos, arrNumCursos, arrSumaPonderada,
                    arrNumCreditos, cantAlumnos);
        }
        if (archCalificaciones.get() == '\n') break;
    }
}

int buscarAlumno(int codAlumno, int *arrCodAlumnos, int cantAlumnos){
    int limInf, limSup, puntoMedio;
    limInf = 0;
    limSup = cantAlumnos - 1;
    while (true){
        if (limInf > limSup) return -1;
        puntoMedio = (limInf + limSup)/2;
        if (arrCodAlumnos[puntoMedio] == codAlumno) return puntoMedio;
        if (codAlumno > arrCodAlumnos[puntoMedio]){
            limInf = puntoMedio + 1;
        } else {
            limSup = puntoMedio - 1;
        }
    }
}

void insertarAlumno(int codAlumno, int nota, double cantCreditos, int *arrCodAlumnos,  int *arrNumCursos,
        double *arrSumaPonderada, double *arrNumCreditos, int &cantAlumnos){

    int i;

    i = cantAlumnos;
    while (true){
        i--;
        if (i < 0 or codAlumno > arrCodAlumnos[i]) break;
        arrCodAlumnos[i+1] = arrCodAlumnos[i];
        arrNumCursos[i+1] = arrNumCursos[i];
        arrSumaPonderada[i+1] = arrSumaPonderada[i];
        arrNumCreditos[i+1] = arrNumCreditos[i];
    }

    arrCodAlumnos[i+1] = codAlumno;
    arrNumCursos[i+1] = 1;
    arrSumaPonderada[i+1] = nota * cantCreditos;
    arrNumCreditos[i+1] = cantCreditos;

    cantAlumnos++;
}

void verificarArreglos(int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPonderada,
        double *arrNumCreditos, int cantAlumnos){

    ofstream archReporte("Prueba.txt", ios::out);

    if (not archReporte.is_open()){
        cout << "ERROR, No se ha podido abrir el archivo Prueba.txt" << endl;
        exit(1);
    }
    for(int i=0; i < cantAlumnos; i++){

        archReporte << setw(10) << arrCodAlumnos[i] << setw(10) << arrNumCursos[i] <<
                setw(10) << arrSumaPonderada[i] << setw(10) << arrNumCreditos[i] << endl;
    }

}

void elaborarReporte(int codFacultad, int *arrCodAlumnos, int *arrNumCursos, double *arrSumaPonderada,
        double *arrNumCreditos, int cantAlumnos){

    ifstream archAlumnos("ArchivoDeDatos/Alumnos.txt", ios::in);
    if (not archAlumnos.is_open()){
        cout << "ERROR, No se ha podido abrir el archivo Alumnos.txt" << endl;
        exit(1);
    }
    ifstream archFacultades("ArchivoDeDatos/Facultades.txt", ios::in);
    if (not archFacultades.is_open()){
        cout << "ERROR, No se ha podido abrir el archivo Facultades.txt" << endl;
        exit(1);
    }
    ofstream archReporte("ArchivoDeReporte/Reporte.txt", ios::out);
    if (not archReporte.is_open()){
        cout << "ERROR, No se ha podido abrir el archivo Reporte.txt" << endl;
        exit(1);
    }

    elaborarEncabezadoReporte(archReporte, archFacultades, codFacultad);
    archReporte.precision(2);
    archReporte << fixed;
    int codAlumno, codFacultadAlumno,  posAlumno;
    double promPonderado;
    char nombreCompleto[100];
    while (true){
        archAlumnos >> codAlumno;
        if (archAlumnos.eof()) break;
        archAlumnos >> nombreCompleto >> codFacultadAlumno;
        if (codFacultadAlumno == codFacultad){
            posAlumno = buscarAlumno(codAlumno, arrCodAlumnos, cantAlumnos);
            if (posAlumno != -1){
                archReporte << codAlumno << " - ";
                imprimirNombreAlumno(nombreCompleto, archReporte);
                promPonderado = arrSumaPonderada[posAlumno]/arrNumCreditos[posAlumno];
                archReporte << setw(6) << arrNumCursos[posAlumno] << setw(22) <<
                        arrSumaPonderada[posAlumno]<< setw(19) << arrNumCreditos[posAlumno] <<
                        setw(19) << promPonderado << endl;
            }
        }

    }



}

void elaborarEncabezadoReporte(ofstream &archReporte, ifstream &archFacultades, int codFacultad){


    archReporte << setw(70) << "INSTITUCION EDUCATIVA TP" << endl;
    archReporte << setw(80) << "PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS" << endl;
    archReporte << setw(60) << "CICLO 24-1" << endl;

    char nombreFacultad[40];
    int codigoFacultad;
    while (true){
        archFacultades >> nombreFacultad;
        if (archFacultades.eof()) break;
        archFacultades >> codigoFacultad;
        if (codigoFacultad == codFacultad){
            imprimirNombreFacultad(nombreFacultad, archReporte);
            break;
        }
    }

    escribirLinea('=', CANT_MAX_LINEA, archReporte);
    archReporte << setw(15) << "ALUMNO" << setw(55) << "No de Cursos" << setw(20) << "Suma Ponderada" <<
            setw(20) << "No. de creditos" << setw(20) << "Prom Ponderado" << endl;
    escribirLinea('=', CANT_MAX_LINEA, archReporte);
}

void escribirLinea(char c, int cant, ofstream &arch){
    for(int i=0; i < cant; i++){
        arch.put(c);
    }
    arch << endl;
}

void imprimirNombreFacultad(char *nombreFacultad, ofstream &archReporte){


    for(int i=0; nombreFacultad[i]; i++){
        if (nombreFacultad[i] == '_'){
            nombreFacultad[i] = ' ';
        }
    }

    archReporte << setw(70) << nombreFacultad << endl;

}

void imprimirNombreAlumno(char *nombreCompleto, ofstream &archReporte){

    int cant, j, k, l, longitud;
    cant = 0;
    char apPaterno[20];
    char apMaterno[20];
    char nombres[50];
    j = 0;
    k = 0;
    l = 0;
    longitud = 0;
    for(int i=0; nombreCompleto[i]; i++){
        if (nombreCompleto[i] == '/'){
            cant++;
        } else {
            if (cant == 0){
                apPaterno[j] = nombreCompleto[i];
                j++;
            } else if (cant == 1){
                apMaterno[k] = nombreCompleto[i];
                k++;
            } else {
                if (nombreCompleto[i] != '-'){
                    nombres[l] = nombreCompleto[i];
                } else {
                    nombres[l] = ' ';
                }
                l++;
            }
            longitud++;
        }
    }

    apPaterno[j] = 0;
    apMaterno[k] = 0;
    nombres[l] = 0;
    convertirCadena(apPaterno);
    convertirCadena(apMaterno);
    convertirCadena(nombres);

    archReporte << nombres << " " << apPaterno << " " << apMaterno;

    for(int i=0; i < 45-longitud; i++){
        archReporte.put(' ');
    }
}

void convertirCadena(char *cadena){

    bool mayuscula;
    mayuscula = true;

    for(int i=0; cadena[i]; i++){
        if (cadena[i] != ' '){
            if (mayuscula){ // solamente un caracter imprime en mayuscula
                mayuscula = false;
            } else {
                cadena[i] = cadena[i] - 'A'+ 'a';
            }
        } else {
            mayuscula = true;
        }
    }

}