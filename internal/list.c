#include <stdio.h>
#include <string.h>

#include "../include/list.h"
#include "../include/io.h"

void add_patient_list(LIST *list){
    printf("\n==============================\n");
    printf(" ADICIONAR PACIENTE - CADASTRO\n");
    printf("==============================\n");

    printf("\n");

    flush();

    printf("Digite o nome do paciente:\n");
    char name[100];
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    PATIENT *patient = init_patient();
    set_patient_name(patient, name);

    PATIENT *last = get_last(list);

    if(last == NULL){
        set_patient_id(patient, 1);
    } else {
        set_patient_id(patient, get_patient_id(last) + 1);
    }

    HISTORY *history = init_history();
    set_patient_history(patient, history);

    add_patient(list, patient);
}

void remove_patient_list(LIST *list){
    printf("\n==============================\n");
    printf(" REMOVA PACIENTE - CADASTRO  \n");
    printf("==============================\n");

    printf("\n");

    printf("Digite o id do paciente: ");
    int id;
    scanf("%d", &id);

    PATIENT *patient = get_patient_by_id(list, id);
    if(patient == NULL){
        printf("Paciente não encontrado\n");
        return;
    }

    remove_patient(list, id);
}

void list_patients_list(LIST *list){
    printf("\n==============================\n");
    printf("       LISTA PACIENTES        \n");
    printf("==============================\n");

    printf("\n");

    print_list(list);
}

void search_patient_by_name_list(LIST *list){
    printf("\n==============================\n");
    printf("       BUSCAR PACIENTE       \n");
    printf("==============================\n");

    printf("\n");

    flush();

    printf("Digite o nome do paciente: ");
    char name[100];
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    PATIENT *patient = get_patient_by_name(list, name);
    if(patient == NULL){
        printf("Paciente não encontrado\n");
        return;
    }

    printf("ID: %d\n", get_patient_id(patient));
    printf("Nome: %s\n", get_patient_name(patient));
    printf("Histórico:\n");
    print_history(get_patient_history(patient));
}

void search_patient_by_id_list(LIST *list){
    printf("\n==============================\n");
    printf("      BUSCAR PACIENTE        \n");
    printf("==============================\n");

    printf("\n");

    printf("Digite o id do paciente: ");
    int id;
    scanf("%d", &id);

    PATIENT *patient = get_patient_by_id(list, id);
    if(patient == NULL){
        printf("Paciente não encontrado\n");
        return;
    }

    printf("ID: %d\n", get_patient_id(patient));
    printf("Nome: %s\n", get_patient_name(patient));
    printf("Histórico:\n");
    print_history(get_patient_history(patient));
}

void list_menu(LIST *list){
    while(true) {
        printf("\n==============================\n");
        printf("    CADASTRO GERAL - LISTA    \n");
        printf("==============================\n");

        printf("\n");

        printf("[1] Adicionar paciente\n");
        printf("[2] Remover paciente\n");
        printf("[3] Listar pacientes\n");
        printf("[4] Buscar por nome\n");
        printf("[5] Buscar por id\n");
        printf("[0] Voltar\n");

        printf("Selecione uma opção: ");

        int option;
        scanf("%d", &option);

        switch(option){
            case 1:
                add_patient_list(list);
                continue;
            case 2:
                remove_patient_list(list);
                continue;
            case 3:
                list_patients_list(list);
                continue;
            case 4:
                search_patient_by_name_list(list);
                continue;
            case 5:
                search_patient_by_id_list(list);
                continue;
            case 0:
                return;
            default:
                printf("Opção inválida\n");
                continue;
        }
    }

    return;
}
