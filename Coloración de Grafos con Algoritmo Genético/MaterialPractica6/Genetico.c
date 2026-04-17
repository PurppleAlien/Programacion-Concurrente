#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODES 100
#define MAX_COLORS 10
#define MAX_POPULATION 100
#define MAX_GENERATIONS 1000
#define MUTATION_RATE 0.1

// Variables globales
int grafo[MAX_NODES][MAX_NODES];       // Matriz de adyacencia
int poblacion[MAX_POPULATION][MAX_NODES]; // Población de cromosomas
int mejorFitness = 5000000;
int mejorCromosoma[MAX_NODES];        // Mejor cromosoma encontrado

// Función para leer archivo y llenar matriz de adyacencia
int leerArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return -1;
    }

    int numRegiones;
    fscanf(archivo, "%d", &numRegiones); // Leer el número de nodos (regiones)

    // Inicializar matriz de adyacencia a 0
    for (int i = 0; i < numRegiones; i++) {
        for (int j = 0; j < numRegiones; j++) {
            grafo[i][j] = 0;
        }
    }

    // Leer conexiones
    for (int i = 0; i < numRegiones; i++) {
        int nodoVecino;
        while (fscanf(archivo, "%d", &nodoVecino) && nodoVecino != -1) {
            grafo[i][nodoVecino] = 1; // Conexión entre nodos
        }
    }

    fclose(archivo);
    return numRegiones;
}

// Mostrar la matriz de adyacencia
void mostrarMatrizAdyacencia(int numRegiones) {
    printf("\nMatriz de adyacencia:\n");
    for (int i = 0; i < numRegiones; i++) {
        for (int j = 0; j < numRegiones; j++) {
            printf("%2d ", grafo[i][j]);
        }
        printf("\n");
    }
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
        for (int j = 0; j < numRegiones; j++) {
            if (grafo[i][j] == 1 && cromosoma[i] == cromosoma[j]) {
                fitness++;
            }
        }
    }
    return fitness;
}

// Selección por torneo
int seleccionarCromosoma(int tamPoblacion) {
    int a = rand() % tamPoblacion;
    int b = rand() % tamPoblacion;
    return calcularFitness(poblacion[a], MAX_NODES) < calcularFitness(poblacion[b], MAX_NODES) ? a : b;
}

// Cruce de un punto
void cruzarCromosomas(int padre1[], int padre2[], int hijo[], int numRegiones) {
    int puntoCruce = rand() % numRegiones;
    for (int i = 0; i < numRegiones; i++) {
        hijo[i] = (i < puntoCruce) ? padre1[i] : padre2[i];
    }
}

// Mutación
void mutarCromosoma(int cromosoma[], int numRegiones, int numColores) {
    for (int i = 0; i < numRegiones; i++) {
        if ((float)rand() / RAND_MAX < MUTATION_RATE) {
            cromosoma[i] = rand() % numColores;
        }
    }
}

// Evaluar población y actualizar mejor solución
void evaluarPoblacion(int tamPoblacion, int numRegiones) {
    for (int i = 0; i < tamPoblacion; i++) {
        int fitness = calcularFitness(poblacion[i], numRegiones);
        if (fitness < mejorFitness) {
            mejorFitness = fitness;
            for (int j = 0; j < numRegiones; j++) {
                mejorCromosoma[j] = poblacion[i][j];
            }
        }
    }
}

// Imprimir cromosoma
void imprimirCromosoma(int cromosoma[], int numRegiones) {
    for (int i = 0; i < numRegiones; i++) {
        printf("%d ", cromosoma[i]);
        if ((i + 1) % 10 == 0) {
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

    int numRegiones = leerArchivo(argv[1]);
    if (numRegiones == -1) {
        return 1;
    }

    printf("Número de regiones: %d\n", numRegiones);
    mostrarMatrizAdyacencia(numRegiones);

    // Leer número de colores y tamaño de población
    int numColores;
    printf("Introduzca el número de colores: ");
    scanf("%d", &numColores);

    int tamPoblacion;
    printf("Introduzca el tamaño de su población: ");
    scanf("%d", &tamPoblacion);

    // Generar población inicial
    generarPoblacion(numRegiones, tamPoblacion, numColores);

    // Evolución
    printf("\nIniciando evolución...\n");
    for (int generacion = 0; generacion < MAX_GENERATIONS; generacion++) {
        int nuevaPoblacion[MAX_POPULATION][MAX_NODES];

        for (int i = 0; i < tamPoblacion; i++) {
            int padre1 = seleccionarCromosoma(tamPoblacion);
            int padre2 = seleccionarCromosoma(tamPoblacion);

            cruzarCromosomas(poblacion[padre1], poblacion[padre2], nuevaPoblacion[i], numRegiones);
            mutarCromosoma(nuevaPoblacion[i], numRegiones, numColores);
        }

        for (int i = 0; i < tamPoblacion; i++) {
            for (int j = 0; j < numRegiones; j++) {
                poblacion[i][j] = nuevaPoblacion[i][j];
            }
        }

        evaluarPoblacion(tamPoblacion, numRegiones);

        printf("Generación %d, Mejor Fitness: %d\n", generacion + 1, mejorFitness);
        if (mejorFitness == 0) {
            printf("Solución óptima encontrada en la generación %d!\n", generacion + 1);
            break;
        }
    }

    // Resultados finales
    printf("\nResultados finales:\n");
    printf("Mejor fitness encontrado: %d\n", mejorFitness);
    printf("Mejor cromosoma:\n");
    imprimirCromosoma(mejorCromosoma, numRegiones);

    return 0;
}
