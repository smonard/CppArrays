#include <stdlib.h>
#include <iostream>
#include <list>

using namespace std;

template <typename T>
class enhanced_list: public list<T> {
  typedef  std::allocator<T> Allocator; 
  public:

    enhanced_list<T>( std::initializer_list<T> init, const Allocator& alloc = Allocator()): list<T>( init, alloc) {}

    template <class Predicate>
    void each(Predicate function){
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
         function(*it);
      }     
    }

    template <class Predicate>    
    uint64_t count(Predicate predicate){
      uint64_t count = 0;
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
         if(predicate(*it))
          count++;
      }     
      return count;
    }
};

