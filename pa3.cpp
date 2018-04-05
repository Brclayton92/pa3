#include <iostream>
#include "pa3.h"
#include <fstream>
#include <vector>

using namespace std;

vector <string> tokens;
vector <string> keywords;
vector <string> identifiers;
vector <string> constants;
vector <string> operators;
vector <string> delimiters;
vector <string> syntaxErrors;

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

int Stack::getSize() {
    return size;
}

/*
 * Stack methods end
 */




/*
 * main methods begin
 */

//adds a frame to the stack for every nested loop found
/*int depthOfNestedLoops(Stack _callStack) {
    int _depthOfNestedLoop = 0;
    int _deepestNestedLoop = 0;
    string tempString;
    int endCount = 0;
    int beginCount = 0;

    while (_callStack.getSize() > 0) {
        tempString = _callStack.pop();
        if (tempString.find("END") != -1) {
            endCount++;
            _deepestNestedLoop++;
        }

        if (tempString.find("BEGIN") != -1) {
            beginCount++;
        }
        else {
            if (_depthOfNestedLoop > _deepestNestedLoop) {
                _deepestNestedLoop = _depthOfNestedLoop;
            }

            _depthOfNestedLoop = 0;
        }
    }

    if (beginCount == endCount) {
        return _deepestNestedLoop;
    }

    else {
        _deepestNestedLoop -= (abs(beginCount - endCount));
        return _deepestNestedLoop;
    }
}*/

// checks looks for tokens composed of capitol letters
/* void keywordsMethod(Stack _callStack, vector<string> *syntaxErrors) {
    string tempString;
    string syntaxString = "";
    int substringStart = -1;
    int subStringSize = 0;
    while (_callStack.getSize() > 0) {
        tempString = _callStack.pop();
        for (int i = 0; i < tempString.size(); i++) {
            if ((int) tempString.at(i) > 64){ // tests if tempstring.at(i) is within askii range of capitol letters
                if ((int) tempString.at(i) < 91){ // tests if tempstring.at(i) is within askii range of capitol letters
                    if (substringStart == -1){
                        substringStart = i;
                    }
                    subStringSize++;
                }
            }

            else {
                syntaxString = tempString.substr(substringStart, subStringSize);
                syntaxErrors->push_back(syntaxS
            }
        }
    }
}
 */

void findTokens(string code) {
    string lastWord = "";
    string currWord = "";
    for (int i = 0; i< code.size(); i++){
        if (code.at(i) == '(' || code.at(i) == ')' || code.at(i) == '+' || code.at(i) == '-' || code.at(i) == '*' || code.at(i) == '/' || code.at(i) == '='
               || code.at(i) == ',' || code.at(i) == ';' ) {
            lastWord = currWord;
            currWord = code.at(i);
            if (lastWord != "") {
                tokens.push_back(lastWord);
            }
            if (code.at(i + 1) != '+') {
                if (currWord != "") {
                    tokens.push_back(currWord);
                }
            }

            else {
                tokens.push_back("++");
                i++;
            }
            currWord = "";
            lastWord = "";
        }

        else if (isLowerCaseLetter(code.at(i))) {
            currWord += code.at(i);

        }

        else if (isWhiteSpace(code.at(i))) {
            if (currWord != "") {
                tokens.push_back(currWord);
            }
            currWord = "";
        }

        else {
            currWord += code.at(i);
        }
    }
}

bool isWhiteSpace(char a) {
    const int asciiVal = (int) a;
    if (asciiVal == 32) {
        return true;
    }

    else {
        return false;
    }
}

bool isLowerCaseLetter(char b) {
    const int asciiVal = (int) b;
    if ((asciiVal > 96) && (asciiVal < 123)){
        return true;
    }

    else {
        return false;
    }
}


/*
 * main methods end
 */

int main() {
    Stack callStack;
    string str;
    string code = "";
    vector <string> codeVector;


    /*
     * write file to tokens vector
     */

    ifstream infile("code.txt", ios::in); // test.text must be located in "C:\Users\Brock\CLionProjects\projectName\cmake-build-debug"

    if (infile.is_open()){
        while (getline(infile, str)) { // returns null when it reaches an empty line in the file
            codeVector.push_back(str + "\n"); //write file to a vector of strings
        }
        infile.close();
    }

    else {
        cout << "no input file available";
    }

    /*
     * end writing file to tokens vector
     */

    for (int i = 0; i < codeVector.size(); i++){
        code += codeVector[i];
    }

    //cout << "The depth of nested loop(s) is " << depthOfNestedLoops(callStack);

    findTokens(code);

    for (int i = 0; i < tokens.size(); i++){
        cout << tokens[i] << "\n";
    }


    return 0;
}


