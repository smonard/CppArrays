# CppArrays

C++ enhanced lists. Just to support handy methods such as each or count.

## Usage


### Each 

```c++
enhanced_list<int> int_list{ 1, 2, 3, 4 };
void (*print_values)(const int&) = [] (const int& number) { std::cout << number << std::endl; };
std::cout << "Content list: " << std::endl;
int_list.each(print_values);
```
Alternatively It could be used:
```c++
int_list.each([] (const auto& number) { std::cout << number << std::endl; });
```
### Count

```c++
enhanced_list<int> int_list{ 1, 2, 3, 4 };
bool (*count_even_values_predicate)(const int&) = [] (const int& number) { return number % 2 == 0; };
unsigned long int even_count = int_list.count(count_even_values_predicate);
std::cout << std::endl << "Even values: " << even_count << std::endl;
```
Alternatively It could be used:
```c++
unsigned long int even_count = int_list.count([] (const int& number) { return number % 2 == 0; } );
```

## Project auto-tasks

Described in `Makefile`

### Run examples

`make run`

### Run tests

`make run_tests`

### Clear generated files 

`make clear`

### Run valgrind checks

`make check` main check
`make check_tests` tests check