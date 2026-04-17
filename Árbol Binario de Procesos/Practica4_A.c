// Practica No.4 Programacion Concurrente // 
// Alumno: Soria Rodriguez Juan Antonio G.  //
//Matricula: 2203041232 // 
// Programa que genera un árbol binario de procesos con una profundidad 
//determinada por el usuario utilizando uso de ciclos iterativos para crear el árbol binario de procesos. //


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>

// Estructura para los nodos de la cola
typedef struct node {
    pid_t pid;
    int depth;
    char name[50];
    struct node* next;
} Node;

// Cola para manejar los nodos
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Inicializar la cola
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Encolar un nodo
void enqueue(Queue* q, pid_t pid, int depth, const char* name) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->pid = pid;
    temp->depth = depth;
    strcpy(temp->name, name);
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

// Desencolar un nodo
Node* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

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

// Crear el árbol de procesos
void create_process_tree(int depth) {
    Queue q;
    initQueue(&q);

    // Nodo raíz
    enqueue(&q, getpid(), 0, "./Primera_Parte");

    printf("%-10s%-8s%-8s%-10s%s\n", "UID", "PID", "PPID", "TTY", "COMMAND");

    while (q.front != NULL) {
        Node* current = dequeue(&q);

        if (current->depth >= depth) {
            free(current);
            continue;
        }

        pid_t left_child = fork();
        if (left_child == 0) {
            // Proceso hijo izquierdo
            char new_name[50];
            sprintf(new_name, "%s_L", current->name);
            print_process_info(new_name);
            enqueue(&q, getpid(), current->depth + 1, new_name);
            continue; // Continúa con el siguiente ciclo en el hijo
        } else if (left_child > 0) {
            pid_t right_child = fork();
            if (right_child == 0) {
                // Proceso hijo derecho
                char new_name[50];
                sprintf(new_name, "%s_R", current->name);
                print_process_info(new_name);
                enqueue(&q, getpid(), current->depth + 1, new_name);
                continue; // Continúa con el siguiente ciclo en el hijo
            } else {
                // Proceso padre
                wait(NULL); // Esperar a que termine el proceso hijo izquierdo
                wait(NULL); // Esperar a que termine el proceso hijo derecho
            }
        } else {
            perror("Error al crear el proceso");
            exit(EXIT_FAILURE);
        }

        free(current);
    }

    sleep(10);  // Mantener el proceso activo por 10 segundos
}

int main() {
    int depth;
    printf("Proporciona el nivel de profundidad de tu Arbol de procesos: ");
    scanf("%d", &depth);

    create_process_tree(depth);

    return 0;
}
