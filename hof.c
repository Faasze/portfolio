#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hof.h"

int CMP (const void* player1, const void* player2){
     if (player1 == NULL || player2 == NULL) {
        return 0;
    }
    struct player* list1 = (struct player*)player1;
    struct player* list2 = (struct player*)player2;
    int result = (list2->score - list1->score);
        return result;
}

int load(struct player list[]){
    FILE *fp=fopen(HOF_FILE, "r");

    if (fp==NULL){
        return -1;
    }

    int count=0;
    char line[100];
    while(fgets(line, sizeof(line), fp) != NULL){
        count++;
    }

    rewind(fp);

    size_t size = (size_t)((count > 10) ? 10 : count);

    for (size_t i = 0; i < size; i++){
        fscanf(fp, "%s %d\n",list[i].name, &list[i].score);
    }

    fclose(fp);

    qsort(list, size, sizeof(struct player), CMP);

    return count;
}

bool save(const struct player list[], const int size){
    if (list == NULL || list[0].name==NULL){
        return false;
    }
        
    FILE* fp = fopen(HOF_FILE, "w");
    if (fp == NULL) {
        return false;
    }
    for(size_t i = 0; i < (size_t)size; i++){
        fwrite(list[i].name, sizeof(char), strlen(list[i].name), fp);
        fwrite(" ", sizeof(char), 1, fp);
        char score_str[10];
        sprintf(score_str, "%d", list[i].score);
        fwrite(score_str, sizeof(char), strlen(score_str), fp);
        fwrite("\n", sizeof(char), 1, fp);
    }
    fclose(fp);
    return true;
}

bool add_player(struct player list[], int* size, const struct player new_player) {
    if (*size >= 10 && list[9].score >= new_player.score)
        return false; 

    int insert_index = *size; 

    for (int i = 0; i < *size; i++) {
        if (list[i].score <= new_player.score) {
            insert_index = i;
            break;
        }
    }

    for (int i = *size - 1; i >= insert_index; i--) {
        list[i + 1] = list[i];
    }

    list[insert_index] = new_player;

    if (*size < 10) {
        (*size)++;
    }

    return true;
}

