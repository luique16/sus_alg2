#include <stdio.h>
#include <string.h>

#include "../include/io.h"
#include "../include/list.h"
#include "../include/queue.h"
#include "../include/patient.h"

#define MAX_LINE_SIZE 1000

void skip_line(FILE *file) {
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, file);
}

void flush(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool save(LIST *list, QUEUE *queue, char *list_filename, char *queue_filename) {
    FILE *queue_file = fopen(queue_filename, "w");

    if(is_queue_empty(queue)){
        fprintf(queue_file, "[]\n");
    } else {
        fprintf(queue_file, "[");

        int size = get_queue_size(queue);

        for (int i = 0; i < size; i++) {
            int level = get_next_level(queue);
            PATIENT *patient = dequeue(queue);

            fprintf(queue_file, "\n  [%d, %d]", get_patient_id(patient), level);

            if (i < size - 1) {
                fprintf(queue_file, ",");
            }
        }

        fprintf(queue_file, "\n]\n");
    }

    fclose(queue_file);


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
            bool hospitalized = is_hospitalized(patient);

            fprintf(list_file, "\n  {\n");
            fprintf(list_file, "    \"id\": %d,\n", get_patient_id(patient));
            fprintf(list_file, "    \"name\": \"%s\",\n", name);
            fprintf(list_file, "    \"hospitalized\": %d\n", hospitalized);
            fprintf(list_file, "  }");

            if (i < size - 1) {
                fprintf(list_file, ",");
            }

            remove_patient(list, id);
        }

        fprintf(list_file, "\n]\n");
    }

    fclose(list_file);

    return true;
}

bool load(LIST **list, QUEUE **queue, char *list_filename, char *queue_filename) {
    // Load list
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
        char history[MAX_LINE_SIZE];
        int hospitalized;

        for (int i = 0; i < 3; i++) {
            char field[20];

            fgets(line, MAX_LINE_SIZE, list_file);
            sscanf(line, "  \"%[^\"]\": ", field);

            if (strcmp(field, "id") == 0) {
                sscanf(line, "  \"id\": %d,", &id);
            } else if (strcmp(field, "name") == 0) {
                sscanf(line, "  \"name\": \"%[^\"]\",", name);
            } else if (strcmp(field, "hospitalized") == 0) {
                int empty = sscanf(line, "  \"hospitalized\": %d,", &hospitalized);
                if (empty == 0) {
                    history[0] = '\0';
                }
            }
        }

        PATIENT *patient = init_patient();
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
                if(line[i + 1] == ',') {
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

    // Load queue
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
