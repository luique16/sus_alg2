#include "../include/patient.h"

#include <stdlib.h>
#include <string.h>

typedef struct _patient {
    int id;
    char *name;
    HISTORY *history;
    bool hospitalized;
} PATIENT;

PATIENT* init_patient(){
    PATIENT *patient = (PATIENT*) calloc(1, sizeof(PATIENT));
    patient->name = (char*) malloc(sizeof(char) * 100);
    patient->hospitalized = false; 

    return patient;
}

void set_patient_name(PATIENT *patient, char *name){
    strcpy(patient->name, name);
}

char* get_patient_name(PATIENT *patient){
    return patient->name;
}

int get_patient_id(PATIENT *patient){
    return patient->id;
}

void set_patient_id(PATIENT *patient, int id){
    patient->id = id;
}

HISTORY* get_patient_history(PATIENT *patient){
    return patient->history;
}

bool set_patient_history(PATIENT *patient, HISTORY *history){
    patient->history = history;
    return true;
}

void hospitalize(PATIENT *patient){
    patient->hospitalized = true;
}

void un_hospitalize(PATIENT *patient){
    patient->hospitalized = false;
}

bool is_hospitalized(PATIENT *patient){
    return patient->hospitalized;
}

void delete_patient(PATIENT **patient) {
    PATIENT *tmp = *patient;
    delete_history(&(tmp->history));
    free(tmp->name);
    free(tmp);
    *patient = NULL;
}
