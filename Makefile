override COMPILER_OPTIONS := -lstdc++ -std=c++2a -fconcepts

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