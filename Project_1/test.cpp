#include <iostream>
#include "config.h"
#include "ListLinked.cpp"

using namespace std;



int main(){

    List<int> valid;
    int data = 1;
    valid.showStructure();

    valid.insert(1);

    valid.insert(2);
    valid.insert(3);
    valid.insert(4);
    valid.showStructure();

    List<int> test(valid);
    valid.showStructure();

    List<int> over;
    over.showStructure();
    over = test;
    over.showStructure();


    cout << "test"<< endl;

    List<int> * invalid = new List<int>;
    invalid -> insert(1);
    invalid -> showStructure();
    delete invalid;
    valid.clear();
    valid.showStructure();   
    over.remove();
    over.remove();
    over.remove();
    over.remove();
    over.showStructure();


    return 0;
}


