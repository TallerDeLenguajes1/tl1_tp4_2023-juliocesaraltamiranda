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
void eliminarNodo(Nodo **tareas, int TareaID);
int ultimoID(Nodo *tareas);
void mostrarTarea(Tarea tarea);
void mostrarTareas(Nodo *tareas, char descripcion[]);
void menuTarea(int TareaID);
void menuPrincipal();
void cargarTareas(Nodo **tareasPendientes, char *buff);
void subMenu(char estado[], int preguntar);
void dobleSalto();
void procesarTareas(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasEnProceso);
void moverTarea(Nodo **tareas1, Nodo **tareas2, int TareaID);
void MostrarDatos(Nodo *tareas);


int main() { 

    srand(time(NULL));

    Nodo *tareasPendientes = inicializarTareas();
    Nodo *tareasRealizada = inicializarTareas();
    Nodo *tareasEnProceso = inicializarTareas();
 
    procesarTareas(&tareasPendientes, &tareasRealizada, &tareasEnProceso);
  
    //liberar memoria para tareas pendientes
    Nodo *siguiente;

    while(tareasPendientes) {
        siguiente =  tareasPendientes->Siguiente;
        free(tareasPendientes->T.Descripcion);
        free(tareasPendientes);
        tareasPendientes = siguiente;                                          
    }

    free(tareasPendientes);

    //liberar memoria para tareas en proceso
    while(tareasEnProceso) {
        siguiente =  tareasEnProceso->Siguiente;
        free(tareasEnProceso->T.Descripcion);
        free(tareasEnProceso);
        tareasEnProceso = siguiente;                                          
    }

    free(tareasEnProceso); 

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

void eliminarNodo(Nodo **tareas, int TareaID) {

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

        free(actual);
        printf("\nTarea %d eliminada\n", TareaID);
    }
}

void procesarTareas(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasEnProceso) {

    int optMenu = 1;
    int idABuscar;
    char *buff = malloc(sizeof(char)*lengthDescripcion);
    int optMenuTareas;
    int optSubMenu;
    Nodo *encontrado;

    while(optMenu !=0) {

        menuPrincipal();
        scanf("%d", &optMenu);

        switch(optMenu) {

            case 1:

            cargarTareas(tareas, buff);

            break;

            case 2:

                mostrarTareas(*tareas, "Pendientes");

                if(*tareas) {

                    subMenu("", 1);
                    scanf("%d", &idABuscar);
                    encontrado = BuscaTareaPorId(*tareas, idABuscar);

                    if(encontrado) {
                        mostrarTarea(encontrado->T);
                        subMenu("Pendientes", 0);
                        scanf("%d", &optMenuTareas);
                    } else {
                        printf("Tarea %d no encontrada\n", idABuscar);
                    }
                        
                
                    if(optMenuTareas == 1) {
                        
                        mostrarTarea(encontrado->T);
                        moverTarea(tareas, tareasRealizadas, idABuscar);
                         
                    }

                    if(optMenuTareas == 2) {
                        moverTarea(tareas, tareasEnProceso, idABuscar);
                    }

                    if(optMenuTareas == 3) {
                        eliminarNodo(tareas, idABuscar);
                    }
                }
                
                
                

            break;

             case 3:

                mostrarTareas(*tareasEnProceso, "En Proceso");
                
                if(*tareasEnProceso) {

                    subMenu("", 1);
                    scanf("%d", &idABuscar);
                    encontrado = BuscaTareaPorId(*tareasEnProceso, idABuscar);

                    if(encontrado) {
                        mostrarTarea(encontrado->T);
                        subMenu("En Proceso", 0);
                        scanf("%d", &optMenuTareas);
                    } else {
                        printf("Tarea %d no encontrada\n", idABuscar);
                    }
                        
                
                    if(optMenuTareas == 1) {
                        
                        mostrarTarea(encontrado->T);
                        moverTarea(tareasEnProceso, tareas, idABuscar);
                         
                    }

                    if(optMenuTareas == 2) {
                        moverTarea(tareasEnProceso, tareasRealizadas, idABuscar);
                    }

                    if(optMenuTareas == 3) {
                        eliminarNodo(tareasEnProceso, idABuscar);
                    }
                }
                
                
                

            break;

             case 4:

                mostrarTareas(*tareasRealizadas, "Realizadas");
                
                if(*tareasRealizadas) {

                    subMenu("", 1);
                    scanf("%d", &idABuscar);
                    encontrado = BuscaTareaPorId(*tareasRealizadas, idABuscar);

                    if(encontrado) {
                        mostrarTarea(encontrado->T);
                        subMenu("Realizadas", 0);
                        scanf("%d", &optMenuTareas);
                    } else {
                        printf("Tarea %d no encontrada\n", idABuscar);
                    }
                        
                
                    if(optMenuTareas == 1) {
                        
                        mostrarTarea(encontrado->T);
                        moverTarea(tareasRealizadas, tareas, idABuscar);
                         
                    }

                    if(optMenuTareas == 2) {
                        moverTarea(tareasRealizadas, tareasEnProceso, idABuscar);
                    }

                    if(optMenuTareas == 3) {
                        eliminarNodo(tareasRealizadas, idABuscar);
                    }
                }
                
                
                

            break;

            case 5:
                mostrarTareas(*tareas, "Pendientes");
                MostrarDatos(*tareas);

                mostrarTareas(*tareasEnProceso, "En Proceso");
                MostrarDatos(*tareasEnProceso);

                mostrarTareas(*tareasRealizadas, "Realizadas");
                MostrarDatos(*tareasRealizadas);

            break;

        }
    }


    free(buff);
    
}

