//
// Created by alexis on 10/13/20.
//

#include "gtest/gtest.h"

extern "C" {
#include "results.h"
}

TEST(init_team, team_null) {
    char str[] = {'a', 'b', 'c', '\0'};
    ASSERT_EQ(init_team(NULL, str, 0, 0, 0), false);
}

TEST(init_team, name_null) {
    Team obj;
    ASSERT_EQ(init_team(&obj, NULL, 0, 0, 0), false);
}

TEST(init_team, ok) {
    Team obj;
    char str[] = {'a', 'b', 'c', '\0'};
    int number = 0;
    double time = 1.5;
    int cntPoints = 1;
    ASSERT_EQ(init_team(&obj, str, number, time, cntPoints), true);
    ASSERT_EQ(obj.cntPoints, cntPoints);
    ASSERT_EQ(obj.time, time);
    ASSERT_EQ(obj.number, number);
    ASSERT_EQ(strlen(obj.name), strlen(str));
    for (int i = 0; i < strlen(str); ++i) {
        ASSERT_EQ(obj.name[i], str[i]);
    }
}

TEST(init_result, null_obj) {
    ASSERT_EQ(init_result(NULL, 10), false);
}

TEST(init_result, small_size) {
    Result obj;
    ASSERT_EQ(init_result(&obj, 9), false);
}

TEST(init_result, ok) {
    Result obj;
    ASSERT_EQ(init_result(&obj, 10), true);
    ASSERT_NE(obj.results, nullptr);
    ASSERT_EQ(obj.size, 10);
}

TEST(compare, neg_time) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 45.3, 9), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    ASSERT_LT(compare(&a, &b), 0);
}

TEST(compare, pos_time) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 8.1, 9), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    ASSERT_GT(compare(&a, &b), 0);
}

TEST(compare, eq_time) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 8.1, 9), true);
    ASSERT_EQ(init_team(&b, str2, 2, 8.1, 9), true);
    ASSERT_EQ(compare(&a, &b), 0);
}

TEST(compare, neg_points) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 10.5, 8), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    ASSERT_LT(compare(&a, &b), 0);
}

TEST(compare, pos_points) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 10.5, 10), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    ASSERT_GT(compare(&a, &b), 0);
}

TEST(assign, null_obj) {
    Team obj;
    ASSERT_EQ(assign(NULL, &obj), false);
    ASSERT_EQ(assign(&obj, NULL), false);
}

TEST(assign, null_name) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 10.5, 10), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    b.name = NULL;
    ASSERT_EQ(assign(&a, &b), false);
}

TEST(assign, empty_name) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 10.5, 10), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    ASSERT_EQ(assign(&a, &b), false);
}

TEST(assign, ok1) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 10.5, 10), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    ASSERT_EQ(assign(&a, &b), true);
    ASSERT_EQ(a.cntPoints, b.cntPoints);
    ASSERT_EQ(a.time, b.time);
    ASSERT_EQ(a.number, b.number);
    ASSERT_EQ(strlen(a.name), strlen(b.name));
    for (int i = 0; i < strlen(b.name); ++i) {
        ASSERT_EQ(a.name[i], b.name[i]);
    }
}

TEST(assign, ok2) {
    Team a, b;
    char str1[] = {'a', 'b', 'c', '\0'};
    char str2[] = {'c', 'd', 'e', '\0'};
    ASSERT_EQ(init_team(&a, str1, 1, 10.5, 10), true);
    ASSERT_EQ(init_team(&b, str2, 2, 10.5, 9), true);
    a.name = NULL;
    ASSERT_EQ(assign(&a, &b), true);
    ASSERT_EQ(a.cntPoints, b.cntPoints);
    ASSERT_EQ(a.time, b.time);
    ASSERT_EQ(a.number, b.number);
    ASSERT_EQ(strlen(a.name), strlen(b.name));
    for (int i = 0; i < strlen(b.name); ++i) {
        ASSERT_EQ(a.name[i], b.name[i]);
    }
}

TEST(find_best, null_obj) {
    ASSERT_EQ(find_best(NULL), nullptr);
}

TEST(find_best, small_size) {
    Result res;
    ASSERT_EQ(init_result(&res, 10), true);
    res.size = 9;
    ASSERT_EQ(find_best(&res), nullptr);
}

TEST(find_best, ok) {
    Result res;
    ASSERT_EQ(init_result(&res, 11), true);
    double time = 10.5;
    char str1[] = {'a', 'b', 'c', '\0'};
    for (int i = 0; i < res.size; ++i) {
        str1[0] = char('a' + i);
        ASSERT_EQ(init_team(&res.results[i], str1, i, time, 10), true);
        time += 1.5;
    }
    Team *answ = find_best(&res);
    ASSERT_NE(answ, nullptr);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(answ[i].number, i);
    }
}

TEST(free_all, null_obj) {
    ASSERT_EQ(free_all(NULL), false);
}

TEST(free_all, ok) {
    Result res;
    ASSERT_EQ(init_result(&res, 11), true);
    double time = 10.5;
    char str1[] = {'a', 'b', 'c', '\0'};
    for (int i = 0; i < res.size; ++i) {
        str1[0] = char('a' + i);
        ASSERT_EQ(init_team(&res.results[i], str1, i, time, 10), true);
        time += 1.5;
    }
    ASSERT_EQ(free_all(&res), true);
}