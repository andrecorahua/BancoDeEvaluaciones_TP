
#include "FuncionesAuxiliares.h"

// Definición de una constante para el número de líneas a imprimir en el reporte
#define LINEAS 135

// Función que procesa el archivo de empresas registradas
// Parámetros:
//   - arrDni: arreglo donde se almacenarán los DNIs de las empresas
//   - cantEmpresas: variable por referencia que almacenará la cantidad de empresas leídas
void procesarEmpresas(int *arrDni, int &cantEmpresas) {
    int i=0;
    ifstream archEmpresas ("ArchivoDeDatos/EmpresasRegistradas.txt",ios::in);
    if (not archEmpresas.is_open()) {
        cout<<"Error opening file EmpresasRegistradas.txt";
        exit(1);
    }
    while (true) {
        archEmpresas>>arrDni[i];
        if (archEmpresas.eof()) break;
        while (archEmpresas.get()!='\n') i++;
    }
    cantEmpresas=i+1;
}


// Función que procesa el archivo de placas registradas
// Parámetros:
//   - arrDniPlacas: arreglo con los DNIs asociados a cada placa
//   - arrC1: arreglo con la letra de cada placa
//   - arrN1: arreglo con el primer número de cada placa
//   - arrN2: arreglo con el segundo número de cada placa
//   - cantPlacas: variable por referencia que almacenará la cantidad de placas leídas
void procesarPlacas(int *arrDniPlacas,char *arrC1,int *arrN1,int *arrN2,int &cantPlacas ){
    // Abre el archivo "PlacasRegistradas.txt" en modo lectura
    ifstream archPlacas("ArchivoDeDatos/PlacasRegistradas.txt",ios::in);

    // Verifica si el archivo se abrió correctamente
    if (not archPlacas.is_open()) {
        // Muestra mensaje de error si no se pudo abrir el archivo
        cout<<"ERROR. No abre el archivo PlacasRegistradas"<<endl;
    }

    // Inicializa el contador de placas en 0
    // Variable 'dni' declarada pero no utilizada (posible código residual)
    int i=0,dni;

    // Variable para leer caracteres separadores (como guiones)
    char c;

    // Bucle infinito que se romperá cuando se llegue al final del archivo
    while (true) {
        // Lee el DNI asociado a la placa
        archPlacas>>arrDniPlacas[i];

        // Si se llegó al final del archivo, sale del bucle
        if (archPlacas.eof())break;

        // Ignora espacios en blanco y saltos de línea
        archPlacas>>ws;

        // Lee la placa en formato: Letra Número1 Separador Número2 (ej: A123-456)
        archPlacas>>arrC1[i]>>arrN1[i]>>c>>arrN2[i];

        // Incrementa el contador para la siguiente placa
        i++;
    }

    // Guarda la cantidad total de placas leídas
    cantPlacas=i;
}

