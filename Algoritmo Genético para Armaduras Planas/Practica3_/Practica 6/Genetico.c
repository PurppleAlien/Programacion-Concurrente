#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODES 100 // Máximo número de nodos permitidos

// Funciones
void visualizarGrafo(const char *nombreArchivo);
void generarSolucionAleatoria(int poblacion[][MAX_NODES], int numRegiones, int numColores, int tamPoblacion);
int calcularFitness(int poblacion[], int matrizVecindades[MAX_NODES][MAX_NODES], int numRegiones);
void encontrarMejorSolucion(int poblacion[][MAX_NODES], int tamPoblacion, int numRegiones, int matrizVecindades[MAX_NODES][MAX_NODES]);

int main() {
    char nombreArchivo[100];
    int numColores, tamPoblacion, numRegiones;

    // Solicitar el nombre del archivo
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);
    visualizarGrafo(nombreArchivo);

    // Leer número de colores y población
    printf("Introduzca el numero de colores: ");
    scanf("%d", &numColores);
    printf("Introduzca el tamaño de su POBLACION: ");
    scanf("%d", &tamPoblacion);

    // Definir el número de regiones basado en el archivo
    numRegiones = 16;  // Según el ejemplo de un grafo 4x4

    // Inicializar la matriz de adyacencia (como ejemplo)
    int matrizVecindades[MAX_NODES][MAX_NODES] = {0};
    // Aquí deberías leer las conexiones del archivo y llenar la matriz adecuadamente

    // Crear una población aleatoria de cromosomas (asignaciones de colores)
    int poblacion[tamPoblacion][MAX_NODES];

    // Generar soluciones aleatorias
    generarSolucionAleatoria(poblacion, numRegiones, numColores, tamPoblacion);

    // Encontrar la mejor solución en la población
    encontrarMejorSolucion(poblacion, tamPoblacion, numRegiones, matrizVecindades);

    return 0;
}

// Función para visualizar el grafo desde un archivo
void visualizarGrafo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    int numNodos;
    fscanf(archivo, "%d", &numNodos); // Leer el número de nodos
    if (numNodos > MAX_NODES) {
        printf("El número de nodos excede el máximo permitido (%d).\n", MAX_NODES);
        fclose(archivo);
        return;
    }

    // Leer la lista de adyacencia
    int grafo[MAX_NODES][MAX_NODES] = {0}; // Matriz de adyacencia inicializada a 0
    for (int i = 0; i < numNodos; i++) {
        int nodoVecino;
        while (fscanf(archivo, "%d", &nodoVecino) && nodoVecino != -1) {
            grafo[i][nodoVecino] = 1; // Marcar conexión entre nodos
        }
    }
    fclose(archivo);

    // Imprimir el grafo en formato visual
    printf("\nGrafo visualizado (matriz de adyacencia):\n");
    for (int i = 0; i < numNodos; i++) {
        for (int j = 0; j < numNodos; j++) {
            printf("%2d ", grafo[i][j]);
        }
        printf("\n");
    }
}

// Función para generar una población aleatoria
void generarSolucionAleatoria(int poblacion[][MAX_NODES], int numRegiones, int numColores, int tamPoblacion) {
    srand(time(NULL)); // Inicializar generador de números aleatorios

    for (int i = 0; i < tamPoblacion; i++) {
        for (int j = 0; j < numRegiones; j++) {
            poblacion[i][j] = rand() % numColores; // Asignación aleatoria de color
        }
    }
}

// Función para calcular el fitness de un cromosoma
int calcularFitness(int poblacion[], int matrizVecindades[MAX_NODES][MAX_NODES], int numRegiones) {
    int contF = 0;

    for (int j = 0; j < numRegiones; j++) {
        for (int z = 0; z < 5; z++) { // Verificar las conexiones
            if (matrizVecindades[j][z] != -1 && poblacion[j] == poblacion[matrizVecindades[j][z]]) {
                contF++;
            }
        }
    }
    return contF;
}

// Función para encontrar la mejor solución en la población
void encontrarMejorSolucion(int poblacion[][MAX_NODES], int tamPoblacion, int numRegiones, int matrizVecindades[MAX_NODES][MAX_NODES]) {
    int mejorFitness = 5000000;
    int indiceMFit = -1;
    int CO[MAX_NODES];

    for (int i = 0; i < tamPoblacion; i++) {
        int contF = calcularFitness(poblacion[i], matrizVecindades, numRegiones);
        if (contF < mejorFitness) {
            mejorFitness = contF;
            indiceMFit = i;
            for (int j = 0; j < numRegiones; j++) {
                CO[j] = poblacion[i][j];
            }
        }
    }

    // Imprimir la mejor solución
    printf("\nEl mejor óptimo se obtuvo en la iteración %d y tiene el fitness = %d\n", indiceMFit, mejorFitness);
    printf("CO[%d] = \n", indiceMFit);
    for (int i = 0; i < numRegiones; i++) {
        printf("%d ", CO[i]);
    }
    printf("\n");
}
