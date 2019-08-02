#ifndef TEST
#define TEST
#include <stdlib.h>
#include <sstream>

#include <iostream>

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

    template<typename T>
    void assertEqual(T actual, T expected) {
        if(expected == actual) 
            ok_test(actual);
        else {
            ostringstream message;
            message << "Expected " << actual << " to be " << expected;
            fail_test(message.str());
        }
    }

    template<typename T>
    void assertEqualList(list<T>* actual, list<T>* expected) {
        size_t size_1 = (*actual).size();
        size_t size_2 = (*expected).size();
        if(size_1 == size_2) 
            verify_each_element(actual, expected);
        else {
            ostringstream message;
            message << "Expected list size: " << size_1 << " to be " << size_2;
            fail_test(message.str());
        }
    }

    template<typename T>
    void assertNotEqual(T* arg1, T* arg2) {
        if(arg1 != arg2) ok_test(arg2);
        else {
            ostringstream message;
            message << "Expected " << arg2 << " other than that value";
            fail_test(message.str());
        }
    }

    const int& getFailedTests(){
        return failed_tests;
    }
    const int& getOks(){
        return ok_asserts;
    }

    private:

    template<typename T>
    void verify_each_element(list<T>* actual, list<T>* expected) {
        for(auto it = (*actual).begin(), it_2 = (*expected).begin(); it != (*actual).end(); ++it) {
            assertEqual(*it, *it_2);
            it_2++;
        }
    }

    template<typename T>
    void fail_test(T output) {
        failed_tests++;
        cout<< "\033[1;31mTest: " << current_test << " ----> Failed. " << output << "\033[0m" << endl;
    }

    template<typename T>
    void ok_test(T result) {
        ok_asserts++;
        cout<< "\033[32mTest: " << current_test << " ----> Ok. " << "Result " << result << "\033[0m" << endl;
    }
};

#endif 