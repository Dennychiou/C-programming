#include <stdio.h>
#include "student.h"
#include <string.h>

void input_students(char names[][MAX_NAME_LENGTH + 1], int scores[], int *count) {
    printf("請輸入學生人數:");
    scanf("%d", count);

    if (*count < 1 || *count > MAX_STUDENTS) {
        printf("學生人數必須在1到%d之間。\n", MAX_STUDENTS);
        *count = 0; 
        return;
    }

    for (int i = 0; i < *count; i++) {
        printf("學生 %d 名字:", i + 1);
        scanf("%s", names[i]);

        printf("學生 %d 成績:", i + 1);
        scanf("%d", &scores[i]);
    }
}

double calculate_average(int scores[], int count){
    if (count == 0) return 0.0;
    int sum = 0;
    for (int i= 0; i< count; i++){
        sum += scores[i];
    }
    return (double)sum / count;
}

int find_max_score(int scores[], int count){
    if (count == 0) return 0;
    int max = scores[0];

    for (int i = 1; i < count; i++){
        if (scores[i] > max) {
            max = scores[i];
        }
    }
    return max;
}

int find_min_score(int scores[], int count) {
    if (count == 0) return 0;
    int min = scores[0];

    for (int i =1; i <count; i++){
        if ( scores[i] < min){
            min = scores[i];
        }
    }
    return min;
}

void count_grades(int scores[], int count, int grade_count[]) {
    for (int i = 0; i < count; i++){
        if (scores[i] >= 90) {
            grade_count[0]++; // 優秀
        }
        else if (scores[i] >= 80) {
            grade_count[1]++; // 良好
        }
        else if (scores[i] >= 60) {
            grade_count[2]++; // 及格
        }
        else {
            grade_count[3]++; // 不及格
        }
}
}

void display_students(char names[][MAX_NAME_LENGTH + 1], int scores[], int count) {
    printf("學生資料:\n");
    for (int i = 0; i < count; i++){
        printf("%s: %d\n", names[i], scores[i]);
    }
}

void display_statistics(int scores[], int count){
    printf("===統計結果:===\n");
    printf("總人數: %d\n", count);
    printf("平均成績: %.2f\n", calculate_average(scores, count));
    printf("最高分: %d\n", find_max_score(scores, count));
    printf("最低分: %d\n", find_min_score(scores, count));
    int grade_count[4] = {0}; 
    count_grades(scores, count, grade_count);
    printf("\n等級統計:\n");
    printf("優秀(90-100): %d (%.2f%%)\n", grade_count[0], (double)grade_count[0] / count * 100);
    printf("良好(80-89): %d (%.2f%%)\n", grade_count[1], (double)grade_count[1] / count * 100);
    printf("及格(60-79): %d (%.2f%%)\n", grade_count[2], (double)grade_count[2] / count * 100);
    printf("不及格(<60): %d (%.2f%%)\n", grade_count[3], (double)grade_count[3] / count * 100);
}

int is_valid_score(int score){
    return score >= 0 && score <= 100;
}