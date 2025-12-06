#ifndef PATIENT_H
    #define PATIENT_H
    #include <stdbool.h>
    #include "history.h"

    typedef struct _patient PATIENT;

    PATIENT* init_patient();
    void set_patient_name(PATIENT *patient, char *name);
    char* get_patient_name(PATIENT *patient);
    int get_patient_id(PATIENT *patient);
    HISTORY* get_patient_history(PATIENT *patient);
    bool set_patient_history(PATIENT *patient, HISTORY *history);
    void set_patient_id(PATIENT *patient, int id);
    bool delete_patient(PATIENT **patient);
#endif
