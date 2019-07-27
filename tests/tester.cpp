#ifndef TEST
#define TEST
#include<stdlib.h>


#include<iostream>

using namespace std;

class tester {

    private:

    int failed_tests = 0;
    int ok_asserts = 0;
    string current_test;

    public:

    virtual void test() = 0;

    void set_current_test(string test_case) {
        this->current_test = test_case;
    }

    void assertEqual(string expected, string actual) {
        if(expected == actual) ok_test(current_test,  (actual));
        else fail_test(current_test,  (expected),  (actual));
    }

    void assertEqual(int expected, int actual) {
        if(expected == actual) ok_test(current_test,  std::to_string(actual));
        else fail_test(current_test,  std::to_string(expected),  std::to_string(actual));
    }

    const int& getFailedTests(){
        return failed_tests;
    }
    const int& getOks(){
        return ok_asserts;
    }

    private:

    void fail_test(string test_name, string expected, string actual) {
        failed_tests++;
        cout<< "\033[1;31mTest: " << test_name << " ----> Failed. " << "Expected " << actual << " to be " << expected << "\033[0m" << endl;
    }

    void ok_test(string test_name, string result) {
        ok_asserts++;
        cout<< "\033[32mTest: " << test_name << " ----> Ok. " << "Result " << result << "\033[0m" << endl;
    }
};

#endif 