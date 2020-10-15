//
// Created by alexis on 10/13/20.
//

#include "gtest/gtest.h"

extern "C" {
#include "results.h"
#include "mergeSort.h"
}

TEST(mergeSort, ok) {
    Result res;
    init_result(&res, 10);
    double time = 10.5;
    char str1[] = {'a', 'b', 'c', '\0'};
    for (int i = 0; i < res.size; ++i) {
        str1[0] = char('a' + i);
        init_team(&res.results[i], str1, i, time, 10);
        time += 1.5;
    }
    merge_sort(res.results, 0, res.size - 1, compare, assign);
    for (int i = 0; i < res.size; ++i) {
        ASSERT_EQ(res.results[i].number, res.size - 1 - i);
    }
}

