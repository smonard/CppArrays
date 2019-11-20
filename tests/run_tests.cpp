#include <iostream>
#include <stdlib.h>
#include "./enhanced_list_test.cpp"

using namespace std;

int main () {
    cout << "Running Tests...." << endl;

    enhanced_list_test intest;
    intest.test();

    cout << "\033[33mDone. Failed asserts: " << intest.get_failed_tests()<< ". Ok Asserts: " << intest.get_oks() << "\033[0m" << endl;

    return 0;
}