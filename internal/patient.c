#include <stdio.h>
#include <string.h>

#include "../include/patient.h"
#include "../include/io.h"

void add_procedure(PATIENT *patient) {
    if(is_history_full(get_patient_history(patient))){
        printf("\nHistórico cheio\n");
        return;
    }

    printf("Escreva o procedimento: ");

    flush();

    char procedure[100];
    fgets(procedure, 100, stdin);
    procedure[strcspn(procedure, "\n")] = '\0';

    add_procedure_to_history(get_patient_history(patient), procedure);
}

void remove_procedure(PATIENT *patient) {
    if(is_history_empty(get_patient_history(patient))){
        printf("\nHistórico vazio\n");
        return;
    }

    pop_last_procedure(get_patient_history(patient));
}

void print(PATIENT *patient){
    printf("\nHistórico:\n");

    print_history(get_patient_history(patient));
}


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

        printf("[1] Mostrar histórico\n");
        printf("[2] Adicionar procedimento\n");
        printf("[3] Remover procedimento\n");
        printf("[4] Alterar status\n");
        printf("[0] Voltar\n");

        printf("Selecione uma opção: ");

        int option;
        scanf("%d", &option);

        switch(option){
            case 1:
                print(patient);
                continue;
            case 2:
                add_procedure(patient);
                continue;
            case 3:
                remove_procedure(patient);
                continue;
            case 4:
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

