#include <stdio.h>

// Función para dibujar un corazón
void dibujarCorazon() {
    printf("   ****     ****   \n");
    printf("  ******   ******  \n");
    printf(" ******** ******** \n");
    printf("  ***************  \n");
    printf("   *************   \n");
    printf("    ***********    \n");
    printf("      *******      \n");
    printf("        ***        \n");
    printf("         *         \n");
}

int main() {
    int n; // Número de veces que se repetirá el mensaje

    // Solicitar al usuario el número de repeticiones
    printf("¿Cuántas veces deseas repetir el mensaje? ");
    scanf("%d", &n);

    // Imprimir el mensaje N veces
    for (int i = 0; i < n; i++) {
        printf("\n");
        dibujarCorazon();
        printf("YOLI, ME ENCANTAS 💖\n");
        dibujarCorazon();
        printf("\n");
    }

    printf("¡Espero que a Yoli le encante tu mensaje! 😊\n");

    return 0;
}

