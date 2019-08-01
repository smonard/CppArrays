#include <iostream>
#include <stdlib.h>
#include "./enhanced_list_test.cpp"

using namespace std;

int main () {
    cout << "Running Tests...." << endl;

    enhanced_list_test intest;
    intest.test();

    cout << "\033[33mDone. Failed asserts: " << intest.getFailedTests()<< ". Ok Asserts: " << intest.getOks() << "\033[0m" << endl;

    return 0;
}