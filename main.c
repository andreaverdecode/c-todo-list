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
void activitiesCount(FILE *activities, int *num_activities);
void readActivities(FILE *activities, Activity list[], int *num_activities);
void printActivities(Activity list[], int *num_activities);
void addActivities(FILE *activities);

int main(int argc, char *argv[]){  
    FILE * fp = NULL;
    Activity activities[MAX_ACTIVITIES] = {};
    int dim, scelta;

    //conto le righe all'apertura del file
    fp = fopen(argv[1], "r");
    activitiesCount(fp, &dim);
    if (dim >= MAX_ACTIVITIES){
        printf("Numero massimo di attivita raggiunto!");
        return -1;
    }
    fclose(fp);

    printf("Che azione vuoi compiere:\n");
    printf("1-Visualizzare la lista\t2-Inserire una nuova attivita: ");
    scanf("%d", &scelta);

    switch (scelta){
    case 1:
        fp = fopen(argv[1], "r"); //apertura del file in modalita lettura

        //controllo che il file si apra correttamente
        if (fp == NULL){
            printf("Errore nell'apertura del file %s", argv[1]); 
        }
        
        readActivities(fp, activities, &dim);
        printActivities(activities, &dim);
        break;

    case 2:
        fp = fopen(argv[1], "a"); //apertura del file in modalita aggiunta

        //controllo che il file si apra correttamente
        if (fp == NULL){
            printf("Errore nell'apertura del file %s", argv[1]);
        }

        addActivities(fp);
        break;
    
    default:
        puts("Scelta non valida");
        break;
    }
    
    fclose(fp); //chiusura del file
}


void activitiesCount(FILE *activities, int *num_activities){
    *num_activities = 0;
    char buffer[100];
    while (fgets(buffer, 100, activities) != NULL){
        (*num_activities)++;
    }
}

//funzione che permette di leggere e archiviare nella lista il contenuto del file
void readActivities(FILE *activities, Activity list[], int *num_activities){
    for(int i = 0; i < *num_activities; i++){
        fscanf(activities, "%50s", list[i].activity);
        fscanf(activities, "%d", &list[i].is_completed);
        fscanf(activities, "%2d", &list[i].creation_date.day);
        fscanf(activities, "%*c%2d", &list[i].creation_date.month);
        fscanf(activities, "%*c%4d", &list[i].creation_date.year);
    }    
}

//funzione che mi permette di stampare a terminale la lista letta dal file
void printActivities(Activity list[], int *num_activities){
    for (int i = 0; i < *num_activities; i++){
        puts("---------------------------------------------------------------");
        printf("Numero %d\n", i + 1);
        printf("\tAttivita': %s\n", list[i].activity);
        printf("\tStato: %d\n", list[i].is_completed);
        printf("\tData di creazione: %d/%d/%d\n", list[i].creation_date.day, list[i].creation_date.month, list[i].creation_date.year);
    }
}

void addActivities(FILE *activities){
    char name[MAX_LENGHT];
    int state, d_date, m_date, y_date;

    printf("Inserisci la nuova attivita': ");
    scanf("%50s", name);
    printf("Inserisci la data di creazione\n");
    printf("Giorno: ");
    scanf("%d", &d_date);
    printf("Mese: ");
    scanf("%d", &m_date);
    printf("Anno: ");
    scanf("%d", &y_date);

    fprintf(activities, "\n%s %d %d/%d/%d", name, 0, d_date, m_date, y_date);
}



