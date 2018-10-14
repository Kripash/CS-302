#include <iostream>
#include "config.h"
#include "QueueLinked.cpp"

using namespace std;



int main(){

    QueueLinked<int> valid;
    //valid.showStructure();

    valid.enqueue(1);

    valid.enqueue(2);
    valid.enqueue(3);
    valid.enqueue(4);
    valid.showStructure();

    QueueLinked<int> test(valid);
    test.showStructure();

    QueueLinked<int> over;
    //over.showStructure();
    //over = over;
    //over.showStructure();
    over = valid; 
    over.enqueue(5);
    over.showStructure();
    test = over;
    test.showStructure();


    cout << "test"<< endl;

   QueueLinked<int> * invalid = new QueueLinked<int>;
    invalid -> enqueue(1);
    invalid -> showStructure();
    delete invalid;
    valid.clear();
    valid.showStructure();   
    over.dequeue();
    over.dequeue();
    over.dequeue();
    over.clear();
    //over.dequeue();
    over.showStructure();

    return 0;
}
