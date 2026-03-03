#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int add_member(Member members[], int *count, Member new_member){

    for (int i = 0; i < *count; i++) {
        if (members[i].member_id == new_member.member_id) {
            return 0;   
        }
    }

    members[*count] = new_member;
    (*count)++;
    return 1;
}

Member* find_member_by_id(Member members[], int count, int member_id){
    for (int i = 0; i < count; i++) {
        if (members[i].member_id == member_id) {
            return &members[i];
        }
    }
    return NULL; 
}

void display_members(Member members[], int count){
    printf("Member ID\tName\tEmail\tPhone\tJoin Date\tBorrowed Count\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%s\t%s\t%d/%d/%d\t%d\n",
               members[i].member_id, members[i].name, members[i].email, members[i].phone,
               members[i].join_date.year, members[i].join_date.month, members[i].join_date.day,
               members[i].borrowed_count);
    }
}

void load_members(Member members[], int *count) {
    FILE *fp = fopen("members.txt", "r");
    if (!fp) return;

    *count = 0;

    while (fscanf(fp, "%d %[^|]|%s|%s|%d %d %d %d\n",
           &members[*count].member_id,
           members[*count].name,
           members[*count].email,
           members[*count].phone,
           &members[*count].join_date.year,
           &members[*count].join_date.month,
           &members[*count].join_date.day,
           &members[*count].borrowed_count) == 8) {

        (*count)++;
    }

    fclose(fp);
}

void save_members(Member members[], int count) {
    FILE *fp = fopen("members.txt", "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s|%s|%s|%d %d %d %d\n",
            members[i].member_id,
            members[i].name,
            members[i].email,
            members[i].phone,
            members[i].join_date.year,
            members[i].join_date.month,
            members[i].join_date.day,
            members[i].borrowed_count);
    }

    fclose(fp);
}

