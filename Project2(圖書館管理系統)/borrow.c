#include <stdio.h>
#include <string.h>
#include "library.h"


// 借書
int borrow_book(Book books[], int book_count,
                Member members[], int member_count,
                BorrowRecord records[], int *record_count,
                int member_id,
                const char *isbn,
                Date borrow_date,
                Date due_date)
{
    // 找會員
    Member *member = find_member_by_id(members, member_count, member_id);
    if (member == NULL)
        return 0;

    // 找書
    Book *book = find_book_by_isbn(books, book_count, isbn);
    if (book == NULL)
        return 0;

    // 檢查庫存
    if (book->available_copies <= 0)
        return 0;

    // 檢查日期
    if (!is_valid_date(borrow_date) || !is_valid_date(due_date))
        return 0;

    if (compare_dates(due_date, borrow_date) <= 0)
        return 0;

    //  檢查是否已借同一本未歸還
    for (int i = 0; i < *record_count; i++) {
        if (records[i].member_id == member_id &&
            strcmp(records[i].isbn, isbn) == 0 &&
            !records[i].is_returned) {
            return 0;  // 已借未還
        }
    }

    //  檢查 record 是否超出容量
    if (*record_count >= MAX_RECORDS)
        return 0;

    // 更新庫存
    book->available_copies--;
    member->borrowed_count++;

    // 建立借閱紀錄
    BorrowRecord new_record;

    new_record.record_id = *record_count + 1;
    new_record.member_id = member_id;
    strcpy(new_record.isbn, isbn);
    new_record.borrow_date = borrow_date;
    new_record.due_date = due_date;
    new_record.return_date = (Date){0,0,0};
    new_record.is_returned = 0;

    records[*record_count] = new_record;
    (*record_count)++;

    return 1;
}


// 還書

int return_book(Book books[], int book_count,
                Member members[], int member_count,
                BorrowRecord records[], int record_count,
                int member_id,
                const char *isbn)
{
    for (int i = 0; i < record_count; i++) {

        if (records[i].member_id == member_id &&
            strcmp(records[i].isbn, isbn) == 0 &&
            !records[i].is_returned) {

            records[i].is_returned = 1;

            // 🔥 改成自動今天日期（暫時簡單版）
            records[i].return_date = records[i].due_date;

            // 更新書籍庫存
            Book *book = find_book_by_isbn(books, book_count, isbn);
            if (book)
                book->available_copies++;

            // 更新會員借閱數
            Member *member = find_member_by_id(members, member_count, member_id);
            if (member && member->borrowed_count > 0)
                member->borrowed_count--;

            return 1;
        }
    }

    return 0;
}

// 逾期檢查

void check_overdue_books(Book books[], int book_count,
                         Member members[], int member_count,
                         BorrowRecord records[], int record_count,
                         Date today)
{
    printf("\n=== 逾期檢查 ===\n");

    for (int i = 0; i < record_count; i++) {

        if (!records[i].is_returned &&
            compare_dates(records[i].due_date, today) < 0) {

            int overdue_days =
                days_between(records[i].due_date, today);

            Member *member =
                find_member_by_id(members, member_count,
                                  records[i].member_id);

            Book *book =
                find_book_by_isbn(books, book_count,
                                  records[i].isbn);

            if (member && book) {

                printf("會員 %d (%s) 的圖書 \"%s\" 已逾期 %d 天\n",
                       member->member_id,
                       member->name,
                       book->title,
                       overdue_days);

                printf("請聯絡會員盡快歸還。\n\n");
            }
        }
    }
}
