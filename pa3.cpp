#include <iostream>
#include "pa3.h"
using namespace std;

/*
 * Stack methods start
 */

//Stack constructor
Stack::Stack() {
    head = nullptr;       // variable for first node in Stack
    tail = nullptr;       //variable for last node in Stack
    size = 0;             // keeps track of size of Stack
}

//method for adding new nodes to Stack
void Stack::push(string _data) {
    node *temp = new node;      // creates a space in memeory for new Node
    temp -> data = _data;      // assigns passed in string to data section of new node
    temp -> next = nullptr;     //initializes the next link to null

    // statement triggered when adding first node, sets head and tail to only node in Stack
    if (head == nullptr) {
        head = temp;
        tail = temp;
    }

        //adds data to current tail and sets tail to next node
    else {
        tail -> next = temp;
        tail = tail -> next;
    }

    size++;
}

//returns data stored in tail then deletes tail it from the Stack
string Stack::pop() { //FIXME: crashes program when called with no nodes in the stack
    node *temp = head;
    string data = tail->data;

    for (int i = 0; i < size; i++) {
        if (temp->next == tail || head == tail) {
            delete tail;
            tail = temp;
            size--;
            return data;
        }

        temp = temp->next;
    }
}

/*
 * Stack methods end
 */

/*
 * main methods begin
 */



/*
 * main methods end
 */

int main() {
    Stack callStack;
    /*
    callStack.push("1");
    callStack.push("2");
    callStack.push("3");
    callStack.push("4");
    callStack.push("5");
    cout << callStack.pop();
    cout << callStack.pop();
    cout << callStack.pop();
    cout << callStack.pop();
    cout << callStack.pop();
    callStack.push("6");
    callStack.push("7");
    cout << callStack.pop();
    cout << callStack.pop();
    */
    return 0;
}