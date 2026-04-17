#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAX_POPULATION 100
#define MAX_COLORS 10
#define MAX_REGIONS 1000

int **graph;  // Grafo dinámico
int **population;  // Población dinámica
int numRegions, populationSize, numColors;

// Leer el grafo desde el archivo
void readGraph(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &numRegions);
    // Asignar memoria dinámica para el grafo
    graph = (int **)malloc(numRegions * sizeof(int *));
    for (int i = 0; i < numRegions; i++) {
        graph[i] = (int *)malloc(numRegions * sizeof(int));
    }

    for (int i = 0; i < numRegions; i++) {
        for (int j = 0; j < numRegions; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
}

// Inicializar la población
void initializePopulation() {
    population = (int **)malloc(populationSize * sizeof(int *));
    for (int i = 0; i < populationSize; i++) {
        population[i] = (int *)malloc(numRegions * sizeof(int));
        for (int j = 0; j < numRegions; j++) {
            population[i][j] = rand() % numColors;
        }
    }
}

// Calcular fitness de un individuo
int calculateFitness(int individual[]) {
    int fitness = 0;
    for (int i = 0; i < numRegions; i++) {
        for (int j = i + 1; j < numRegions; j++) {
            if (graph[i][j] == 1 && individual[i] == individual[j]) {
                fitness++;
            }
        }
    }
    return fitness;
}

// Operación genética: cruzamiento
void crossover(int parent1[], int parent2[], int child[]) {
    int midpoint = numRegions / 2;
    for (int i = 0; i < numRegions; i++) {
        child[i] = (i < midpoint) ? parent1[i] : parent2[i];
    }
}

// Operación genética: mutación
void mutate(int individual[]) {
    int index = rand() % numRegions;
    individual[index] = rand() % numColors;
}

// Ejecutar iteraciones genéticas
void geneticAlgorithm(int maxIterations) {
    int newPopulation[MAX_POPULATION][MAX_REGIONS];
    int fitness[MAX_POPULATION];

    for (int i = 0; i < populationSize; i++) {
        fitness[i] = calculateFitness(population[i]);
    }

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        printf("Iteración %d, Mejor Fitness: %d\n", iteration, fitness[0]);

        for (int i = 0; i < populationSize; i += 2) {
            int parent1 = rand() % populationSize;
            int parent2 = rand() % populationSize;

            crossover(population[parent1], population[parent2], newPopulation[i]);
            mutate(newPopulation[i]);

            crossover(population[parent2], population[parent1], newPopulation[i + 1]);
            mutate(newPopulation[i + 1]);
        }

        for (int i = 0; i < populationSize; i++) {
            for (int j = 0; j < numRegions; j++) {
                population[i][j] = newPopulation[i][j];
            }
            fitness[i] = calculateFitness(population[i]);
        }

        // Encontrar el mejor fitness
        int bestFitness = fitness[0];
        for (int i = 1; i < populationSize; i++) {
            if (fitness[i] < bestFitness) {
                bestFitness = fitness[i];
            }
        }
    }

    // Mostrar el mejor individuo después de las 400 iteraciones
    int bestIndex = 0;
    for (int i = 1; i < populationSize; i++) {
        if (fitness[i] < fitness[bestIndex]) {
            bestIndex = i;
        }
    }

    printf("El mejor óptimo después de las operaciones genéticas tiene el fitness = %d\n", fitness[bestIndex]);
    printf("CO[N]:\n");
    for (int i = 0; i < numRegions; i++) {
        printf("%d ", population[bestIndex][i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo_grafo>\n", argv[0]);
        return EXIT_FAILURE;
    }

    srand(time(NULL));

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Leer el grafo desde el archivo
    readGraph(argv[1]);

    // Solo el proceso principal lee la entrada
    if (rank == 0) {
        printf("Introduzca el número de colores: ");
        scanf("%d", &numColors);

        printf("Introduzca el tamaño de su POBLACIÓN: ");
        scanf("%d", &populationSize);
    }

    // Compartir los valores de numColors y populationSize entre los procesos
    MPI_Bcast(&numColors, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&populationSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Inicializar la población
    initializePopulation();

    // Mostrar la población inicial (solo en el proceso principal)
    if (rank == 0) {
        printf("\nPoblación inicial:\n");
        for (int i = 0; i < populationSize; i++) {
            for (int j = 0; j < numRegions; j++) {
                printf("%d ", population[i][j]);
            }
            printf("\n");
        }
    }

    // Ejecutar el algoritmo genético
    printf("\nAplicando operaciones genéticas:\n");
    geneticAlgorithm(400);

    // Liberar memoria dinámica
    for (int i = 0; i < numRegions; i++) {
        free(graph[i]);
    }
    free(graph);
    
    for (int i = 0; i < populationSize; i++) {
        free(population[i]);
    }
    free(population);

    // Finalizar MPI
    MPI_Finalize();

    return 0;
}