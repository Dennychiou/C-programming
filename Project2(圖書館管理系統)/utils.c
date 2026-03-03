#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "library.h"

int compare_dates(Date d1, Date d2) {
    if (d1.year != d2.year)
        return d1.year - d2.year;
    if (d1.month != d2.month)
        return d1.month - d2.month;
    return d1.day - d2.day;
}

int is_valid_date(Date date) {

    if (date.year < 1 || date.month < 1 || date.month > 12 || date.day < 1)
        return 0;

    int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ((date.year % 4 == 0 && date.year % 100 != 0) ||
        (date.year % 400 == 0)) {
        days_in_month[1] = 29;
    }

    if (date.day > days_in_month[date.month - 1])
        return 0;

    return 1;
}

int date_to_days(Date d) {
    int days = d.year * 365 + d.day;

    int month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ((d.year % 4 == 0 && d.year % 100 != 0) ||
        (d.year % 400 == 0)) {
        month_days[1] = 29;
    }

    for (int i = 0; i < d.month - 1; i++)
        days += month_days[i];

    return days;
}

int days_between(Date d1, Date d2) {
    return abs(date_to_days(d2) - date_to_days(d1));
}

int strcasecmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = tolower(*s1);
        char c2 = tolower(*s2);

        if (c1 != c2)
            return c1 - c2;

        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void load_books(Book books[], int *count) {
    FILE *fp = fopen("books.txt", "r");
    if (!fp) {
        printf("books.txt not found!\n");
        return;
    }

    char line[512];
    *count = 0;

    while (fgets(line, sizeof(line), fp)) {

        if (sscanf(line,
            "%s %s %s %s %d %d %d %d %d %f",
            books[*count].isbn,
            books[*count].title,
            books[*count].author,
            books[*count].category,
            &books[*count].publish_date.year,
            &books[*count].publish_date.month,
            &books[*count].publish_date.day,
            &books[*count].total_copies,
            &books[*count].available_copies,
            &books[*count].price) == 10) {

            (*count)++;
        }
    }

    fclose(fp);
}

void save_books(Book books[], int count) {
    FILE *fp = fopen("books.txt", "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %s|%s|%s|%d %d %d %d %d %.2f\n",
            books[i].isbn,
            books[i].title,
            books[i].author,
            books[i].category,
            books[i].publish_date.year,
            books[i].publish_date.month,
            books[i].publish_date.day,
            books[i].total_copies,
            books[i].available_copies,
            books[i].price);
    }

    fclose(fp);
}

void load_members(Member members[], int *count) {
    FILE *fp = fopen("members.txt", "r");
    if (!fp) {
        printf("members.txt not found!\n");
        return;
    }

    char line[512];
    *count = 0;

    while (fgets(line, sizeof(line), fp)) {

        if (sscanf(line,
            "%d %s %s %s %d %d %d %d",
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

void load_records(BorrowRecord records[], int *count) {
    FILE *fp = fopen("records.txt", "r");
    if (!fp) return;

    *count = 0;

    while (fscanf(fp, "%d %d %s %d %d %d %d %d %d %d %d %d %d\n",
           &records[*count].record_id,
           &records[*count].member_id,
           records[*count].isbn,
           &records[*count].borrow_date.year,
           &records[*count].borrow_date.month,
           &records[*count].borrow_date.day,
           &records[*count].due_date.year,
           &records[*count].due_date.month,
           &records[*count].due_date.day,
           &records[*count].return_date.year,
           &records[*count].return_date.month,
           &records[*count].return_date.day,
           &records[*count].is_returned) == 13) {

        (*count)++;
    }

    fclose(fp);
}

void save_records(BorrowRecord records[], int count) {
    FILE *fp = fopen("records.txt", "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %d %s %d %d %d %d %d %d %d %d %d %d\n",
            records[i].record_id,
            records[i].member_id,
            records[i].isbn,
            records[i].borrow_date.year,
            records[i].borrow_date.month,
            records[i].borrow_date.day,
            records[i].due_date.year,
            records[i].due_date.month,
            records[i].due_date.day,
            records[i].return_date.year,
            records[i].return_date.month,
            records[i].return_date.day,
            records[i].is_returned);
    }

    fclose(fp);
}