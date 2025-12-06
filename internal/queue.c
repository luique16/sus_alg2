#include <stdio.h>

#include "../include/list.h"
#include "../include/queue.h"

#include "patient.c"

void add_patient_queue(LIST *list, QUEUE *queue){
    if(is_queue_full(queue)){
        printf("\nFila cheia\n");
        return;
    }

    printf("\n==============================\n");
    printf("  ADICIONAR PACIENTE - FILA\n");
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

    enqueue(queue, patient);
}

void call_patient_queue(LIST *list, QUEUE *queue){
    if(is_queue_empty(queue)){
        printf("Sem pacientes na fila.\n");
        return;
    }

    printf("\n==============================\n");
    printf("  CHAMAR PACIENTE - FILA\n");
    printf("==============================\n");

    printf("\n");

    PATIENT *patient = dequeue(queue);

    user_menu(patient);
}

void list_queue(LIST *list, QUEUE *queue){
    printf("\n==============================\n");
    printf("          LISTA FILA          \n");
    printf("==============================\n");

    printf("\n");

    print_queue(queue);
}

void queue_menu(LIST *list, QUEUE *queue){
    while(true) {
        printf("\n==============================\n");
        printf("         GERENCIAR FILA       \n");
        printf("==============================\n");

        printf("\n");

        printf("[1] Adicionar paciente à fila\n");
        printf("[2] Chamar paciente\n");
        printf("[3] Listar fila\n");
        printf("[0] Voltar\n");

        printf("Selecione uma opção: ");

        int option;
        scanf("%d", &option);

        switch(option){
            case 1:
                add_patient_queue(list, queue);
                continue;
            case 2:
                call_patient_queue(list, queue);
                continue;
            case 3:
                list_queue(list, queue);
                continue;
            case 0:
                return;
            default:
                printf("Opção inválida\n");
                continue;
        }
    }
}
