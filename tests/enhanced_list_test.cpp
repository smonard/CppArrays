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
    }

    private:

    void count_with_closure() { 
        set_current_test("Counts given a predicate (as var)");
        enhanced_list<int> list = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        
        bool (*predicate)(const int&) = [] (const int& number) -> bool { return number > 50; };
        uint64_t actual = list.count(predicate);
        uint64_t expected = 3;

        assertEqual(expected, actual);
    }

    void count_with_lambda() {
        set_current_test("Counts given a predicate (directly)");
        enhanced_list<int> list = { 21, 50, 8, 49, 8, 8, 5, 55, 21, 55, 985};
        
        uint64_t actual = list.count([&] (const int& number) -> bool { return number > 55; });
        uint64_t expected = 1;

        assertEqual(expected, actual);
    }

    void each_with_closure() {
        set_current_test("Executes a code block for each element (code block as var)");
        enhanced_list<int> list = { 1, 5, 8 ,4};
        string actual;

        auto var = [&] (const int& number) { actual.append(to_string(number)); };
        list.each(var);
        string expected = "1584";

        assertEqual(expected, actual);
    }

    void each_with_lambda() {
        set_current_test("Executes a code block for each element (code block sent directly)");
        enhanced_list<int> list = { 1, 5, 4};
        string actual;

        list.each([&] (const int& number) { actual.append(to_string(number)); });
        string expected = "154";

        assertEqual(expected, actual);
    }
};