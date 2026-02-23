#include <stdio.h>
#include "student.h"

int main() {
    char names[MAX_STUDENTS][MAX_NAME_LENGTH + 1];
    int scores[MAX_STUDENTS];
    int count = 0; 

    printf("=== score manage system ===\n\n");
    input_students(names, scores, &count);
    printf("\n");
    display_students(names, scores, count);
    printf("\n");
    display_statistics(scores, count);
    printf("\n");  
    
    return 0;
}