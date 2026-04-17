#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100 // Máximo número de nodos permitidos

void visualizarGrafo(const char *nombreArchivo);

int main() {
    char nombreArchivo[100];
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);
    visualizarGrafo(nombreArchivo);
    return 0;
}

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
    printf("   "); // Espaciado para encabezados
    for (int i = 0; i < numNodos; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < numNodos; i++) {
        printf("%2d ", i); // Número de nodo
        for (int j = 0; j < numNodos; j++) {
            printf("%2d ", grafo[i][j]);
        }
        printf("\n");
    }

    // Imprimir el grafo como lista de adyacencia
    printf("\nGrafo visualizado (lista de adyacencia):\n");
    for (int i = 0; i < numNodos; i++) {
        printf("Nodo %d: ", i);
        for (int j = 0; j < numNodos; j++) {
            if (grafo[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}
