# 編譯器設定
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# 目標檔案
TARGET = student_manager
SOURCES = main.c student.c
HEADERS = student.h
OBJECTS = $(SOURCES:.c=.o)

# 預設目標
all: $(TARGET)

# 編譯主程式
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# 編譯目標檔案
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 執行程式
run: $(TARGET)
	./$(TARGET)

# 測試（範例）
test: $(TARGET)
	@echo "執行測試..."
	@echo "3\n張三\n85\n李四\n92\n王五\n78" | ./$(TARGET)

# 清理編譯檔案
clean:
	rm -f $(TARGET) $(OBJECTS)

# 重新編譯
rebuild: clean all

# 安裝（將執行檔複製到指定目錄）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# 顯示幫助資訊
help:
	@echo "可用的目標:"
	@echo "  all      - 編譯程式 (預設)"
	@echo "  run      - 編譯並執行程式"
	@echo "  test     - 執行簡單測試"
	@echo "  clean    - 清理編譯檔案"
	@echo "  rebuild  - 重新編譯"
	@echo "  install  - 安裝程式到系統"
	@echo "  help     - 顯示此幫助資訊"

# 檢查記憶體洩漏（需要安裝valgrind）
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# 程式碼格式化（需要安裝clang-format）
format:
	clang-format -i $(SOURCES) $(HEADERS)

# 靜態分析（需要安裝cppcheck）
analyze:
	cppcheck --enable=all $(SOURCES)

# 建立發佈版本（優化編譯）
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# 建立除錯版本
debug: CFLAGS += -g -DDEBUG
debug: clean $(TARGET)

# 宣告虛假目標
.PHONY: all run test clean rebuild install help valgrind format analyze release debug 