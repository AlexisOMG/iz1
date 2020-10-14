//
// Created by alexis on 10/13/20.
//

#ifndef IZ1_1_MERGESORT_H
#define IZ1_1_MERGESORT_H

#include "results.h"

void merge(Team *arr, int left, int middle, int right, int (*compare)(Team *, Team *),
           bool (*assign)(Team *, Team *));

void merge_sort(Team *arr, int left, int right, int (*compare)(Team *, Team *), bool (*assign)(Team *, Team *));

#endif //IZ1_1_MERGESORT_H
