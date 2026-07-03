#include <stdio.h>

#define MAX_LENGHT 51
#define MAX_ACTIVITIES 20

//definisco un tipo "date" per gestire le date
typedef struct{
    int day;
    int month;
    int year;
}Date;

//definisco un tipo "state" per monitorare lo stato della mia attivita
typedef enum{
    ONGOING,
    COMPLETED
}State;

//uso una struct per la singola attivita
typedef struct{
    char activity[MAX_LENGHT];
    State is_completed;
    Date creation_date;
    Date completion_date;
}Activity;

//prototipi di funzione
void readActivities(FILE * activities, Activity list[], int *num_activities);
void printActivities(Activity list[], int *num_activities);

int main(int argc, char *argv[]){  
    FILE * fp = NULL;
    Activity activities[MAX_ACTIVITIES] = {};
    int dim;

    fp = fopen(argv[1], "r"); //apertura del file

    //controllo che il file si apra correttamente
    if (fp == NULL){
        printf("Errore nell'apertura del file %s", argv[1]); 
    }
    
    readActivities(fp, activities, &dim);
    printActivities(activities, &dim);
    
    fclose(fp); //chiusura del file
}

//funzione che permette di leggere e archiviare nella lista il contenuto del file
void readActivities(FILE * activities, Activity list[], int *num_activities){
    *num_activities = 0;

    while (feof(activities) == 0 && *num_activities < MAX_ACTIVITIES){
        fscanf(activities, "%50s", list[*num_activities].activity);
        fscanf(activities, "%d", &list[*num_activities].is_completed);
        fscanf(activities, "%2d", &list[*num_activities].creation_date.day);
        fscanf(activities, "%*c%2d", &list[*num_activities].creation_date.month);
        fscanf(activities, "%*c%4d", &list[*num_activities].creation_date.year);
        (*num_activities)++;
        if (fgetc(activities) == EOF){
            break;
        }
    }    
}

//funzione che mi permette di stampare a terminale la lista letta dal file
void printActivities(Activity list[], int *num_activities){
    for (int i = 0; i < *num_activities; i++){
        puts("---------------------------------------------------------------");
        printf("Numero %d\n", i + 1);
        printf("\tAttivita': %s\n", list[i].activity);
        printf("\tStato: %d\n", list[i].is_completed);
        printf("\tData di creazione: %d/%d/%d\n", list[i].creation_date.day, list[i].creation_date.month, list[i].creation_date.year);\
    }
}

