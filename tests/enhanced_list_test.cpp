#include "../src/enhanced_list.cpp"
#include "tester.cpp"

using namespace std;

class enhanced_list_test : public tester {
    public:

    void test(){
        count_with_closure();
        count_with_lambda();
        each_with_closure();
        each_with_lambda();
        filter_with_closure();
        filter_with_lambda();
        new_filtered_with_closure();
        new_filtered_with_lambda();
        map_with_closure();
        map_with_lamdba();
        new_mapped_with_closure();
        new_mapped_with_lambda();
        inmutable_elements();
        access_element_by_index();
        implements_base_constructors();
    }

    private:

    void count_with_closure() { 
        set_current_test("Counts given a predicate (as var)");
        enhanced_list<int> list = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        uint64_t expected = 3;
        
        bool (*predicate)(const int&) = [] (const int& number) -> bool { return number > 50; };
        uint64_t actual = list.count(predicate);

        assert_equal(expected, actual);
    }

    void count_with_lambda() {
        set_current_test("Counts given a predicate (directly)");
        enhanced_list<int> list = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        uint64_t expected = 1;
        
        uint64_t actual = list.count([&] (const int& number) -> bool { return number > 55; });

        assert_equal(expected, actual);
    }

    void each_with_closure() {
        set_current_test("Executes a code block for each element (code block as var)");
        enhanced_list<int> list = { 1, 5, 8 ,4};
        string actual;
        string expected = "1584";

        auto var = [&] (const int& number) { actual.append(to_string(number)); };
        list.each(var);

        assert_equal(expected, actual);
    }

    void each_with_lambda() {
        set_current_test("Executes a code block for each element (code block sent directly)");
        enhanced_list<int> list = { 1, 5, 4};
        string actual;
        string expected = "154";

        list.each([&] (const int& number) { actual.append(to_string(number)); });

        assert_equal(expected, actual);
    }
    
