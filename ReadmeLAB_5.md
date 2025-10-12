**PLAN PROYECTO TIPO ARREGLO**


1) Preparar estructura y entorno
Crea carpetas:
ArchivoDeDatos/ (insumos .txt)
ArchivoDeReporte/ (salidas)
Biblioteca/ (código común)
Archivos base:
main.cpp
Biblioteca/FuncionesAuxiliares.h
Biblioteca/FuncionesAuxiliares.cpp
Compila un “hola mundo” para confirmar toolchain.

2) Definir el contrato (header) primero
En FuncionesAuxiliares.h declara todas las funciones que usará main:
Lecturas: procesarEmpresas, procesarPlacas, procesarTabla
Búsquedas: buscarIndiceEmpresa, buscarIndicePlaca, buscarIndiceInfraccion
Proceso central: procesarInfracciones
Ordenamientos: ordenarEmpresas, ordenarMultas (+ swaps cambiarInt/Double/Char)
Reporte: lineas, crearCabeceraCompanias, crearCabeceraInfraccion, crearReporte
Con el header listo, main puede incluirlo y compilar aunque las funciones estén vacías.

3) Crear datos de prueba mínimos (para iterar rápido)
ArchivoDeDatos/EmpresasRegistradas.txt
11111111
22222222
ArchivoDeDatos/PlacasRegistradas.txt
11111111 A123-456
22222222 B555-111
ArchivoDeDatos/TablaDeInfracciones.txt
L 101 50.00
G 201 150.00
M 301 300.00
ArchivoDeDatos/InfraccionesCometidas.txt
01/01/2024 A123-456 L 101
02/01/2024 B555-111 G 201
03/01/2024 A123-456 M 301
Estos archivos te permiten probar fin a fin en pocos minutos.

4) Esqueleto de main y constantes
Define límites: MAX_EMPRESAS, MAX_PLACAS, MAX_TABLA.
Declara arreglos, llama a las funciones en este orden:
procesarEmpresas
procesarPlacas
procesarTabla
procesarInfracciones
Añade al inicio el comentario descriptivo exigido.
Compila; si enlaza, vas bien.

5) Implementar lecturas con límites y validaciones
Implementa estas tres primero y pruébalas de inmediato:

procesarEmpresas
procesarPlacas
procesarTabla
Consejos:

Verifica apertura de archivo; si falla, muestra error y exit(1).
Tras cada extracción del stream, valida el estado del stream.
Evita desbordes: antes de i++ verifica i < MAX_…; si no, corta y reporta.
Limpia fin de línea con ignore hasta ‘\n’.
Prueba: después de cada lectura, imprime cantEmpresas/cantPlacas/cantMultas y un par de registros por consola.

6) Implementar búsquedas sencillas
buscarIndiceEmpresa: lineal por DNI.
buscarIndicePlaca: match en c1, n1, n2.
buscarIndiceInfraccion: match en gra y codMulta.
Prueba con casos que existan y que no existan (debe retornar -1).
Tip: si los datos son grandes, después podrías optimizar con mapas, pero no es necesario para terminar rápido.

7) Implementar procesamiento central
procesarInfracciones:
Lee cada registro: fecha, placa (c1, n1, n2), gravedad y código.
Obtén índicePlaca → DNI → índiceEmpresa.
Obtén índiceInfraccion.
Si ambos índices son válidos, actualiza:
arrCantL/M/MG
arrMultaL/M/MG sumando arrValorMulta[indiceInfraccion]
arrCantCod[indiceInfraccion]++
Al final:
ordenarEmpresas (sincronizando todos los arreglos por empresa)
ordenarMultas (sincronizando los arreglos de la tabla)
crearReporte
Mientras pruebas, imprime logs si algún índice = -1 para detectar inconsistencias de datos.

8) Implementar ordenamientos y utilidades
cambiarInt/Double/Char (swaps).
ordenarEmpresas y ordenarMultas con doble bucle sencillo.
lineas(cant, char, ofstream&).
Prueba: antes del reporte, verifica que, tras ordenar, los arreglos sigan alineados (muestra 2–3 filas por consola).

9) Implementar reporte
crearCabeceraCompanias, crearCabeceraInfraccion, crearReporte.
Formato: fixed, precision(2), setw para columnas.
Genera ArchivoDeReporte/Reporte.txt y revisa:
Totales por empresa y totales por infracción.
Sumas finales coherentes.
Si el formato no es idéntico al requerido, ajusta títulos, separadores y anchos.

10) Validación rápida de consistencia
La suma de arrCantCod sobre todas las multas debe igualar
sum(arrCantL + arrCantM + arrCantMG) sobre todas las empresas.
La suma de montos por empresa debe igualar la suma por código de multa:
Σ_empresas (L+M+MG) == Σ_multas (valor * cantidad).
Haz 2 asserts o prints para confirmar.

11) Endurecer entradas y bordes
Maneja placas sin empresa o multas no encontradas: ignora y loguea.
Maneja archivos vacíos sin fallar.
Si superas límites de MAX_…, corta y reporta claramente.
12) Entrega limpia
Quita prints de depuración.
Mantén nombres claros y comentarios breves encima de cada función.
Verifica rutas relativas y existencia de carpetas al ejecutar.
Vuelve a correr con datos de prueba y con los datos reales.
