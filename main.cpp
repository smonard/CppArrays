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
  cout << endl << "Even values of original list: " << int_list.count([] (const int& number) { return number % 2 == 0; } ) << endl;
  
  auto mapped_list = int_list
          ._filter(is_prime)
          ->_map([&] (const int& number) {  
            ostringstream element;
            element << "result for " << number << " = " << to_string(factorial(number));
            return element.str();
          });
          
  auto mapped_list_2 = (*mapped_list).map([] (const string& message) {  
            ostringstream element;
            element << "The " << message;
            return element.str();
          });

  cout << "Contents of the new list: " << endl;
  void (*print_values)(const string&) = [] (const string& result) { cout << result << endl; };
  (*mapped_list_2).each(print_values);
  
  return 0;
}
