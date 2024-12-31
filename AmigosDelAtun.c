#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 10

typedef struct lista {

    char * nombreLegislador;            // valor del nodo, en este caso se necesita el nombre de un legislador
    struct lista * siguiente;           // puntero al siguiente nodo de la lista

}lista;

void insertar(char * nombre, lista **i);

void suprimir(char * nombre, lista **i);

int miembro(char * nombre, lista *i);

void mostrar(lista * i);

void procesarMandato(char mandato, char * nombreLegislador, lista **cBuenos, lista **cMalos);

void liberarLista(lista * i);

int main() {

    lista * chicos_buenos;      // puntero simple que apunta al inicio de la lista
    lista * chicos_malos;

    chicos_buenos = NULL;       // inicio de la lista Chicos Buenos
    chicos_malos = NULL;        // inicio de la lista Chicos Malos


    printf("La Sociedad para la Prevencion de Injusticias con el Atun (SPIA) le da la bienvenida: \n");

    char mandato;
    char nombreLegislador[MAX_NOMBRE + 1];      // reservo 11 lugares teniendo en cuenta el caracter nulo

    printf("\nIngrese el mandato (F para favorable, D para desfavorable, E para salir): ");
    scanf(" %c", &mandato);

    while (mandato != 'E' && mandato != 'e') {

        printf("\nIngrese el nombre del Legislador (maximo 10 caracteres): ");
        scanf("%10s", nombreLegislador);


        procesarMandato(mandato, nombreLegislador, &chicos_buenos, &chicos_malos);

        printf("\nIngrese el mandato (F para favorable, D para desfavorable, E para salir): ");
        scanf(" %c", &mandato);
    }

        printf("\nLista Ordenada Chicos Buenos: \n");
        mostrar(chicos_buenos);

        printf("\nLista Ordenada Chicos Malos: \n");
        mostrar(chicos_malos);

        liberarLista(chicos_buenos);
        liberarLista(chicos_malos);

    return 0;
}

void insertar(char * nombre , lista **i) {

    if (*i == NULL) {       // Chequear si la lista está vacia

        printf("Insertando a %s en la lista.\n", nombre);

        *i = (lista*) malloc(sizeof(lista));    // crear un nuevo nodo

        (*i)->nombreLegislador = (char *) malloc(MAX_NOMBRE + 1);

        strcpy((*i)->nombreLegislador, nombre);

        (*i)->siguiente = NULL;


    } else if ((strcmp(nombre, (*i)->nombreLegislador) < 0)) {  // Cuando el nombre va al inicio

        printf("Insertando a %s en la lista.\n", nombre);

        lista * nuevo = (lista*) malloc(sizeof(lista));     // Creo un nuevo nodo y reservo memoria

        nuevo->nombreLegislador = (char*) malloc(MAX_NOMBRE + 1);   // reservar memoria para el nombre

        strcpy(nuevo->nombreLegislador, nombre);

        nuevo->siguiente = *i;      //  el nuevo nodo apunta al nodo actual

        *i = nuevo;                 // ahora la lista empieza con el nuevo nodo

    } else if ((*i)->siguiente == NULL || strcmp(nombre, (*i)->siguiente->nombreLegislador) < 0)  {  // Insertar en el medio o al final

        printf("Insertando a %s en la lista.\n", nombre);

        lista * nuevo = (lista*) malloc(sizeof(lista));

        nuevo->nombreLegislador = (char*) malloc(MAX_NOMBRE + 1);

        strcpy(nuevo->nombreLegislador, nombre);

        nuevo->siguiente = (*i)->siguiente;         // el nuevo nodo apunta al siguiente nodo de la lista

        (*i)->siguiente = nuevo;    // el nodo de la lista apunta al siguiente nodo

    }  else if (strcmp(nombre, (*i)->nombreLegislador) == 0) {

        printf("Ya existe el nombre %s en la lista.\n", nombre);

    } else {        // si char * nombre no cumple con las condiciones previas:

        insertar(nombre, &(*i)->siguiente);      // llamado a función recursiva para encontrar el lugar adecuado para la inserción
    }
}


void suprimir(char * nombre, lista **i) {

    if (*i == NULL) {

        printf("\nNo existe legislador a eliminar.\n");

    } else {

        if (strcmp(nombre, (*i)->nombreLegislador) == 0) {      // elimino al primero
            printf("\nElimino a %s\n", nombre);
            lista * aux = *i;       // guardar nodo a eliminar
            *i = (*i)->siguiente;   // mover el puntero al siguiente nodo


        } else if ((*i)->siguiente != NULL && strcmp(nombre, (*i)->siguiente->nombreLegislador) == 0) {        // elimino al siguiente

            printf("Elimino a %s\n", nombre);
            lista * aux = (*i)->siguiente;
            (*i)->siguiente = (*i)->siguiente->siguiente;

        } else {
            suprimir(nombre, &(*i)->siguiente);
        }
    }
}


int miembro(char * nombre, lista *i) {

    while (i != NULL) {     // ciclo while para recorrer la lista, mientres no llegue al final de la lista...

        if (strcmp(nombre, i->nombreLegislador) == 0) {

            return 1;       // el legislador está en la lista
        }

        i = i->siguiente;   // iteración, avanzo al siguiente nodo
    }

    return 0;       // el legislador no se encontró en la lista
}

void mostrar(lista * i) {

    if (i != NULL) {

        printf("%s\n", i->nombreLegislador);
        mostrar(i->siguiente);
    }
}

void procesarMandato(char mandato, char * nombreLegislador, lista **cBuenos, lista **cMalos) {

    switch (mandato) {

        case 'F':
        case 'f':

            if (!miembro(nombreLegislador, *(cBuenos))) {       // pregunto si el legislador NO está en la lista

                insertar(nombreLegislador, cBuenos);                // entonces lo inserto en la lista
            }

            if (miembro(nombreLegislador, *(cMalos))) {         // si está en la lista lo elimino

                suprimir(nombreLegislador, cMalos);
            }
            break;

        case 'D':
        case 'd':

            if (!miembro(nombreLegislador, *(cMalos))) {    // pregunto si el legislador NO está en la lista

                insertar(nombreLegislador, cMalos);             // lo inserto
            }

            if (miembro(nombreLegislador, *(cBuenos))) {        // si está en la lista lo elimino

                suprimir(nombreLegislador, cBuenos);
            }
            break;

        default:
            printf("Mandato no valido.\n");
            break;
    }
}

void liberarLista(lista * i) {

    lista * aux;        // puntero auxiliar para guardar la referencia del nodo actual de la lista
                        // quiero liberar su memoria antes de moverme al siguiente nodo
    while (i != NULL) {

        aux = i;
        i = i->siguiente;
        free(aux->nombreLegislador);        // libero la memoria reservada para el nombre
        free(aux);                          // libero la memoria reservada para el nodo
    }
}
