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
    }

    private:

    void count_with_closure() { 
        set_current_test("Counts given a predicate (as var)");
        enhanced_list<int> list = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        uint64_t expected = 3;
        
        bool (*predicate)(const int&) = [] (const int& number) -> bool { return number > 50; };
        uint64_t actual = list.count(predicate);

        assertEqual(expected, actual);
    }

    void count_with_lambda() {
        set_current_test("Counts given a predicate (directly)");
        enhanced_list<int> list = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        uint64_t expected = 1;
        
        uint64_t actual = list.count([&] (const int& number) -> bool { return number > 55; });

        assertEqual(expected, actual);
    }

    void each_with_closure() {
        set_current_test("Executes a code block for each element (code block as var)");
        enhanced_list<int> list = { 1, 5, 8 ,4};
        string actual;
        string expected = "1584";

        auto var = [&] (const int& number) { actual.append(to_string(number)); };
        list.each(var);

        assertEqual(expected, actual);
    }

    void each_with_lambda() {
        set_current_test("Executes a code block for each element (code block sent directly)");
        enhanced_list<int> list = { 1, 5, 4};
        string actual;
        string expected = "154";

        list.each([&] (const int& number) { actual.append(to_string(number)); });

        assertEqual(expected, actual);
    }
    
    void filter_with_closure() {
        set_current_test("Filters elements given a predicate (code block as var)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        bool (*var)(const int&) = [] (const int& number) -> bool { return number != 4; };
        int actual = (*list.filter(var)).front();

        assertEqual(expected, actual);
        assertEqual(list.size(), (size_t)1);
    }

    void filter_with_lambda() {
        set_current_test("Filters elements given a predicate (code block sent directly)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        int actual = (*list.filter([&] (const int& number) { return number != 4; })).front();

        assertEqual(expected, actual);
        assertEqual(list.size(), (size_t)1);
    }

    void new_filtered_with_closure() {
        set_current_test("Returns a new filtered list a predicate (code block as var)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        bool (*var)(const int&) = [] (const int& number) -> bool { return number != 4; };
        auto new_list = list._filter(var);
        int actual = (*new_list).front();

        assertEqual(expected, actual);
        assertNotEqual(new_list.get(), &list);
        assertEqual((*new_list).size(), (size_t)1);
    }

    void new_filtered_with_lambda() {
        set_current_test("Returns a new filtered list given a predicate (code block sent directly)");
        enhanced_list<int> list = { 4,4,4,2,4};
        int expected = 2;

        auto new_list = list._filter([&] (const int& number) -> bool { return number != 4; });
        int actual = (*new_list).front();

        assertEqual(expected, actual);
        assertNotEqual(new_list.get(), &list);
        assertEqual((*new_list).size(), (size_t)1);
    }

    void map_with_closure() {
        set_current_test("It maps elements given a predicate (code block within a variable)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<int> expected_list = { 10, 20, 20, 70, 70 };

        int (*mapping)(const int&) = [] (const int& number) -> int { return number * 10; };
        enhanced_list<int>* actual_list = list.map(mapping);

        assertEqualList(&expected_list, actual_list);
        assertEqual(actual_list, &list);
    }

    void map_with_lamdba() {
        set_current_test("It maps elements given a predicate (code block sent directly)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<int> expected_list = { 10, 20, 20, 70, 70 };

        enhanced_list<int>* actual_list = list.map([] (const int& number) -> int { return number * 10; });

        assertEqualList(&expected_list, actual_list);
        assertEqual(actual_list, &list);
    }

    void new_mapped_with_closure() {
        set_current_test("Returns a new list applying the mapping (code block within a variable)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<string> expected_list = { "odd", "even", "even", "odd", "odd" };

        string (*mapping)(const int&) = [] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; };
        unique_ptr<enhanced_list<string>> actual_list = list._map<string>(mapping);

        assertEqualList(&expected_list, actual_list.get());
        unique_ptr<enhanced_list<string>> actual_list_2 = list._map(mapping);
        assertEqualList(&expected_list, actual_list_2.get());
    }

    void new_mapped_with_lambda() {
        set_current_test("Returns a new list applying the mapping (code block sent directly)");
        enhanced_list<int> list = { 1, 2 ,2 , 7 , 7};
        enhanced_list<string> expected_list = { "odd", "even", "even", "odd", "odd" };

        unique_ptr<enhanced_list<string>> actual_list = list._map<string>([&] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; });

        assertEqualList(&expected_list, actual_list.get());
        unique_ptr<enhanced_list<string>> actual_list_2 = list._map([&] (const int& number) -> string { return number % 2 == 0? "even" : "odd"; });
        assertEqualList(&expected_list, actual_list_2.get());
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

        assertEqualList(list_2.get(), &expected_list);
    }

    void access_element_by_index() {
        set_current_test("Access element by index");
        enhanced_list<string> list = { "1", "2", "3", "4" };
        string expected_item = "3";

        const string& actual_item = list[2];

        assertEqual(actual_item, expected_item); 
    }
};