//
// Created by Brock on 3/29/2018.
//
#ifndef PA3_PA3_H
#define PA3_PA3_H

using namespace std;
#include "string"
#include <vector>

struct node {
    string data;
    node *next;
};

class Stack {
    private:
        node *head;
        node *tail;
        int size;

    public:
        Stack();
        void push(string _data);
        string pop();
        int getSize();
};

int depthOfNestedLoops(Stack _callStack);
//void keywordsMethod(Stack _callStack, vector <string> *syntaxErrors);
void findTokens(string code);
bool isWhiteSpace(char a);


#endif //PA3_PA3_H
