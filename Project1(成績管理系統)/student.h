#ifndef STUDENT_H
#define STUDENT_H

// 常數定義
#define MAX_STUDENTS 30
#define MAX_NAME_LENGTH 20
#define GRADE_LEVELS 4

// 等級定義
#define EXCELLENT 90  // 優秀
#define GOOD 80       // 良好
#define PASS 60       // 及格
#define FAIL 0        // 不及格

// 函式宣告

/**
 * 輸入學生資料
 * @param names 學生姓名陣列
 * @param scores 學生成績陣列
 * @param count 學生人數指標
 */
void input_students(char names[][MAX_NAME_LENGTH + 1], int scores[], int *count);

/**
 * 計算平均成績
 * @param scores 成績陣列
 * @param count 學生人數
 * @return 平均成績
 */
double calculate_average(int scores[], int count);

/**
 * 找出最高分
 * @param scores 成績陣列
 * @param count 學生人數
 * @return 最高分
 */
int find_max_score(int scores[], int count);

/**
 * 找出最低分
 * @param scores 成績陣列
 * @param count 學生人數
 * @return 最低分
 */
int find_min_score(int scores[], int count);

/**
 * 統計各等級人數
 * @param scores 成績陣列
 * @param count 學生人數
 * @param grade_count 等級統計陣列 [優秀, 良好, 及格, 不及格]
 */
void count_grades(int scores[], int count, int grade_count[]);

/**
 * 顯示所有學生資料
 * @param names 學生姓名陣列
 * @param scores 學生成績陣列
 * @param count 學生人數
 */
void display_students(char names[][MAX_NAME_LENGTH + 1], int scores[], int count);

/**
 * 顯示統計結果
 * @param scores 成績陣列
 * @param count 學生人數
 */
void display_statistics(int scores[], int count);

/**
 * 驗證成績是否有效
 * @param score 成績
 * @return 1表示有效，0表示無效
 */
int is_valid_score(int score);

/**
 * 根據成績獲取等級字串
 * @param score 成績
 * @return 等級字串
 */
const char* get_grade_string(int score);

#endif 