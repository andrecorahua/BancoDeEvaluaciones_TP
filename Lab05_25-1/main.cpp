/*
Programa: Gestión y consolidación de infracciones por empresa
  Autor: Andre Corahua

  Descripción específica:
  - Lee el padrón de empresas y carga sus DNIs en arrDni, guardando la cantidad en cantEmpresas.
  - Lee el archivo de placas y separa cada placa en:
      * arrDniPlacas (DNI del titular de la placa)
      * arrC1 (letra de la placa)
      * arrN1 y arrN2 (partes numéricas de la placa)
    Guardando la cantidad total en cantPlacas.
  - Lee la tabla de infracciones y carga:
      * arrGra (gravedad: L, M o MG)
      * arrCodMulta (código de infracción)
      * arrValorMulta (monto asociado)
    Guardando la cantidad total en cantMultas.
  - Procesa todas las infracciones cruzando empresas, placas y tabla:
      * Acumula por empresa la cantidad de multas leves, graves y muy graves
        en arrCantL, arrCantM y arrCantMG.
      * Suma los montos por tipo de gravedad en arrMultaL, arrMultaM y arrMultaMG.
      * Cuenta ocurrencias por código de infracción en arrCantCod.
  - El main solo orquesta la lectura de archivos y el procesamiento,
    dejando los resultados consolidados en los arreglos indicados.
*/
#include "Biblioteca/FuncionesAuxiliares.h"
#define MAX_EMPRESAS 45
#define MAX_PLACAS 150
#define MAX_TABLA 150

int main() {

    int arrDni[MAX_EMPRESAS];
    int cantEmpresas;
    procesarEmpresas(arrDni,cantEmpresas);
    char arrC1[MAX_PLACAS];// arreglo Caracter 1
    int arrDniPlacas[MAX_PLACAS];
    int arrN1[MAX_PLACAS];//arreglo Numero 1 (de la placa)
    int arrN2[MAX_PLACAS];//arreglo Numero 2 (de la placa)
    int cantPlacas;

    // Llamada a la función que lee el archivo de placas y llena los arreglos correspondientes
    // Formato esperado de placa: Letra-Número1-Número2 (ej: A123-456)
    procesarPlacas(arrDniPlacas,arrC1,arrN1,arrN2,cantPlacas);
    char arrGra[MAX_TABLA];//arreglo Gravedad
    int arrCodMulta[MAX_TABLA];
    int cantMultas;
    double arrValorMulta[MAX_TABLA];
    procesarTabla(arrGra,arrCodMulta,arrValorMulta,cantMultas);// tabla de infracciones
    int arrCantL[MAX_EMPRESAS]={0};//arreglo Cantidad multas LEVES
    int arrCantM[MAX_EMPRESAS]={0};//arreglo Cantidad multas GRAVES
    int arrCantMG[MAX_EMPRESAS]={0};//arreglo Cantidad multas MUY GRAVES
    int arrCantCod[MAX_TABLA]={0};//arreglo Cantidad Codigo multado

    // Declaración e inicialización de arreglo para acumular el monto total de multas L, M y MG por empresa
    double arrMultaL[MAX_EMPRESAS]={0};
    double arrMultaM[MAX_EMPRESAS]={0};
    double arrMultaMG[MAX_EMPRESAS]={0};
    procesarInfracciones(arrDni,arrDniPlacas,arrC1,arrN1,arrN2,arrGra,arrCodMulta,arrValorMulta,arrCantL,arrCantM,
        arrCantMG,arrMultaL,arrMultaM,arrMultaMG,cantEmpresas,cantPlacas,cantMultas,arrCantCod);
    return 0;
}