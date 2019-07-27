#include "src/enhanced_list.cpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
  enhanced_list<int> int_list{ 1, 2, 3, 4 };
  auto print_values = [] (const auto& number) { cout << number << endl; };
  
  cout << "Content list: " << endl;
  int_list.each(print_values);
  cout << endl << "Even values: " << int_list.count([] (const int& number) { return number % 2 == 0; } ) << endl;

  return 0;
}
