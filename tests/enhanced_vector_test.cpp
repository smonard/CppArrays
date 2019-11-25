#include "../src/enhanced_vector.cpp"
#include "tester.cpp"

using namespace std;

class enhanced_vector_test : public tester {
    public:

    void test() override {
        cout<< "Vector tests" << endl;
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
        enhanced_vector<int> vector = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        uint64_t expected = 3;
        
        bool (*predicate)(const int&) = [] (const int& number) -> bool { return number > 50; };
        uint64_t actual = vector.count(predicate);

        assert_equal(expected, actual);
    }

    void count_with_lambda() {
        set_current_test("Counts given a predicate (directly)");
        enhanced_vector<int> vector = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        uint64_t expected = 1;
        
        uint64_t actual = vector.count([&] (const int& number) -> bool { return number > 55; });

        assert_equal(expected, actual);
    }

    void each_with_closure() {
        set_current_test("Executes a code block for each element (code block as var)");
        enhanced_vector<int> vector = { 1, 5, 8 ,4};
        string actual;
        string expected = "1584";

        auto var = [&] (const int& number) { actual.append(to_string(number)); };
        vector.each(var);

        assert_equal(expected, actual);
    }

    void each_with_lambda() {
        set_current_test("Executes a code block for each element (code block sent directly)");
        enhanced_vector<int> vector = { 1, 5, 4};
        string actual;
        string expected = "154";

        vector.each([&] (const int& number) { actual.append(to_string(number)); });

        assert_equal(expected, actual);
    }
    
    void filter_with_closure() {
        set_current_test("Filters elements given a predicate (code block as var)");
        enhanced_vector<int> vector = { 4,4,4,2,4};
        int expected = 2;

        bool (*var)(const int&) = [] (const int& number) -> bool { return number != 4; };
        int actual = (*vector.filter(var)).front();

        assert_equal(expected, actual);
        assert_equal(vector.size(), (size_t)1);
    }

    void filter_with_lambda() {
        set_current_test("Filters elements given a predicate (code block sent directly)");
        enhanced_vector<int> vector = { 4,4,4,2,4};
        int expected = 2;

        int actual = (*vector.filter([&] (const int& number) { return number != 4; })).front();

        assert_equal(expected, actual);
        assert_equal(vector.size(), (size_t)1);
    }

    void new_filtered_with_closure() {
        set_current_test("Returns a new filtered vector a predicate (code block as var)");
        enhanced_vector<int> vector = { 4,4,4,2,4};
        int expected = 2;

        bool (*var)(const int&) = [] (const int& number) -> bool { return number != 4; };
        auto new_vector = vector._filter(var);
        int actual = (*new_vector).front();

        assert_equal(expected, actual);
        assert_not_equal(new_vector.get(), &vector);
        assert_equal((*new_vector).size(), (size_t)1);
    }

    void new_filtered_with_lambda() {
        set_current_test("Returns a new filtered vector given a predicate (code block sent directly)");
        enhanced_vector<int> vector = { 4,4,4,2,4};
        int expected = 2;

        auto new_vector = vector._filter([&] (const int& number) -> bool { return number != 4; });
        int actual = (*new_vector).front();

        assert_equal(expected, actual);
        assert_not_equal(new_vector.get(), &vector);
        assert_equal((*new_vector).size(), (size_t)1);
    }

    void map_with_closure() {
        set_current_test("It maps elements given a predicate (code block within a variable)");
        enhanced_vector<int> vector = { 1, 2 ,2 , 7 , 7};
        enhanced_vector<int> expected_vector = { 10, 20, 20, 70, 70 };

        int (*mapping)(const int&) = [] (const int& number) -> int { return number * 10; };
        enhanced_vector<int>* actual_vector = vector.map(mapping);

        assert_equal_vector(&expected_vector, actual_vector);
        assert_equal(actual_vector, &vector);
    }

    void map_with_lamdba() {
        set_current_test("It maps elements given a predicate (code block sent directly)");
        enhanced_vector<int> vector = { 1, 2 ,2 , 7 , 7 };
        enhanced_vector<int> expected_vector = { 10, 20, 20, 70, 70 };

        enhanced_vector<int>* actual_vector = vector.map([] (const int& number) -> int { return number * 10; });

        assert_equal_vector(&expected_vector, actual_vector);
        assert_equal(actual_vector, &vector);
    }

