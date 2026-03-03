#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int add_book(Book books[], int *count, Book new_book){
        // 檢查 ISBN 是否已存在
    for (int i = 0; i < *count; i++) {
        if (strcmp(books[i].isbn, new_book.isbn) == 0) {
            return 0;   // 已存在
        }
    }

    books[*count] = new_book;
    (*count)++;
    return 1;  // 新增成功
}
    

Book* find_book_by_isbn(Book books[], int count, const char *isbn){
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            return &books[i];
        }
    }
    return NULL; // 未找到
}
int find_books_by_title(Book books[], int count, const char *title, Book results[]){
    int found_count = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(books[i].title, title) != NULL) {
            results[found_count++] = books[i];
        }
    }
    return found_count;
}
void display_books(Book books[], int count){
    printf("ISBN\t\tTitle\t\tAuthor\t\tCategory\tPublish Date\tTotal Copies\tAvailable Copies\tPrice\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%s\t%s\t%s\t%d/%d/%d\t%d\t%d\t%.2f\n",
               books[i].isbn, books[i].title, books[i].author, books[i].category,
               books[i].publish_date.year, books[i].publish_date.month, books[i].publish_date.day,
               books[i].total_copies, books[i].available_copies, books[i].price);
    }
}

int update_book(Book books[], int count, const char *isbn, Book updated_book){
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            books[i] = updated_book;
            return 1;  // 更新成功
        }
    }
    return 0;  // 未找到
}