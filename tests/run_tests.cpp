#include <iostream>
#include <stdlib.h>
#include "./enhanced_list_test.cpp"

using namespace std;

int main () {
    cout << "Running Tests...." << endl;

    enhanced_list_test intest;
    intest.test();

    cout << "Done. Failed asserts: " << intest.getFailedTests()<< ". Ok Asserts: " << intest.getOks() << endl;

    return 0;
}