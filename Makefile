CXX = g++ -g -Wall -Werror -Wextra -std=c++17

all:install test gcov_report dvi dist

install:
	-mkdir build
	cd build && qmake ../Calc_V2/Calc_V2.pro && make
	cd build && cp -r Calc_V2.app ~/Desktop
	rm -drf build

uninstall:
	rm -rf ~/Desktop/Calc_V2.app ~/Desktop/Calc_V2.tar.gz

dvi:
	open INSTRUCTION.md

dist: uninstall install
	tar -cvzf ~/Desktop/Calc_V2.tar.gz ~/Desktop/Calc_V2.app
	rm -rf ~/Desktop/Calc_V2.app


test:
	$(CXX) -lgtest test.cc Calc_V2/model/SmartCalc.cc Calc_V2/model/PolishNotation.cc --coverage -o test
	./test

gcov_report: clean test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info    
	open ./report/index.html
	rm -rf *.o *.a *.out *gcda *.info *.gcno

clean:
	rm -rf *.o *.a *.out *gcda *.info test report *.dSYM *.gcno run_test

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i Calc_V2/*/*.cc Calc_V2/*/*.h
	clang-format -n Calc_V2/*/*.cc Calc_V2/*/*.h
	rm .clang-format