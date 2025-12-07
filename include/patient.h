#ifndef PATIENT_H
    #define PATIENT_H
    #include <stdbool.h>

    typedef struct _patient PATIENT;

    PATIENT* init_patient();
    void set_patient_name(PATIENT *patient, char *name);
    char* get_patient_name(PATIENT *patient);
    int get_patient_id(PATIENT *patient);
    void set_patient_id(PATIENT *patient, int id);
    void hospitalize(PATIENT *patient);
    void un_hospitalize(PATIENT *patient);
    bool is_hospitalized(PATIENT *patient);
    void delete_patient(PATIENT **patient);
#endif
