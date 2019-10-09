override COMPILER_OPTIONS := -lstdc++ -std=c++2a -fconcepts
override VALGRIND_OPTIONS := --tool=memcheck --leak-check=yes -s
override SOURCES := src/enhanced_list.cpp

clear:
	rm -rf build/*

lib: clear
	gcc -c $(COMPILER_OPTIONS) $(SOURCES) -o build/libcpparrays.a

build: clear
	gcc $(COMPILER_OPTIONS) main.cpp $(SOURCES) -o build/enhanced_list_example

build_tests: clear
	gcc $(COMPILER_OPTIONS) tests/run_tests.cpp -o build/tests_runner

run_tests: build_tests
	build/tests_runner

run: build
	build/enhanced_list_example

check: build
	valgrind $(VALGRIND_OPTIONS) build/enhanced_list_example

check_tests: build_tests
	valgrind $(VALGRIND_OPTIONS) build/tests_runner

install: run
