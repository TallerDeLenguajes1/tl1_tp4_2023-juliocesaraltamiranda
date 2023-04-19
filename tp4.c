#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}Tarea;



void inicializarTareas(Tarea **tareas, int cantTareas);
Tarea *cargarTarea(int itera, char *buff);
void cargarTareasPendientes(Tarea **tareas, int cantTareas);
void cargarTareasRealizadas(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantTareas);
void mostrarTareas(Tarea **tareas, int cantTareas);
void liberarMemoriaTareas(Tarea **tareas, int cantTareas);

int main() {

    srand(time(NULL));

    int cantTareas;
    
    printf("Ingrese cantidad de tareas: ");

    scanf("%d", &cantTareas);
    
    Tarea **tareasPendientes = malloc(sizeof(Tarea *) * cantTareas);
    Tarea **tareasRealizadas = malloc(sizeof(Tarea *) * cantTareas);

    //inicializa tareas
    inicializarTareas(tareasPendientes, cantTareas);
    inicializarTareas(tareasRealizadas, cantTareas);

    //cargar de tareas
    cargarTareasPendientes(tareasPendientes, cantTareas);
    cargarTareasRealizadas(tareasPendientes, tareasRealizadas, cantTareas);

    //mostrar tareas
    printf("Tareas pendientes:");
    mostrarTareas(tareasPendientes, cantTareas);
    printf("\n\nTareas realizadas:");
    mostrarTareas(tareasRealizadas, cantTareas);

    //liberacion de memoria para tareas
    liberarMemoriaTareas(tareasPendientes, cantTareas);
    liberarMemoriaTareas(tareasRealizadas, cantTareas);

    

    return 0;
}

void inicializarTareas(Tarea **tareas, int cantTareas) {

    for(int i = 0; i < cantTareas; i++) { tareas[i] = NULL; }
}

Tarea *cargarTarea(int itera, char *buff) {

    Tarea *tarea = malloc(sizeof(Tarea));
    
    tarea->Descripcion = malloc(sizeof(char)*100);

    tarea->TareaID = itera;
    tarea->Duracion = rand() % 90 + 11;
    getchar();

    printf("Ingrese descripcion para TareaID %d: ",  tarea->TareaID);

    gets(buff);
    strcpy(tarea->Descripcion, buff);

    
    return tarea;
}

void cargarTareasPendientes(Tarea **tareas, int cantTareas) {

    char *buff = malloc(sizeof(char)*100);

    for(int i = 0; i < cantTareas; i++) {

        Tarea *tarea = cargarTarea(i, buff);
        tareas[i] = tarea;
    }

    free(buff);
}

void cargarTareasRealizadas(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantTareas) {

    int opt;

    for(int i = 0; i < cantTareas; i++) {
        
        printf("\n\nTareaID %d - %s\n", 
        tareasPendientes[i]->TareaID, 
        tareasPendientes[i]->Descripcion);
        printf("Desea agregarla como tarea realizada? ingrese una opcion, siendo 1 = SI | 2 = NO ");

        scanf("%d", &opt);

        if(opt == 1) {
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        } else {
            tareasRealizadas[i] = NULL;
        }
        
    }
}

void mostrarTareas(Tarea **tareas, int cantTareas) {
    
    for(int i = 0; i < cantTareas; i++) {
        
        if(tareas[i] != NULL) {
            printf("\n\nTareaID: %d\n", tareas[i]->TareaID);        
            printf("Descripcion: %s \n", tareas[i]->Descripcion);
            printf("Duracion: %d", tareas[i]->Duracion);
        }
       
    }
}

void liberarMemoriaTareas(Tarea **tareas, int cantTareas) {

    for(int i = 0; i < cantTareas; i++) {
        if(tareas[i] != NULL) {
            free(tareas[i]->Descripcion);
            free(tareas[i]);
        }
        
    }

    free(tareas);
}
