# 第二章專案：圖書館管理系統

## 專案描述

設計並實作一個圖書館管理系統，運用結構來組織和管理複雜的資料。此專案將深入運用結構的各種特性，包括：
- 結構的定義和使用
- 巢狀結構設計
- 結構陣列操作
- 結構與函式的配合
- 記憶體管理

## 功能需求

### 核心功能
1. **圖書資料管理**：新增、修改、刪除圖書資料
2. **會員資料管理**：管理圖書館會員資訊
3. **借閱系統**：處理圖書借閱和歸還
4. **搜尋功能**：根據不同條件搜尋圖書
5. **統計報表**：顯示借閱統計和圖書狀態

### 資料結構設計

#### 日期結構
```c
typedef struct {
    int year;
    int month;
    int day;
} Date;
```

#### 圖書結構
```c
typedef struct {
    char isbn[14];          // ISBN號碼
    char title[100];        // 書名
    char author[50];        // 作者
    char category[30];      // 分類
    Date publish_date;      // 出版日期
    int total_copies;       // 總數量
    int available_copies;   // 可借數量
    float price;           // 價格
} Book;
```

#### 會員結構
```c
typedef struct {
    int member_id;          // 會員編號
    char name[50];          // 姓名
    char email[50];         // 電子郵件
    char phone[15];         // 電話
    Date join_date;         // 加入日期
    int borrowed_count;     // 目前借閱數量
} Member;
```

#### 借閱記錄結構
```c
typedef struct {
    int record_id;          // 記錄編號
    int member_id;          // 會員編號
    char isbn[14];          // 圖書ISBN
    Date borrow_date;       // 借閱日期
    Date due_date;          // 到期日期
    Date return_date;       // 歸還日期（未歸還時為{0,0,0}）
    int is_returned;        // 是否已歸還
} BorrowRecord;
```

## 技術要求

### 1. 必須實作的函式

#### 圖書管理函式
```c
// 新增圖書
int add_book(Book books[], int *count, Book new_book);

// 搜尋圖書（根據ISBN）
Book* find_book_by_isbn(Book books[], int count, const char *isbn);

// 搜尋圖書（根據書名）
int find_books_by_title(Book books[], int count, const char *title, Book results[]);

// 顯示所有圖書
void display_books(Book books[], int count);

// 更新圖書資料
int update_book(Book books[], int count, const char *isbn, Book updated_book);
```

#### 會員管理函式
```c
// 新增會員
int add_member(Member members[], int *count, Member new_member);

// 搜尋會員
Member* find_member_by_id(Member members[], int count, int member_id);

// 顯示所有會員
void display_members(Member members[], int count);
```

#### 借閱管理函式
```c
// 借閱圖書
int borrow_book(Book books[], int book_count, Member members[], int member_count,
                BorrowRecord records[], int *record_count, 
                int member_id, const char *isbn);

// 歸還圖書
int return_book(Book books[], int book_count, 
                BorrowRecord records[], int record_count,
                int member_id, const char *isbn);

// 顯示借閱記錄
void display_borrow_records(BorrowRecord records[], int count);

// 檢查逾期書籍
void check_overdue_books(BorrowRecord records[], int count);
```

#### 工具函式
```c
// 日期比較
int compare_dates(Date d1, Date d2);

// 計算兩個日期之間的天數差
int days_between(Date d1, Date d2);

// 驗證日期有效性
int is_valid_date(Date date);

// 字串比較（忽略大小寫）
int strcasecmp_custom(const char *s1, const char *s2);
```

### 2. 使用者介面
實作一個選單驅動的介面：
```
=== 圖書館管理系統 ===
1. 圖書管理
   1.1 新增圖書
   1.2 搜尋圖書
   1.3 顯示所有圖書
   1.4 修改圖書資料
2. 會員管理
   2.1 新增會員
   2.2 搜尋會員
   2.3 顯示所有會員
3. 借閱管理
   3.1 借閱圖書
   3.2 歸還圖書
   3.3 顯示借閱記錄
   3.4 檢查逾期書籍
4. 統計報表
   4.1 借閱統計
   4.2 熱門圖書
5. 結束程式
請選擇功能：
```

## 檔案結構

```
Project/
├── src/
│   ├── main.c          # 主程式
│   ├── book.c          # 圖書管理相關函式
│   ├── member.c        # 會員管理相關函式
│   ├── borrow.c        # 借閱管理相關函式
│   └── utils.c         # 工具函式
├── include/
│   ├── library.h       # 主要標頭檔案
│   ├── book.h          # 圖書相關宣告
│   ├── member.h        # 會員相關宣告
│   ├── borrow.h        # 借閱相關宣告
│   └── utils.h         # 工具函式宣告
├── data/
│   ├── books.txt       # 圖書資料檔案
│   ├── members.txt     # 會員資料檔案
│   └── records.txt     # 借閱記錄檔案
├── Makefile           # 編譯規則
└── README.md          # 說明文件
```

## 資料儲存格式

### books.txt 格式
```
ISBN,Title,Author,Category,PublishYear,PublishMonth,PublishDay,TotalCopies,AvailableCopies,Price
9789861234567,C程式設計,譚浩強,程式設計,2020,3,15,5,3,450.00
9789867895432,資料結構,蔡文能,電腦科學,2019,8,20,3,1,520.00
```

### members.txt 格式
```
MemberID,Name,Email,Phone,JoinYear,JoinMonth,JoinDay,BorrowedCount
1001,張三,zhang@email.com,0912345678,2023,1,15,2
1002,李四,li@email.com,0923456789,2023,2,20,0
```

### records.txt 格式
```
RecordID,MemberID,ISBN,BorrowYear,BorrowMonth,BorrowDay,DueYear,DueMonth,DueDay,ReturnYear,ReturnMonth,ReturnDay,IsReturned
1,1001,9789861234567,2023,11,1,2023,11,15,2023,11,10,1
2,1001,9789867895432,2023,11,5,2023,11,19,0,0,0,0
```

## 範例輸出

```
=== 新增圖書 ===
ISBN: 9789861234567
書名: C程式設計
作者: 譚浩強
分類: 程式設計
出版日期 (年 月 日): 2020 3 15
總數量: 5
價格: 450.00
圖書新增成功！

=== 借閱圖書 ===
會員編號: 1001
ISBN: 9789861234567
借閱日期: 2023/11/1
到期日期: 2023/11/15
借閱成功！

=== 逾期檢查 ===
會員 1002 (李四) 的圖書 "資料結構" 已逾期 5 天
請聯絡會員盡快歸還。
```

## 評分標準

| 項目 | 分數 | 說明 |
|------|------|------|
| 結構設計 | 25% | 結構定義合理、成員齊全 |
| 功能實作 | 30% | 各項功能正常運作 |
| 程式結構 | 20% | 模組化設計、函式規劃 |
| 錯誤處理 | 15% | 輸入驗證、異常處理 |
| 使用者介面 | 10% | 操作友善、資訊清楚 |

## 擴展挑戰（選擇性）

1. **檔案持久化**：實作資料的儲存和載入
2. **進階搜尋**：支援複合條件搜尋
3. **罰款系統**：逾期罰款計算
4. **預約系統**：書籍預約功能
5. **資料分析**：借閱趨勢分析
6. **備份功能**：資料備份和還原

## 開發建議

1. **分階段開發**：先實作基本的結構和單一功能
2. **測試驅動**：每完成一個函式就測試
3. **模組化設計**：將相關功能分組到不同檔案
4. **文檔註解**：為每個函式寫清楚的註解
5. **錯誤處理**：考慮各種邊界情況和錯誤輸入
 