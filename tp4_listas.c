#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define lengthDescripcion 100


typedef struct {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;



Nodo *inicializarTareas();
Tarea cargarTarea(int TareaID, char *buff);
Nodo *crearNodo(Tarea tarea);
void insertarNodo(Nodo **tareas, Tarea tarea);
void buscarTareas(Nodo *tareas, Nodo *tareasRealizadas, char opt[]);
Nodo *BuscaTareaPorId(Nodo *tareas, int TareaID);
Nodo *BuscaTareaPorPalabra(Nodo *tareas, char descripcion[]);
void moverNodo(Nodo **tareas, int TareaID);
int ultimoID(Nodo *tareas);
void mostrarTarea(Tarea tarea);
void mostrarTareas(Nodo *tareas, char descripcion[]);
void menuTarea(int TareaID);
void menuPrincipal();
void cargarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas, char *buff);
void procesarTareas(Nodo **tareas, Nodo **tareasRealizadas);
void cargarTareasRealizada(Nodo **tareasPendientes, Nodo **tareasRealizadas, int TareaID);



int main() { 

    srand(time(NULL));

    Nodo *tareasPendientes = inicializarTareas();
    Nodo *tareasRealizada = inicializarTareas();
 
    procesarTareas(&tareasPendientes, &tareasRealizada);
  
    //liberar memoria para tareas pendientes
    Nodo *siguiente;

    while(tareasPendientes) {
        siguiente =  tareasPendientes->Siguiente;
        free(tareasPendientes->T.Descripcion);
        free(tareasPendientes);
        tareasPendientes = siguiente;                                          
    }

    free(tareasPendientes);

    //liberar memoria para tareas realizadas
    while(tareasRealizada) {
        siguiente =  tareasRealizada->Siguiente;
        free(tareasRealizada->T.Descripcion);
        free(tareasRealizada);
        tareasRealizada = siguiente;                                          
    }

    free(tareasRealizada); 
    
  
    

    return 0;
}

Nodo *inicializarTareas() { return NULL; }

Tarea cargarTarea(int TareaID, char *buff) {

    Tarea tarea;

    tarea.TareaID = TareaID;
    getchar();
    tarea.Descripcion = malloc(sizeof(char)*lengthDescripcion);

    printf("\nTarea %d - Ingrese descripcion: ", tarea.TareaID);
    gets(buff);
    strcpy(tarea.Descripcion, buff);

    tarea.Duracion = rand() % 88 + 11;
    
    return tarea;        
}

