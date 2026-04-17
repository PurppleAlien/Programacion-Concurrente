// Practica No.4 Programacion Concurrente // 
// Alumno: Soria Rodriguez Juan Antonio G.  //
//Matricula: 2203041232 // 
// Programa que genera un árbol binario de procesos con una profundidad 
//determinada por el usuario utilizando uso de recursividad para crear el árbol binario de procesos. //

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>

// Imprimir la información del proceso
void print_process_info(const char* name) {
    struct passwd *pw;
    uid_t uid = getuid();  // Obtiene el UID del usuario actual
    pw = getpwuid(uid);    // Obtiene la estructura passwd que contiene información del usuario

    // Obtener el nombre del terminal
    char* tty = ttyname(STDIN_FILENO);
    if (tty == NULL) {
        tty = "unknown";
    }

    // Imprime el UID, PID, PPID, TTY y el nombre del proceso
    printf("%-10s%-8d%-8d%-10s%s\n", pw->pw_name, getpid(), getppid(), tty, name);
}

// Crear el árbol de procesos de manera recursiva
void create_process_tree_recursive(int depth, int current_depth) {
    // Base de la recursión: detenerse cuando se alcanza la profundidad máxima
    if (current_depth > depth) {
        return;
    }

    // Imprimir la información del proceso actual
    char name[50];
    sprintf(name, "./Recursivo_%d", current_depth);
    print_process_info(name);

    // Crear dos procesos hijos
    for (int i = 0; i < 2; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error al crear el proceso");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proceso hijo: continuar generando el árbol de procesos
            create_process_tree_recursive(depth, current_depth + 1);
            sleep(10);  // Mantener el proceso activo por 10 segundos
            exit(0);
        } else {
            // Proceso padre: esperar a que termine el proceso hijo
            wait(NULL);
        }
    }
}

int main() {
    int depth;
    printf("Proporciona el nivel de profundidad de tu Árbol de procesos: ");
    scanf("%d", &depth);

    // Imprimir encabezado
    printf("%-10s%-8s%-8s%-10s%s\n", "UID", "PID", "PPID", "TTY", "COMMAND");

    // Llamar a la función recursiva para iniciar el árbol de procesos
    create_process_tree_recursive(depth, 0);

    return 0;
}