// Función que procesa la tabla de infracciones
// Parámetros:
//   - arrGra: arreglo con la gravedad de cada infracción (L=Leve, G=Grave, M=Muy Grave)
//   - arrCodMulta: arreglo con los códigos de cada multa
//   - arrValorMulta: arreglo con el valor monetario de cada multa
//   - cantMultas: variable por referencia que almacenará la cantidad de multas leídas
void procesarTabla(char *arrGra,int *arrCodMulta,double *arrValorMulta,int &cantMultas) {
    // Abre el archivo "TablaDeInfracciones.txt" en modo lectura
    ifstream  archTabla("ArchivoDeDatos/TablaDeInfracciones.txt",ios::in);
    if (not archTabla.is_open()) {
        cout<<"ERROR. No abre el archivo TablaDeInfracciones"<<endl;
    }
    int i=0;
    while (true) {
        archTabla>>arrGra[i]>>arrCodMulta[i]>>arrValorMulta[i];
        if (archTabla.eof())break;
        while (archTabla.get()!='\n');
        i++;
    }
    cantMultas=i;
}
void procesarInfracciones(int *arrDni,int *arrDniPlacas,char *arrC1,int *arrN1,int *arrN2,char *arrGra,int *arrCodMulta,double *arrValorMulta,
                        int *arrCantL,int *arrCantM,int *arrCantMG,double *arrMultaL,double *arrMultaM,double *arrMultaMG,
                        int cantEmpresas,int cantPlacas,int cantMultas,int *arrCantCod){
    ifstream archInfra("ArchivoDeDatos/InfraccionesCometidas.txt",ios::in);

    if (not archInfra.is_open()) {
        cout<<"ERROR. No abre el archivo InfraccionesCometidas"<<endl;
    }
    int d,m,a,n1,n2,codMulta,indicePlaca,indiceInfraccion,dniPlaca,indiceEmpresa;
    char c,c1,gra;
    while (true) {
        archInfra>>d>>c>>m>>c>>a;
        if (archInfra.eof())break;
        archInfra>>ws;
        archInfra>>c1>>n1>>c>>n2;
        indicePlaca=buscarIndicePlaca(c1,arrC1,n1,arrN1,n2,arrN2,cantPlacas);
        dniPlaca=arrDniPlacas[indicePlaca];
        indiceEmpresa=buscarIndiceEmpresa(dniPlaca,arrDni,cantEmpresas);
        archInfra>>ws;
        archInfra>>gra>>codMulta;
        indiceInfraccion=buscarIndiceInfraccion(gra,arrGra,codMulta,arrCodMulta,cantMultas);
        arrCantCod[indiceInfraccion]++;
        if (indiceInfraccion>=0 and indiceEmpresa>=0) {
            // Si la infracción es LEVE
            if (arrGra[indiceInfraccion]=='L') {
                arrCantL[indiceEmpresa]++;
                arrMultaL[indiceEmpresa]=arrMultaL[indiceEmpresa]+arrValorMulta[indiceInfraccion];
            }
            else if(arrGra[indiceInfraccion]=='G'){
                arrCantM[indiceEmpresa]++;
                arrMultaM[indiceEmpresa]=arrMultaM[indiceEmpresa]+arrValorMulta[indiceInfraccion];
            }
            else if (arrGra[indiceInfraccion]=='M') {
                arrCantMG[indiceEmpresa]++;
                arrMultaMG[indiceEmpresa]=arrMultaMG[indiceEmpresa]+arrValorMulta[indiceInfraccion];
            }
        }
    }
    ordenarEmpresas(arrDni,arrCantL,arrCantM,arrCantMG,arrMultaL,arrMultaM,arrMultaMG,cantEmpresas);
    ordenarMultas(arrGra,arrCodMulta,arrValorMulta,arrCantCod,cantMultas);
    crearReporte(arrDni,arrDniPlacas,arrC1,arrN1,arrN2,arrGra,arrCodMulta,arrValorMulta,arrCantL,arrCantM,arrCantMG,arrMultaL,arrMultaM,arrMultaMG,
                cantEmpresas,cantPlacas,cantMultas,arrCantCod);
}
void crearReporte(int *arrDni,int *arrDniPlacas,char *arrC1,int *arrN1,int *arrN2,char *arrGra,int *arrCodMulta,double *arrValorMulta,
                        int *arrCantL,int *arrCantM,int *arrCantMG,double *arrMultaL,double *arrMultaM,double *arrMultaMG,
                        int cantEmpresas,int cantPlacas,int cantMultas,int *arrCantCod) {
    ofstream archReporte("ArchivoDeReporte/Reporte.txt",ios::out);
    archReporte<<fixed;
    archReporte.precision(2);
    crearCabeceraCompanias(archReporte);
    int i=0;
    while (i<cantEmpresas) {
        lineas(LINEAS,'=',archReporte);
        archReporte<<"COMPANIA No. "<<i<<" DNI DEL REPRESENTANTE LEGAL: "<<arrDni[i]<<endl;
        lineas(LINEAS,'-',archReporte);
        archReporte<<"MULTAS APLICADAS SEGUN LA GRAVEDAD:"<<endl;
        archReporte<<setw(20)<<"LEVES"<<setw(36)<<"GRAVES"<<setw(31)<<"MUY GRAVES"<<setw(30)<<"TOTALES"<<endl;
        archReporte<<setw(12)<<"CANTIDAD"<<setw(19)<<"TOTAL DE MULTAS"<<setw(16)<<"CANTIDAD"<<setw(18)<<"TOTAL DE MULTAS"
                   <<setw(14)<<"CANTIDAD"<<setw(19)<<"TOTAL DE MULTAS"<<setw(14)<<"CANTIDAD"<<setw(19)<<"TOTAL DE MULTAS"<<endl;
        archReporte<<setw(8)<<arrCantL[i]<<setw(18)<<arrMultaL[i]<<setw(17)<<arrCantM[i]<<setw(18)<<arrMultaM[i]
                   <<setw(15)<<arrCantMG[i]<<setw(14)<<arrMultaMG[i]<<setw(19)<<arrCantL[i]+arrCantM[i]+arrCantMG[i]
                   <<setw(17)<<arrMultaL[i]+arrMultaM[i]+arrMultaMG[i]<<endl;
        i++;
    }
    lineas(LINEAS,'/',archReporte);archReporte<<endl;
    crearCabeceraInfraccion(archReporte);
    archReporte<<setw(41)<<"CODIGO"<<setw(17)<<"GRAVEDAD"<<setw(15)<<"MULTA"<<setw(17)<<"CANTIDAD"<<setw(18)<<"MONTO TOTAL"<<endl;
    int j=0,cantidadTotal=0;
    double montoTotal=0;;
    while (j<cantMultas) {
        archReporte<<setw(40)<<arrCodMulta[j]<<setw(10)<<" ";
        if (arrGra[j]=='L')archReporte<<"LEVE     ";
        else if (arrGra[j]=='G')archReporte<<"GRAVE    ";
        else if (arrGra[j]=='M')archReporte<<"MUY GRAVE";
        archReporte<<setw(15)<<arrValorMulta[j]<<setw(12)<<arrCantCod[j]<<setw(20)<<arrValorMulta[j]*arrCantCod[j]<<endl;
        cantidadTotal=cantidadTotal+arrCantCod[j];
        montoTotal=montoTotal+(arrValorMulta[j]*arrCantCod[j]);
        j++;
    }

    lineas(LINEAS,'-',archReporte);
    archReporte<<setw(41)<<"TOTAL"<<setw(45)<<cantidadTotal<<setw(20)<<montoTotal<<endl;
    lineas(LINEAS,'=',archReporte);
}
void crearCabeceraCompanias(ofstream &archReporte) {
    archReporte<<setw(79)<<"MINISTERIO DE TRANSPORTE"<<endl;
    archReporte<<setw(83)<<"MULTAS IMPUESTAS A LAS COMPANIAS"<<endl;
}
void crearCabeceraInfraccion(ofstream &archReporte) {
    archReporte<<setw(83)<<"MULTAS IMPUESTAS POR INFRACCION"<<endl;
    lineas(LINEAS,'=',archReporte);
}
int buscarIndiceEmpresa(int dniPlaca,int *arrDni,int cantEmpresas) {
    int indice=0;

    while (indice<cantEmpresas) {
        if (dniPlaca==arrDni[indice])return indice;
        indice++;
    }
    return -1;
}
int buscarIndicePlaca(char c1,char *arrC1,int n1,int *arrN1,int n2,int *arrN2,int cantPlacas) {
    int indice=0;
    while (indice<cantPlacas) {
        if (c1==arrC1[indice] and n1==arrN1[indice] and n2==arrN2[indice])return indice;
        indice++;
    }
    return -1;
}

