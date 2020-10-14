//
// Created by alexis on 10/13/20.
//

#ifndef IZ1_1_RESULTS_H
#define IZ1_1_RESULTS_H
#include <stdbool.h>
#define MIN_SIZE 10

struct team {
    char *name;
    int number;
    double time;
    int cntPoints;
};

typedef struct team Team;

struct result {
    Team *results;
    int size;
};

typedef struct result Result;

bool init_team(Team *res, char *name, int number, double time, int cntPoints);

bool init_result(Result *res, int size);

int compare(Team *a, Team *b);

bool assign(Team *a, Team *b);

Team * find_best(Result *res);

bool free_all(Result *res);


#endif //IZ1_1_RESULTS_H
