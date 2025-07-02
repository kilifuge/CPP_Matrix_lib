CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++20 -g

SRC = $(wildcard s21_*.cpp)
TEST_SRC = $(wildcard tests/s21_*.cpp)

OBJ = $(patsubst %.cpp,%.o,$(SRC))
TEST_OBJ = $(patsubst %.cpp,%.o,$(TEST_SRC))
GCOV_TEST_OBJ = $(patsubst %.cpp,gcov_%.o,$(SRC))

GCOV_FLAGS = --coverage
LIBS = -lgtest -lgtest_main -pthread

all: s21_matrix_oop.a

s21_matrix_oop.a: $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

test: s21_matrix_oop.a $(TEST_OBJ)
	$(CC) $(FLAGS) $(TEST_OBJ) s21_matrix_oop.a -o ./unit_tests $(LIBS)
	./unit_tests

%.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@

%.o: tests/%.cpp
	$(CC) -c $(FLAGS) $< -o $@

gcov_%.o: %.cpp
	$(CC) -c $(FLAGS) $(GCOV_FLAGS) $< -o $@

gcov_report: s21_matrix_oop.a $(GCOV_TEST_OBJ) $(TEST_OBJ)
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(GCOV_TEST_OBJ) $(TEST_OBJ) -o ./gcov_tests $(LIBS)
	./gcov_tests
	lcov -t "s21_matrix_test" -o s21_test.info -c -d . --no-external
	lcov --extract s21_test.info "$(CURDIR)/s21_*.cpp" -o s21_test_filtered.info
	genhtml -o report s21_test_filtered.info

clean:
	rm -rf *.o *.gcno *.gcda *.gcov gcov_tests unit_tests *.info report/ s21_matrix_oop.a tests/*.o

rebuild_gcov: clean all test gcov_report

rebuild: clean all test