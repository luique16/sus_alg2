#include "../include/history.h"
#include "../include/patient.h"

#include <stdlib.h>
#include <string.h>

typedef struct _patient {
    int id;
    char *name;
    HISTORY *history;
} PATIENT;

PATIENT* init_patient(){
    PATIENT *patient = (PATIENT*) calloc(1, sizeof(PATIENT));
    patient->name = (char*) malloc(sizeof(char) * 100);

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

HISTORY* get_patient_history(PATIENT *patient){
    return patient->history;
}

bool set_patient_history(PATIENT *patient, HISTORY *history){
    patient->history = history;
    return true;
}

void set_patient_id(PATIENT *patient, int id){
    patient->id = id;
}

bool delete_patient(PATIENT **patient) {
    PATIENT *tmp = *patient;
    free(tmp->name);
    delete_history(&(tmp->history));
    free(tmp);
    *patient = NULL;
    return true;
}
