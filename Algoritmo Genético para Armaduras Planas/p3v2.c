#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_OBJETOS 60
#define LONGITUD_CROMOSOMA 60
#define MAX_ITERACIONES 1000

// Estructura para almacenar los datos del archivo de prueba
typedef struct {
    float probabilidad_cruza;
    float probabilidad_mutacion;
    int num_objetos;
    float capacidad_maxima;
    float pesos[MAX_OBJETOS];
    int longitudes[MAX_OBJETOS];
} DatosAlgoritmo;

// Función para leer el archivo de datos
int leer_archivo(const char *nombre_archivo, DatosAlgoritmo *datos) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error de apertura!!! (NO ABIERTO)\n");
        return 0;
    }

    // Leer los datos del archivo
    fscanf(archivo, "%f", &datos->probabilidad_cruza);
    datos->probabilidad_cruza /= 100;  // Convertir porcentaje a decimal

    fscanf(archivo, "%f", &datos->probabilidad_mutacion);
    datos->probabilidad_mutacion /= 100;  // Convertir porcentaje a decimal

    fscanf(archivo, "%d", &datos->num_objetos);
    fscanf(archivo, "%f", &datos->capacidad_maxima);

    for (int i = 0; i < datos->num_objetos; i++) {
        fscanf(archivo, "%f %d", &datos->pesos[i], &datos->longitudes[i]);
    }

    fclose(archivo);
    return 1;
}

// Función para mostrar la portada
void mostrar_portada() {
    printf("*   **    **    ******    **     **    ********* \n");
    printf("*   **    **    **  **    ** * * **       ***    \n");
    printf("*   **    **    ******    **  *  **       ***    \n");
    printf("*   **    **    **  **    **     **       ***    \n");
    printf("*    ******     **  **    **     **    ********* \n");
    printf("  PROGRAMACION CONCURRENTE \n");
    printf("  PRACTICA III \n");
    printf("  ALGORITMO GENETICO PARA EL DESARROLLO DE ARMADURAS PLANAS \n");
    printf("AUTORES .- Erick Ricardo Martínez Martínez & Juan Antonio Soria Rodriguez\n");
    printf("  FECHA DE CREACION: 15/11/2024\n");
    printf(" Presiona Enter para continuar ....\n");
    getchar(); // Espera por Enter
}

// Función para mostrar el menú
void mostrar_menu() {
    printf("Practica 3 - Algoritmo Genetico Para el desarrollo de Armaduras Planas\n");
    printf("Seleccione una opción:\n");
    printf("1. Abrir archivo existente e inicializar el Algoritmo Genetico\n");
    printf("2. Salir del programa\n");
}

// Función para solicitar datos al usuario para el algoritmo genético
void solicitar_datos_algoritmo(int *num_cromosomas, int *num_iteraciones) {
    printf("Escribe el numero de cromosomas para la poblacion: ");
    scanf("%d", num_cromosomas);
    printf("Escribe el numero de iteraciones (Generaciones): ");
    scanf("%d", num_iteraciones);
}

// Función para inicializar la población con cromosomas aleatorios
void inicializar_poblacion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas) {
    for (int i = 0; i < num_cromosomas; i++) {
        for (int j = 0; j < LONGITUD_CROMOSOMA; j++) {
            poblacion[i][j] = rand() % 2; // Genera un bit aleatorio (0 o 1)
        }
    }
}

// Función para calcular el peso y la función de aptitud de un cromosoma
void calcular_peso_y_aptitud(int cromosoma[LONGITUD_CROMOSOMA], DatosAlgoritmo *datos, float *peso, float *aptitud) {
    *peso = 0;
    for (int i = 0; i < datos->num_objetos; i++) {
        if (cromosoma[i] == 1) {
            *peso += datos->pesos[i];
        }
    }
    *aptitud = 1 / (*peso + 1); // Ejemplo simplificado de función de aptitud
}

// Función para imprimir los pesos y las funciones de aptitud de los cromosomas
void imprimir_pesos_y_aptitud(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, DatosAlgoritmo *datos) {
    printf("EVALUACION DE LA POBLACION DE LA ITERACION\n");
    printf("-------------------------------------------------------------\n");
    printf("Cromosoma\tPeso\t\tFuncion de Aptitud\tProbabilidad\tProbabilidad Acumulada\n");
    printf("-------------------------------------------------------------\n");
    float probabilidad_acumulada = 0;
    for (int i = 0; i < num_cromosomas; i++) {
        float peso, aptitud;
        calcular_peso_y_aptitud(poblacion[i], datos, &peso, &aptitud);
        float probabilidad = aptitud;
        probabilidad_acumulada += probabilidad;
        printf("[%d]\t\t%.6f\t%.6f\t\t%.6f\t\t%.6f\n", i, peso, aptitud, probabilidad, probabilidad_acumulada);
    }
    printf("-------------------------------------------------------------\n");
}

// Función para evaluar la población
void evaluar_poblacion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, DatosAlgoritmo *datos, float aptitudes[MAX_OBJETOS], float probabilidades[MAX_OBJETOS]) {
    float suma_aptitudes = 0;
    for (int i = 0; i < num_cromosomas; i++) {
        float peso, aptitud;
        calcular_peso_y_aptitud(poblacion[i], datos, &peso, &aptitud);
        aptitudes[i] = aptitud;
        suma_aptitudes += aptitud;
    }
    for (int i = 0; i < num_cromosomas; i++) {
        probabilidades[i] = aptitudes[i] / suma_aptitudes;
    }
}

