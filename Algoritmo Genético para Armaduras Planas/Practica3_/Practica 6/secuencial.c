#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CROMOSOMAS 8
#define LONGITUD_CROMOSOMA 10
#define MAX_COLORES 2
#define PROBABILIDAD_MUTACION 0.1

// Función para generar una población inicial
void generar_poblacion_inicial(int poblacion[MAX_CROMOSOMAS][LONGITUD_CROMOSOMA], int num_colores) {
    for (int i = 0; i < MAX_CROMOSOMAS; i++) {
        for (int j = 0; j < LONGITUD_CROMOSOMA; j++) {
            poblacion[i][j] = rand() % num_colores; // Valores aleatorios según el número de colores
        }
    }
}

// Función para calcular el fitness de un cromosoma (ejemplo simplificado)
int calcular_fitness(int cromosoma[LONGITUD_CROMOSOMA]) {
    int fitness = 0;
    for (int i = 0; i < LONGITUD_CROMOSOMA - 1; i++) {
        if (cromosoma[i] != cromosoma[i + 1]) {
            fitness++;
        }
    }
    return fitness;
}

// Función para realizar el cruzamiento
void cruzar_cromosomas(int padre1[LONGITUD_CROMOSOMA], int padre2[LONGITUD_CROMOSOMA], 
                       int hijo1[LONGITUD_CROMOSOMA], int hijo2[LONGITUD_CROMOSOMA]) {
    int punto_cruza = LONGITUD_CROMOSOMA / 2;
    for (int i = 0; i < punto_cruza; i++) {
        hijo1[i] = padre1[i];
        hijo2[i] = padre2[i];
    }
    for (int i = punto_cruza; i < LONGITUD_CROMOSOMA; i++) {
        hijo1[i] = padre2[i];
        hijo2[i] = padre1[i];
    }
}

// Función para mutar un cromosoma
void mutar_cromosoma(int cromosoma[LONGITUD_CROMOSOMA], int num_colores) {
    for (int i = 0; i < LONGITUD_CROMOSOMA; i++) {
        float prob = (float)rand() / RAND_MAX;
        if (prob <= PROBABILIDAD_MUTACION) {
            cromosoma[i] = rand() % num_colores; // Mutar a un valor aleatorio
        }
    }
}

// Función principal para ejecutar el algoritmo genético
void algoritmo_genetico(int num_colores) {
    int poblacion[MAX_CROMOSOMAS][LONGITUD_CROMOSOMA];
    int nueva_poblacion[MAX_CROMOSOMAS][LONGITUD_CROMOSOMA];
    int fitness[MAX_CROMOSOMAS];
    int optimo = LONGITUD_CROMOSOMA; // Objetivo inicial

    // Generar la población inicial
    generar_poblacion_inicial(poblacion, num_colores);

    while (optimo > 0) {
        // Evaluar la población
        for (int i = 0; i < MAX_CROMOSOMAS; i++) {
            fitness[i] = calcular_fitness(poblacion[i]);
            if (fitness[i] < optimo) {
                optimo = fitness[i];
            }
        }

        // Operadores genéticos: Cruzamiento
        for (int i = 0; i < MAX_CROMOSOMAS; i += 2) {
            cruzar_cromosomas(poblacion[i], poblacion[i + 1], 
                              nueva_poblacion[i], nueva_poblacion[i + 1]);
        }

        // Operadores genéticos: Mutación
        for (int i = 0; i < MAX_CROMOSOMAS; i++) {
            mutar_cromosoma(nueva_poblacion[i], num_colores);
        }

        // Reemplazar la población
        for (int i = 0; i < MAX_CROMOSOMAS; i++) {
            for (int j = 0; j < LONGITUD_CROMOSOMA; j++) {
                poblacion[i][j] = nueva_poblacion[i][j];
            }
        }

        // Salida de estado actual
        printf("Optimo actual: %d\n", optimo);
    }

    printf("Solución óptima encontrada con fitness = %d\n", optimo);
}

int main() {
    srand(time(NULL));
    int num_colores = MAX_COLORES;

    printf("Ejecutando el algoritmo genético secuencial...\n");
    algoritmo_genetico(num_colores);

    return 0;
}

