#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#define LPAL 30
#define TAM 101
#define TAMPAL 16
#define DIMENSION 12


#define VERTICAL 1
#define HORIZONTAL 2
#define NO_ENCONTRADO 3

#define TODO_OK 4
#define FALLA 5

typedef struct
{
    char **matriz;
    char pal[LPAL][TAMPAL];
    char pista[LPAL][TAM];
    int tamanio;
    int cantPal;
    int cantPistas;
}
Tablero;

void bienvenida();
int crearTablero(Tablero *tab);
bool cantidadPalabras(Tablero *tab);
bool cantidadPistas(Tablero *tab);

/** Iniciar **/
void iniciarTablero(Tablero *tab);
bool iniciarPalabras(Tablero *tab);
bool iniciarPistas(Tablero *tab);

/** Palabras **/
void insertarPalabras(Tablero *tab);
void ubicarPalabras(Tablero *tab, char *palabra, int longitud, int orientacion);
void insertarPalabrasRandom(Tablero *tab);
bool esLetra(char c);
char* aMayuscula(char *entrada);
char* aMinuscula(char *entrada);
char* esComando(char *entrada);
bool pista(char *entrada);
bool verificarPalabraEstablecida(Tablero *tab, char *entrada);

/** Horizontal **/
bool espacioDisponibleHorizontal(Tablero *tab, char *palabra, int fila, int columna);
void escribirPalabraHorizontal(Tablero *tab, char *palabra, int longitud, int fila, int columna);

/** Vertical **/
bool espacioDisponibleVertical(Tablero *tab, char *palabra, int fila, int columna);
void escribirPalabraVertical(Tablero *tab, char *palabra, int longitud, int fila, int columna);

/** Imprimir **/
void imprimirTablero(Tablero *tab);
void imprimirPista(Tablero *tab);

/** Juego **/
bool iniciaJuego(Tablero *tab);
bool finalizarJuego(char *entrada);
bool buscarUbicacion(Tablero *tab, char *entrada);
int verificarPalabra(Tablero *tab, char *entrada, int fila, int columna);
void ocultarPalabra(Tablero *tab, char *entrada, int fila, int columna, int rta);
void ocultarPalabraEncontrada(Tablero *tab, char *entrada);
void ocultarPista(Tablero *tab, int i);
void ingresarPalabra(char *entrada);
void ingresarPalabraPostPista(char *entrada);
void tiempoTranscurrido(time_t tiempoInicio, time_t tiempoFin);
int verificarTamanio(Tablero *tab);
void liberarTablero(Tablero *tab);
void liberarTableroFalla(Tablero *tab, int PosFalla);
void limpiarBufferEntrada();



#endif // FUNCIONES_H_INCLUDED
