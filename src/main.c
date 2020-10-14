//
// Created by alexis on 10/13/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/results.h"

int main() {
    int size = 0;
    char *name = NULL;
    int number = 0;
    double time = 0.0;
    int cntPoints = 0;
    printf("Enter size:\n");
    scanf("%d", &size);
    assert(size >= 10);
    Result res;
    init_result(&res, size);
    for (int i = 0; i < size; ++i) {
        if (name != NULL) {
            free(name);
        }
        name = (char*)calloc(128, sizeof(char));
        printf("Enter name:\n");
        scanf("%127s", name);
        assert(strlen(name) > 0 && strlen(name) < 128);
        printf("Enter number:\n");
        scanf("%d", &number);
        assert(number >= 0);
        printf("Enter time:\n");
        scanf("%lf", &time);
        assert(time >= (double)0.0);
        printf("Enter cnt of points:\n");
        scanf("%d", &cntPoints);
        assert(cntPoints > 0);
        init_team(&res.results[i], name, number, time, cntPoints);
    }
    Team *answ = find_best(&res);
    if (answ != NULL) {
        for (int i = 0; i < 10; ++i) {
            printf("\nTeam: %d\n%s\nTime: %lf\nCount of points: %d\n",
                   answ[i].number,
                   answ[i].name,
                   answ[i].time,
                   answ[i].cntPoints);
            free(answ[i].name);
        }
        free(answ);
    }
    free_all(&res);
    free(name);
    return EXIT_SUCCESS;
}
