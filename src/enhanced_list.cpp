#include <stdlib.h>
#include <iostream>
#include <list>
#include <memory>

using namespace std;

template <typename T>
class enhanced_list: public list<T> {
  typedef  std::allocator<T> Allocator;

  public:

    enhanced_list<T>( std::initializer_list<T> init, const Allocator& alloc = Allocator()): list<T>( init, alloc) {}
    enhanced_list<T>(): list<T>() {}

    template <typename Predicate>
    void each(Predicate function){
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
         function(*it);
      }     
    }

    template <typename Predicate>    
    uint64_t count(Predicate predicate){
      uint64_t count = 0;
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
         if(predicate(*it))
          count++;
      }     
      return count;
    }
    
    template <typename Predicate>    
    enhanced_list<T> * filter(Predicate predicate) {
      (*this).remove_if([&] (const T& element) -> bool { return !predicate(element); });
      return this;
    }

    template <typename Predicate> 
    unique_ptr<enhanced_list<T>> get_new_filtered(Predicate predicate) {
      unique_ptr<enhanced_list<T>> new_list = make_unique<enhanced_list<T>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
         if(predicate(*it)){
            (*new_list).push_back(*it);
         }
      }     
      return new_list;
    }

    template<typename R, class Predicate>
    unique_ptr<enhanced_list<R>> map(Predicate predicate) {
      unique_ptr<enhanced_list<R>> new_list = make_unique<enhanced_list<R>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
         (*new_list).push_back(predicate(*it));
      }
      return new_list;
    }

    template<class Predicate>
    auto map(Predicate predicate) {
      auto new_list = make_unique<enhanced_list<decltype(predicate(declval<T>()))>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
         (*new_list).push_back(predicate(*it));
      }
      return new_list;
    }

};

