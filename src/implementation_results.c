//
// Created by alexis on 10/13/20.
//

#include <stdlib.h>
#include <string.h>
#include "../include/results.h"
#include "../include/mergeSort.h"

bool init_team(Team *res, char *name, int number, double time, int cntPoints) {
    if (res == NULL) {
        return false;
    }
    if (name == NULL) {
        return false;
    }
    res->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
    memcpy(res->name, name, sizeof(char) * strlen(name));
    res->name[strlen(name)] = '\0';
    res->number = number;
    res->time = time;
    res->cntPoints = cntPoints;
    return true;
}

bool init_result(Result *res, int size) {
    if (res == NULL) {
        return false;
    }
    if (size < MIN_SIZE) {
        return false;
    }
    res->results = (Team*)calloc(size, sizeof(Team));
    res->size = size;
    return true;
}

int compare(Team *a, Team *b) {
    if (a->cntPoints - b->cntPoints == 0) {
        if (a->time > b->time) {
            return -1;
        } else if (a->time < b->time) {
            return 1;
        }
        return 0;
    }
    return a->cntPoints - b->cntPoints;
}

bool assign(Team *a, Team *b) {
    if (a == NULL) {
        return false;
    }
    if (b == NULL) {
        return false;
    }
    a->number = b->number;
    a->time = b->time;
    a->cntPoints = b->cntPoints;
    if (b->name == NULL) {
        return false;
    }
    if (strlen(b->name) <= 0) {
        return false;
    }
    if (a->name == NULL) {
        a->name = (char *) malloc(sizeof(char) * strlen(b->name) + 1);
    } else {
        free(a->name);
        a->name = (char *) calloc(strlen(b->name) + 1, sizeof(char));
    }
    memcpy(a->name, b->name, sizeof(char) * strlen(b->name));
    a->name[strlen(b->name)] = '\0';
    return true;
}

Team * find_best(Result *res) {
    if (res == NULL) {
        return NULL;
    }
    if (res->size < MIN_SIZE) {
        return NULL;
    }
    merge_sort(res->results, 0, res->size - 1, compare, assign);
    Team *answ = (Team*)calloc(10, sizeof(Team));
    for (int i = res->size - 1, j = 0; j < 10 && i >= res->size - 10; --i, ++j) {
        if(assign(&answ[j], &res->results[i]) == false) {
            return NULL;
        }
    }
    return answ;
}

bool free_all(Result *res) {
    if (res == NULL) {
        return false;
    }
    for (int i = 0; i < res->size; ++i) {
        if (res->results[i].name != NULL) {
            free(res->results[i].name);
        }
    }
    free(res->results);
    return true;
}