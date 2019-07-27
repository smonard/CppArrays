override COMPILER_OPTIONS := -lstdc++ -std=c++2a -fconcepts
override VALGRIND_OPTIONS := --tool=memcheck --leak-check=yes

clear:
	rm -rf build/*

build: clear
	gcc $(COMPILER_OPTIONS) main.cpp -o build/enhanced_list_example

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