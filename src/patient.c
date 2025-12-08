#include "../include/patient.h"

#include <stdlib.h>
#include <string.h>

typedef struct _patient {
    int id;
    char *name;
    HISTORY *history;
    bool hospitalized;
} PATIENT;

/*
    @brief cria um paciente
    @return
*/
PATIENT* init_patient(){
    PATIENT *patient = (PATIENT*) calloc(1, sizeof(PATIENT));
    patient->name = (char*) malloc(sizeof(char) * 100);
    patient->hospitalized = false; 

    return patient;
}

/*
    @brief nomeia o paciente
    @param patient paciente
    @param name nome do paciente
    @return
*/
void set_patient_name(PATIENT *patient, char *name){
    strcpy(patient->name, name);
}

/*
    @brief retorna o nome do paciente
    @param patient paciente
    @return
*/
char* get_patient_name(PATIENT *patient){
    return patient->name;
}

/*
    @brief retorna o id do paciente
    @param patient paciente
    @return
*/
int get_patient_id(PATIENT *patient){
    return patient->id;
}

/*
    @brief atribui um id ao paciente
    @param patient paciente
    @param id id a ser atribuido
    @return
*/
void set_patient_id(PATIENT *patient, int id){
    patient->id = id;
}

/*
    @brief retorna o historico do paciente
    @param patient paciente
    @return
*/
HISTORY* get_patient_history(PATIENT *patient){
    return patient->history;
}

/*
    @brief atribui um historico ao paciente
    @param patient paciente
    @param history historico a ser atribuido
    @return
*/
bool set_patient_history(PATIENT *patient, HISTORY *history){
    patient->history = history;
    return true;
}

/*
    @brief atribui o status de hospitalizado ao paciente
    @param patient paciente
    @return
*/
void hospitalize(PATIENT *patient){
    patient->hospitalized = true;
}

/*
    @brief remove o status de hospitalizado ao paciente
    @param patient paciente
    @return
*/
void un_hospitalize(PATIENT *patient){
    patient->hospitalized = false;
}

/*
    @brief verifica se o paciente esta hospitalizado
    @param patient paciente
    @return true caso esteja, false caso contrario
*/
bool is_hospitalized(PATIENT *patient){
    return patient->hospitalized;
}

/*
    @brief deleta o paciente
    @param patient paciente
    @return
*/
void delete_patient(PATIENT **patient) {
    PATIENT *tmp = *patient;
    delete_history(&(tmp->history));
    free(tmp->name);
    free(tmp);
    *patient = NULL;
}
