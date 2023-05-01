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

typedef struct Node {       // Respetar esta tipificación para evitar errores a posteriori

    Tarea T;
    struct Node *next;

} Node;


// Declaración de funciones

Node *crearListaVacia();
void cargarTareas(Node **head);
Node *crearNodoTarea(int cont);
void insertarNodoTareaAlFinal(Node **head, Node *NewNode);
void controlTareas(Node **listaGeneral, Node **listaPendientes, Node **listaRealizadas);
void eliminarNodoTarea(Node **head, int datoBuscado);
void mostrarListaTareas(Node *head);
void mostrarUnicaTarea(Node *node);

void buscarTareaID(Node **listaPendientes, Node **listaRealizadas);
void buscarTareaKeyword(Node **listaPendientes, Node **listaRealizadas);


// Programa principal

int main() {

    int cant_tareas, resp;

    Node *listaTareas, *listaTareasRealizadas, *listaTareasPendientes;

    listaTareas = crearListaVacia();
    listaTareasPendientes = crearListaVacia();
    listaTareasRealizadas = crearListaVacia();

    printf("\n\n > A continuaci%cn, ingrese las tareas: \n", 162);
    cargarTareas(&listaTareas);

    printf("\n\n >> A continuaci%cn, se listan las tareas ingresadas: \n\n", 162);

    mostrarListaTareas(listaTareas);

    printf("\n\n >> Ahora, se listan las tareas para su control: \n\n");

    controlTareas(&listaTareas, &listaTareasPendientes, &listaTareasRealizadas);

    printf("\n\n >> Esta es la lista de tareas realizadas: \n\n");
    
    mostrarListaTareas(listaTareasRealizadas);

    printf("\n\n >> Esta es la lista de tareas pendientes: \n\n");
    
    mostrarListaTareas(listaTareasPendientes);

    getchar();

    printf("\n\n >> B%csqueda de tareas: \n", 163);
    
    printf("\n > %cDesea buscar tareas por ID o por palabra clave? \n [1] - Por ID \n [2] - Por palabra clave \n\n >> Su respuesta: ", 168);
    scanf("%d", &resp);

    while(resp != 1 && resp != 2) {

        printf("\n\t (!) Por favor, ingrese una opci%cn v%clida: ", 162, 160);
        scanf("%d", &resp);

    }

    fflush(stdin);

    if(resp == 1) {
        buscarTareaID(&listaTareasPendientes, &listaTareasRealizadas);
    }
    else {
        buscarTareaKeyword(&listaTareasPendientes, &listaTareasRealizadas);
    }

    getchar();

    return 0;

}


// Desarrollo de funciones

Node *crearListaVacia() {

    return NULL;

}

Node *crearNodoTarea(int cont) {

    char *buff;

    buff = (char *) malloc(sizeof(char) * 100);

    srand(time(NULL));

    Node *NewNode = (Node *) malloc(sizeof(Node));

    NewNode->T.tareaID = cont;
    NewNode->T.duracion = rand() % 91 + 10;

    printf("\n\t > Ingrese la descripci%cn de la tarea %d: ", 162, cont);
    gets(buff);

    NewNode->T.descripcion = (char *) malloc(sizeof(char) * (strlen(buff) + 1));

    strcpy(NewNode->T.descripcion, buff);

    free(buff);

    NewNode->next = NULL;       // El nodo creado debe apuntar a NULL

    return NewNode;     // (!) Importante retornar el nodo creado

}

void cargarTareas(Node **head) {

    int cont = 1, resp = 1;
    Node *aux;

    while(resp) {

        Node *NewNode = crearNodoTarea(cont);       // Se crea el nodo usando una función

        cont++;

        insertarNodoTareaAlFinal(head, NewNode);       // Se inserta el nuevo nodo en la lista enlazada

        printf("\n\n %cDesea a%cadir otra tarea? \n\n [1] - Si \n [0] - No \n\n >> Su respuesta: ", 168, 164);
        scanf("%d", &resp);

        while(resp != 1 && resp != 0) {

            printf("\n\t (!) Por favor, ingrese una opci%cn v%clida: ", 162, 160);
            scanf("%d", &resp);

        }

        fflush(stdin);

    }

}

