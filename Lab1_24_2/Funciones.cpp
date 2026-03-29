

#include <iostream>      // Entrada y salida estándar
#include <iomanip>       // Manipulación de formato de salida
#include <cmath>         // Funciones matemáticas (sin, cos, etc.)
#include "Funciones.h"   // Archivo de cabecera con las declaraciones de funciones

using namespace std;     // Usar espacio de nombres estándar

// Función principal que controla la impresión del reporte completo
void ImprimirReporte() {
    int dd, mm, aa;      // Variables para día, mes y año
    char c;              // Variable para leer caracteres separadores (como '/')
    cin >> dd >> c >> mm >> c >> aa;  // Lee la fecha en formato dd/mm/aa
    ImprimirEncabezadoDeReporte(dd, mm, aa);  // Imprime el encabezado con la fecha

    ImprimirRepartidores();  // Imprime la información de todos los repartidores
}

// Imprime el encabezado del reporte con la fecha formateada
void ImprimirEncabezadoDeReporte(int dd, int mm, int aa) {
    cout <<setw(50)<< "EMPRESA DE REPARTOS A DOMICILIO TP S. A." << endl;
    cout <<setw(37)<< "FECHA DE LOS REPARTOS: " << setw(2) << setfill('0') << dd << "/"
         << mm << "/" << aa << setfill(' ') << endl;  // Formatea día con 2 dígitos, rellena con 0
    ImprimirLinea('=', 100);  // Imprime una línea de 100 caracteres '='
}

// Imprime una línea compuesta por 'cant' veces el caracter 'simbolo'
void ImprimirLinea(char simbolo, int cant) {
    for (int i = 0; i < cant; ++i) {
        cout.put(simbolo);//"cout.put()" se utiliza cuando solo necesitas imprimir un carácter
    }
    cout << endl;
}

// Lee y procesa la información de cada repartidor hasta el fin de archivo
void ImprimirRepartidores() {
    int dni;  // Variable para el DNI del repartidor
    int cont; // Contador para controlar la longitud del nombre impreso
    while (true) {
        cont = 0;
        cin >> dni;  // Lee el DNI
        if (cin.eof()) break;  // Si se llega al fin de archivo, termina el ciclo

        cout << "Repartidor: " << endl;
        cout << "Nombre: ";
        EscribirTexto(' ', cont);  // Lee y escribe el nombre del repartidor, hasta encontrar espacio
        cout << setw(55 - cont) << " ";  // Ajusta espacios para alinear el DNI
        cout << "DNI: " << dni << endl;
        ImprimirLinea('-', 100);  // Línea separadora

        // while (cin.get()!='\n');  // Comentado: podría limpiar buffer hasta fin de línea
        ImprimirContenido();  // Imprime los datos de la ruta del repartidor
    }
}

// Lee y escribe el texto del nombre del repartidor hasta encontrar el delimitador
void EscribirTexto(char delimitador, int &cont) {
    char letra;
    cin >> letra;  // Lee el primer caracter
    cont = 0;
    while (letra != delimitador) {  // Mientras no sea el delimitador (espacio)
        if (letra == '/' or letra == '-') {  // Si es '/' o '-', imprime espacio y lee siguiente
            cout << " ";
            cin >> letra;
        }
        cout << letra;  // Imprime la letra
        cont++;         // Incrementa contador de caracteres impresos
        letra = cin.get();  // Lee siguiente caracter (incluye espacios)
    }
}