    void new_mapped_with_closure() {
        set_current_test("Returns a new vector applying the mapping (code block within a variable)");
        enhanced_vector<int> vector = { 1, 2 ,2 , 7 , 7};
        enhanced_vector<string> expected_vector = { "odd", "even", "even", "odd", "odd" };

        string (*mapping)(const int&) = [] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; };
        unique_ptr<enhanced_vector<string>> actual_vector = vector._map<string>(mapping);

        assert_equal_vector(&expected_vector, actual_vector.get());
        unique_ptr<enhanced_vector<string>> actual_vector_2 = vector._map(mapping);
        assert_equal_vector(&expected_vector, actual_vector_2.get());
    }

    void new_mapped_with_lambda() {
        set_current_test("Returns a new vector applying the mapping (code block sent directly)");
        enhanced_vector<int> vector = { 1, 2 ,2 , 7 , 7};
        enhanced_vector<string> expected_vector = { "odd", "even", "even", "odd", "odd" };

        unique_ptr<enhanced_vector<string>> actual_vector = vector._map<string>([&] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; });

        assert_equal_vector(&expected_vector, actual_vector.get());
        unique_ptr<enhanced_vector<string>> actual_vector_2 = vector._map([&] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; });
        assert_equal_vector(&expected_vector, actual_vector_2.get());
    }

    void inmutable_elements() {
        set_current_test("Inmutable elements in code block");

        enhanced_vector<int> vector = { 1, 2 ,2 , 7 , 7};
        enhanced_vector<int> expected_vector = { 1, 2 ,2 , 7 , 7};

        auto vector_2 = vector.filter([] (int number) { number = 0; return true; })->_filter([] (int number) { number = 0; return true; });
        vector_2->each([] (int number) { number = 0; });
        vector_2->_map([] (int number) { number = 0; return number; });
        vector_2->_map<int>([] (int number) { number = 0; return number; });
        vector_2->count([] (int number) { number = 0; return true; });

        assert_equal_vector(vector_2.get(), &expected_vector);
    }

    void access_element_by_index() {
        set_current_test("Access element by index");
        enhanced_vector<string> vector = { "1", "2", "3", "4" };
        string expected_item = "3";

        const string& actual_item = vector[2];

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

    //enhanced_vector<T>()
    void empty_constr() {
        enhanced_vector<string> enhanced_vector;
        vector<string> vector;

        assert_equal_vector(&enhanced_vector, &vector);
    }

    //explicit enhanced_vector<T>( size_type count, const Allocator& alloc = Allocator() )
    void count_constr() {
        enhanced_vector<string> enhanced_vector(1);
        vector<string> vector(1);

        assert_equal_vector(&enhanced_vector, &vector);
    }

    //enhanced_vector<T>( size_type count, const T& value, const Allocator& alloc = Allocator())
    void repetition_value_constr(){
        enhanced_vector<string> enhanced_vector(2, "word");
        vector<string> vector(2, "word");

        assert_equal_vector(&enhanced_vector, &vector);
    }

    //enhanced_vector<T>( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
    void iterators_constr(){
        vector<string> words = {"the", "vector"};
        enhanced_vector<string> enhanced_vector(words.begin(), words.end());
        vector<string> vector(words.begin(), words.end());

        assert_equal_vector(&enhanced_vector, &vector);
    }

    //enhanced_vector<T>( std::initializer_vector<T> init, const Allocator& alloc = Allocator())
    void literal_constr(){
        enhanced_vector<string> enhanced_vector = { "1", "2" };
        vector<string> vector = { "1", "2" };

        assert_equal_vector(&enhanced_vector, &vector);
    }

    void copy_constr(){
        vector<string> vector = { "copy" };
        enhanced_vector<string> enhanced_vector = { vector };

        assert_equal_vector(&enhanced_vector, &vector);
    }

    void move_constr(){
        vector<string> vector = { "move" };
        enhanced_vector<string> expected_vector = { "move" };
        enhanced_vector<string> enhanced_vector = std::move(vector);

        assert_equal_vector(&enhanced_vector, &vector);
    }
};
