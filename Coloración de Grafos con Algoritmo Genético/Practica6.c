#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_REGIONES 16 // Número de regiones (4x4 matriz)
#define MAX_ITERACIONES 1000
#define TAMANO_POBLACION 8
#define NUM_COLORES 4 // Número de colores disponibles

// Estructura para almacenar un cromosoma
typedef struct {
    int genes[NUM_REGIONES];
    int fitness;
} Cromosoma;

// Prototipos de funciones
void inicializar_poblacion(Cromosoma poblacion[], int num_colores);
int calcular_fitness(Cromosoma *cromosoma, int matriz_adyacencia[NUM_REGIONES][NUM_REGIONES]);
void cruzar(Cromosoma poblacion[], float probabilidad_cruza);
void mutar(Cromosoma *cromosoma, float probabilidad_mutacion, int num_colores);
Cromosoma seleccionar_mejor(Cromosoma poblacion[]);
void imprimir_cromosoma(Cromosoma cromosoma);

// Matriz de adyacencia para el grafo (4x4)
int matriz_adyacencia[NUM_REGIONES][NUM_REGIONES] = {
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Nodo 0
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Nodo 1
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Nodo 2
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // Nodo 3
    {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Nodo 4
    // Continúa definiendo la matriz para todas las regiones...
};

int main() {
    srand(time(NULL));

    Cromosoma poblacion[TAMANO_POBLACION];
    float probabilidad_cruza = 0.7; // 70%
    float probabilidad_mutacion = 0.1; // 10%
    int iteraciones = 0;

    // Inicializar población
    inicializar_poblacion(poblacion, NUM_COLORES);

    // Evaluar fitness inicial
    for (int i = 0; i < TAMANO_POBLACION; i++) {
        poblacion[i].fitness = calcular_fitness(&poblacion[i], matriz_adyacencia);
    }

    while (iteraciones < MAX_ITERACIONES) {
        // Seleccionar, cruzar y mutar
        cruzar(poblacion, probabilidad_cruza);
        for (int i = 0; i < TAMANO_POBLACION; i++) {
            mutar(&poblacion[i], probabilidad_mutacion, NUM_COLORES);
            poblacion[i].fitness = calcular_fitness(&poblacion[i], matriz_adyacencia);
        }

        // Imprimir mejor cromosoma
        Cromosoma mejor = seleccionar_mejor(poblacion);
        printf("Iteración %d: Mejor fitness = %d\n", iteraciones, mejor.fitness);

        if (mejor.fitness == 0) {
            printf("¡Óptimo encontrado!\n");
            imprimir_cromosoma(mejor);
            break;
        }
        iteraciones++;
    }

    if (iteraciones == MAX_ITERACIONES) {
        printf("No se alcanzó el óptimo en el número máximo de iteraciones.\n");
    }

    return 0;
}

void inicializar_poblacion(Cromosoma poblacion[], int num_colores) {
    for (int i = 0; i < TAMANO_POBLACION; i++) {
        for (int j = 0; j < NUM_REGIONES; j++) {
            poblacion[i].genes[j] = rand() % num_colores;
        }
        poblacion[i].fitness = 0;
    }
}

int calcular_fitness(Cromosoma *cromosoma, int matriz_adyacencia[NUM_REGIONES][NUM_REGIONES]) {
    int fitness = 0;
    for (int i = 0; i < NUM_REGIONES; i++) {
        for (int j = 0; j < NUM_REGIONES; j++) {
            if (matriz_adyacencia[i][j] == 1 && cromosoma->genes[i] == cromosoma->genes[j]) {
                fitness++;
            }
        }
    }
    return fitness;
}

void cruzar(Cromosoma poblacion[], float probabilidad_cruza) {
    for (int i = 0; i < TAMANO_POBLACION - 1; i += 2) {
        if ((float)rand() / RAND_MAX <= probabilidad_cruza) {
            int punto_cruza = rand() % NUM_REGIONES;
            for (int j = punto_cruza; j < NUM_REGIONES; j++) {
                int temp = poblacion[i].genes[j];
                poblacion[i].genes[j] = poblacion[i + 1].genes[j];
                poblacion[i + 1].genes[j] = temp;
            }
        }
    }
}

void mutar(Cromosoma *cromosoma, float probabilidad_mutacion, int num_colores) {
    for (int i = 0; i < NUM_REGIONES; i++) {
        if ((float)rand() / RAND_MAX <= probabilidad_mutacion) {
            cromosoma->genes[i] = rand() % num_colores;
        }
    }
}

Cromosoma seleccionar_mejor(Cromosoma poblacion[]) {
    Cromosoma mejor = poblacion[0];
    for (int i = 1; i < TAMANO_POBLACION; i++) {
        if (poblacion[i].fitness < mejor.fitness) {
            mejor = poblacion[i];
        }
    }
    return mejor;
}

void imprimir_cromosoma(Cromosoma cromosoma) {
    printf("Cromosoma: [");
    for (int i = 0; i < NUM_REGIONES; i++) {
        printf("%d", cromosoma.genes[i]);
        if (i < NUM_REGIONES - 1) printf(", ");
    }
    printf("]\n");
}

