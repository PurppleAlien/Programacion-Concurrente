#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODES 100
#define MAX_COLORS 10
#define MAX_POPULATION 100

// Variables globales
int grafo[MAX_NODES][5]; // Matriz de vecindades (máximo 5 conexiones por nodo)
int poblacion[MAX_POPULATION][MAX_NODES];
int mejorFitness = 5000000;
int co[MAX_NODES]; // Copia del mejor cromosoma
int iteracionMejor = -1; // Iteración donde se encontró el mejor óptimo

// Función para leer el archivo y llenar la matriz de vecindades
int leerArchivo(const char *nombreArchivo, int *renglones, int *columnas) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return -1;
    }

    int numRegiones;
    fscanf(archivo, "%d", &numRegiones);

    *renglones = numRegiones;
    *columnas = 5; // Fijo según definición del grafo

    for (int i = 0; i < numRegiones; i++) {
        for (int j = 0; j < 5; j++) {
            int nodo;
            fscanf(archivo, "%d", &nodo);
            grafo[i][j] = nodo;
        }
    }
    fclose(archivo);
    return numRegiones;
}

// Generar población inicial aleatoria
void generarPoblacion(int numRegiones, int tamPoblacion, int numColores) {
    srand(time(NULL));
    for (int i = 0; i < tamPoblacion; i++) {
        for (int j = 0; j < numRegiones; j++) {
            poblacion[i][j] = rand() % numColores;
        }
    }
}

// Función de fitness
int calcularFitness(int cromosoma[], int numRegiones) {
    int fitness = 0;
    for (int i = 0; i < numRegiones; i++) {
        for (int j = 0; j < 5; j++) {
            int vecino = grafo[i][j];
            if (vecino != -1 && cromosoma[i] == cromosoma[vecino]) {
                fitness++;
            }
        }
    }
    return fitness;
}

// Evaluar población y encontrar el mejor cromosoma
void evaluarPoblacion(int tamPoblacion, int numRegiones) {
    for (int i = 0; i < tamPoblacion; i++) {
        int fitness = calcularFitness(poblacion[i], numRegiones);
        printf("Cromosoma %d, Fitness: %d\n", i + 1, fitness); // Mostrar fitness de cada cromosoma
        if (fitness < mejorFitness) {
            mejorFitness = fitness;
            iteracionMejor = i + 1; // Registrar la iteración
            for (int j = 0; j < numRegiones; j++) {
                co[j] = poblacion[i][j];
            }
        }
    }
}

// Función para imprimir cromosomas
void imprimirCromosoma(int cromosoma[], int numRegiones) {
    for (int i = 0; i < numRegiones; i++) {
        printf("%d ", cromosoma[i]);
        if ((i + 1) % 4 == 0) { // Formatear para mostrar como una matriz 4x4
            printf("\n");
        }
    }
    printf("\n");
}

// Función principal
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo_grafo>\n", argv[0]);
        return 1;
    }

    int renglones, columnas;
    int numRegiones = leerArchivo(argv[1], &renglones, &columnas);
    if (numRegiones == -1) {
        return 1;
    }

    printf("Número de renglones leídos: %d\n", renglones);
    printf("Número de columnas leídas: %d\n", columnas);

    int numColores;
    printf("Introduzca el número de colores: ");
    scanf("%d", &numColores);
    if (numColores > MAX_COLORS) {
        printf("El número máximo de colores permitidos es %d.\n", MAX_COLORS);
        return 1;
    }

    int tamPoblacion;
    printf("Introduzca el tamaño de su población: ");
    scanf("%d", &tamPoblacion);
    if (tamPoblacion > MAX_POPULATION) {
        printf("El tamaño máximo de la población permitido es %d.\n", MAX_POPULATION);
        return 1;
    }

    // Generar población inicial
    generarPoblacion(numRegiones, tamPoblacion, numColores);

    // Evaluar población
    printf("\nEvaluando población...\n");
    evaluarPoblacion(tamPoblacion, numRegiones);

    // Resultados
    printf("\nResultados:\n");
    printf("Mejor fitness encontrado: %d\n", mejorFitness);
    printf("Mejor cromosoma encontrado en la iteración: %d\n", iteracionMejor);
    printf("Mejor cromosoma:\n");
    imprimirCromosoma(co, numRegiones);

    return 0;
}
