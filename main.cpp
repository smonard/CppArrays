#include "src/enhanced_list.cpp"
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;

int factorial(const int& number) {
  return (number == 1) ? 1 :  number * (factorial(number - 1));
}

bool is_prime(const int& number) {
  int counter = 0;
  for (int iterator_number = 1; iterator_number <= number; iterator_number++) {
    if (number % iterator_number == 0) {
      counter++;
    }
  }
  return counter == 2;
}

int main() {
  enhanced_list<int> int_list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  std::cout << endl << "Even values from original list: " << int_list.count([] (const int& number) { return number % 2 == 0; } ) << endl;
  
  auto mapped_list = int_list
          ._filter(is_prime)
          ->_map([] (const int& number) {  
            ostringstream element;
            element << "result for " << number << " = " << to_string(factorial(number));
            return element.str();
          })->_map([] (const string& message) {  
            ostringstream element;
            element << "The " << message;
            return element.str();
          });

  std::cout << "Contents of the new list: " << endl;
  void (*print_values)(const string&) = [] (const string& result) { std::cout << result << endl; };
  (*mapped_list).each(print_values);
  
  return 0;
}
