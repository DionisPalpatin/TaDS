SRC_DIR := src
OUT_DIR := out
UNIT_TEST_SRC_DIR := unit_tests
SCRIPTS := func_tests/scripts

# Флаги компилятора
COMPILER_FLAGS_DEBUG := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -g3
UNIT_TESTS_LINKING_FLAGS := -lcheck -lpthread -lrt -lm -lsubunit
HEADERS := -I inc

# Получаемые исполняемые файлы
TARGET := app.exe
TARGET_UNIT_TESTS := unit_tests.exe

# Файлы стандартной версии программы
OBJ_FILES_LIST := sort.o file.o array.o main.o
OBJ_FILES = $(addprefix $(OUT_DIR)/, $(OBJ_FILES_LIST))

# Файлы юнит-тестов
UNIT_TESTS_OBJ_FILES_LIST := check_sort.o check_file.o check_array.o check_main.o sort.o file.o array.o
UNIT_TESTS_OBJ_FILES := $(addprefix $(OUT_DIR)/, $(UNIT_TESTS_OBJ_FILES_LIST))


.PHONY: unit func clean


$(OUT_DIR):
	@mkdir -p $@


# Блок с правилами для получения объектных файлов стандартной версии программы
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(COMPILER_FLAGS_DEBUG) $(HEADERS) -o $@ -c $<


# Блок с правилами для получения объектных файлов юнит-тестов
$(OUT_DIR)/%.o: $(UNIT_TEST_SRC_DIR)/%.c
	@gcc $(COMPILER_FLAGS_DEBUG) $(HEADERS) -o $@ -c $<


# Получение итогового файла
$(TARGET): $(OUT_DIR) $(OBJ_FILES)
	@gcc $(OBJ_FILES) -o $(TARGET)

$(TARGET_UNIT_TESTS): $(OUT_DIR) $(UNIT_TESTS_OBJ_FILES)
	@gcc $(UNIT_TESTS_OBJ_FILES) -o $(TARGET_UNIT_TESTS) $(UNIT_TESTS_LINKING_FLAGS)


# Запуск функциональных тестов
func: $(TARGET)
	@cd $(SCRIPTS); ./func_tests.sh


valgrind_func: $(TARGET)
	@export USE_VALGRIND=1; cd $(SCRIPTS); ./func_tests.sh


# Запуск модульных тестов
unit: $(TARGET_UNIT_TESTS)
	@./unit_tests.exe


valgrind_unit: $(TARGET_UNIT_TESTS)
	@valgrind -q --leak-check=full --track-origins=yes ./unit_tests.exe


# Очистка директории от временных и/или полученных во время выполнения команд файлов
clean:
	@rm -rf ./out/ *.exe