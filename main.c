#include <stdio.h>

#define MAX_LENGHT 50

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

int main(int argc, char *argv[]){  
}
