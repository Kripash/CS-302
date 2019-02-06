#include <iostream>

using namespace std;

#include "Timer.cpp"
#include "testvector.cpp"

const int numRepetitions = 1000000;

int main(int argc, char **argv) {
    cout << endl << "Enter the number of values: ";
    int numValues;
    cin >> numValues;
    double test = numValues;

    Timer t;
    t.start();
    for (int i = 0; i < numRepetitions; ++i) {
	++test;
    }
    t.stop();
    cout << "Cost for pre-increment: " << t.getElapsedTime() << endl;

    Timer u;
    u.start();
    for (int i = 0; i < numRepetitions; ++i) {
	test++;
    }
    u.stop();
    cout << "Cost for post-increment: " << u.getElapsedTime() << endl;

    return 0;
}
