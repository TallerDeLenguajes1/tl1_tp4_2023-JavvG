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
void mostrar_unica_tarea(Tarea *tarea);
void mostrar_unica_tarea(Tarea *tarea);
void control_tareas(Tarea **tareas_pendientes, int cantidad, Tarea **tareas_realizadas);
void buscar_tarea_por_ID(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad);
void buscar_tarea_por_palabra(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad);


// Programa principal

int main() {

    int cant_tareas, resp;

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

    printf("\n\n >> A continuaci%cn, se listan las tareas realizadas: \n", 162);
    mostrar_tareas(realizadas, cant_tareas);

    printf("\n\n >> A continuaci%cn, se listan las tareas pendientes: \n", 162);
    mostrar_tareas(tareas, cant_tareas);

    printf("\n\n >> B%csqueda de tareas: \n", 163);
    

    printf("\n > %cDesea buscar tareas por ID o por palabra clave? \n [1] - Por ID \n [2] - Por palabra clave \n\n >> Su respuesta: ", 168);
    scanf("%d", &resp);

    while(resp != 1 && resp != 2) {

        printf("\n\t (!) Por favor, ingrese una opci%cn v%clida: ", 162, 160);
        scanf("%d", &resp);

    }

    fflush(stdin);

    if(resp == 1) {
        buscar_tarea_por_ID(tareas, realizadas, cant_tareas);
    }
    else {
        buscar_tarea_por_palabra(tareas, realizadas, cant_tareas);
    }

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

            mostrar_unica_tarea(arreglo[i]);

        }

    }

    if(flag) {
        printf("\n\t\t (!) Esta lista de tareas no tiene elementos");
    }
}

void mostrar_unica_tarea(Tarea *tarea) {

    printf("\n\t\t ------ TAREA ID: %d ------ ", tarea->tareaID);
    printf("\n\t\t - Duraci%cn: %d minutos", 162, tarea->duracion);
    printf("\n\t\t - Descripci%cn: %s", 162, tarea->descripcion);
    printf("\n\n");

}


void control_tareas(Tarea **tareas_pendientes, int cantidad, Tarea **tareas_realizadas) {

    int i;

    for(i=0; i<cantidad; i++) {

        int resp;

        mostrar_unica_tarea(tareas_pendientes[i]);

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

void buscar_tarea_por_ID(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad) {

    int search_ID, i, flag = 0;

    printf("\n > Ingrese el ID de la tarea que desea buscar: ");
    scanf("%d", &search_ID);

    while(search_ID <= 0) {

        printf("\n\t (!) Los ID's son n%cmeros naturales no nulos. Ingrese nuevamente:  ", 163);
        scanf("%d", &search_ID);

    }

    fflush(stdin);

    for(i=0; i<cantidad; i++) {

        if(tareas_pendientes[i] != NULL && tareas_pendientes[i]->tareaID == search_ID) {

            flag = 1;

            printf("\n\n >> La tarea ID: %d se encuentra en la lista de tareas pendientes. Estos son los detalles: \n\n", tareas_pendientes[i]->tareaID);
            mostrar_unica_tarea(tareas_pendientes[i]);

        }

    }

    for(i=0; i<cantidad; i++) {

        if(tareas_realizadas[i] != NULL && tareas_realizadas[i]->tareaID == search_ID) {

            flag = 1;

            printf("\n\n >> La tarea ID: %d se encuentra en la lista de tareas realizadas. Estos son los detalles: \n\n", tareas_realizadas[i]->tareaID);
            mostrar_unica_tarea(tareas_realizadas[i]);

        }

    }

    if(flag == 0) {

        printf("\n\n >> La b%csqueda no arroj%c resultados", 163, 162);

    }

}

void buscar_tarea_por_palabra(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad) {

    char *buff, *search_keyword;

    int flag = 0, i;

    buff = (char *) malloc(sizeof(char) * 100);

    printf("\n > Ingrese la palabra clave para buscar la tarea: ");
    gets(buff);

    search_keyword = (char *) malloc(sizeof(char) * (strlen(buff) + 1));

    strcpy(search_keyword, buff);

    strlwr(search_keyword);     // Se transforman todos los caracteres a minúsculas

    free(buff);

    for(i=0; i<cantidad; i++) {

        if(tareas_pendientes[i] != NULL) {

            flag = 1;

            char *str1;     // Cadena copia

            str1 = (char *) malloc(sizeof(char) * strlen(tareas_pendientes[i]->descripcion));

            strcpy(str1, tareas_pendientes[i]->descripcion);

            strlwr(str1);       // Se transforman todos los caracteres a minúsculas

            char *punt = strstr(str1, search_keyword);

            if(punt != NULL) {

                printf("\n\n >> La tarea buscada se encuentra en la lista de tareas pendientes. Estos son los detalles: \n\n");
                mostrar_unica_tarea(tareas_pendientes[i]);

                break;      // Detiene el ciclo

            }
            else {
                flag = 0;
            }

            free(str1);

        }

    }

    for(i=0; i<cantidad; i++) {

        if(tareas_realizadas[i] != NULL) {

            flag = 1;

            char *str1;     // Cadena copia

            str1 = (char *) malloc(sizeof(char) * strlen(tareas_realizadas[i]->descripcion));

            strcpy(str1, tareas_realizadas[i]->descripcion);

            strlwr(str1);       // Se transforman todos los caracteres a minúsculas

            char *punt = strstr(str1, search_keyword);

            if(punt != NULL) {

                printf("\n\n >> La tarea buscada se encuentra en la lista de tareas realizadas. Estos son los detalles: \n\n");
                mostrar_unica_tarea(tareas_realizadas[i]);

                break;      // Detiene el ciclo 

            }
            else {
                flag = 0;
            }

            free(str1);

        }

    }

    if(flag == 0) {

        printf("\n\n >> La b%csqueda no arroj%c resultados", 163, 162);

    }

    free(search_keyword);


}