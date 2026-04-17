#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_POPULATION 100
#define MAX_COLORS 10
#define MAX_REGIONS 1000

int graph[MAX_REGIONS][MAX_REGIONS];
int population[MAX_POPULATION][MAX_REGIONS];
int numRegions, populationSize, numColors;

// Leer el grafo desde el archivo
void readGraph(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &numRegions);
    for (int i = 0; i < numRegions; i++) {
        for (int j = 0; j < numRegions; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
}

// Inicializar la población
void initializePopulation() {
    for (int i = 0; i < populationSize; i++) {
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
        printf("Iteración %d, Fitness: %d\n", iteration, fitness[0]);

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

        // Comentado para que no termine antes de 500 iteraciones
        // if (bestFitness == 0) {
        //     printf("Óptimo alcanzado en la iteración %d\n", iteration);
        //     break;
        // }
    }

    // Mostrar el mejor individuo después de las 500 iteraciones
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

    readGraph(argv[1]);

    printf("Introduzca el numero de colores: ");
    scanf("%d", &numColors);

    printf("Introduzca el tamaño de su POBLACION: ");
    scanf("%d", &populationSize);

    initializePopulation();

    printf("\nPoblación inicial:\n");
    for (int i = 0; i < populationSize; i++) {
        for (int j = 0; j < numRegions; j++) {
            printf("%d ", population[i][j]);
        }
        printf("\n");
    }

    printf("\nAplicando operaciones genéticas:\n");
    geneticAlgorithm(500);

    return 0;
}
