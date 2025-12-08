#include "../include/history.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_MAX_SIZE 10
#define DEFAULT_MAX_SIZE_TEXT 100

typedef struct _history {
    char* procedures[DEFAULT_MAX_SIZE];
    int size;
} HISTORY;

HISTORY* init_history(){
    HISTORY *history = (HISTORY*) calloc(1, sizeof(HISTORY));
    history->size = 0;

    return history;
}

/*
    @brief carrega o historico
    @param history historico do paciente
    @param text texto do historico
    @return true para carregamento feito, false para algum erro
*/
bool load_history(HISTORY *history, char *text) {
    int procedures_count = 0;
    int procedure_size = 0;

    char procedure[DEFAULT_MAX_SIZE_TEXT];

    for (int i = 0; i <= strlen(text); i++) {
        if (procedures_count >= DEFAULT_MAX_SIZE)
            return false;

        if (text[i] == ';' || text[i] == '\0') {
            procedure[procedure_size] = '\0';

            if (procedure_size > 0) {
                history->procedures[procedures_count] = strdup(procedure);
                procedures_count++;
                history->size++;
            }

            procedure_size = 0;
        } else {
            if (procedure_size < DEFAULT_MAX_SIZE_TEXT - 1) {
                procedure[procedure_size++] = text[i];
            } else {
                return false;
            }
        }
    }

    return true;
}

/*
    @brief salva o historico
    @param history historico do paciente
    @return texto do historico
*/
char* save_history(HISTORY *history) {
    char* text = calloc(DEFAULT_MAX_SIZE * (DEFAULT_MAX_SIZE_TEXT + 1), sizeof(char));

    if(history->size == 0){
        return text;
    }

    for(int i = 0; i < history->size - 1; i++) {
        strcat(text, history->procedures[i]);
        strcat(text, ";");
    }

    strcat(text, history->procedures[history->size - 1]);

    return text;
}

/*
    @brief verifica se o historico esta vazio
    @param history historico do paciente
    @return true caso esteja vazio, false caso nao esteja vazio
*/
bool is_history_empty(HISTORY *history){
    return history->size == 0;
}

/*
    @brief salva o historico
    @param history historico do paciente
    @return true caso esteja vazio, false caso nao esteja vazio
*/
bool is_history_full(HISTORY *history){
    return history->size >= DEFAULT_MAX_SIZE;
}

/*
    @brief adiciona procedimento ao historico
    @param history historico do paciente
    @param procedure procedimento a ser adicionado no historico
    @return 
*/
void add_procedure_to_history(HISTORY *history, char *procedure){
    char* procedure_copy = (char*) malloc(sizeof(char) * DEFAULT_MAX_SIZE_TEXT);

    if(is_history_full(history)){
        return;
    }

    strcpy(procedure_copy, procedure);

    history->procedures[history->size] = procedure_copy;

    history->size++;
}

/*
    @brief procura o ultimo procedimento
    @param history historico do paciente
    @return texto do ultimo procedimento
*/
char* get_last_procedure(HISTORY *history){
    if(history == NULL || is_history_empty(history)){
        return NULL;
    }

    return history->procedures[history->size - 1];
}

/*
    @brief exclui o ultimo procedimento
    @param history historico do paciente
    @return
*/
void pop_last_procedure(HISTORY *history){
    if(history == NULL || is_history_empty(history)){
        return;
    }

    char* procedure = history->procedures[history->size - 1];

    free(procedure);

    history->size--;
}

/*
    @brief deleta o historico completo
    @param history historico do paciente
    @return true caso funcione, false caso contrario
*/
bool delete_history(HISTORY **history) {
    if(*history == NULL){
        return false;
    }

    for(int i = 0; i < (*history)->size; i++){
        free((*history)->procedures[i]);
    }

    free(*history);
    *history = NULL;

    return true;
}

/*
    @brief printa o historico
    @param history historico do paciente
    @return
*/
void print_history(HISTORY *history){
    if(history == NULL){
        return;
    }

    for(int i = 0; i < history->size; i++){
        printf("[%d] %s\n", i + 1, history->procedures[i]);
    }
}