int buscarIndiceInfraccion(char gra,char *arrGra,int codMulta,int *arrCodMulta,int cantMultas) {
    int indice=0;
    while (indice<cantMultas) {
        if (gra==arrGra[indice] and codMulta==arrCodMulta[indice])return indice;
        indice++;
    }
    return -1;
}
void ordenarEmpresas(int *arrDni,int *arrCantL,int *arrCantM,int *arrCantMG,double *arrMultaL,double *arrMultaM,double *arrMultaMG,int cantEmpresas) {
    for (int i=0;i<cantEmpresas-1;i++) {
        for (int j=i+1;j<cantEmpresas;j++) {
            if (arrDni[i]>arrDni[j]) {
                cambiarInt(arrDni,i,j);
                cambiarInt(arrCantL,i,j);
                cambiarInt(arrCantM,i,j);
                cambiarInt(arrCantMG,i,j);
                cambiarDouble(arrMultaL,i,j);
                cambiarDouble(arrMultaM,i,j);
                cambiarDouble(arrMultaMG,i,j);
            }
        }
    }
}
void ordenarMultas(char *arrGra,int *arrCodMulta,double *arrValorMulta,int *arrCantCod,int cantMultas) {
    for (int i=0;i<cantMultas-1;i++) {
        for (int j=i+1;j<cantMultas;j++) {
            if (arrCodMulta[i]>arrCodMulta[j]) {
                cambiarInt(arrCodMulta,i,j);
                cambiarChar(arrGra,i,j);
                cambiarDouble(arrValorMulta,i,j);
                cambiarInt(arrCantCod,i,j);
            }
        }
    }
}
void cambiarInt(int *arr,int i,int j) {
    int aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
}
void cambiarDouble(double *arr,int i,int j) {
    double aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
}
void cambiarChar(char *arr,int i,int j) {
    char aux=arr[i];
    arr[i]=arr[j];
    arr[j]=aux;
}
void lineas(int cantLineas,char c,ofstream &archReporte) {
    int i=0;
    while (i<cantLineas) {
        archReporte<<c;
        i++;
    }
    archReporte<<endl;
}