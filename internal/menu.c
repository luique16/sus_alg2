#include <stdio.h>
#include <stdbool.h>

#include "../include/list.h"
#include "../include/queue.h"
#include "list.c"
#include "queue.c"

int menu() {
    printf("\n==============================\n");
    printf("   PRONTO SOCORRO SUS - MENU  \n");
    printf("==============================\n");


    printf("\n");
    printf("[1] Gerenciar pacientes (cadastro geral)\n");
    printf("[2] Gerenciar fila de espera\n");
    printf("[0] Sair\n");

    printf("Selecione uma opção: ");

    int option;
    scanf("%d", &option);

    return option;
}

bool handle_menu_option(int option, LIST *list, QUEUE *queue){
    switch(option){
        case 1:
            list_menu(list);
            return true;
        case 2:
            queue_menu(list, queue);
            return true;
        default:
            return false;
    }
}
