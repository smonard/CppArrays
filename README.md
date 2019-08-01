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
### Filter

```c++
enhanced_list<int> int_list{ 1, 2, 3, 4 };
bool (*even_values_predicate)(const int&) = [] (const int& number) { return number % 2 == 0; };
int_list.filter(even_values_predicate); // Gets the filtering performed on the same list, returns a pointer to itself
int_list.get_new_filtered(even_values_predicate); // Gets a new list containing only the elements satisfying the predicate 
                                                  // returns a unique pointer to the new list
```
Alternatively It could be used: (so variable capturing may be used)
```c++
int_list.filter([&] (const int& number) { return number % outer_var == 0; }); //or
int_list.get_new_filtered([&] (const int& number) { return number % outer_var == 0; });
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