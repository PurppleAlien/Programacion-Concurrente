#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_OBJETOS 60
#define LONGITUD_CROMOSOMA 60
#define MAX_ITERACIONES 1000

// Estructura para almacenar los datos del archivo de prueba
typedef struct
{
    float probabilidad_cruza;
    float probabilidad_mutacion;
    int num_objetos;
    float capacidad_maxima;
    float pesos[MAX_OBJETOS];
    int longitudes[MAX_OBJETOS];
} DatosAlgoritmo;

// Función para leer el archivo de datos
int leer_archivo(const char *nombre_archivo, DatosAlgoritmo *datos)
{
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL)
    {
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

    for (int i = 0; i < datos->num_objetos; i++)
    {
        fscanf(archivo, "%f %d", &datos->pesos[i], &datos->longitudes[i]);
    }

    fclose(archivo);
    return 1;
}

// Función para mostrar la portada
void mostrar_portada()
{
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
void mostrar_menu()
{
    printf("Practica 3 - Algoritmo Genetico Para el desarrollo de Armaduras Planas\n");
    printf("Seleccione una opción:\n");
    printf("1. Abrir archivo existente e inicializar el Algoritmo Genetico\n");
    printf("2. Salir del programa\n");
}

// Función para solicitar datos al usuario para el algoritmo genético
void solicitar_datos_algoritmo(int *num_cromosomas, int *num_iteraciones)
{
    printf("Escribe el numero de cromosomas para la poblacion: ");
    scanf("%d", num_cromosomas);
    printf("Escribe el numero de iteraciones (Generaciones): ");
    scanf("%d", num_iteraciones);
    printf("\n");
    printf("*********************************************************************");
}

// Función para inicializar la población con cromosomas aleatorios
void inicializar_poblacion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas)
{
    for (int i = 0; i < num_cromosomas; i++)
    {
        for (int j = 0; j < LONGITUD_CROMOSOMA; j++)
        {
            poblacion[i][j] = rand() % 2; // Genera un bit aleatorio (0 o 1)
        }
    }
}

// Función para imprimir cromosomas
void evaluar_poblacion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, DatosAlgoritmo *datos)
{
    for (int i = 0; i < num_cromosomas; i++)
    {
        printf("Cromosoma [%d]=[", i);
        for (int j = 0; j < LONGITUD_CROMOSOMA; j++)
        {
            printf("%d", poblacion[i][j]);
        }
        printf("]\n");
    }
}

// Función para realizar la mutación
void realizar_mutacion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, float probabilidad_mutacion)
{
    for (int i = 0; i < num_cromosomas; i++)
    {
        for (int j = 0; j < LONGITUD_CROMOSOMA; j++)
        {
            if ((rand() / (float)RAND_MAX) < probabilidad_mutacion)
            {
                poblacion[i][j] = 1 - poblacion[i][j]; // Cambiar el bit
            }
        }
    }
}

// Función para hacer la selección (simplificada, adaptarlo a tus necesidades)
void seleccion(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas)
{
    // Aquí deberías implementar la selección de cromosomas para el cruce
}

// Función para hacer el cruce (simplificado, adaptarlo a tus necesidades)
void cruce(int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA], int num_cromosomas, float probabilidad_cruza)
{
    // Implementa la lógica de cruce de los cromosomas
}

int main()
{
    srand(time(NULL)); // Inicializar la semilla para la aleatoriedad

    mostrar_portada(); // Mostrar la portada

    int opcion = 0;
    DatosAlgoritmo datos;
    int num_cromosomas = 0, num_iteraciones = 0;
    int poblacion[MAX_OBJETOS][LONGITUD_CROMOSOMA];

    while (opcion != 2)
    {
        mostrar_menu(); // Mostrar el menú
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
        {
            // Solicitar nombre del archivo
            char nombre_archivo[100];
            printf("Proporciona el nombre del archivo con extension: ");
            scanf("%s", nombre_archivo);

            if (leer_archivo(nombre_archivo, &datos))
            {
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
                for (int i = 0; i < num_iteraciones; i++)
                {
                    printf("\n");
                    printf("------------------------------------------------------------------");
                    printf("Evaluación de la población - Iteración %d\n", i + 1);
                    evaluar_poblacion(poblacion, num_cromosomas, &datos);
                    realizar_mutacion(poblacion, num_cromosomas, datos.probabilidad_mutacion);
                    cruce(poblacion, num_cromosomas, datos.probabilidad_cruza);
                    printf("\n");
                    printf("------------------------------------------------------------------");
                    
                }
            }
        }
        break;

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
