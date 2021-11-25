CFLAGS=-Wall -Werror -Wextra
LIBS=-lcheck
GCOV=-fprofile-arcs -ftest-coverage
OBJECTS=s21_bonus.o\
		s21_string.o\
		s21_sscanf.o\
		s21_sprintf.o
SOURSES=s21_bonus.c\
		s21_string.c\
		s21_sscanf.c\
		s21_sprintf.c
all: main
main: clean s21_string.a test gcov_report
s21_string.a: 
	gcc -c $(SOURSES) 
	@ar rcs s21_string.a $(OBJECTS)
test: s21_string.a unit_tests
unit_tests:
	gcc -c unit_tests.c  -o unit_tests.o
	gcc unit_tests.o s21_string.a  -lcheck -o unit_tests.o
	./unit_tests.o

gcov_report: s21_string.a
	@gcc $(GCOV) unit_tests.c  -lcheck $(SOURSES) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.*

clean:
	@rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./sprintf_o ./sscanf_o ./string_o

rebuild: clean all