// Función para realizar la mutación
void realizar_mutacion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, float probabilidad_mutacion) {
    for (int i = 0; i < num_cromosomas; i++) {
        for (int j = 0; j < LONGITUD_CROMOSOMA; j++) {
            if ((rand() / (float)RAND_MAX) < probabilidad_mutacion) {
                poblacion[i][j] = 1 - poblacion[i][j]; // Cambiar el bit
            }
        }
    }
}

// Función para hacer la selección (simplificada, adaptarlo a tus necesidades)
void seleccion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, float probabilidades[MAX_OBJETOS]) {
    int nueva_poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA];
    float probabilidad_acumulada[MAX_OBJETOS];
    probabilidad_acumulada[0] = probabilidades[0];
    for (int i = 1; i < num_cromosomas; i++) {
        probabilidad_acumulada[i] = probabilidad_acumulada[i - 1] + probabilidades[i];
    }

    for (int i = 0; i < num_cromosomas; i++) {
        float punto_ruleta = (rand() / (float)RAND_MAX);
        for (int j = 0; j < num_cromosomas; j++) {
            if (punto_ruleta <= probabilidad_acumulada[j]) {
                memcpy(nueva_poblacion[i], poblacion[j], sizeof(int) * LONGITUD_CROMOSOMA);
                break;
            }
        }
    }

    memcpy(poblacion, nueva_poblacion, sizeof(int) * MAX_OBJETOS * LONGITUD_CROMOSOMA);
}

// Función para hacer el cruce (simplificado, adaptarlo a tus necesidades)
void cruce(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, float probabilidad_cruza) {
    for (int i = 0; i < num_cromosomas; i += 2) {
        if ((rand() / (float)RAND_MAX) < probabilidad_cruza) {
            int punto_cruce = rand() % LONGITUD_CROMOSOMA;
            for (int j = punto_cruce; j < LONGITUD_CROMOSOMA; j++) {
                int temp = poblacion[i][j];
                poblacion[i][j] = poblacion[i + 1][j];
                poblacion[i + 1][j] = temp;
            }
        }
    }
}

// Función para buscar el mejor cromosoma en la población
void encontrar_mejor_cromosoma(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, DatosAlgoritmo *datos, int *mejor_cromosoma, float *mejor_aptitud) {
    *mejor_aptitud = 0;
    for (int i = 0; i < num_cromosomas; i++) {
        float peso, aptitud;
        calcular_peso_y_aptitud(poblacion[i], datos, &peso, &aptitud);
        if (aptitud > *mejor_aptitud) {
            *mejor_aptitud = aptitud;
            *mejor_cromosoma = i;
        }
    }
}

int main() {
    srand(time(NULL)); // Inicializar la semilla para la aleatoriedad

    mostrar_portada(); // Mostrar la portada

    int opcion = 0;
    DatosAlgoritmo datos;
    int num_cromosomas = 0, num_iteraciones = 0;
    int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA];
    float aptitudes[MAX_OBJETOS];
    float probabilidades[MAX_OBJETOS];

    while (opcion != 2) {
        mostrar_menu(); // Mostrar el menú
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1: {
            // Solicitar nombre del archivo
            char nombre_archivo[100];
            printf("Proporciona el nombre del archivo con extension: ");
            scanf("%s", nombre_archivo);

            if (leer_archivo(nombre_archivo, &datos)) {
                printf("Los Datos leidos fueron los siguientes:\n");
                printf("Probabilidad de Cruza = %.2f\n", datos.probabilidad_cruza);
                printf("Probabilidad de Mutacion = %.2f\n", datos.probabilidad_mutacion);
                printf("Num de objetos = %d\n", datos.num_objetos);
                printf("Capacidad maxima = %.2f\n", datos.capacidad_maxima);

                // Solicitar datos para el algoritmo genético
                solicitar_datos_algoritmo(&num_cromosomas, &num_iteraciones);

                // Inicializar la población con cromosomas aleatorios
                inicializar_poblacion(poblacion, num_cromosomas);

                // Ejecutar el algoritmo genético
                for (int iteracion = 0; iteracion < num_iteraciones; iteracion++) {
                    printf("Evaluación de la población - Iteración %d\n", iteracion + 1);
                    evaluar_poblacion(poblacion, num_cromosomas, &datos, aptitudes, probabilidades);

                    // Imprimir la evaluación de la población con probabilidades
                    imprimir_pesos_y_aptitud(poblacion, num_cromosomas, &datos);

                    // Selección
                    seleccion(poblacion, num_cromosomas, probabilidades);

                    // Cruce
                    cruce(poblacion, num_cromosomas, datos.probabilidad_cruza);

                    // Mutación
                    realizar_mutacion(poblacion, num_cromosomas, datos.probabilidad_mutacion);

                    // Evaluar de nuevo para mostrar el mejor cromosoma
                    evaluar_poblacion(poblacion, num_cromosomas, &datos, aptitudes, probabilidades);

                    // Buscar el mejor cromosoma en la población
                    int mejor_cromosoma;
                    float mejor_aptitud;
                    encontrar_mejor_cromosoma(poblacion, num_cromosomas, &datos, &mejor_cromosoma, &mejor_aptitud);

                    printf("Mejor Cromosoma de la Iteración %d: [%d] con Aptitud: %.6f\n", iteracion + 1, mejor_cromosoma, mejor_aptitud);
                    float peso;
                    calcular_peso_y_aptitud(poblacion[mejor_cromosoma], &datos, &peso, &mejor_aptitud);
                    printf("Peso del Mejor Cromosoma: %.6f\n", peso);
                }
            }
        } break;

        case 2:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opción inválida. Intenta de nuevo.\n");
            break;
        }
    }

    return 0;
}