void mostrarListaTareas(Node *head) {

    if(head == NULL) {

        printf("\n\n\t (!) No hay elementos en la lista\n\n");

    }

    while(head != NULL) {

        mostrarUnicaTarea(head);

        head = head->next;

    }

}

void mostrarUnicaTarea(Node *node) {

    printf("\n\t\t ------ TAREA ID: %d ------ ", node->T.tareaID);
    printf("\n\t\t - Duraci%cn: %d minutos", 162, node->T.duracion);
    printf("\n\t\t - Descripci%cn: %s", 162, node->T.descripcion);
    printf("\n\n");

}

void eliminarNodoTarea(Node **head, int datoBuscado) {

    Node *aux = *head, *auxAnterior = *head;      // Se declaran dos auxiliares, ambos inicializados en a cabecera de a lista a analizar

    while(aux != NULL && aux->T.tareaID != datoBuscado) {       // Condición: mientras aux no sea nulo (es decir, mientras no se haya llegado al final de la lista) y el valor de tareaID en el nodo actual (aux->T.tareaID) no sea igual a datoBuscado.

        auxAnterior = aux;      // Avanza al siguiente nodo
        aux = aux->next;        // Avanza al siguiente nodo

    }

    if(aux != NULL) {

        if(aux == *head) { // Si el nodo a eliminar es el primer nodo, entonces cambiar la cabeza de la lista

            *head = aux->next;

        } else { // Si no es el primer nodo, entonces actualizar el puntero al nodo anterior

            auxAnterior->next = aux->next;

        }

        free(aux); // Liberar memoria del nodo eliminado

    }
    else {

        printf("\n\n\t (!) El ID de tarea ingresado no existe en la lista.\n\n");

    }

    /* if(aux) {       // Si se encontró el nodo, se sigue con lo siguiente:

        auxAnterior = aux;      // Se asigna auxAnterior como el nodo siguiente a aux
        aux = aux->next;        // Se asigna aux como el nodo siguiente a aux->next
        free(aux);      // Se libera la memoria del nodo aux con la función free(), eliminándolo de la lista enlazada

    } */

    //Nota: se pueden simplificar las líneas auxAnterior = aux y aux = aux->next con auxAnterior->next = aux->next siempre y cuando sea seguro asumir que auxAnterior no es NULL y aux no es el último nodo de la lista.

    // Si el ciclo while termina y aux es nulo (es decir, si no se encontró un nodo con tareaID igual a datoBuscado), entonces no se hace nada y la función termina

}

void insertarNodoTareaAlFinal(Node **head, Node *NewNode) {

    if(*head == NULL) {           // Si la lista está vacía, entonces la cabecera será el nuevo nodo creado

        *head = NewNode;        // Es necesario actualizar el puntero *head cuando se crea el primer nodo de la lista (cuando la lista está vacía), ya que la cabecera de la lista debe apuntar al primer nodo.

    }
    else {

        Node *aux = *head;

        while(aux->next != NULL) {      // Con esta condición la cabecera avanza hasta al penúltimo elemento de la lista enlazada
            
            aux = aux->next;      // Avanza al nodo siguiente

        }
        aux->next = NewNode;        // Inserta el nodo al final de la lista

    }

}

void controlTareas(Node **listaGeneral, Node **listaPendientes, Node **listaRealizadas) {

    int resp;
    Node *head = *listaGeneral;

    while(head != NULL) {

        mostrarUnicaTarea(head);
        
        printf("\t\t %cSe realiz%c esta tarea? \n\n [1] - Si \n [0] - No \n\n >> Su respuesta: ", 168, 162);
        scanf("%d", &resp);

        while(resp != 1 && resp != 0) {

            printf("\n\t (!) Por favor, ingrese una opci%cn v%clida: ", 162, 160);
            scanf("%d", &resp);

        }

        fflush(stdin);

        if(resp == 1) {

            Node *NewNode1 = (Node *) malloc(sizeof(Node));

            NewNode1->T.tareaID = head->T.tareaID;
            NewNode1->T.descripcion = head->T.descripcion;
            NewNode1->T.duracion = head->T.duracion;
            NewNode1->next = NULL;

            insertarNodoTareaAlFinal(listaRealizadas, NewNode1);

        }
        else {

            Node *NewNode2 = (Node *) malloc(sizeof(Node));

            NewNode2->T.tareaID = head->T.tareaID;
            NewNode2->T.descripcion = head->T.descripcion;
            NewNode2->T.duracion = head->T.duracion;
            NewNode2->next = NULL;

            insertarNodoTareaAlFinal(listaPendientes, NewNode2);

        }

        eliminarNodoTarea(listaGeneral, head->T.tareaID);       // Se elimina el nodo en cuestión de la lista principal de tareas

        head = head->next;      // El operador -> tiene mayor precedencia que el operador de indirección *, por lo que primero se aplica -> a *listaGeneral antes de aplicar * al resultado.

    }

}

