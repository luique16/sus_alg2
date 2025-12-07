#include <stdio.h>
#include <string.h>

#include "../include/patient.h"

void change_status(PATIENT *patient){
    if (patient == NULL) {
        printf("Paciente não encontrado\n");
        return;
    }

    if (is_hospitalized(patient)) {
        un_hospitalize(patient);
    } else {
        hospitalize(patient);
    }
}

void user_menu(PATIENT *patient){
    if (patient == NULL) {
        printf("Paciente não encontrado\n");
        return;
    }

    while(true){
        printf("\n==============================\n");
        printf("    GERENCIAMENTO PACIENTE    \n");
        printf("==============================\n");

        printf("\n");

        printf("Nome: %s\n", get_patient_name(patient));
        printf("Id: %d\n", get_patient_id(patient));
        printf("Status: %s\n", is_hospitalized(patient) ? "Internado" : "Externo");

        printf("\n");

        printf("[1] Alterar status\n");
        printf("[0] Voltar\n");

        printf("Selecione uma opção: ");

        int option;
        scanf("%d", &option);

        switch(option){
            case 1:
                change_status(patient);
                continue;
            case 0:
                return;
            default:
                printf("Opção inválida\n");
                continue;
        }

    }
}