Nodo *crearNodo(Tarea tarea) {

    Nodo *nuevoNodo = malloc(sizeof(Nodo));
    nuevoNodo->T = tarea;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

void insertarNodo(Nodo **tareas, Tarea tarea) {

    Nodo *ultimoNodo = *tareas;
    Nodo *nuevoNodo = crearNodo(tarea);
    

    if(ultimoNodo == NULL) {
        *tareas = nuevoNodo;
    } else {

        while(ultimoNodo->Siguiente) {
            ultimoNodo = ultimoNodo->Siguiente;
        }
        ultimoNodo->Siguiente = nuevoNodo;
    }

}

Nodo *BuscaTareaPorId(Nodo *tareas, int TareaID) {

    while(tareas && tareas->T.TareaID != TareaID) {
        tareas = tareas->Siguiente;
    }

    return tareas;
}

void moverNodo(Nodo **tareas, int TareaID) {

    Nodo *anterior = NULL;
    Nodo *actual = *tareas;
    
    while(actual && actual->T.TareaID != TareaID) {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if(actual) {

        if(anterior == NULL) {//primero
            *tareas = actual->Siguiente;
        } else {
            anterior->Siguiente = actual->Siguiente;
        }

        //free(actual); //en este tp no se necesita eliminar el nodo
    }
}

void procesarTareas(Nodo **tareas, Nodo **tareasRealizadas) {

    int optMenu = 1;
    char *buff = malloc(sizeof(char)*lengthDescripcion);

    while(optMenu !=0) {

        menuPrincipal();
        scanf("%d", &optMenu);

        switch(optMenu) {

            case 1:
                cargarTareas(tareas, tareasRealizadas, buff);
            break;

            case 2:
               buscarTareas(*tareas, *tareasRealizadas, "id");
            break;

            case 3:
               buscarTareas(*tareas, *tareasRealizadas, "palabra");
            break;
          
            case 4:
                mostrarTareas(*tareas, "pendientes");
            break;

            case 5:
                mostrarTareas(*tareasRealizadas, "realizadas");
            break;
        }
    }


    free(buff);
    
}

void menuPrincipal() {
    printf("\n");
    printf("\n");
    printf("1- Cargar tareas\n");
    printf("2- Buscar tareas por id\n");
    printf("3- Buscar tareas por palabra\n");
    printf("4- Mostrar tareas pendientes\n");
    printf("5- Mostrar tareas realizadas\n");
    printf("0- Salir del menu\n");
}

void menuTarea(int TareaID) {
    printf("\n");
    printf("\n");
    printf("1- Seguir cargando tareas\n");
    printf("2- Tarea %d actualizar como tarea realizada\n", TareaID);
    printf("0- Volver al menu principal\n");
}

void cargarTareasRealizada(Nodo **tareasPendientes, Nodo **tareasRealizadas, int TareaID) {

    Nodo *nodoEncontrado = BuscaTareaPorId(*tareasPendientes, TareaID);

    if(nodoEncontrado) {
        insertarNodo(tareasRealizadas, nodoEncontrado->T);
        moverNodo(tareasPendientes, TareaID);
        printf("\nTarea %d agregada en tareas realizadas\n", TareaID);
    }
}

void mostrarTarea(Tarea tarea) {
    printf("\n\nTareaID: %d\n", tarea.TareaID);        
    printf("Descripcion: %s \n", tarea.Descripcion);
    printf("Duracion: %d", tarea.Duracion);
}

void mostrarTareas(Nodo *tareas, char descripcion[]) {

    printf("\n\nListado de tareas %s: ", descripcion);

    if(tareas == NULL) {
        printf("\nNo hay tareas %s", descripcion);
        return;
    }

    while(tareas) {
        mostrarTarea(tareas->T);
        tareas = tareas->Siguiente;
    }
}

int ultimoID(Nodo *tareas) {

    if(tareas == NULL) {
        return 0;
    }
    
    while(tareas->Siguiente) {        
        tareas = tareas->Siguiente;
    }
    
    if(tareas) {
        return tareas->T.TareaID;
    }
    
    return 0;
}

Nodo *BuscaTareaPorPalabra(Nodo *tareas, char descripcion[]) {

    while(tareas) {

        if(strstr(tareas->T.Descripcion, descripcion)!=NULL) {
            return tareas;
        }

        tareas = tareas->Siguiente;
    }

    return NULL;
}

void cargarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas, char *buff) {

    Tarea tarea;
    int ingresar;
    int realizada;
    int optMenuTareas = 1;

    ingresar = 1;
    realizada = 0;
    int TareaID =  ultimoID(*tareasPendientes);
    if(TareaID >= 0) { TareaID++; }
    while(ingresar) {

        tarea = cargarTarea(TareaID, buff);
        insertarNodo(tareasPendientes, tarea);
        printf("\nTarea %d agregada en tareas pendientes\n", TareaID);

        menuTarea(tarea.TareaID);
        scanf("%d", &optMenuTareas);

        if(optMenuTareas == 0) {
            ingresar = 0;
        }

        if(optMenuTareas == 1) {
            ingresar = 1;
        }

        if(optMenuTareas == 2) {
            realizada = 1;
        }

        if(realizada) {
            cargarTareasRealizada(tareasPendientes, tareasRealizadas, tarea.TareaID);
            realizada = 0;
        }

        TareaID++;
    }
    
}
void buscarTareas(Nodo *tareas, Nodo *tareasRealizadas, char opt[]) {

    Nodo *encontrado;
    char palabra[lengthDescripcion];
    int idABuscar;

    if(opt == "id") {

        printf("\nIngrese TareaID: ");               
        scanf("%d", &idABuscar);

        //buscamos en tareas pendientes
        encontrado = BuscaTareaPorId(tareas, idABuscar);

        if(encontrado) {

            printf("\nTarea %d encontrada en tareas pendientes", idABuscar);
            mostrarTarea(encontrado->T);       

        } else {

            //buscamos en tareas realizadas
            encontrado = BuscaTareaPorId(tareasRealizadas, idABuscar);

            if(encontrado) {

                printf("\nTarea %d encontrada en tareas realizadas", idABuscar);
                mostrarTarea(encontrado->T);       

            } else {

                printf("\nTarea %d no encontrada\n", idABuscar);

            }
        }

    } else {

        printf("\nIngrese palabra: ");               
        scanf("%s", &palabra);

        //buscamos en tareas pendientes
        encontrado = BuscaTareaPorPalabra(tareas, palabra);

        if(encontrado) {

            printf("\nTarea %d encontrada en tareas pendientes", encontrado->T.TareaID);
            mostrarTarea(encontrado->T);       

        } else {

            //buscamos en tareas realizadas
            encontrado = BuscaTareaPorPalabra(tareasRealizadas, palabra);

            if(encontrado) {

                printf("\nTarea %d encontrada en tareas realizadas", encontrado->T.TareaID);
                mostrarTarea(encontrado->T);       

            } else {

                printf("\nTarea con la palabra %s no encontrada\n", palabra);

            }
        }
    }

}