// Imprime los datos de la ruta para un repartidor (3 tramos)
void ImprimirContenido() {
    int hsal, hlleg, msal, mlleg, ssal, slleg;  // Horas, minutos y segundos de salida y llegada
    double velcProm;  // Velocidad promedio
    EncabezadoRepartidor();  // Imprime encabezado de tabla de ruta

    double puntoXpar = 0.0, puntoYpar = 0.0;  // Coordenadas del punto de partida (inicial 0,0)
    double puntoXlleg, puntoYlleg;  // Coordenadas del punto de llegada
    int i = 1;
    char c;  // Para leer caracteres separadores ':', '"', etc.
    double distancia, angTotal;
    int horaRecorrida, anggrad, angmin, angseg;

    cin >> hsal >> c >> msal >> c >> ssal;  // Lee hora de salida (hh:mm:ss)

    while (i <= 3) {  // Para los 3 tramos de entrega
        cin >> velcProm;  // Lee velocidad promedio
        cin >> hlleg >> c >> mlleg >> c >> slleg;  // Lee hora de llegada (hh:mm:ss)

        // Imprime datos de tramo con formato alineado
        cout << "Tramo " << i << ":  " << setw(2) << setfill('0') << hsal << ":" << setw(2) << msal
             << ":" << setw(2) << ssal << setfill(' ');
        cout << setw(2) << " " << setw(2) << setfill('0') << hlleg << ":" << setw(2) << mlleg
             << ":" << setw(2) << slleg << setfill(' ');
        cout << setw(4) << " " << setprecision(2) << fixed << velcProm;

        // Calcula el tiempo recorrido en formato hhmmss restando llegada - salida
        horaRecorrida = (hlleg * 10000 + mlleg * 100 + slleg) - (hsal * 10000 + msal * 100 + ssal);

        distancia = CalcularDistancia(horaRecorrida, velcProm);  // Calcula distancia recorrida
        cout << setw(4) << " " << setprecision(2) << fixed << distancia;

        // Lee ángulo en grados, minutos y segundos
        cin >> anggrad >> c >> angmin >> c >> angseg >> c;

        // Convierte ángulo total a grados decimales
        angTotal = double(anggrad) + double(angmin / 60.0) + double(angseg / 3600.0);

        // Calcula coordenadas del punto de llegada usando trigonometría
        puntoXlleg = sin(angTotal * M_PI / 180.0) * distancia + puntoXpar;  // Corregido: convertir a radianes y sumar punto anterior
        puntoYlleg = cos(angTotal * M_PI / 180.0) * distancia + puntoYpar;

        // Imprime puntos de partida y llegada
        cout << setw(7) << " " << setprecision(2) << fixed << puntoXpar << " - " << puntoYpar;
        cout << setw(7) << " " << setprecision(2) << fixed << puntoXlleg << " - " << puntoYlleg;
        cout << setw(7) << " " << setprecision(2) << fixed << distancia;

        // Actualiza punto de partida para el siguiente tramo
        puntoXpar = puntoXlleg;
        puntoYpar = puntoYlleg;

        // Calcula pago según distancia recorrida en el tramo
        double pago;
        if (distancia < 10.5) {
            pago = 8.5;
        } else if (distancia < 20.5) {
            pago = 17.75;
        } else if (distancia < 35.5) {
            pago = 29.85;
        } else {
            pago = 0.0;  // Tramo de retorno no se paga
        }
        cout << setw(8) << " " << setprecision(2) << fixed << pago;
        cout << endl;

        c = cin.get();  // Lee siguiente caracter (posiblemente salto de línea)
        i++;
    }
    ImprimirLinea('=', 100);  // Línea separadora final
}

// Imprime el encabezado de la tabla de datos de la ruta
void EncabezadoRepartidor() {
    cout << "DATOS DE LA RUTA:" << endl;
    cout << setw(9) << " " << "HORA INI" << setw(3) << " " << "HORA FIN" << setw(3) << " " << "VELOCIDAD"
         << setw(2) << " " << "DISTANCIA" << setw(2) << " " << "PUNTO DE PARTIDA(X, Y)" << setw(2) << " "
         << "PUNTO DE LLEGADA(X, Y)" << setw(2) << " " << "DISTANCIA ACUMULADA" << setw(2) << " "
         << "PAGO DE ENVIO" << endl;
}

// Calcula la distancia recorrida dado el tiempo y la velocidad
double CalcularDistancia(int hRecorrida, double velocidad) {
    double distancia;
    double HoraRecorrida;
    HoraRecorrida = double(hRecorrida) / 10000.0;  // Convierte hhmmss a horas decimales (aprox)
    distancia = velocidad * HoraRecorrida;  // distancia = velocidad * tiempo
    return distancia;
}