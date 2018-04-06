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
        int depthOfNestedLoop;

    public:
        Stack();
        void push(string _data);
        string pop();
        int getSize();
};

void findTokens(string code);
bool isWhiteSpace(char a);
bool isLowerCaseLetter(char b);
int compiler(int i);
bool isOperator(string str);
bool isKeyword(string str);
bool isDelimiter(char d);
int findDepthOfNestedLoops();

#endif //PA3_PA3_H