void dobleSalto() {
    printf("\n");
    printf("\n");
}

void menuPrincipal() {
    dobleSalto();
    printf("1- Cargar tareas\n");
    printf("2- Listar tareas Pendientes\n");
    printf("3- Listar tareas En Proceso\n");
    printf("4- Listar tareas Realizadas\n");
    printf("5- Listar todas las tareas\n");
    printf("0- Salir del menu\n");
}

void subMenu(char estado[], int preguntar) {

    dobleSalto();

    if(preguntar) {
        printf("Que tarea desea seleccionar?. Ingrese el id de la tarea\n");
        return;
    }

    if(estado == "Pendientes") {
        printf("1- Mover a tareas Realizadas\n");
        printf("2- Mover a tareas En Proceso\n");
    } else if(estado == "En Proceso") {
        printf("1- Mover a tareas Pendientes\n");
        printf("2- Mover a tareas Realizadas\n");
    } else if(estado == "Realizadas") {
        printf("1- Mover a tareas Pendientes\n");
        printf("2- Mover a tareas En Proceso\n");
    }

    printf("3- Eliminar tarea\n");
    printf("0- Volver al menu principal\n");

}

void menuTarea(int TareaID) {
    printf("\n");
    printf("\n");
    printf("1- Seguir cargando tareas\n");
    printf("0- Volver al menu principal\n");
}


void moverTarea(Nodo **tareas1, Nodo **tareas2, int TareaID) {

    Nodo *nodoEncontrado = BuscaTareaPorId(*tareas1, TareaID);

    if(nodoEncontrado) {
        insertarNodo(tareas2, nodoEncontrado->T);
        eliminarNodo(tareas1, TareaID);
        printf("\nTarea %d actualizada\n", TareaID);
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

void cargarTareas(Nodo **tareasPendientes, char *buff) {

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

void MostrarDatos(Nodo *tareas) {

    int cantTareas = 0;
    int tiempo = 0;

    while(tareas) {
        cantTareas++;
        tiempo+=tareas->T.Duracion;
        tareas = tareas->Siguiente;
    }
    dobleSalto();
    printf("Cantidad de tareas: %d\n", cantTareas);
    printf("Tiempo de tareas: %d\n", tiempo);

}
