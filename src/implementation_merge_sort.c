//
// Created by alexis on 10/13/20.
//

#include <stdlib.h>
#include "../include/mergeSort.h"

void merge(Team *arr, int left, int middle, int right, int (*compare)(Team *, Team *),
           bool (*assign)(Team *, Team *)) {
    Team *tmp = (Team*)calloc(right - left + 1, sizeof(Team));
    for (int i = 0; i < right - left + 1; ++i) {
        init_team(&tmp[i], "-1", -1, 0, -1);
    }
    int i = left, j = middle + 1, h = 0;
    while (h < right - left + 1) {
        if (j <= right && (i == middle + 1 || compare(&arr[j], &arr[i]) < 0)) {
            assign(&tmp[h], &arr[j]);
            ++h;
            ++j;
        }
        else {
            assign(&tmp[h], &arr[i]);
            ++h;
            ++i;
        }
    }

    for (int t = 0, z = left; t < h; ++t, ++z) {
        assign(&arr[z], &tmp[t]);
    }
    for (int t = 0; t < right - left + 1; ++t) {
        if (tmp[t].name != NULL) {
            free(tmp[t].name);
        }
    }
    free(tmp);
}

void merge_sort(Team *arr, int left, int right, int (*compare)(Team *, Team *), bool (*assign)(Team *, Team *)) {
    if (left == right) return;
    int middle = (right + left) / 2;
    merge_sort(arr, left, middle, compare, assign);
    merge_sort(arr, middle + 1, right, compare, assign);
    merge(arr, left, middle, right, compare, assign);
}