void buscarTareaID(Node **listaPendientes, Node **listaRealizadas) {

    int IDBuscado, i, flag = 0;

    Node *headL1 = *listaPendientes, *headL2 = *listaRealizadas;

    printf("\n > Ingrese el ID de la tarea que desea buscar: ");
    scanf("%d", &IDBuscado);

    while(IDBuscado <= 0) {

        printf("\n\t (!) Los ID's son n%cmeros naturales no nulos. Ingrese nuevamente:  ", 163);
        scanf("%d", &IDBuscado);

    }

    fflush(stdin);

    while(headL1 != NULL) {

        if(headL1 != NULL && headL1->T.tareaID == IDBuscado) {

            flag = 1;

            printf("\n\n >> La tarea ID: %d se encuentra en la lista de tareas pendientes. Estos son los detalles: \n\n", (*listaPendientes)->T.tareaID);
            mostrarUnicaTarea(headL1);

        }

        headL1 = headL1->next;

    }

    

    while(headL2 != NULL) {

        if(headL2 != NULL && headL2->T.tareaID == IDBuscado) {

            flag = 1;

            printf("\n\n >> La tarea ID: %d se encuentra en la lista de tareas realizadas. Estos son los detalles: \n\n", (*listaRealizadas)->T.tareaID);
            mostrarUnicaTarea(headL2);

        }

        headL2 = headL2->next;

    }

    if(flag == 0) {

        printf("\n\n >> La b%csqueda no arroj%c resultados", 163, 162);

    }

}

void buscarTareaKeyword(Node **listaPendientes, Node **listaRealizadas) {

    char *buff, *keyword;

    int flag1 = 0, flag2 = 0, i;

    Node *headL1 = *listaPendientes, *headL2 = *listaRealizadas;

    buff = (char *) malloc(sizeof(char) * 100);

    printf("\n > Ingrese la palabra clave para buscar la tarea: ");
    gets(buff);

    keyword = (char *) malloc(sizeof(char) * (strlen(buff) + 1));

    strcpy(keyword, buff);

    strlwr(keyword);     // Se transforman todos los caracteres a minúsculas

    free(buff);

    while(headL1 != NULL) {

        flag1 = 1;

        char *str1;     // Cadena copia

        str1 = (char *) malloc(sizeof(char) * strlen(headL1->T.descripcion));

        strcpy(str1, headL1->T.descripcion);

        strlwr(str1);       // Se transforman todos los caracteres a minúsculas

        char *punt = strstr(str1, keyword);

        if(punt != NULL) {

            printf("\n\n >> La tarea buscada se encuentra en la lista de tareas pendientes. Estos son los detalles: \n\n");

            mostrarUnicaTarea(headL1);

            break;      // Detiene el ciclo

        }
        else {
            flag1 = 0;
        }

        free(str1);

        headL1 = headL1->next;

    }

    while(headL2 != NULL) {

        flag2 = 1;

        char *str1;     // Cadena copia

        str1 = (char *) malloc(sizeof(char) * strlen(headL2->T.descripcion));

        strcpy(str1, headL2->T.descripcion);

        strlwr(str1);       // Se transforman todos los caracteres a minúsculas

        char *punt = strstr(str1, keyword);

        if(punt != NULL) {

            printf("\n\n >> La tarea buscada se encuentra en la lista de tareas realizadas. Estos son los detalles: \n\n");

            mostrarUnicaTarea(headL2);

            break;      // Detiene el ciclo

        }
        else {
            flag2 = 0;
        }

        free(str1);

        headL2 = headL2->next;

    }

    if(flag1 == 0 && flag2 == 0) {

        printf("\n\n >> La b%csqueda no arroj%c resultados", 163, 162);

    }

    free(keyword);


}