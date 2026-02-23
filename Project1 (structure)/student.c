#include <stdio.h>
#include "student.h"
#include <string.h>

void input_students(char names[][MAX_NAME_LENGTH + 1], int scores[], int *count) {
    printf("students: ");
    scanf("%d", count);
    if (*count <1 || *count > MAX_STUDENTS) {
        printf("overload input again\n");
        *count = 0;
        return;
    }
    for (int i = 0; i < *count; i++) {
        printf("number %d 's student name: ", i + 1);
        scanf("%20s", names[i]);
        int score;
        do {
            printf("input %s score: ", names[i]);
            scanf("%d", &score);
            if (score < 0 || score > 100) {
                printf("nonsense input again。\n");
            }
        }
        while (!is_valid_score(score));
        scores[i] = score;
    }
}

double calculate_average(int scores[], int count){
    if (count == 0) return 0.0;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += scores[i];
    }
    return (double)sum / count;
}

int find_max_score(int scores[], int count){
    if (count == 0) return 0;
    int max = scores[0];
    for (int i = 1; i < count; i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }
    return max;
}

int find_min_score(int scores[], int count) {
    if (count == 0) return 0;
    int min = scores[0];
    for (int i = 1; i < count; i++) {
        if (scores[i] < min) {
            min = scores[i];
        }
    }
    return min;
}

void count_grades(int scores[], int count, int grade_count[]) {
    for (int i = 0; i < 4; i++) {
        grade_count[i] = 0;
    }
    for (int i = 0; i < count; i++) {
        if (scores[i] >= 90) {
            grade_count[0]++;
        } else if (scores[i] >= 80) {
            grade_count[1]++;
        } else if (scores[i] >= 60) {
            grade_count[2]++;
        } else {
            grade_count[3]++;
        }
    }
}

void display_students(char names[][MAX_NAME_LENGTH + 1], int scores[], int count) {
    printf("=== student data ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s: %d分\n", i + 1, names[i], scores[i]);
        if (scores[i] >= 90) {
            printf("excellent\n");
        } else if (scores[i] >= 80) {
            printf("good\n");
        } else if (scores[i] >= 60) {
            printf("pass\n");
        } else {
            printf("failed\n");
        }
    }
}

void display_statistics(int scores[], int count){
    if (count == 0) {
        printf("no student data。\n");
        return;
    }
    double average = calculate_average(scores, count);
    int max_score = find_max_score(scores, count);
    int min_score = find_min_score(scores, count);
    
    int grade_count[4] = {0}; 
    count_grades(scores, count, grade_count);
    
    printf("=== score data ===\n");
    printf("avg score: %.2f\n", average);
    printf("highest score: %d\n", max_score);
    printf("lowest score: %d\n", min_score);
    printf("nums of excellent: %d\n", grade_count[0]);
    printf("nums of good: %d\n", grade_count[1]);
    printf("nums of pass: %d\n", grade_count[2]);
    printf("nums of failedg: %d\n", grade_count[3]);
}

int is_valid_score(int score){
    return (score >= 0 && score <= 100);
}