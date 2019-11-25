#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template <class T>
class enhanced_vector: public vector<T> {
  typedef std::allocator<T> Allocator;
  typedef std::size_t size_type;

  public:

    // until C++17)
    // vector();

    enhanced_vector<T>() noexcept (noexcept(Allocator())) : vector<T>() {}

    //until C++17
    //explicit vector( const Allocator& alloc );

    explicit enhanced_vector<T>(const Allocator& alloc) noexcept : vector<T>( alloc ) {}

    // until C++11
    // explicit vector( size_type count,
    //                 const T& value = T(),
    //                 const Allocator& alloc = Allocator());

    enhanced_vector<T>(size_type count, const T& value, const Allocator& alloc = Allocator()) : vector<T>(count, value, alloc) {}


    // until C++14
    // explicit vector( size_type count );

    explicit enhanced_vector<T>(size_type count, const Allocator& alloc = Allocator()) : vector<T>( count, alloc ) {}

    template< class InputIt >
    enhanced_vector<T>(InputIt first, InputIt last, const Allocator& alloc = Allocator() ) : vector<T>( first, last, alloc ) {}

    enhanced_vector<T>(const vector<T>& other) : vector<T>( other ) {}

    enhanced_vector<T>(const vector<T>& other, const Allocator& alloc) : vector<T>( other, alloc ) {}

    // until C++17
    // vector( vector&& other );

    enhanced_vector<T>( vector<T>&& other ) noexcept : vector<T>( other ) {}

    enhanced_vector<T>(vector<T>&& other, const Allocator& alloc) : vector<T>( other, alloc ) {}

    enhanced_vector<T>(std::initializer_list<T> init, const Allocator& alloc = Allocator()) : vector<T>( init, alloc ) {}

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
    enhanced_vector<T> * filter(Predicate predicate) {
      for(auto it = (*this).begin(); it != (*this).end();) {
        T const& element = (*it);
        if(!predicate(element)){
          (*this).erase(it);
        } else {
          ++it;
        }
      }
      return this;
    }

    template <typename Predicate> 
    unique_ptr<enhanced_vector<T>> _filter(Predicate predicate) {
      unique_ptr<enhanced_vector<T>> new_vector = make_unique<enhanced_vector<T>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        if(predicate(element)){
          (*new_vector).push_back(*it);
        }
      }     
      return new_vector;
    }

    template <typename Predicate>
    enhanced_vector<T> * map(Predicate predicate){
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        *it = predicate(*it);
      }
      return this;
    }

    template<typename R, class Predicate>
    unique_ptr<enhanced_vector<R>> _map(Predicate predicate) {
      unique_ptr<enhanced_vector<R>> new_vector = make_unique<enhanced_vector<R>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        (*new_vector).push_back(predicate(element));
      }
      return new_vector;
    }

    template<class Predicate>
    auto _map(Predicate predicate) {
      auto new_vector = make_unique<enhanced_vector<decltype(predicate(declval<T>()))>>();
      for(auto it = (*this).begin(); it != (*this).end(); ++it) {
        T const& element = (*it);
        (*new_vector).push_back(predicate(element));
      }     
      return new_vector;
    }
};
