#include <stdio.h>

#define LIST_FILENAME "list.json"
#define QUEUE_FILENAME "queue.json"

#include "include/io.h"
#include "include/list.h"
#include "include/queue.h"

#include "internal/menu.c"

int main() {
    // Carregar os dados
    LIST *list = init_list();
    QUEUE *queue = init_queue();

    bool success = load(&list, &queue, LIST_FILENAME, QUEUE_FILENAME);

    if(!success){
        printf("Erro ao carregar dados\n");
        return 1;
    }

    // Loop do menu
    while(true){
        int option = menu();

        if (option == 0) {
            success = save(list, queue, LIST_FILENAME, QUEUE_FILENAME);

            if(!success){
                printf("Erro ao salvar dados\n");
                return 1;
            }

            delete_list(&list);
            delete_queue(&queue);

            return 0;
        }

        if (option > 2 || option < 0) {
            printf("Opção inválida\n");
            continue;
        }

        handle_menu_option(option, list, queue);
    }
}