    void filter_with_closure() {
        set_current_test("Filters elements given a predicate (code block as var)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        bool (*var)(const int&) = [] (const int& number) -> bool { return number != 4; };
        int actual = (*list.filter(var)).front();

        assert_equal(expected, actual);
        assert_equal(list.size(), (size_t)1);
    }

    void filter_with_lambda() {
        set_current_test("Filters elements given a predicate (code block sent directly)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        int actual = (*list.filter([&] (const int& number) { return number != 4; })).front();

        assert_equal(expected, actual);
        assert_equal(list.size(), (size_t)1);
    }

    void new_filtered_with_closure() {
        set_current_test("Returns a new filtered list a predicate (code block as var)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        bool (*var)(const int&) = [] (const int& number) -> bool { return number != 4; };
        auto new_list = list._filter(var);
        int actual = (*new_list).front();

        assert_equal(expected, actual);
        assert_not_equal(new_list.get(), &list);
        assert_equal((*new_list).size(), (size_t)1);
    }

    void new_filtered_with_lambda() {
        set_current_test("Returns a new filtered list given a predicate (code block sent directly)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        auto new_list = list._filter([&] (const int& number) -> bool { return number != 4; });
        int actual = (*new_list).front();

        assert_equal(expected, actual);
        assert_not_equal(new_list.get(), &list);
        assert_equal((*new_list).size(), (size_t)1);
    }

    void map_with_closure() {
        set_current_test("It maps elements given a predicate (code block within a variable)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<int> expected_list = { 10, 20, 20, 70, 70 };

        int (*mapping)(const int&) = [] (const int& number) -> int { return number * 10; };
        enhanced_list<int>* actual_list = list.map(mapping);

        assert_equal_list(&expected_list, actual_list);
        assert_equal(actual_list, &list);
    }

    void map_with_lamdba() {
        set_current_test("It maps elements given a predicate (code block sent directly)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7 };
        enhanced_list<int> expected_list = { 10, 20, 20, 70, 70 };

        enhanced_list<int>* actual_list = list.map([] (const int& number) -> int { return number * 10; });

        assert_equal_list(&expected_list, actual_list);
        assert_equal(actual_list, &list);
    }

    void new_mapped_with_closure() {
        set_current_test("Returns a new list applying the mapping (code block within a variable)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<string> expected_list = { "odd", "even", "even", "odd", "odd" };

        string (*mapping)(const int&) = [] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; };
        unique_ptr<enhanced_list<string>> actual_list = list._map<string>(mapping);

        assert_equal_list(&expected_list, actual_list.get());
        unique_ptr<enhanced_list<string>> actual_list_2 = list._map(mapping);
        assert_equal_list(&expected_list, actual_list_2.get());
    }

    void new_mapped_with_lambda() {
        set_current_test("Returns a new list applying the mapping (code block sent directly)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<string> expected_list = { "odd", "even", "even", "odd", "odd" };

        unique_ptr<enhanced_list<string>> actual_list = list._map<string>([&] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; });

        assert_equal_list(&expected_list, actual_list.get());
        unique_ptr<enhanced_list<string>> actual_list_2 = list._map([&] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; });
        assert_equal_list(&expected_list, actual_list_2.get());
    }

    void inmutable_elements() {
        set_current_test("Inmutable elements in code block");

        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<int> expected_list = { 1, 2 ,2 , 7 , 7};

        auto list_2 = list.filter([] (int number) { number = 0; return true; })->_filter([] (int number) { number = 0; return true; });
        list_2->each([] (int number) { number = 0; });
        list_2->_map([] (int number) { number = 0; return number; });
        list_2->_map<int>([] (int number) { number = 0; return number; });
        list_2->count([] (int number) { number = 0; return true; });

        assert_equal_list(list_2.get(), &expected_list);
    }

    void access_element_by_index() {
        set_current_test("Access element by index");
        enhanced_list<string> list = { "1", "2", "3", "4" };
        string expected_item = "3";

        const string& actual_item = list[2];

        assert_equal(actual_item, expected_item); 
    }

    void implements_base_constructors() {
        set_current_test("Implements base costructors");

        empty_constr();
        count_constr();
        repetition_value_constr();
        iterators_constr();
        literal_constr();
        copy_constr();
        move_constr();
    }

    //enhanced_list<T>()
    void empty_constr() {
        enhanced_list<string> enhanced_list;
        list<string> list;

        assert_equal_list(&enhanced_list, &list);
    }

    //explicit enhanced_list<T>( size_type count, const Allocator& alloc = Allocator() )
    void count_constr() {
        enhanced_list<string> enhanced_list(1);
        list<string> list(1);

        assert_equal_list(&enhanced_list, &list);
    }

    //enhanced_list<T>( size_type count, const T& value, const Allocator& alloc = Allocator())
    void repetition_value_constr(){
        enhanced_list<string> enhanced_list(2, "word");
        list<string> list(2, "word");

        assert_equal_list(&enhanced_list, &list);
    }

    //enhanced_list<T>( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
    void iterators_constr(){
        list<string> words = {"the", "list"};
        enhanced_list<string> enhanced_list(words.begin(), words.end());
        list<string> list(words.begin(), words.end());

        assert_equal_list(&enhanced_list, &list);
    }

    //enhanced_list<T>( std::initializer_list<T> init, const Allocator& alloc = Allocator())
    void literal_constr(){
        enhanced_list<string> enhanced_list = { "1", "2" };
        list<string> list = { "1", "2" };

        assert_equal_list(&enhanced_list, &list);
    }

    void copy_constr(){
        list<string> list = { "copy" };
        enhanced_list<string> enhanced_list = { list };

        assert_equal_list(&enhanced_list, &list);
    }

    void move_constr(){
        list<string> list = { "move" };
        enhanced_list<string> expected_list = { "move" };
        enhanced_list<string> enhanced_list = std::move(list);

        assert_equal_list(&enhanced_list, &list);
    }
};
