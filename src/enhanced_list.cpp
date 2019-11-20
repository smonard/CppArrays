#include <stdlib.h>
#include <iostream>
#include <list>
#include <memory>

using namespace std;

template <typename T>
class enhanced_list: public list<T> {
  typedef std::allocator<T> Allocator;
  typedef std::size_t size_type;

  public:

    enhanced_list<T>(): list<T>() {}
    
    explicit enhanced_list<T>( const Allocator& alloc ): list<T>(alloc) {}
    
    // until C++11
    // explicit enhanced_list<T>( size_type count, const T& value = T(), const Allocator& alloc = Allocator()): list<T>( count, value, alloc ) {}
    
    enhanced_list<T>( size_type count, const T& value, const Allocator& alloc = Allocator()): list<T>( count, value, alloc ) {}
    
    // until C++14
    // explicit enhanced_list<T>( size_type count ): list<T>( count ) {}
    
    explicit enhanced_list<T>( size_type count, const Allocator& alloc = Allocator() ): list<T>(count, alloc) {}
    
    template< class InputIt >
    enhanced_list<T>( InputIt first, InputIt last, const Allocator& alloc = Allocator() ): list<T>(first, last, alloc) {}
    
    enhanced_list<T>( const list<T>& other ): list<T>(other) {}
    
    enhanced_list<T>( const list<T>& other, const Allocator& alloc ): list<T>(other, alloc) {}
    
    enhanced_list<T>( list<T>&& other ): list<T>(other) {}
    
    enhanced_list<T>( list<T>&& other, const Allocator& alloc ): list<T>(other, alloc) {} 
    
    enhanced_list<T>( std::initializer_list<T> init, const Allocator& alloc = Allocator()): list<T>( init, alloc ) {}

    template <typename Predicate>
    void each(Predicate predicate){
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        predicate(element);
      }     
    }

    template <typename Predicate>    
    uint64_t count(Predicate predicate){
      uint64_t count = 0;
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        if(predicate(element))
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
    unique_ptr<enhanced_list<T>> _filter(Predicate predicate) {
      unique_ptr<enhanced_list<T>> new_list = make_unique<enhanced_list<T>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        if(predicate(element)){
          (*new_list).push_back(*it);
        }
      }     
      return new_list;
    }

    template <typename Predicate>
    enhanced_list<T> * map(Predicate predicate){
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        *it = predicate(*it);
      }
      return this;
    }

    template<typename R, class Predicate>
    unique_ptr<enhanced_list<R>> _map(Predicate predicate) {
      unique_ptr<enhanced_list<R>> new_list = make_unique<enhanced_list<R>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        (*new_list).push_back(predicate(element));
      }
      return new_list;
    }

    template<class Predicate>
    auto _map(Predicate predicate) {
      auto new_list = make_unique<enhanced_list<decltype(predicate(declval<T>()))>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        (*new_list).push_back(predicate(element));
      }     
      return new_list;
    }

    T const& operator[](const int& index) const {
        return *next((*this).begin(), index);
    }
};
