#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}Tarea;

int main(){


    srand(time(NULL));
    int cant,opc,i_realizado;
    i_realizado = 0;
    printf("Ingrese cantidad de tareas: ");
    scanf("%d", &cant);

    Tarea **tarea = (Tarea **)malloc(sizeof(Tarea *)*cant);//tareas pendientes
    Tarea **tarea2 = (Tarea **)malloc(sizeof(Tarea *)*cant);//tareas realizadas

    //Tarea *tarea = (Tarea *)malloc(sizeof(Tarea )*cant);
    char *buff = (char *)malloc(sizeof(char)*100);
    
    for(int i=0;i<cant; i++) { tarea[i] = NULL; tarea2[i] = NULL;}

    for(int i=0;i<cant; i++) {

        tarea[i] = (Tarea *)malloc(sizeof(Tarea));
        
        tarea[i]->TareaID = i;
        tarea[i]->Duracion = (rand() % 90) + 10;
        tarea[i]->Descripcion = (char *)malloc(sizeof(char)*100);
        
        getchar();
        printf("Descripcion: ");
        gets(buff);
        strcpy(tarea[i]->Descripcion, buff);
        

    }
    

    
    for(int i=0;i<cant; i++) {
        /*printf("Descripcion: %s\n",  tarea[i]->Descripcion);
        printf("Duracion: %d\n",  tarea[i]->Duracion);*/
        printf("Se resolvio TareaID: %d - Descripcion: %s?\t(Si = 1 No = 2)\n", tarea[i]->TareaID, tarea[i]->Descripcion);
        scanf("%d",&opc);
        if (opc == 1)
        {
            i_realizado++;
            //tarea2[i_realizado] = (Tarea *)malloc(sizeof(Tarea));
            tarea2[i_realizado] = tarea[i];
            tarea[i] = NULL;
        }
    }
    printf("tareas realizadas: \n");
    
    for (int i = 0; i < i_realizado; i++)
    {
    
        printf("Descripcion: %s\n",  tarea2[i]->Descripcion);
        printf("Duracion: %d\n",  tarea2[i]->Duracion);
    
    }
    

    for(int i=0;i<cant; i++) {
        free(tarea[i]->Descripcion);
    }

    for(int i=0;i<i_realizado; i++) {
       
        free(tarea2[i]->Descripcion);
    }
    
    

    free(tarea);
    free(tarea2);
    free(buff);

    return 0;
}
