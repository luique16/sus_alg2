#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/io.h"
#include "../include/list.h"
#include "../include/queue.h"
#include "../include/patient.h"
#include "../include/history.h"

#define MAX_LINE_SIZE 1000

/*
    @brief pula uma linha
    @param file arquivo do historico
    @return
*/
void skip_line(FILE *file) {
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, file);
}


/*
    @brief limpa a entrada padrao
    @return
*/
void flush(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/*
    @brief salva o estado atual do sistema
    @param list lista de pacientes
    @param queue fila de pacientes
    @param list_filename nome do arquivo de lista
    @param queue_filename nome do arquivo de fila
    @return true caso salve, false caso contrario
*/
bool save(LIST *list, QUEUE *queue, char *list_filename, char *queue_filename) {
    // Salva fila
    FILE *queue_file = fopen(queue_filename, "w");

    if(is_queue_empty(queue)){
        fprintf(queue_file, "[]\n");
    } else {
        fprintf(queue_file, "[");

        int size = get_queue_size(queue);

        for (int i = 0; i < size; i++) {
            int level = get_next_level(queue);
            PATIENT *patient = dequeue(queue);

            fprintf(queue_file, "\n  [%d, %d]", get_patient_id(patient), level); // "tupla" de id e nivel de urgencia

            if (i < size - 1) {
                fprintf(queue_file, ",");
            }
        }

        fprintf(queue_file, "\n]\n");
    }

    fclose(queue_file);


    // Salva lista
    FILE *list_file = fopen(list_filename, "w");

    if(is_list_empty(list)){
        fprintf(list_file, "[]\n");
    } else {
        fprintf(list_file, "[");

        int size = get_list_size(list);
        for (int i = 0; i < size; i++) {
            int id = get_patient_id(get_first(list));
            PATIENT *patient = get_patient_by_id(list, id);

            char* name = get_patient_name(patient);
            char* history = save_history(get_patient_history(patient));
            bool hospitalized = is_hospitalized(patient);

            fprintf(list_file, "\n  {\n");
            fprintf(list_file, "    \"id\": %d,\n", get_patient_id(patient));
            fprintf(list_file, "    \"name\": \"%s\",\n", name);
            fprintf(list_file, "    \"history\": \"%s\",\n", history);
            fprintf(list_file, "    \"hospitalized\": %d\n", hospitalized);
            fprintf(list_file, "  }");

            if (i < size - 1) {
                fprintf(list_file, ",");
            }

            free(history);
            remove_patient(list, id);
        }

        fprintf(list_file, "\n]\n");
    }

    fclose(list_file);

    return true;
}

bool load(LIST **list, QUEUE **queue, char *list_filename, char *queue_filename) {
    // Carrega lista
    FILE *list_file = fopen(list_filename, "r");

    if (list_file == NULL) {
        printf("Error: list file not found\n");
        return false;
    }

    bool complete = false;

    char line[MAX_LINE_SIZE];

    fgets(line, MAX_LINE_SIZE, list_file);

    if (strncmp(line, "[]", 2) == 0)
        complete = true;

    while (!complete) {
        skip_line(list_file);

        int id;
        char name[MAX_LINE_SIZE];
        char history_text[MAX_LINE_SIZE];
        int hospitalized;

        for (int i = 0; i < 4; i++) {
            char field[20];

            fgets(line, MAX_LINE_SIZE, list_file);
            sscanf(line, "  \"%[^\"]\": ", field);

            if (strcmp(field, "id") == 0) {
                sscanf(line, "  \"id\": %d,", &id);
            } else if (strcmp(field, "name") == 0) {
                sscanf(line, "  \"name\": \"%[^\"]\",", name);
            } else if (strcmp(field, "history") == 0) {
                int empty = sscanf(line, "  \"history\": \"%[^\"]\",", history_text);
                if (empty == 0) {
                    history_text[0] = '\0';
                }
            } else if (strcmp(field, "hospitalized") == 0) {
                sscanf(line, "  \"hospitalized\": %d", &hospitalized);
            }
        }
        
        HISTORY *history = init_history();
        load_history(history, history_text);

        PATIENT *patient = init_patient();
        set_patient_history(patient, history);
        set_patient_id(patient, id);
        set_patient_name(patient, name);

        if (hospitalized == 1) {
            hospitalize(patient);
        } else {
            un_hospitalize(patient);
        }

        add_patient(*list, patient);

        fgets(line, MAX_LINE_SIZE, list_file);
        bool end = true;

        for(int i = 0; i < strlen(line); i += 1) {
            if(line[i] == '}') {
                if(line[i + 1] == ',') { // verifica se o ultimo caractere da linha é vírgula para continuar
                    end = false;
                }
                break;
            }
        }

        if (end) {
            complete = true;
        }
    }

    fclose(list_file);

    // Carrega fila
    FILE *queue_file = fopen(queue_filename, "r");

    if (queue_file == NULL) {
        printf("Error: queue file not found\n");
        return false;
    }

    complete = false;

    fgets(line, MAX_LINE_SIZE, queue_file);

    if (strcmp(line, "[]\n") == 0) {
        complete = true;
    }

    while (!complete) {
        int id;
        int level;

        fgets(line, 100, queue_file);

        if (strncmp(line, "]", 2) == 0 || strncmp(line, "]", 1) == 0) {
            complete = true;
            break;
        }

        sscanf(line, "  [%d, %d],", &id, &level);

        PATIENT *patient = get_patient_by_id(*list, id);

        if (patient != NULL) {
            enqueue(*queue, patient, level);
        }
    }

    fclose(queue_file);

    return true;
}
