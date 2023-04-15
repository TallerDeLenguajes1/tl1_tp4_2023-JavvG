// Granero Javier - Abril 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declaración de estructuras

struct {
    
    int tareaID;
    char *descripcion;
    int duracion;

} typedef Tarea;


// Declaración de funciones

void iniciar_arreglo_vacio(Tarea **arreglo, int cantidad);
void cargar_tareas(Tarea **arreglo, int cantidad);
void mostrar_tareas(Tarea **arreglo, int cantidad);
void control_tareas(Tarea **tareas_pendientes, int cantidad, Tarea **tareas_realizadas);


// Programa principal

int main() {

    int cant_tareas;

    Tarea **tareas, **realizadas;

    printf("\n > Ingrese la cantidad de tareas que desea cargar: ");
    scanf("%d", &cant_tareas);

    while(cant_tareas <= 0) {

        printf("\n\t (!) Debe ingresar un n%cmero no negativo: ", 163);
        scanf("%d", &cant_tareas);

    }

    fflush(stdin);

    tareas = (Tarea **) malloc(sizeof(Tarea *) * cant_tareas);      // Se asigna memoria dinámica para el arreglo principal

    realizadas = (Tarea **) malloc(sizeof(Tarea *) * cant_tareas);

    iniciar_arreglo_vacio(tareas, cant_tareas);     // Se inicializa el arreglo de arreglo apuntando a NULL


    printf("\n\n > A continuaci%cn, ingrese las tareas: \n", 162);

    cargar_tareas(tareas, cant_tareas);


    printf("\n\n >> A continuaci%cn, se listan las tareas previamente ingresadas para su control: \n", 162);

    control_tareas(tareas, cant_tareas, realizadas);


    printf("\n\n >> A continuaci%cn, se listan las tareas pendientes: \n", 162);

    mostrar_tareas(tareas, cant_tareas);


    printf("\n\n >> A continuaci%cn, se listan las tareas realizadas: \n", 162);

    mostrar_tareas(realizadas, cant_tareas);


    getchar();

    return 0;

}


// Desarrollo de funciones

void iniciar_arreglo_vacio(Tarea **arreglo, int cantidad) {

    int i;

    for(i=0; i<cantidad; i++) {

        arreglo[i] = NULL;

    }

}

void cargar_tareas(Tarea **arreglo_tareas, int cantidad) {

    int i;
    char *buff;

    srand(time(NULL));

    for(i=0; i<cantidad; i++) {

        arreglo_tareas[i] = (Tarea *) malloc(sizeof(Tarea));       // Se asigna memoria dinámmica para cada uno de los arreglos anidados

        arreglo_tareas[i]->tareaID = i+1;

        buff = (char *) malloc(sizeof(char) * 100);

        printf("\n\t > Ingrese la descripci%cn de la tarea %d: ", 162, i+1);
        gets(buff);

        arreglo_tareas[i]->descripcion = (char *) malloc(sizeof(char) * (strlen(buff) + 1));

        strcpy(arreglo_tareas[i]->descripcion, buff);

        arreglo_tareas[i]->duracion = rand() % 91 + 10;

    }

}

void mostrar_tareas(Tarea **arreglo, int cantidad) {

    int i, flag = 1;

    for(i=0; i<cantidad; i++) {

        if(arreglo[i] != NULL) {

            flag = 0;

            printf("\n\t\t ------ TAREA ID: %d ------ ", arreglo[i]->tareaID);
            printf("\n\t\t - Duraci%cn: %d minutos", 162, arreglo[i]->duracion);
            printf("\n\t\t - Descripci%cn: %s", 162, arreglo[i]->descripcion);
            printf("\n\n");

        }

    }

    if(flag) {
        printf("\n\t\t (!) Esta lista de tareas no tiene elementos");
    }
}


void control_tareas(Tarea **tareas_pendientes, int cantidad, Tarea **tareas_realizadas) {

    int i;

    for(i=0; i<cantidad; i++) {

        int resp;

        printf("\n\t\t ------ TAREA ID: %d ------ ", tareas_pendientes[i]->tareaID);
        printf("\n\t\t - Duraci%cn: %d minutos", 162, tareas_pendientes[i]->duracion);
        printf("\n\t\t - Descripci%cn: %s", 162, tareas_pendientes[i]->descripcion);
        printf("\n\n");

        printf("\t\t %cSe realiz%c esta tarea? \n\n [1] - Si \n [0] - No \n\n >> Su respuesta: ", 168, 162);
        scanf("%d", &resp);

        while(resp != 1 && resp != 0) {

            printf("\n\t (!) Por favor, ingrese una opci%cn v%clida: ", 162, 160);
            scanf("%d", &resp);

        }

        fflush(stdin);

        tareas_realizadas[i] = (Tarea *) malloc(sizeof(Tarea));

        if(resp) {

            tareas_realizadas[i] = tareas_pendientes[i];
            tareas_pendientes[i] = NULL;

        }
        else {
            tareas_realizadas[i] = NULL;
        }

    }

}