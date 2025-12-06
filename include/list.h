#ifndef LIST_H
    #define LIST_H
    #include <stdbool.h>
    #include "patient.h"

    typedef struct _list LIST;

    LIST* init_list();
    void add_patient(LIST *list, PATIENT *patient);
    void remove_patient(LIST *list, int patient_id);
    PATIENT* get_patient_by_id(LIST *list, int patient_id);
    PATIENT* get_patient_by_name(LIST *list, char *name);
    int get_last_patients_id(LIST *list);
    PATIENT* get_first(LIST *list);
    PATIENT* get_last(LIST *list);
    void print_list(LIST *list);
    bool delete_list(LIST **list);
    bool is_list_empty(LIST *list);
    int get_list_size(LIST *list);
#endif
