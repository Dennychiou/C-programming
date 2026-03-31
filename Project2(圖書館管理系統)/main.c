#include <stdio.h>
#include "library.h"

int main() {

    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    BorrowRecord records[MAX_RECORDS];

    int book_count = 0;
    int member_count = 0;
    int record_count = 0;

    //  啟動時自動讀檔
    load_books(books, &book_count);
    load_members(members, &member_count);
    load_records(records, &record_count);

    printf("Books loaded: %d\n", book_count);
    printf("Members loaded: %d\n", member_count);
    printf("Records loaded: %d\n", record_count);   

    int choice;

    while (1) {

        printf("\n=== 圖書館管理系統 ===\n");
        printf("1. 新增圖書\n");
        printf("2. 新增會員\n");
        printf("3. 借書\n");
        printf("4. 還書\n");
        printf("5. 逾期檢查\n");
        printf("0. 離開\n");
        printf("請選擇: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("系統關閉\n");
            break;
        }

        if (choice == 1) {

            Book b;

            printf("\n=== 新增圖書 ===\n");

            printf("ISBN: ");
            scanf("%s", b.isbn);

            printf("書名: ");
            scanf(" %[^\n]", b.title);

            printf("作者: ");
            scanf(" %[^\n]", b.author);

            printf("分類: ");
            scanf(" %[^\n]", b.category);

            printf("出版日期 (年 月 日): ");
            scanf("%d %d %d",
                  &b.publish_date.year,
                  &b.publish_date.month,
                  &b.publish_date.day);

            printf("總數量: ");
            scanf("%d", &b.total_copies);

            b.available_copies = b.total_copies;

            printf("價格: ");
            scanf("%f", &b.price);

            if (add_book(books, &book_count, b)) {
                printf("圖書新增成功！\n");
                save_books(books, book_count); 
            } else {
                printf("新增失敗（ISBN 重複）\n");
            }
        }


        else if (choice == 2) {

            Member m;

            printf("\n=== 新增會員 ===\n");

            printf("會員編號: ");
            scanf("%d", &m.member_id);

            printf("姓名: ");
            scanf(" %[^\n]", m.name);

            printf("Email: ");
            scanf("%s", m.email);

            printf("電話: ");
            scanf("%s", m.phone);

            printf("加入日期 (年 月 日): ");
            scanf("%d %d %d",
                  &m.join_date.year,
                  &m.join_date.month,
                  &m.join_date.day);

            m.borrowed_count = 0;

            if (add_member(members, &member_count, m)) {
                printf("會員新增成功！\n");
                save_members(members, member_count);  
            } else {
                printf("新增失敗（ID 重複）\n");
            }
        }


        else if (choice == 3) {

            int member_id;
            char isbn[20];
            Date borrow_date, due_date;

            printf("\n=== 借閱圖書 ===\n");

            printf("會員編號: ");
            scanf("%d", &member_id);

            printf("ISBN: ");
            scanf("%s", isbn);

            printf("借閱日期 (年 月 日): ");
            scanf("%d %d %d",
                  &borrow_date.year,
                  &borrow_date.month,
                  &borrow_date.day);

            printf("到期日期 (年 月 日): ");
            scanf("%d %d %d",
                  &due_date.year,
                  &due_date.month,
                  &due_date.day);

            if (borrow_book(books, book_count,
                            members, member_count,
                            records, &record_count,
                            member_id,
                            isbn,
                            borrow_date,
                            due_date)) {

                printf("借閱成功！\n");

                save_books(books, book_count);
                save_members(members, member_count);
                save_records(records, record_count);
            } else {
                printf("借閱失敗！\n");
            }
        }


        else if (choice == 4) {

            int member_id;
            char isbn[20];

            printf("\n=== 還書 ===\n");

            printf("會員編號: ");
            scanf("%d", &member_id);

            printf("ISBN: ");
            scanf("%s", isbn);

            if (return_book(books, book_count,
                            members, member_count,
                            records, record_count,
                            member_id,
                            isbn)) {

                printf("還書成功！\n");

                save_books(books, book_count);
                save_members(members, member_count);
                save_records(records, record_count);

            } else {
                printf("還書失敗！\n");
            }
        }


        else if (choice == 5) {

            Date today;

            printf("\n請輸入今天日期 (年 月 日): ");
            scanf("%d %d %d",
                  &today.year,
                  &today.month,
                  &today.day);

            check_overdue_books(books, book_count,
                                members, member_count,
                                records, record_count,
                                today);
        }

        else {
            printf("無效選項\n");
        }
    }
    return 0;
}
