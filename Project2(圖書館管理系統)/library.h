#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 1000
#define MAX_MEMBERS 500
#define MAX_RECORDS 2000



typedef struct {
    int year;
    int month;
    int day;
} Date;


typedef struct {
    char isbn[14];
    char title[100];
    char author[50];
    char category[30];
    Date publish_date;
    int total_copies;
    int available_copies;
    float price;
} Book;


typedef struct {
    int member_id;
    char name[50];
    char email[50];
    char phone[15];
    Date join_date;
    int borrowed_count;
} Member;


typedef struct {
    int record_id;
    int member_id;
    char isbn[14];
    Date borrow_date;
    Date due_date;
    Date return_date;
    int is_returned;
} BorrowRecord;


// Book 模組

int add_book(Book books[], int *count, Book new_book);

Book* find_book_by_isbn(Book books[], int count, const char *isbn);

int find_books_by_title(Book books[], int count,
                        const char *title, Book results[]);

void display_books(Book books[], int count);

int update_book(Book books[], int count,
                const char *isbn, Book updated_book);

// Member 

int add_member(Member members[], int *count, Member new_member);

Member* find_member_by_id(Member members[], int count, int member_id);

void display_members(Member members[], int count);



// Borrow 

int borrow_book(Book books[], int book_count,
                Member members[], int member_count,
                BorrowRecord records[], int *record_count,
                int member_id,
                const char *isbn,
                Date borrow_date,
                Date due_date);

int return_book(Book books[], int book_count,
                Member members[], int member_count,
                BorrowRecord records[], int record_count,
                int member_id,
                const char *isbn);

void check_overdue_books(Book books[], int book_count,
                         Member members[], int member_count,
                         BorrowRecord records[], int record_count,
                         Date today);


// Utils 

int compare_dates(Date d1, Date d2);

int days_between(Date d1, Date d2);

int is_valid_date(Date date);

int strcasecmp_custom(const char *s1, const char *s2);

// 檔案讀寫txt

void load_books(Book books[], int *count);
void save_books(Book books[], int count);

void load_members(Member members[], int *count);
void save_members(Member members[], int count);

void load_records(BorrowRecord records[], int *count);
void save_records(BorrowRecord records[], int count);

#endif